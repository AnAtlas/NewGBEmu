//
// Created by derdro on 1/18/18.
//
#include "SquareChannel.hpp"
#include "../Bits.hpp"

const byte DUTY_POSITION_AMOUNT = 8;

SquareChannel::SquareChannel(AudioMemoryInterface &memory)
    : SoundChannel(memory)
{
  m_volumeInitial = 0;
  m_volumeEnvelopeTimer = 0;
  m_volumeEnvelopePeriod = 0;
  m_volumeEnvelopeDirection = EnvelopeDirection::DECREASE;
  m_dutyPosition = 0;
  m_dutySelect = 0;
}

void SquareChannel::step(){
  if (m_timer == 0){
    //Increment Duty position
    incDutyPosition();

    //Reload Timer
    reloadTimer();
  }
  m_timer--;
}

/*
 * Envelope increases or decreases the volume by 1
 * Speeds of this are controlled by the envelope timer
 */
void SquareChannel::stepEnvelope() {
  if (m_volumeEnvelopePeriod > 0){
    if (m_volumeEnvelopeTimer == 0){
      if (m_volumeEnvelopeDirection == EnvelopeDirection::DECREASE && m_volume > 0)
        m_volume--;
      else if (m_volumeEnvelopeDirection == EnvelopeDirection::INCREASE && m_volume < 15)
        m_volume++;

      m_volumeEnvelopeTimer = m_volumeEnvelopePeriod;
    }
    m_volumeEnvelopeTimer--;
  }
}

void SquareChannel::trigger(){
  m_dutyPosition = 0;

  setStatus(true);

  //Load length, if it's 0 set it to 64
  fetchLength();
  if (m_length == 0)
    m_length = DEFAULT_LENGTH;

  fetchFrequency();
  reloadTimer();

  fetchVolumeEnvelopePeriod();
  m_volumeEnvelopeTimer = m_volumeEnvelopePeriod;

  fetchVolumeInitial();
  m_volume = m_volumeInitial;

  fetchDutySelect();

  fetchVolumeEnvelopeDirection();
}

/**
 * Generate a sound sample, based on the duty position and volume
 */
SoundSample SquareChannel::generateSample() {
  SoundSample sample(0,0);
  if (m_enabled){
    byte output = (bitOn(m_dutyPatterns[m_dutySelect], m_dutyPosition)) ? m_volume : (byte)0;
    setSampleVolumes(sample, output);
  }
  return sample;
}

///Channel 2
void SquareChannel::fetchEnabled(){

}

///Channel 2 NR51(FF25) bit 5
void SquareChannel::fetchLeftEnabled() {
  m_leftEnabled = bitOn(m_memory.readNR51(), 5);
}

///Channel 2 NR51(FF25) bit 1
void SquareChannel::fetchRightEnabled() {
  m_leftEnabled = bitOn(m_memory.readNR51(), 1);
}

/**
 * Frequency is 2 registers, 8 lower bits, and 3 higher bits
 * Channel 2 LSB NR23(FF18) 8 bits (7-0)
 * Channel 2 MSB NR24(FF19) 3 bits (2-0)
 */
void SquareChannel::fetchFrequency(){
  m_frequency = ((word)m_memory.readNR24() & (word)0b111) << 8;
  m_frequency |= ((word)m_memory.readNR23() & (word)0xFF);
}

/**Channel 2 NR21(FF16) 6 bits (5-0)
 * Length = 64 - Register value
 */
void SquareChannel::fetchLength(){
  m_length = (byte)(64 - m_memory.readNR21() & (byte)0b00111111);
}

///Channel 2 NR24(FF19) 1 bit (6)
void SquareChannel::fetchLengthEnabled(){
  m_lengthEnabled = bitOn(m_memory.readNR24(), 6);
}

///Channel 2 NR22(FF17) 4 bits (7-4)
void SquareChannel::fetchVolumeInitial() {
  m_volumeInitial = (m_memory.readNR22() & (byte)0b11110000) >> 4;
}

/**
 * Volume Envelope period
 * Where n = last 3 bits of Volume Envelope Control Register
 * Channel 2 NR22(FF17) 3 bits (2-0)
 */
void SquareChannel::fetchVolumeEnvelopePeriod() {
  m_volumeEnvelopePeriod = m_memory.readNR22() & (byte)0b111;
}

///Channel 2 NR22(FF17) 1 bit (3)
void SquareChannel::fetchVolumeEnvelopeDirection() {
  m_volumeEnvelopeDirection = (bitOn(m_memory.readNR22(), 3)) ? EnvelopeDirection::INCREASE : EnvelopeDirection::DECREASE;
}

///Channel 2 NR21(FF16) 2 bits (7-6)
void SquareChannel::fetchDutySelect() {
  m_dutySelect = (m_memory.readNR21() & (byte)0b11000000) >> 6;
}

void SquareChannel::reloadTimer() {
  m_timer = ((word)2048 - m_frequency) * (word)4;
}

void SquareChannel::incDutyPosition() {
  m_dutyPosition++;
  if (m_dutyPosition == DUTY_POSITION_AMOUNT)
    m_dutyPosition = 0;
}

///Channel 2 status bit = NR52(FF26) bit 0
void SquareChannel::setStatus(bool on) {
  if (on){
    m_enabled = true;
    m_memory.writeNR52(bitSetOn(m_memory.readNR52(), 1));
  }
  else{
    m_enabled = false;
    m_memory.writeNR52(bitSetOff(m_memory.readNR52(), 1));
  }
}
