//
// Created by derdro on 1/18/18.
//

#ifndef GBEMU_SQUARECHANNEL_HPP
#define GBEMU_SQUARECHANNEL_HPP
#include "../../Components/AudioMemoryInterface.hpp"
#include "SquareChannel.hpp"

class SquareSweepChannel : public SquareChannel
{
private:
  enum SweepDirection{
    DECREASE = 0,
    INCREASE = 1
  };

  //Channel can be enabled while sweep isn't
  bool m_sweepEnabled;

  //
  byte m_sweepPeriod;

  SweepDirection m_sweepDirection;

  byte m_sweepShift;

  byte m_sweepTimer;

public:
  explicit SquareSweepChannel(AudioMemoryInterface& memory);

  void step() override;
  void stepLength() override;
  void stepEnvelope() override;
  void stepSweep() override;

  void trigger() override;
};
#endif //GBEMU_SQUARECHANNEL_HPP
