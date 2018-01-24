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
  typedef enum SweepDirection{
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
  SquareSweepChannel(AudioMemoryInterface& memory);

  void stepLength();
  void stepEnvelope();
  void stepSweep();
};
#endif //GBEMU_SQUARECHANNEL_HPP
