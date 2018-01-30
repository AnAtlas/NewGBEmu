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

  byte m_waveVolume;

  //Each Channel Gets attributes from different registers, delegate this to specified functions
  void fetchEnabled() override;
  void fetchLeftEnabled() override;
  void fetchRightEnabled() override;
  void fetchFrequency() override;
  void fetchLength() override;
  void fetchLengthEnabled() override;

  void reloadTimer() override;
  void setStatus(bool on) override;

  void fetchWaveRAM();
  void fetchWaveVolume();
  void incWavePosition();
public:
  explicit WaveChannel(AudioMemoryInterface& memory);

  void step() override;
  void stepEnvelope() override{};
  void stepSweep() override {};

  void trigger() override;

  SoundSample generateSample() override;
};

#endif //GBEMU_WAVECHANNEL_HPP
