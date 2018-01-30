//
// Created by derdro on 1/24/18.
//
#include "NoiseChannel.hpp"
#include "../Bits.hpp"

const byte BASE_DIVISOR [] = { 8, 16, 32, 48, 64, 80, 96, 112};

NoiseChannel::NoiseChannel(AudioMemoryInterface &memory) : SquareChannel(memory)
{
  m_LFSR = 0;
  m_counterWidth = CounterStepWidth::BITS_15;
  m_divisorIndex = 0;
}

void NoiseChannel::step(){
  if (m_timer == 0){
    ///All sound is based off of the value in LFSR
    ///When clocked, last two bits are XOR'ed, then put into the high bit of LFSR, after LFSR
    ///Is shifted right by 1 bit
    bool xorTrue = (((m_LFSR & (word)0b10) >> 1) ^ (m_LFSR & (word)0b1)) == (word)1;

    ///Shift LFSR right 1
    m_LFSR >>= 1;

    ///PUt the result of the XOR into the now empty high bit
    if (xorTrue){
      if (m_counterWidth == CounterStepWidth::BITS_15)
        m_LFSR |= 0x4000;
      else{
        ///If width mode is 7-bit, the XOR Result is put into bit 6
        m_LFSR &= 0x3F;
        m_LFSR |= 0x40;
      }
    }
  }
  m_timer--;
}

void NoiseChannel::trigger() {
  m_enabled = true;

  fetchLength();
  if (m_length == 0)
    m_length = DEFAULT_LENGTH;

  fetchDivisorIndex();
  fetchFrequency();
  reloadTimer();

  fetchVolumeEnvelopePeriod();
  m_volumeEnvelopeTimer = m_volumeEnvelopePeriod;

  fetchVolumeInitial();
  m_volume = m_volumeInitial;

  fetchCounterStepWidth();

  //LSFR bits are set to 1
  m_LFSR = 0x7FFF;
}

SoundSample NoiseChannel::generateSample(){
  SoundSample sample(0,0);
  if (bitOff((byte)m_LFSR, 0))
    setSampleVolumes(sample, m_volume);
  return sample;
}

void NoiseChannel::fetchEnabled(){

}

///Channel 4 NR51(FF25) bit 7
void NoiseChannel::fetchLeftEnabled() {
  m_leftEnabled = bitOn(m_memory.readNR51(), 7);
}

///Channel 4 NR51(FF25) bit 3
void NoiseChannel::fetchRightEnabled() {
  m_leftEnabled = bitOn(m_memory.readNR51(), 3);
}

///Channel 4 NR43(FF22) 4 bits(7-4)
void NoiseChannel::fetchFrequency(){
  m_frequency = (m_memory.readNR43() >> 4) & (byte)0b1111;
}

/**Channel 4 NR41(FF20) 6 bits (5-0)
 * Length = 64 - Register value
 */
void NoiseChannel::fetchLength(){
  m_length = (byte)(64 - m_memory.readNR41() & (byte)0b00111111);
}

///Channel 4 NR44(FF23) 1 bit(6)
void NoiseChannel::fetchLengthEnabled(){
  m_lengthEnabled = bitOn(m_memory.readNR44(), 6);
}

///Channel 4 NR42(FF21) 4 bits (7-4)
void NoiseChannel::fetchVolumeInitial(){
  m_volumeInitial = (m_memory.readNR42() & (byte)0b11110000) >> 4;
}

///Channel 4 NR42(FF21) 3 bits (2-0)
void NoiseChannel::fetchVolumeEnvelopePeriod(){
  m_volumeEnvelopePeriod = m_memory.readNR42() & (byte)0b111;
}

///Channel 4 NR42(FF21) 1 bit (3)
void NoiseChannel::fetchVolumeEnvelopeDirection(){
  m_volumeEnvelopeDirection = (bitOn(m_memory.readNR42(), 3)) ? EnvelopeDirection::INCREASE : EnvelopeDirection::DECREASE;
}

///NR43(FF22) 3 bits (2-0)
void NoiseChannel::fetchDivisorIndex() {
  m_divisorIndex = m_memory.readNR43() & (byte)0b111;
}

///NR43(FF22) 1 bit (3)
void NoiseChannel::fetchCounterStepWidth() {
  m_counterWidth = (bitOn(m_memory.readNR43(), 3)) ? CounterStepWidth::BITS_7 : CounterStepWidth::BITS_15;
}

byte NoiseChannel::getDivisor() {
  return (m_divisorIndex < 8) ? BASE_DIVISOR[m_divisorIndex] : (byte)8;
}

void NoiseChannel::reloadTimer() {
  m_timer = getDivisor() << m_frequency;
}

///Channel 4 status bit = NR52(FF26) bit 3
void NoiseChannel::setStatus(bool on) {
  if (on){
    m_enabled = true;
    m_memory.writeNR52(bitSetOn(m_memory.readNR52(), 3));
  }
  else{
    m_enabled = false;
    m_memory.writeNR52(bitSetOff(m_memory.readNR52(), 3));
  }
}
