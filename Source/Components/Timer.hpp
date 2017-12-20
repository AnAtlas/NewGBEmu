//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_TIMER_HPP
#define NEWGBEMU_TIMER_HPP
#include "../Utilities/Types.hpp"
#include "TimerMemoryInterface.hpp"

class Timer{
private:
  TimerMemoryInterface& m_memory;
  word m_divTicks;
  word m_timerTicks;

public:
  Timer(TimerMemoryInterface& memory);
  void step(byte ticks);

};
#endif //NEWGBEMU_TIMER_HPP
