//
// Created by derdro on 12/15/17.
//

#include "CartMBC3.hpp"

CartMBC3::CartMBC3(CartType cartType, std::string romPath, RamModule::RamSize ramSize)
  :Cartridge(romPath), m_hasBattery(false), m_ramModule(ramSize), m_rtcModule(), m_ramBankOrTimerNumber(0),
   m_ramTimerEnableRange(MBC3Address::RAM_TIMER_ENABLE, MBC3Address::RAM_TIMER_ENABLE_END),
   m_romBankNumberRange(MBC3Address::ROM_BANK_NUMBER, MBC3Address::ROM_BANK_NUMBER_END),
   m_ramBankNumberRange(MBC3Address::RAM_BANK_NUMBER, MBC3Address::RAM_BANK_NUMBER_END),
   m_ramRange(MBC3Address::RAM_BANK,MBC3Address::RAM_BANK_END),
   m_latchClockRange(MBC3Address::LATCH_CLOCK, MBC3Address::LATCH_CLOCK_END)
{
  if (cartType == CartType::MBC3_RAM_BATTERY || cartType == CartType::MBC3_TIMER_BATTERY
    || cartType == CartType::MBC3_TIMER_RAM_BATTERY)
      m_hasBattery = true;
}

bool CartMBC3::loadCartridge() {
  bool retVal = loadRomBank0() && loadRomBankX(1);

  return retVal;
}

void CartMBC3::writeByte(word address, byte value) {
  if (m_ramTimerEnableRange.contains(address)){
    m_ramModule.writeEnableAddress(value);
    m_rtcModule.writeEnableAddress(value);
  }
  else if (m_romBankNumberRange.contains(address)){
    auto romBankNumber = (byte)(value & 0b1111111);
    if (!romBankNumber)
      romBankNumber = 1;
    loadRomBankX(romBankNumber);
  }
  else if (m_ramBankNumberRange.contains(address)){
    m_ramBankOrTimerNumber = (byte)(value & 0b1111);
    if (m_ramBankOrTimerNumber < 4)
      m_ramModule.setRamBank(m_ramBankOrTimerNumber);
    else if (m_ramBankOrTimerNumber <= 0x0C)
      m_rtcModule.registerSelect(m_ramBankOrTimerNumber);
  }
  else if (m_latchClockRange.contains(address)){
    m_rtcModule.writeLatchClockAddress(value);
  }
  else if (m_ramRange.contains(address)) {
    if (m_ramBankOrTimerNumber <= 3)
      m_ramModule.writeByte(address, value);
    else if (m_ramBankOrTimerNumber <= 0x0C)
      m_rtcModule.writeByte(value);
  }
}

byte CartMBC3::readByte(word address) const {
  if (m_romRange.contains(address))
    return m_rom[address];
  else if (m_ramRange.contains(address)){
    if (m_ramBankOrTimerNumber <= 0x03)
      return m_ramModule.readByte(address);
    if (m_ramBankOrTimerNumber <= 0x0C)
      return m_rtcModule.readRegister();
  }
  return 0xFF;
}