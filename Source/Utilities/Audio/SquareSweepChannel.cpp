//
// Created by derdro on 1/24/18.
//
#include "SquareSweepChannel.hpp"
#include "../Bits.hpp"

SquareSweepChannel::SquareSweepChannel(AudioMemoryInterface &memory) : SquareChannel(memory)
{
  m_sweepEnabled = false;
  m_sweepPeriod = 0;
  m_sweepDirection = SweepDirection::DECREASE;
  m_sweepShift = 0;
  m_sweepTimer = 0;
}

void SquareSweepChannel::stepSweep() {
  ///if sweepPeriod is 0, sweep is disabled
  if (m_sweepPeriod > 0){
    if (m_sweepEnabled && m_sweepTimer == 0){
      word newFreq = calculateSweep();

      ///Frequency is only 11 bits
      if (newFreq > 2047)
        setStatus(false);
      else if (newFreq < 2047 && m_sweepShift > 0){
        m_sweepFrequency = newFreq;
        m_frequency = newFreq;
      }

    }
    m_sweepTimer = m_sweepPeriod;
  }
}

void SquareSweepChannel::trigger() {
  //Load basic square channel attributes
  SquareChannel::trigger();

  //Load sweep attributes
  m_sweepFrequency = m_frequency;

  fetchSweepPeriod();
  m_sweepTimer = m_sweepPeriod;

  fetchSweepDirection();

  fetchSweepShift();
  m_sweepEnabled = (m_sweepPeriod > 0 || m_sweepShift > 0);

  if (m_sweepShift > 0)
    calculateSweep();
}

word SquareSweepChannel::calculateSweep() {
  word newFreq = 0;
  newFreq = m_sweepFrequency >> m_sweepShift;
  if (m_sweepDirection == SweepDirection::INCREASE)
    newFreq += m_sweepFrequency;
  else
    newFreq = m_sweepFrequency - newFreq;
  return newFreq;
}

void SquareSweepChannel::fetchEnabled(){

}

///Channel 1 NR51(FF25) bit 4
void SquareSweepChannel::fetchLeftEnabled() {
  m_leftEnabled = bitOn(m_memory.readNR51(), 4);
}

///Channel 1 NR51(FF25) bit 0
void SquareSweepChannel::fetchRightEnabled() {
  m_leftEnabled = bitOn(m_memory.readNR51(), 0);
}

/**
 * Frequency is 2 registers, 8 lower bits, and 3 higher bits
 * Channel 1 LSB NR13(FF13) 8 bits (7-0)
 * Channel 1 MSB NR14(FF14) 3 bits (2-0)
 */
void SquareSweepChannel::fetchFrequency(){
  m_frequency = ((word)m_memory.readNR14() & (word)0b111) << 8;
  m_frequency |= ((word)m_memory.readNR13() & (word)0xFF);
}

/**Channel 1 NR11(FF11) 6 bits (5-0)
 * Length = 64 - Register value
 */
void SquareSweepChannel::fetchLength(){
  m_length = (byte)(64 - m_memory.readNR11() & (byte)0b00111111);
}

///Channel 1 NR14(FF14) 1 bit (6)
void SquareSweepChannel::fetchLengthEnabled(){
  m_lengthEnabled = bitOn(m_memory.readNR14(), 6);
}

///Channel 1 NR12(FF12) 4 bits (7-4)
void SquareSweepChannel::fetchVolumeInitial(){
  m_volumeInitial = (m_memory.readNR12() & (byte)0b11110000) >> 4;
}

/**
 * Volume Envelope period
 * Where n = last 3 bits of Volume Envelope Control Register
 * Channel 1 NR12(FF12) 3 bits (2-0)
 */
void SquareSweepChannel::fetchVolumeEnvelopePeriod(){
  m_volumeEnvelopePeriod = m_memory.readNR12() & (byte)0b111;
}

///Channel 1 NR12(FF12) 1 bit (3)
void SquareSweepChannel::fetchVolumeEnvelopeDirection(){
  m_volumeEnvelopeDirection = (bitOn(m_memory.readNR12(), 3)) ? EnvelopeDirection::INCREASE : EnvelopeDirection::DECREASE;
}

///Channel 1 NR11(FF11) 2 bits(7-6)
void SquareSweepChannel::fetchDutySelect(){
  m_dutySelect = (m_memory.readNR11() & (byte)0b11000000) >> 6;
}

///Channel 1 NR10(FF10) 3 bits(6-4)
void SquareSweepChannel::fetchSweepPeriod() {
  m_sweepPeriod = (m_memory.readNR10() & (byte)0b01110000) >> 4;
}

///Channel 1 NR10(FF10) 3 bits(2-0)
void SquareSweepChannel::fetchSweepShift() {
  m_sweepShift = m_memory.readNR10() & (byte)0b111;
}

///Channel 1 NR10(FF10) 1 bit(3)
void SquareSweepChannel::fetchSweepDirection() {
  m_sweepDirection = (bitOn(m_memory.readNR10(), 3)) ? SweepDirection::DECREASE : SweepDirection::INCREASE;
}

///Channel 1 status bit = NR52(FF26) bit 0
void SquareSweepChannel::setStatus(bool on) {
  if (on){
    m_enabled = true;
    m_memory.writeNR52(bitSetOn(m_memory.readNR52(), 0));
  }
  else{
    m_enabled = false;
    m_memory.writeNR52(bitSetOff(m_memory.readNR52(), 0));
  }
}