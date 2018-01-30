//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_MEMORY_HPP
#define GBEMU_MEMORY_HPP
#include "../Utilities/Types.hpp"
#include "../Cartridges/Cartridge.hpp"
#include "../Utilities/AddressRange.hpp"
#include "MemoryInterfaces/CpuMemoryInterface.hpp"
#include "MemoryInterfaces/GpuMemoryInterface.hpp"
#include "MemoryInterfaces/TimerMemoryInterface.hpp"
#include "MemoryInterfaces/InputMemoryInterface.hpp"
#include "MemoryInterfaces/AudioMemoryInterface.hpp"
#include "Input.hpp"
#include "Apu.hpp"

namespace Address{
  enum {
    IntVBlank = 0x40,
    IntLCDState = 0x48,
    IntTimer = 0x50,
    IntSerial = 0x58,
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
    NR10 = 0xFF10,
    NR11 = 0xFF11,
    NR12 = 0xFF12,
    NR13 = 0xFF13,
    NR14 = 0xFF14,
    NR20 = 0xFF15,
    NR21 = 0xFF16,
    NR22 = 0xFF17,
    NR23 = 0xFF18,
    NR24 = 0xFF19,
    NR30 = 0xFF1A,
    NR31 = 0xFF1B,
    NR32 = 0xFF1C,
    NR33 = 0xFF1D,
    NR34 = 0xFF1E,
    NR40 = 0xFF1F,
    NR41 = 0xFF20,
    NR42 = 0xFF21,
    NR43 = 0xFF22,
    NR44 = 0xFF23,
    NR50 = 0xFF24,
    NR51 = 0xFF25,
    NR52 = 0xFF26,
    WavePattern = 0xFF30,
    WavePatternEnd = 0xFF3F,
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
}

namespace IntFlags{
  enum{
    VBLANK = 0b1,
    LCD_STAT = 0b10,
    TIMER = 0b100,
    SERIAL = 0b1000,
    JOYPAD = 0b10000
  };
}

class Memory : public CpuMemoryInterface, GpuMemoryInterface, TimerMemoryInterface, InputMemoryInterface,
  AudioMemoryInterface
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
  Input m_input;
  MemoryAudioInterface* m_apu;

  AddressRange m_romRange;
  AddressRange m_ramRange;
  AddressRange m_wRamRange;
  AddressRange m_echoRange;

  word m_divRegister;
  bool m_inBios;

  bool addressOnCartridge(word address) const;
  void initializeRegisters(bool runBios);
public:
  explicit Memory(bool runBios);
  byte readByte(word address) const override;
  void writeByte(word address, byte value) override;
  void writeShort(word address, word value) override;
  word readShort(word address) const override;
  void linkCartridge(std::shared_ptr<Cartridge> cartridge);
  void linkApu(Apu* apu);
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
  void requestVBlankInterrupt() override;
  void requestLcdStatInterrupt() override;
  //Timer functions
  void incDivRegister(byte ticks) override;
  byte incTimerCounter() override;
  void writeTimerCounter(byte value) override;
  byte readTimerCounter() override;
  byte readTimerModulo() override;
  byte readTimerControl() override;
  void requestTimerInterrupt() override;
  //Input functions
  byte readP1() override;
  void writeP1Inputs(byte value) override;
  void requestInputInterrupt() override;
  //Audio functions
  byte readNR10() const override;
  byte readNR11() const override;
  byte readNR12() const override;
  byte readNR13() const override;
  byte readNR14() const override;
  byte readNR21() const override;
  byte readNR22() const override;
  byte readNR23() const override;
  byte readNR24() const override;
  byte readNR31() const override;
  byte readNR32() const override;
  byte readNR33() const override;
  byte readNR34() const override;
  byte readNR41() const override;
  byte readNR42() const override;
  byte readNR43() const override;
  byte readNR44() const override;
  byte readNR50() const override;
  byte readNR51() const override;
  byte readNR52() const override;

  byte readWaveRAM(int index) const override;
  void writeNR52(byte value) override;
};
#endif //GBEMU_MEMORY_HPP
