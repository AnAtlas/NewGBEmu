//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_MEMORY_HPP
#define GBEMU_MEMORY_HPP
#include "../Utilities/Types.hpp"
#include "../Cartridges/Cartridge.hpp"
#include "../Utilities/AddressRange.hpp"

class Memory {
private:
  union{
    struct {
      byte cart1[0x4000];
      byte cart2[0x4000];
      byte vRam[0x2000]; //0x8000
      byte sRam[0x2000]; //0xA000
      byte wram[0x2000];
      byte echo[0x1E00];
      byte oam[0xA0];	//0xFE00
      byte blank[0x60];
      byte ioPorts[0x4C]; //0xFF00
      byte blank2[0x34];
      byte hRam[0x80];
      byte ieRegister[0x01];
    };
    byte m_memory[0xFFFF];
  };
  std::shared_ptr<Cartridge> m_cartridge;

  AddressRange m_romRange;
  AddressRange m_ramRange;

  bool m_inBios;
  byte m_inputRow1;
  byte m_inputRow2;

  void copy(word destination, word source, word length);
  bool addressOnCartridge(word address);

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
  byte readByte(word address);
  void writeByte(word address, byte value);
  void linkCartridge(std::shared_ptr<Cartridge> cartridge);
};
#endif //GBEMU_MEMORY_HPP
