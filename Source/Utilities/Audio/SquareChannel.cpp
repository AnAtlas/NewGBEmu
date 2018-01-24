//
// Created by derdro on 1/18/18.
//
#include "SquareChannel.hpp"

SquareChannel::SquareChannel(AudioMemoryInterface &memory)
    : SoundChannel(memory)
{
  m_volumeInitial = 0;
  m_volumeEnvelopeTimer = 0;
  m_volumeEnvelopePeriod = 0;
  m_volumeEnvelopeDirection = EnvelopeDirection::DECREASE;
  m_dutyPosition = 0;
  m_dutySelect = 0;
}

void SquareChannel::step(){

}

void SquareChannel::stepLength() {

}

void SquareChannel::stepSweep() {

}

void SquareChannel::stepEnvelope() {

}

void SquareChannel::trigger(){

}