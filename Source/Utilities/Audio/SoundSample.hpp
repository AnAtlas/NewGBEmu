//
// Created by derdro on 1/24/18.
//

#ifndef GBEMU_SOUNDSAMPLE_HPP
#define GBEMU_SOUNDSAMPLE_HPP

struct SoundSample
{
  short m_left;
  short m_right;

  SoundSample() {
    m_left = 0;
    m_right = 0;
  }

  SoundSample(short left, short right) : m_left(left), m_right(right)
  {
  }

  SoundSample& operator+=(const SoundSample& rhs){
    m_left += rhs.m_left;
    m_right += rhs.m_right;
    return *this;
  }

  SoundSample& operator+=(byte volume){
    m_left += volume;
    m_right += volume;
    return *this;
  }

  void setLeft(byte volume){
    m_left = volume;
  }

  void setRight(byte volume){
    m_right = volume;
  }
};
#endif //GBEMU_SOUNDSAMPLE_HPP