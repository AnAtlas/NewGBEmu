//
// Created by derdro on 1/18/18.
//

#ifndef GBEMU_SOUNDCHANNEL_HPP
#define GBEMU_SOUNDCHANNEL_HPP

#include <iostream>
#include "../Types.hpp"
#include "../../Components/MemoryInterfaces/AudioMemoryInterface.hpp"
#include "SoundSample.hpp"


class SoundChannel{
protected:
  bool m_enabled;

  //m_timer - set to (2048 - [frequency])*4, each cpu cycle is decremented, when 0 reset
  word m_timer;

  //m_frequency - 11 bit value loaded from NRx3 and NRx4
  word m_frequency;

  //m_length - writing to NRx1 loads this as 64 - [n]. every other step decrements, when 0 channel is silenced
  byte m_length;

  //m_lengthEnabled - when false a length = 0 does not silence the channel
  bool m_lengthEnabled;

  //m_volume - current volume of channel, depending on which channel is enabled (or both!)
  byte m_volume;

  bool m_leftEnabled;
  bool m_rightEnabled;

  AudioMemoryInterface& m_memory;

  const byte DEFAULT_LENGTH = 64;
  const byte DEFAULT_LENGTH_WAVE = 255;

  //Each Channel Gets attributes from different registers, delegate this to specified functions
  virtual void fetchEnabled() = 0;
  virtual void fetchFrequency() = 0;
  virtual void fetchLength() = 0;
  virtual void fetchLengthEnabled() = 0;
  virtual void fetchLeftEnabled() = 0;
  virtual void fetchRightEnabled() = 0;
  virtual void reloadTimer() = 0;

  virtual void setStatus(bool on) = 0;

  void setSampleVolumes(SoundSample& sample, byte volume);

public:
  explicit SoundChannel(AudioMemoryInterface& memory);

  //SoundChannels step every cpu cycle
  virtual void step() = 0;
  //Various functions step at different intervals
  void stepLength();
  virtual void stepEnvelope() = 0;
  virtual void stepSweep() = 0;


  virtual SoundSample generateSample() = 0;

  virtual void trigger() = 0;
};

#endif //GBEMU_SOUNDCHANNEL_HPP
