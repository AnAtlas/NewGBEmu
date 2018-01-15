//
// Created by derdro on 12/15/17.
//

#ifndef GBEMU_RTCMODULE_HPP
#define GBEMU_RTCMODULE_HPP


#include <chrono>
#include "../Utilities/Types.hpp"

/**
 * Helper class to keep track of time
 */
class DateTime{
private:
  int m_timeConversions [4]{1, 60, 3600, 86400};
public:
  union{
    struct{
      byte m_seconds;
      byte m_minutes;
      byte m_hours;
      byte m_dayCounter;
      byte m_flags;
    };
    byte m_registers[5];
  };
  long m_timeStamp;
  DateTime(){}

  void update(){
    long newTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    long difference = newTime - m_timeStamp;
    for (int i = 3; i >= 0; --i){
      long deltaT = difference/m_timeConversions[i];
      m_registers[i] += deltaT;
      difference -= deltaT*m_timeConversions[i];
    }
    m_timeStamp = newTime;
  }

  void updateTimeStamp(){
    m_timeStamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
  }
};

/*
 * This class is used in a few MBC3 Catridges as a real time clock
 */
class RTCModule{
private:
  byte m_selectedRegister;

  DateTime m_latchTime;
  DateTime m_realTime;
  bool m_latchReady;
  bool m_enabled;

public:
  RTCModule(): m_latchTime(), m_realTime(),
         m_selectedRegister(8), m_latchReady(false), m_enabled(false)
  {
  }

  void load(){
    std::ifstream inFile;
    Settings& settings = Settings::getInstance();
    std::string savePath;
    std::string romName;
    settings.getSetting("SaveDir", savePath);
    settings.getSetting("CurrentRom", romName);
    romName = romName.substr(0, romName.find('.'));
    inFile.open(savePath + romName + ".rtc", std::ios::in | std::ios::binary);
    if (inFile.is_open()){
      inFile.read((char*)m_realTime.m_registers, 5);
      inFile.read((char*)&m_realTime.m_timeStamp, 4);
      inFile.read((char*)m_latchTime.m_registers, 5);
      inFile.read((char*)&m_latchTime.m_timeStamp, 4);
      m_realTime.update();
      inFile.close();
    }
    else{
      std::cout << romName << ".rtc not found" << std::endl;
    }
  }

  void save(){
    std::ofstream outFile;
    Settings& settings = Settings::getInstance();
    std::string savePath;
    std::string romName;
    settings.getSetting("SaveDir", savePath);
    settings.getSetting("CurrentRom", romName);
    romName = romName.substr(0, romName.find('.'));
    outFile.open(savePath + romName + ".rtc", std::ios::out | std::ios::binary);
    outFile.write((const char*)m_realTime.m_registers, 5);
    outFile.write((const char*)&m_realTime.m_timeStamp, 4);
    outFile.write((const char*)m_latchTime.m_registers, 5);
    outFile.write((const char*)&m_latchTime.m_timeStamp, 4);
    outFile.close();
  }

  void registerSelect(byte reg){
    m_selectedRegister = reg;
  }

  void latchTime(){
    m_realTime.update();
    m_latchTime = m_realTime;
  }

  void writeByte(byte value){
    if (!m_enabled)
      return;

    switch(m_selectedRegister){
      case 0x08:m_realTime.m_seconds = value; break;
      case 0x09:m_realTime.m_minutes = value; break;
      case 0x0A:m_realTime.m_hours = value; break;
      case 0x0B:m_realTime.m_dayCounter = value; break;
      case 0x0C:m_realTime.m_flags = value; break;
      default: ;break;
    }
    m_realTime.updateTimeStamp();
  }

  byte readRegister() const{
    if (!m_enabled)
      return 0xFF;
    switch(m_selectedRegister){
      case 0x08:return m_latchTime.m_seconds;
      case 0x09:return m_latchTime.m_minutes;
      case 0x0A:return m_latchTime.m_hours;
      case 0x0B:return m_latchTime.m_dayCounter;
      case 0x0C:return m_latchTime.m_flags;
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
