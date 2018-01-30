//
// Created by derdro on 1/24/18.
//
#include "WaveChannel.hpp"
#include "../Bits.hpp"

const byte WAVE_POSITION_AMOUNT = 32;

byte WaveVolumeShift [4] = {4, 0, 1, 2};


WaveChannel::WaveChannel(AudioMemoryInterface &memory) : SoundChannel(memory)
{
  m_wavePosition = 0;
  m_DACEnabled = false;
  m_sampleBuffer = 0;
}

void WaveChannel::step(){
  if (m_timer == 0){
    //Increment wave position
    incWavePosition();

    //Fill sample buffer, remember samples are only 4 bits each
    m_sampleBuffer = m_wavePatternRAM[m_wavePosition/2];
    m_sampleBuffer >>= (1 - (m_wavePosition%2)) * 4;
    m_sampleBuffer &= 0x0F;

    reloadTimer();
  }
  m_timer--;
}

void WaveChannel::trigger() {
  m_enabled = true;

  fetchLength();
  if (m_length == 0)
    m_length = DEFAULT_LENGTH_WAVE;

  fetchFrequency();
  reloadTimer();
  fetchWaveRAM();
  fetchWaveVolume();
  m_wavePosition = 0;
}

/**
 * Generate a sound sample, based on the duty position and volume
 */
SoundSample WaveChannel::generateSample() {
  SoundSample sample(0,0);
  if (m_enabled && m_DACEnabled){
    byte output = m_sampleBuffer >> WaveVolumeShift[m_waveVolume];
    setSampleVolumes(sample, output);
  }
  return sample;
}

void WaveChannel::fetchEnabled(){

}

///Channel 3 NR51(FF25) bit 6
void WaveChannel::fetchLeftEnabled() {
  m_leftEnabled = bitOn(m_memory.readNR51(), 6);
}

///Channel 3 NR51(FF25) bit 2
void WaveChannel::fetchRightEnabled() {
  m_leftEnabled = bitOn(m_memory.readNR51(), 2);
}

/**
 * Frequency is 2 registers, 8 lower bits, and 3 higher bits
 * Channel 1 LSB NR33(FF1D) 8 bits (7-0)
 * Channel 1 MSB NR34(FF1E) 3 bits (2-0)
 */
void WaveChannel::fetchFrequency(){
  m_frequency = ((word)m_memory.readNR34() & (word)0b111) << 8;
  m_frequency |= ((word)m_memory.readNR33() & (word)0xFF);
}

/**Channel 3 NR31(FF1B) 8 bits (7-0)
 * Length = 256 - Register value
 */
void WaveChannel::fetchLength(){
  m_length = (byte)(256 - m_memory.readNR31());
}

void WaveChannel::fetchLengthEnabled(){

}

void WaveChannel::fetchWaveRAM() {
  for (int i = 0; i < 16; ++i){
    m_wavePatternRAM[i] = m_memory.readWaveRAM(i);
  }
}

void WaveChannel::reloadTimer() {
  m_timer = ((word)2048 - m_frequency) * (word)2;
}

void WaveChannel::incWavePosition() {
  m_wavePosition++;
  if (m_wavePosition == WAVE_POSITION_AMOUNT)
    m_wavePosition = 0;
}

///Channel 3 status bit = NR52(FF26) bit 2
void WaveChannel::setStatus(bool on) {
  if (on){
    m_enabled = true;
    m_memory.writeNR52(bitSetOn(m_memory.readNR52(), 2));
  }
  else{
    m_enabled = false;
    m_memory.writeNR52(bitSetOff(m_memory.readNR52(), 2));
  }
}

///Channel 3 Wave Volume = NR32(FF1C) 2 bits (6-5)
void WaveChannel::fetchWaveVolume() {
  m_waveVolume = ((m_memory.readNR32() & (byte)0b01000000) >> 5) | ((m_memory.readNR32() & (byte)0b00100000) >> 5);
}