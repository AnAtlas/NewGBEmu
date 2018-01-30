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

  //Linear Feedback Shift Register 15-bit, OR 7-bit depending on mode
  word m_LFSR;

  CounterStepWidth m_counterWidth;

  byte m_divisorIndex;

  void fetchVolumeInitial() override;
  void fetchVolumeEnvelopePeriod() override;
  void fetchVolumeEnvelopeDirection() override;

  void reloadTimer() override;

  //Each Channel Gets attributes from different registers, delegate this to specified functions
  void fetchEnabled() override;
  void fetchLeftEnabled() override;
  void fetchRightEnabled() override;
  void fetchFrequency() override;
  void fetchLength() override;
  void fetchLengthEnabled() override;
  void setStatus(bool on) override;

  void fetchDivisorIndex();
  void fetchCounterStepWidth();

  byte getDivisor();

public:
  explicit NoiseChannel(AudioMemoryInterface& memory);

  void step() override;

  void trigger() override;

  SoundSample generateSample() override;
};

#endif //GBEMU_NOISECHANNEL_HPP
