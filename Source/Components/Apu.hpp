//
// Created by derdro on 1/10/18.
//

#ifndef GBEMU_APU_HPP
#define GBEMU_APU_HPP

#include "../Utilities/Types.hpp"
#include "AudioMemoryInterface.hpp"
#include "../Utilities/Audio/SoundChannel.hpp"
#include "MemoryAudioInterface.hpp"
#include "../Utilities/Audio/SoundSample.hpp"
//#include <SFML/Audio/SoundBuffer.hpp>
//#include <SFML/Audio/Sound.hpp>

class Apu : public MemoryAudioInterface{
public:


private:
  AudioMemoryInterface& m_memory;

  std::shared_ptr<SoundChannel> m_channels[4];

  //sf::Sound m_soundPlayer;
  //sf::SoundBuffer m_soundBuffer;
  const static int BUFFER_SIZE = 1024;
  SoundSample m_sampleBuffer [BUFFER_SIZE];
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

  void initTriggered(int channelIndex) override;
};
#endif //GBEMU_APU_HPP
