//
// Created by derdro on 1/24/18.
//
#include "SquareSweepChannel.hpp"

SquareSweepChannel::SquareSweepChannel(AudioMemoryInterface &memory) : SquareChannel(memory)
{
  m_sweepEnabled = false;
  m_sweepPeriod = 0;
  m_sweepDirection = SweepDirection::DECREASE;
  m_sweepShift = 0;
  m_sweepTimer = 0;
}
