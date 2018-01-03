//
// Created by derdro on 12/14/17.
//

#include "CartMBC5.hpp"

CartMBC5::CartMBC5(CartType cartType, std::string romPath, RamModule::RamSize ramSize)
  :Cartridge(romPath), m_ramModule(ramSize),
   m_ramEnableRange(MBC5Address::RAM_ENABLE, MBC5Address::RAM_ENABLE_END),
   m_romBankNumberLowRange(MBC5Address::ROM_BANK_NUMBER_LOW, MBC5Address::ROM_BANK_NUMBER_LOW_END),
   m_romBankNumberHighBitRange(MBC5Address::ROM_BANK_NUMBER_HIGH_BIT, MBC5Address::ROM_BANK_NUMBER_HIGH_BIT_END),
   m_ramBankNumberRange(MBC5Address::RAM_BANK_NUMBER, MBC5Address::RAM_BANK_NUMBER_END),
   m_ramRange(MBC5Address::RAM_BANK,MBC5Address::RAM_BANK_END),
   m_romBankNumberLow8(0), m_romBankNumberHigh1(0), m_ramBankNumber(0)
{
  if (cartType == CartType::MBC5_RAM_BATTERY)
    m_hasBattery= true;
}

bool CartMBC5::loadCartridge() {
  bool retVal = loadRomBank0() && loadRomBankX(1);
  if (m_hasBattery)
    m_ramModule.load(getRomName());
  return retVal;
}

void CartMBC5::shutDown() {
  if (m_hasBattery){
    m_ramModule.save(getRomName());
  }
}

void CartMBC5::writeByte(word address, byte value) {
  if (m_ramEnableRange.contains(address)){
    m_ramModule.writeEnableAddress(value);
  }
  else if (m_romBankNumberLowRange.contains(address)){
    m_romBankNumberLow8 = value;
    changeRomBank();
  }
  else if (m_romBankNumberHighBitRange.contains(address)){
    m_romBankNumberHigh1 = value & (byte)0b1;
    changeRomBank();
  }
  else if (m_ramBankNumberRange.contains(address)){
    m_ramBankNumber = (byte)(value & 0b111);
    changeRamBank();
  }
  else if (m_ramRange.contains(address)){
    m_ramModule.writeByte(address, value);
  }
}

byte CartMBC5::readByte(word address) const {
  if (m_romRange.contains(address)){
    return m_rom[address];
  }
  else if (m_ramRange.contains(address)){
    return m_ramModule.readByte(address);
  }

  return 0xFF;
}

void CartMBC5::changeRomBank() {
  word bank = m_romBankNumberLow8 | ((m_romBankNumberHigh1 & (byte)0x01) << 8);
  loadRomBankX(bank);
}

void CartMBC5::changeRamBank() {
  m_ramModule.setRamBank(m_ramBankNumber);
}