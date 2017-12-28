//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_CARTMBC5_HPP
#define GBEMU_CARTMBC5_HPP

#include "Cartridge.hpp"
#include "../Utilities/AddressRange.hpp"
#include "RamModule.hpp"

class CartMBC5: public Cartridge
{
private:
  enum MBC5Address{
    RAM_BANK = 0xA000,
    RAM_BANK_END = 0xBFFF,
    RAM_ENABLE = 0x0000,
    RAM_ENABLE_END = 0x1FFF,
    ROM_BANK_NUMBER_LOW = 0x2000,
    ROM_BANK_NUMBER_LOW_END = 0x2FFF,
    ROM_BANK_NUMBER_HIGH_BIT = 0x3000,
    ROM_BANK_NUMBER_HIGH_BIT_END = 0x3FFF,
    RAM_BANK_NUMBER = 0x4000,
    RAM_BANK_NUMBER_END = 0x5FFF
  };
  byte m_romBankNumberLow8;
  byte m_romBankNumberHigh1;
  byte m_ramBankNumber;
  bool m_hasBattery;
  bool m_hasRumble;

  RamModule m_ramModule;

  AddressRange m_ramRange;
  AddressRange m_ramEnableRange;
  AddressRange m_romBankNumberLowRange;
  AddressRange m_romBankNumberHighBitRange;
  AddressRange m_ramBankNumberRange;

  void changeRomBank();
  void changeRamBank();
public:
  explicit CartMBC5(CartType cartType, std::string romPath, RamModule::RamSize ramSize);

  bool loadCartridge() override;
  byte readByte(word address) const override;
  void writeByte(word address, byte value) override;
};

#endif //GBEMU_CARTMBC5_HPP
