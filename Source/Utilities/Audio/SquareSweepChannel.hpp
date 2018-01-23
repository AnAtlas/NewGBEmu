//
// Created by derdro on 1/18/18.
//

#ifndef GBEMU_SQUARECHANNEL_HPP
#define GBEMU_SQUARECHANNEL_HPP
#include "SoundChannel.hpp"
class SquareSweepChannel : public SoundChannel
{
private:

public:
  SquareSweepChannel(AudioMemoryInterface& memory);

  void stepLength();
  void stepEnvelope();
  void stepSweep();
};
#endif //GBEMU_SQUARECHANNEL_HPP
