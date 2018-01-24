//
// Created by derdro on 1/24/18.
//
#include "NoiseChannel.hpp"

NoiseChannel::NoiseChannel(AudioMemoryInterface &memory) : SquareChannel(memory)
{
  m_LFSR = 0;
  m_counterWidth = CounterStepWidth::BITS_15;
  m_divisorIndex = 0;
}

void NoiseChannel::step(){

}

void NoiseChannel::stepLength() {

}

void NoiseChannel::stepSweep() {

}

void NoiseChannel::stepEnvelope() {

}

void NoiseChannel::trigger() {

}
