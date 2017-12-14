//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_CARTMBC1_HPP
#define GBEMU_CARTMBC1_HPP

#include "Cartridge.hpp"
#include "../Utilities/AddressRange.hpp"

class CartMBC1: public Cartridge
{
private:
  enum MBC1Address{
    RAM_BANK = 0xA000,
    RAM_BANK_END = 0xBFFF,
    RAM_ENABLE = 0x0000,
    RAM_ENABLE_END = 0x1FFF,
    ROM_BANK_NUMBER = 0x2000,
    ROM_BANK_NUMBER_END = 0x3FFF
  };
  byte m_ramBank[0x2000];
  bool m_ramEnabled;
  BankingMode m_bankingMode;

  AddressRange m_ramRange;
  AddressRange m_ramEnableRange;
  AddressRange m_romBankNumberRange;
  AddressRange m_ramOrUpperRomBankNumber;
  AddressRange m_bankingModeSelect;

  bool loadRamBankX(byte ramBankIndex);
public:
  explicit CartMBC1(std::string romPath);

  bool loadCartridge() override;
  byte readByte(word address) override;
  bool writeByte(word address, byte value) override;
};

#endif //GBEMU_CARTMBC1_HPP
