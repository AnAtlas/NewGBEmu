//
// Created by derdro on 1/24/18.
//

#ifndef GBEMU_NOISECHANNEL_HPP
#define GBEMU_NOISECHANNEL_HPP

#include "SquareChannel.hpp"

class NoiseChannel : public SquareChannel
{
private:
  enum CounterStepWidth{
    BITS_15 = 0,
    BITS_7 = 1
  };

  //Linear Feedback Shift Register 15-bit
  word m_LFSR;

  CounterStepWidth m_counterWidth;

  byte m_divisorIndex;

public:
  NoiseChannel(AudioMemoryInterface& memory);

  void step() override;
  void stepLength() override;
  void stepEnvelope() override;
  void stepSweep() override;

  void trigger() override;
};

#endif //GBEMU_NOISECHANNEL_HPP
