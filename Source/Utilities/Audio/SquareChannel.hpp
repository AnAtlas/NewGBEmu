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

public:
  explicit SquareChannel(AudioMemoryInterface& memory);

  void step() override;
  void stepLength() override;
  void stepEnvelope() override;
  void stepSweep() override;

  void trigger() override;
};
#endif //GBEMU_TESTCHANNEL_HPP
