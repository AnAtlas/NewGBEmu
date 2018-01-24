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
}

void SoundChannel::step() {
  std::cout << "ERROR" << std::endl;
};