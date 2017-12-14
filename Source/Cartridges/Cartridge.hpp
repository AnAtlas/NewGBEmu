//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_ICARTRIDGE_HPP
#define GBEMU_ICARTRIDGE_HPP
#include <string>
#include <fstream>
#include <iostream>

#include "../Utilities/Types.hpp"

class Cartridge
{
protected:
  enum CartAddress{
    ROM_BANK0 = 0x0000,
    RAM_BANK0 = 0xA000,
    ROM_NAME = 0x134
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
    byte m_rom[0xFFFF];
  };

  std::string m_romPath;

  //Load the first 0x4000 bytes of the rom into romBank0
  bool loadRomBank0();

  //Load the Xth 0x4000 bytes of the rom  into romBankX
  bool loadRomBankX(byte romBankIndex);

public:
  Cartridge(std::string& romPath): m_romPath(romPath){}

  const std::string getRomName() const;

  //These functions are overloaded by the appropriate cart representation
  virtual bool loadCartridge() = 0;
  virtual byte readByte(word address) = 0;
  virtual bool writeByte(word address, byte value) = 0;
};
#endif //GBEMU_ICARTRIDGE_HPP
