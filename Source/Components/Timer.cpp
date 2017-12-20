//
// Created by derdro on 12/20/17.
//
#include "Timer.hpp"

enum TimerControlFlags{
  TIMER_ENABLE = 0b100,
  MAIN_FREQ_DIVIDER = 0b11
};

word TimerFrequencies[4] = {
  1024, 16, 64, 256
};

Timer::Timer(TimerMemoryInterface& memory)
  : m_memory(memory), m_timerTicks(0), m_divTicks(0)
{

}

void Timer::step(byte ticks) {
  m_divTicks += ticks;
  if (m_divTicks >255){
    m_memory.incDivRegister();
    m_divTicks -= 256;
  }

  if (m_memory.readTimerControl() & TimerControlFlags::TIMER_ENABLE){
    m_timerTicks += ticks;
    word tFreq = TimerFrequencies[m_memory.readTimerControl() & TimerControlFlags::MAIN_FREQ_DIVIDER];
    if (m_timerTicks >= tFreq){
      m_timerTicks -= tFreq;
      byte timerCounter = m_memory.readTimerCounter();
      if (timerCounter == 0xFF){
        timerCounter = m_memory.readTimerModulo();
        m_memory.requestInterrupt(2);
      }
      else
        timerCounter++;
      m_memory.writeTimerCounter(timerCounter);
    }
  }
}