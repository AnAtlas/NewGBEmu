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
  enum CartAddress{
    ROM_BANK0 = 0x0000,
    ROM_BANK0_END = 0x3FFF,
    ROM_BANKX = 0x4000,
    ROM_BANKX_END = 0x7FFF,
    RAM_BANK0 = 0xA000,
    ROM_NAME = 0x134,
    CART_TYPE = 0x147,
    ROM_SIZE = 0x148,
    RAM_SIZE = 0x149
  };

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
    MBC3_RAM_BATTERY = 0x13
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
  //Load the first 0x4000 bytes of the rom into romBank0
  bool loadRomBank0();

  //Load the Xth 0x4000 bytes of the rom  into romBankX
  bool loadRomBankX(byte romBankIndex);

public:
  Cartridge(std::string& romPath);

  const std::string getRomName() const;

  //These functions are overloaded by the appropriate cart representation
  virtual bool loadCartridge() = 0;
  virtual byte readByte(word address) const = 0;
  virtual void writeByte(word address, byte value) = 0;

  friend class CartridgeFactory;
};

typedef std::shared_ptr<Cartridge> CartridgePtr;
#endif //GBEMU_ICARTRIDGE_HPP
