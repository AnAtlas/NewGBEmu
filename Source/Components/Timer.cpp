//
// Created by derdro on 12/20/17.
//
#include "Timer.hpp"

/**
 * Notes
 * When TIMA overflows the value from TMA is loaded and IF timer is set to 1, but it doesn't happen immediately.
 * Timer interrupt and TMA loading is delayed 1 cycle (4 clocks) from the TIMA overflow.
 * For one cycle, after the overflow, TIMA is 00h not TMA
 */
enum TimerControlFlags{
  TIMER_ENABLE = 0b100,
  MAIN_FREQ_DIVIDER = 0b11
};

word TimerFrequencies[4] = {
  1024, 16, 64, 256
};

Timer::Timer(TimerMemoryInterface& memory)
  : m_memory(memory), m_timerTicks(0), m_divTicks(0), m_timaOverflowed(false)
{

}

void Timer::step(byte ticks) {
  m_memory.incDivRegister(ticks);

  if (m_memory.readTimerControl() & TimerControlFlags::TIMER_ENABLE){
    if (m_timaOverflowed){
      m_timaOverflowed = false;
      m_memory.writeTimerCounter(m_memory.readTimerModulo());
    }
    m_timerTicks += ticks;
    word tFreq = TimerFrequencies[m_memory.readTimerControl() & TimerControlFlags::MAIN_FREQ_DIVIDER];
    if (m_timerTicks >= tFreq){
      m_timerTicks -= tFreq;
      byte tima = m_memory.incTimerCounter();
      if (!tima){
        m_timaOverflowed = true;
        //Interrupt won't be seen until after the next instruction, so it's alright to have this here
        m_memory.requestTimerInterrupt();
      }
    }
  }
}