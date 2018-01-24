//
// Created by derdro on 1/24/18.
//
#include "WaveChannel.hpp"

WaveChannel::WaveChannel(AudioMemoryInterface &memory) : SoundChannel(memory)
{
  m_wavePosition = 0;
  m_DACEnabled = false;
  m_sampleBuffer = 0;
}