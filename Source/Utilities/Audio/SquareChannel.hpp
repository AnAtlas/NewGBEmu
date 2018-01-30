//
// Created by derdro on 1/24/18.
//

#ifndef GBEMU_TESTCHANNEL_HPP
#define GBEMU_TESTCHANNEL_HPP

#include "SoundChannel.hpp"

class SquareChannel : public SoundChannel
{
protected:

  enum EnvelopeDirection{
    DECREASE = 0,
    INCREASE = 1
  };

  const byte m_dutyPatterns [4] = {0b00000001, 0b10000001, 0b10000111, 0b01111110};

  //Initial volume on Trigger
  byte m_volumeInitial;

  //Set to [m_volumeEnvelopePeriod], on the 7th step of frame sequencer, it decrements
  //When 0, increase or decrease volume depending on [m_envelopeDirection] unless reached min/max
  byte m_volumeEnvelopeTimer;

  //Sets m_volumeEnvelopeTimer
  byte m_volumeEnvelopePeriod;

  //Explained in m_volumeEnvelopetimer
  EnvelopeDirection m_volumeEnvelopeDirection;

  //Position in the duty pattern, patterns defined above
  byte m_dutyPosition;

  //Which duty is currently being used 0-3
  byte m_dutySelect;

  virtual void fetchVolumeInitial();
  virtual void fetchVolumeEnvelopePeriod();
  virtual void fetchVolumeEnvelopeDirection();
  virtual void fetchDutySelect();


  void incDutyPosition();
  void reloadTimer() override;
private:
  //Each Channel Gets attributes from different registers, delegate this to specified functions
  void fetchEnabled() override;
  void fetchFrequency() override;
  void fetchLength() override;
  void fetchLengthEnabled() override;
  void fetchLeftEnabled() override;
  void fetchRightEnabled() override;
  void setStatus(bool on) override;

public:
  explicit SquareChannel(AudioMemoryInterface& memory);

  void step() override;
  void stepSweep() override {};
  void stepEnvelope() override;

  void trigger() override;

  SoundSample generateSample() override;
};
#endif //GBEMU_TESTCHANNEL_HPP
