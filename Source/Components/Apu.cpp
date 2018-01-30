//
// Created by derdro on 1/10/18.
//
#include <chrono>
#include <thread>
#include "Apu.hpp"
#include "../Utilities/Bits.hpp"
#include "../Utilities/Audio/SquareChannel.hpp"
#include "../Utilities/Audio/SquareSweepChannel.hpp"
#include "../Utilities/Audio/WaveChannel.hpp"
#include "../Utilities/Audio/NoiseChannel.hpp"

Apu::Apu(AudioMemoryInterface &memory) : m_memory(memory), m_sequenceTimer(TICKS_PER_SEQUENCE), m_sequenceStep(0),
    m_sampleTimer(TICKS_PER_SAMPLE), m_bufferIndex(0)
{
  m_channels[0] = std::make_shared<SquareSweepChannel>(memory);
  m_channels[1] = std::make_shared<SquareChannel>(memory);
  m_channels[2] = std::make_shared<WaveChannel>(memory);
  m_channels[3] = std::make_shared<NoiseChannel>(memory);
}

void Apu::step(byte ticks) {
  //Check if Audio is enabled
  if (bitOff(m_memory.readNR52(), 7))
    return;


  for (int i = 0; i < ticks; i++){
    for (auto& channel : m_channels)
      channel->step();

    m_sequenceTimer--;
    if (m_sequenceTimer == 0){
      //Perform correct Audio Step
      //Length counter is updated every 2nd step
      if (m_sequenceStep % 2 == 0){
        for (auto& channel : m_channels)
          channel->stepLength();
      }

      //Volume envelope is adjusted every 7th step
      if (m_sequenceStep == 7){
        for (auto& channel : m_channels)
          channel->stepEnvelope();
      }

      //Sweep is ajusted every 2nd and 6th step
      if (m_sequenceStep == 2 || m_sequenceStep == 6){
        for (auto& channel : m_channels)
          channel->stepSweep();
      }

      //Step the Sequencer
      m_sequenceStep++;
      if (m_sequenceStep == STEPS_PER_SEQUENCE)
        m_sequenceStep = 0;

      m_sequenceTimer = TICKS_PER_SEQUENCE;
    }

    //Load sample into SFML
    m_sampleTimer--;
    if (m_sampleTimer == 0){
      SoundSample sample(0,0);
      for (auto& channel : m_channels) {
        sample += channel->generateSample();
      }
      m_finalSampleBuffer[m_bufferIndex] = sample.m_left;
      m_finalSampleBuffer[m_bufferIndex+1] = sample.m_right;
      //m_sampleBuffer[m_bufferIndex] = sample.m_left;

      m_bufferIndex+=2;

      if (m_bufferIndex >= BUFFER_SIZE * 2){
        m_bufferIndex = 0;

        while(m_soundPlayer.getStatus() != sf::Sound::Status::Stopped){
          //std::this_thread::sleep_for(std::chrono::microseconds(1));
        }

        m_soundBuffer.loadFromSamples(m_finalSampleBuffer, BUFFER_SIZE * 2, 2, SAMPLE_RATE);
        m_soundPlayer.setBuffer(m_soundBuffer);
        m_soundPlayer.play();
      }
      m_sampleTimer = TICKS_PER_SAMPLE;
    }
  }
}

void Apu::initTriggered(int channelIndex) {
  m_channels[channelIndex]->trigger();
}