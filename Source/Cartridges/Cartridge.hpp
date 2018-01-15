//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_ICARTRIDGE_HPP
#define GBEMU_ICARTRIDGE_HPP
#include <string>
#include <fstream>
#include <iostream>
#include <memory>

#include "../Utilities/Types.hpp"
#include "../Utilities/AddressRange.hpp"

class Cartridge
{
protected:
  enum CartType{
    ROM_ONLY = 0,
    MBC1 = 1,
    MBC1_RAM = 2,
    MBC1_RAM_BATTERY = 3,
    MBC2 = 5,
    MBC2_BATTERY = 6,
    ROM_RAM = 8,
    ROM_RAM_BATTERY = 9,
    MBC3_TIMER_BATTERY = 0xF,
    MBC3_TIMER_RAM_BATTERY = 0x10,
    MBC3 = 0x11,
    MBC3_RAM = 0x12,
    MBC3_RAM_BATTERY = 0x13,
    MBC5 = 0x19,
    MBC5_RAM = 0x1A,
    MBC5_RAM_BATTERY = 0x1B,
    MBC5_RUMBLE = 0x1C,
    MBC5_RUMBLE_RAM = 0x1D,
    MBC5_RUMBLE_RAM_BATTERY = 0x1E
  };

  //Each ROM Bank is 16 KB between Bank0 and BankX
  enum RomSize{
    KB_32 = 0, // 2 Bank
    KB_64 = 1, // 4 Banks
    KB_128 = 2,// 8 Bank
    KB_256 = 3,// 16 Banks
    KB_512 = 4,// 32 Banks
    MB_1 = 5,  // 64 Banks
    MB_2 = 6,  //128 Banks
    MB_4 = 7,  //256 Banks
    MB_8 = 8,  //512 Banks
    MB_1_1 = 0x52, // 72 Banks
    MB_1_2 = 0x53, // 80 Banks
    MB_1_5 = 0x54 //  96 Banks
  };

  enum BankingMode{
    ROM_BANKING_MODE = 0,
    RAM_BANKING_MODE = 1
  };

  union {
    struct{
      byte m_romBank0[0x4000];
      byte m_romBankX[0x4000];
    };
    byte m_rom[0x8000];
  };

  std::string m_romPath;
  AddressRange m_romRange;
  word m_maxRamBank;
  word m_maxRomBank;
  //Load the first 0x4000 bytes of the rom into romBank0
  bool loadRomBank0();

  //Load the Xth 0x4000 bytes of the rom  into romBankX
  bool loadRomBankX(word romBankIndex);

public:
  Cartridge(std::string& romPath);

  const std::string getRomName() const;

  //These functions are overloaded by the appropriate cart representation
  virtual bool loadCartridge() = 0;
  virtual void shutDown() = 0;
  virtual byte readByte(word address) const = 0;
  virtual void writeByte(word address, byte value) = 0;

  enum CartAddress{
    ROM_BANK0 = 0x0000,
    ROM_BANK0_END = 0x3FFF,
    ROM_BANKX = 0x4000,
    ROM_BANKX_END = 0x7FFF,
    RAM_BANK = 0xA000,
    RAM_BANK_END = 0xBFFF,
    ROM_NAME = 0x134,
    CART_TYPE = 0x147,
    ROM_SIZE = 0x148,
    RAM_SIZE = 0x149
  };

  friend class CartridgeFactory;
};

typedef std::shared_ptr<Cartridge> CartridgePtr;
#endif //GBEMU_ICARTRIDGE_HPP
