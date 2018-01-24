//
// Created by derdro on 1/24/18.
//

#ifndef GBEMU_WAVECHANNEL_HPP
#define GBEMU_WAVECHANNEL_HPP

#include "SquareChannel.hpp"

/**
 * NOTES
 * m_timer = (2048-[m_frequency])*2
 * m_length = 8 bits, not 6 bits
 */
class WaveChannel : public SoundChannel
{
private:
  byte m_wavePosition;

  bool m_DACEnabled;

  byte m_sampleBuffer;

  //Wave Pattern RAM
  //Waveform storage for sound data, holds 32 4-bit samples that are played upper 4 bits first
  byte m_wavePatternRAM [16] = {0};

public:
  WaveChannel(AudioMemoryInterface& memory);

  void stepLength();
  void stepEnvelope();
  void stepSweep();
};

#endif //GBEMU_WAVECHANNEL_HPP
