//
// Created by derdro on 1/18/18.
//

#ifndef GBEMU_SQUARECHANNEL_HPP
#define GBEMU_SQUARECHANNEL_HPP
#include "../../Components/MemoryInterfaces/AudioMemoryInterface.hpp"
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

  word m_sweepFrequency;

  SweepDirection m_sweepDirection;

  byte m_sweepShift;

  byte m_sweepTimer;

  //Each Channel Gets attributes from different registers, delegate this to specified functions
  void fetchEnabled() override;
  void fetchLeftEnabled() override;
  void fetchRightEnabled() override;
  void fetchFrequency() override;
  void fetchLength() override;
  void fetchLengthEnabled() override;
  void fetchVolumeInitial() override;
  void fetchVolumeEnvelopePeriod() override;
  void fetchVolumeEnvelopeDirection() override;
  void fetchDutySelect() override;
  void setStatus(bool on) override;

  void fetchSweepPeriod();
  void fetchSweepShift();
  void fetchSweepDirection();
  word calculateSweep();
public:
  explicit SquareSweepChannel(AudioMemoryInterface& memory);

  void stepSweep() override;

  void trigger() override;
};
#endif //GBEMU_SQUARECHANNEL_HPP
