//
// Created by derdro on 1/10/18.
//

#ifndef GBEMU_APU_HPP
#define GBEMU_APU_HPP

#include "../Utilities/Types.hpp"
#include "AudioMemoryInterface.hpp"
#include "../Utilities/Audio/SoundChannel.hpp"
#include <SFML/Audio.hpp>

struct Sample{
  short left = 0;
  short right = 0;

  Sample(short l, short r){
    left = l;
    right = r;
  }

  Sample& operator+=(const Sample& rhs){
    this->left += rhs.left;
    this->right += rhs.right;
    return *this;
  }
};

class Apu{
private:
  AudioMemoryInterface& m_memory;

  SoundChannel m_channels[4];

  sf::Sound m_soundPlayer;
  sf::SoundBuffer m_soundBuffer;
  const int BUFFER_SIZE = 1024;
  Sample m_sampleBuffer [BUFFER_SIZE];
  int m_bufferIndex;
  const int CPU_SPEED = 4194304;
  const unsigned int SAMPLE_RATE = 96000;
  const int TICKS_PER_SEQUENCE = 8192;
  const int STEPS_PER_SEQUENCE = 8;
  const int TICKS_PER_SAMPLE = CPU_SPEED / SAMPLE_RATE;

  int m_sequenceTimer;
  int m_sequenceStep;
  int m_sampleTimer;
  
public:
  explicit Apu(AudioMemoryInterface& memory);
  void step(byte ticks);
};
#endif //GBEMU_APU_HPP
