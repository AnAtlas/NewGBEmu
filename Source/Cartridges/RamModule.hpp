//
// Created by derdro on 12/15/17.
//

#ifndef GBEMU_RAMMODULE_HPP
#define GBEMU_RAMMODULE_HPP


#include "../Utilities/Types.hpp"

class RamModule{
public:
  enum RamSize{
    KB_0 = 0, //Banks
    KB_2 = 1, //1/4 Bank
    KB_8 = 2, //1 Bank
    KB_32 = 3, // 4 Banks
    KB_128 = 4,// 16 Banks
    KB_64 = 5 // 8 Banks
  };

private:
  byte* m_ramBank;
  byte m_ramTotal[0x2C000];
  RamSize m_ramSize;
  bool m_enabled;

public:
  explicit RamModule(RamSize ramSize)
    :m_enabled(false), m_ramSize(ramSize), m_ramBank(m_ramTotal), m_ramTotal{0} {

  }

  void writeByte(word address, byte value) {
    if (m_enabled){
      m_ramBank[address - 0xA000] = value;
    }
  }

  byte readByte(word address) const {
    byte retVal = 0xFF;
    if (m_enabled && m_ramSize > RamSize::KB_0){
      if (m_ramSize == RamSize::KB_2){
        if (address - 0xA000 < 0x07FF)
          retVal = m_ramBank[address - 0xA000];
      }
      else
        retVal = m_ramBank[address - 0xA000];
    }
    return retVal;
  }

  void writeEnableAddress(byte value){
    m_enabled = ((value & 0xF) == 0x0A);
  }

  void setRamBank(byte ramBankIndex) {
    m_ramBank = m_ramTotal + (ramBankIndex * 0x4000);
  }

};
#endif //GBEMU_RAMMODULE_HPP
