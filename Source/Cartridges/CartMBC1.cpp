//
// Created by derdro on 12/14/17.
//

#include "CartMBC1.hpp"

CartMBC1::CartMBC1(CartType cartType, std::string romPath, RamModule::RamSize ramSize)
  :Cartridge(romPath), m_ramModule(ramSize),
   m_bankingMode(BankingMode::ROM_BANKING_MODE),
   m_ramEnableRange(MBC1Address::RAM_ENABLE, MBC1Address::RAM_ENABLE_END),
   m_romBankNumberRange(MBC1Address::ROM_BANK_NUMBER, MBC1Address::ROM_BANK_NUMBER_END),
   m_ramBankNumberRange(MBC1Address::RAM_BANK_NUMBER, MBC1Address::RAM_BANK_NUMBER_END),
   m_bankingModeRange(MBC1Address::BANKING_MODE, MBC1Address::BANKING_MODE_END),
   m_ramRange(MBC1Address::RAM_BANK,MBC1Address::RAM_BANK_END),
   m_romBankNumber(1), m_ramBankNumber(0)
{
  if (cartType == CartType::MBC1_RAM_BATTERY)
    m_hasBattery= true;
}

bool CartMBC1::loadCartridge() {
  bool retVal = loadRomBank0() && loadRomBankX(1);
  if (m_hasBattery)
    m_ramModule.load(getRomName());
  return retVal;
}

void CartMBC1::shutDown() {
  if (m_hasBattery)
    m_ramModule.save(getRomName());
}

void CartMBC1::writeByte(word address, byte value) {
  if (m_ramEnableRange.contains(address)){
    m_ramModule.writeEnableAddress(value);
  }
  else if (m_romBankNumberRange.contains(address)){
    m_romBankNumber = (byte)(value & 0b11111);
    if (!m_romBankNumber)
      m_romBankNumber = 1;
    changeBanks();
  }
  else if (m_ramBankNumberRange.contains(address)){
    m_ramBankNumber = (byte)(value & 0b11);

    changeBanks();
  }
  else if (m_bankingModeRange.contains(address)){
    if (value)
      m_bankingMode = BankingMode::RAM_BANKING_MODE;
    else
      m_bankingMode = BankingMode::ROM_BANKING_MODE;
    changeBanks();
  }
  else if (m_ramRange.contains(address)){
    m_ramModule.writeByte(address, value);
  }
}

byte CartMBC1::readByte(word address) const {
  if (m_romRange.contains(address)){
    return m_rom[address];
  }
  else if (m_ramRange.contains(address)){
    return m_ramModule.readByte(address);
  }

  return 0xFF;
}

void CartMBC1::changeBanks() {
  if (m_bankingMode == BankingMode::ROM_BANKING_MODE){
    m_ramModule.setRamBank(0);
    loadRomBankX(m_romBankNumber | (m_ramBankNumber << 5));
  }
  else{
    m_ramModule.setRamBank(m_ramBankNumber);
    loadRomBankX(m_romBankNumber);
  }
}