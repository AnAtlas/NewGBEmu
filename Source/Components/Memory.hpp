//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_MEMORY_HPP
#define GBEMU_MEMORY_HPP
#include "../Utilities/Types.hpp"
#include "../Cartridges/Cartridge.hpp"
#include "../Utilities/AddressRange.hpp"
#include "CpuMemoryInterface.hpp"
#include "GpuMemoryInterface.hpp"
#include "TimerMemoryInterface.hpp"

enum IntFlags{
  VBLANK = 1,
  LCD_STAT = 1 << 1,
  TIMER = 1 << 2,
  SERIAL = 1 << 3,
  JOYPAD = 1 << 4
};

class Memory : public CpuMemoryInterface, GpuMemoryInterface, TimerMemoryInterface
{
private:
  union{
    struct {
      byte m_cart1[0x4000];
      byte m_cart2[0x4000];
      byte m_vRam[0x2000]; //0x8000
      byte m_sRam[0x2000]; //0xA000
      byte m_wram[0x2000];
      byte m_echo[0x1E00];
      byte m_oam[0xA0];	//0xFE00
      byte m_blank[0x60];
      byte m_ioPorts[0x4C]; //0xFF00
      byte m_blank2[0x34];
      byte m_hRam[0x80];
      byte m_ieRegister[0x01];
    };
    byte m_memory[0xFFFF];
  };
  std::shared_ptr<Cartridge> m_cartridge;

  AddressRange m_romRange;
  AddressRange m_ramRange;
  AddressRange m_wRamRange;
  AddressRange m_echoRange;

  bool m_inBios;
  byte m_inputRow1;
  byte m_inputRow2;

  bool addressOnCartridge(word address) const;

  enum Address {
    IntVBlank = 0x40,
    IntLCDState = 0x48,
    IntTimer = 0x50,
    IntJoypad = 0x60,
    Cart1 = 0x0000,
    Cart2 = 0x4000,
    Vram = 0x8000,
    Sram = 0xA000,
    Wram = 0xC000,
    Echo = 0xE000,
    Oam = 0xFE00,
    Blank = 0xFEA0,
    IoPorts = 0xFF00,
    P1 = 0xFF00,			//P1 Register for reading joypad info
    DivReg = 0xFF04,		//DIV
    TimerCounter = 0xFF05,	//TIMA
    TimerModulo = 0xFF06,	//TMA
    TimerControl = 0xFF07,	//TAC
    IntFlags = 0xFF0F,
    LcdControl = 0xFF40,
    LcdStatus = 0xFF41,
    ScrollY = 0xFF42,
    ScrollX = 0xFF43,
    LineY = 0xFF44,
    LYC = 0xFF45,
    DMA = 0xFF46,
    BackgroundPalette = 0xFF47,
    ObjectPalette0 = 0xFF48,
    ObjectPalette1 = 0xFF49,
    ExitBios = 0xFF50,
    WindowY = 0xFF4A,
    WindowX = 0xFF4B,
    Blank2 = 0xFF4C,
    Hram = 0xFF80,
    IeRegister = 0xFFFF
  };

public:
  explicit Memory(bool runBios);
  byte readByte(word address) const override;
  void writeByte(word address, byte value) override;
  void writeShort(word address, word value) override;
  word readShort(word address) const override;
  void linkCartridge(std::shared_ptr<Cartridge> cartridge);
  void requestInterrupt(byte bit) override;

  //Cpu Functions
  byte getIntFlags() const override;
  byte getIntsEnabled() const override;
  void resetIntFlag(byte bitIndex) override;
  //Gpu functions
  byte readLcdStatus() const override;
  byte readLcdControl() const override;
  byte readLineY() const override;
  byte readLYC() const override;
  byte readBackgroundPalette() const override;
  byte readObjectPalette0() const override;
  byte readObjectPalette1() const override;
  byte readOam(word address) const override;
  byte readVram(word address) const override;
  byte readScrollX() const override;
  byte readScrollY() const override;
  byte readWindowX() const override;
  byte readWindowY() const override;
  void writeLcdStatus(byte value) override;
  void writeLineY(byte value) override;
  //Timer functions
  void incDivRegister() override;
  void writeTimerCounter(byte value) override;
  byte readTimerCounter() override;
  byte readTimerModulo() override;
  byte readTimerControl() override;
};
#endif //GBEMU_MEMORY_HPP
