//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_CARTMBC1_HPP
#define GBEMU_CARTMBC1_HPP

#include "Cartridge.hpp"
#include "../Utilities/AddressRange.hpp"
#include "RamModule.hpp"

class CartMBC1: public Cartridge
{
private:
  enum MBC1Address{
    RAM_BANK = 0xA000,
    RAM_BANK_END = 0xBFFF,
    RAM_ENABLE = 0x0000,
    RAM_ENABLE_END = 0x1FFF,
    ROM_BANK_NUMBER = 0x2000,
    ROM_BANK_NUMBER_END = 0x3FFF,
    RAM_BANK_NUMBER = 0x4000,
    RAM_BANK_NUMBER_END = 0x5FFF,
    BANKING_MODE = 0x6000,
    BANKING_MODE_END = 0x7FFF
  };
  byte m_romBankNumber;
  byte m_ramBankNumber;
  bool m_hasBattery;
  RamModule m_ramModule;

  BankingMode m_bankingMode;

  AddressRange m_ramRange;
  AddressRange m_ramEnableRange;
  AddressRange m_romBankNumberRange;
  AddressRange m_ramBankNumberRange;
  AddressRange m_bankingModeRange;

  void changeBanks();
public:
  explicit CartMBC1(CartType cartType, std::string romPath, RamModule::RamSize ramSize);

  bool loadCartridge() override;
  void shutDown() override;
  byte readByte(word address) const override;
  void writeByte(word address, byte value) override;
};

#endif //GBEMU_CARTMBC1_HPP
