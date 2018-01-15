//
// Created by derdro on 12/15/17.
//

#ifndef GBEMU_CARTMBC3_HPP
#define GBEMU_CARTMBC3_HPP

#include "Cartridge.hpp"
#include "../Utilities/AddressRange.hpp"
#include "RamModule.hpp"
#include "RTCModule.hpp"

class CartMBC3: public Cartridge
{
private:
  enum MBC3Address{
    RAM_BANK = 0xA000,
    RAM_BANK_END = 0xBFFF,
    RAM_TIMER_ENABLE = 0x0000,
    RAM_TIMER_ENABLE_END = 0x1FFF,
    ROM_BANK_NUMBER = 0x2000,
    ROM_BANK_NUMBER_END = 0x3FFF,
    RAM_BANK_NUMBER = 0x4000,
    RAM_BANK_NUMBER_END = 0x5FFF,
    LATCH_CLOCK = 0x6000,
    LATCH_CLOCK_END = 0x7FFF
  };

  RamModule m_ramModule;
  RTCModule m_rtcModule;

  byte m_ramBankOrTimerNumber;
  bool m_hasBattery;

  AddressRange m_ramRange;
  AddressRange m_ramTimerEnableRange;
  AddressRange m_romBankNumberRange;
  AddressRange m_ramBankNumberRange;
  AddressRange m_latchClockRange;

public:
  explicit CartMBC3(CartType cartType, std::string romPath, RamModule::RamSize ramSize);

  bool loadCartridge() override;
  void shutDown() override;
  byte readByte(word address) const override;
  void writeByte(word address, byte value) override;
};
#endif //GBEMU_CARTMBC3_HPP
