//
// Created by derdro on 1/18/18.
//

#ifndef GBEMU_SOUNDCHANNEL_HPP
#define GBEMU_SOUNDCHANNEL_HPP

#include <iostream>
#include "../Types.hpp"
#include "../../Components/AudioMemoryInterface.hpp"
#include "../../Components/Apu.hpp"

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

  //m_volume - current volume of channel
  byte m_volume;

  AudioMemoryInterface& m_memory;

public:
  explicit SoundChannel(AudioMemoryInterface& memory);

  //SoundChannels step every cpu cycle
  virtual void step();
  //Various functions step at different intervals
  virtual void stepLength();
  virtual void stepEnvelope();
  virtual void stepSweep();

  virtual Sample generateSample();

  virtual void trigger() = 0;
};

#endif //GBEMU_SOUNDCHANNEL_HPP
