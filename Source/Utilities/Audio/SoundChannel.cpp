//
// Created by derdro on 1/18/18.
//

#include "SoundChannel.hpp"

SoundChannel::SoundChannel(AudioMemoryInterface &memory) : m_memory(memory)
{
  m_enabled = false;
  m_timer = 0;
  m_frequency = 0;
  m_volume = 0;
  m_length = 0;
  m_lengthEnabled = false;
  m_leftEnabled = false;
  m_rightEnabled = false;
}

void SoundChannel::stepLength() {
  if (m_length > 0){
    setStatus(true);
    m_length--;
  }
  if (m_enabled){
    if (m_lengthEnabled && m_length == 0)
      setStatus(false);
  }
};

void SoundChannel::setSampleVolumes(SoundSample& sample, byte volume) {
  if (m_leftEnabled){
    byte leftVolume = (m_memory.readNR50() & (byte)0b01110000) >> 4;
    sample.setLeft(volume * leftVolume);
  }
  if (m_rightEnabled){
    byte rightVolume = (m_memory.readNR50() & (byte)0b111);
    sample.setRight(volume * rightVolume);
  }
}