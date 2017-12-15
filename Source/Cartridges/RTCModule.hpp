//
// Created by derdro on 12/15/17.
//

#ifndef GBEMU_RTCMODULE_HPP
#define GBEMU_RTCMODULE_HPP


#include "../Utilities/Types.hpp"

/*
 * This class is used in a few MBC3 Catridges as a real time clock
 */
class RTCModule{
private:
  byte m_seconds;
  byte m_minutes;
  byte m_hours;
  byte m_dayCounter;
  byte m_flags;
  byte m_selectedRegister;

  bool m_latchReady;
  bool m_enabled;

public:
  RTCModule(): m_seconds(0), m_minutes(0), m_hours(0), m_dayCounter(0), m_flags(0),
         m_selectedRegister(8), m_latchReady(false), m_enabled(false)
  {

  }
  void registerSelect(byte reg){
    m_selectedRegister = reg;
  }

  void latchTime(){
    std::cout << "Warning, time not correct" << std::endl;
    m_seconds = 5;
    m_hours = 4;
    m_minutes = 9;
    m_dayCounter = 20;
    m_flags = 0b00000001;
  }

  void writeByte(byte value){
    if (!m_enabled)
      return;

    switch(m_selectedRegister){
      case 0x08:m_seconds = value; break;
      case 0x09:m_minutes = value; break;
      case 0x0A:m_hours = value; break;
      case 0x0B:m_dayCounter = value; break;
      case 0x0C:m_flags = value; break;
      default: ;break;
    }
  }

  byte readRegister() const{
    if (!m_enabled)
      return 0xFF;

    switch(m_selectedRegister){
      case 0x08:return m_seconds;
      case 0x09:return m_minutes;
      case 0x0A:return m_hours;
      case 0x0B:return m_dayCounter;
      case 0x0C:return m_flags;
      default: return 0xFF;
    }
  }

  void writeEnableAddress(byte value){
    m_enabled = ((value & 0xF) == 0x0A);
  }

  void writeLatchClockAddress(byte value){
    if (value == 0)
      m_latchReady = true;
    else{
      if (value == 1){
        if (m_latchReady)
          latchTime();
      }
      m_latchReady = false;
    }
  }
};
#endif //GBEMU_RTCMODULE_HPP
