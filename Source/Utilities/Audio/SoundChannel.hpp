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
private:
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
};

#endif //GBEMU_SOUNDCHANNEL_HPP
