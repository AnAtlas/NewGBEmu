//
// Created by derdro on 1/18/18.
//

#ifndef GBEMU_SQUARECHANNEL_HPP
#define GBEMU_SQUARECHANNEL_HPP
#include "SoundChannel.hpp"
class SquareChannel : public SoundChannel
{
private:
  bool m_hasSweep;

public:
  SquareChannel(AudioMemoryInterface& memory);

  void stepLength();
  void stepEnvelope();
  void stepSweep();
};
#endif //GBEMU_SQUARECHANNEL_HPP
