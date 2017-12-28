//
// Created by derdro on 12/20/17.
//

#ifndef GBEMU_TIMERMEMORYINTERFACE_HPP
#define GBEMU_TIMERMEMORYINTERFACE_HPP

#include "../Utilities/Types.hpp"

class TimerMemoryInterface{
private:

public:
  virtual void incDivRegister(byte ticks) = 0;
  virtual byte incTimerCounter() = 0;
  virtual void writeTimerCounter(byte value) = 0;
  virtual byte readTimerCounter() = 0;
  virtual byte readTimerModulo() = 0;
  virtual byte readTimerControl() = 0;
  virtual void requestInterrupt(byte bit) = 0;
};
#endif //GBEMU_TIMERMEMORYINTERFACE_HPP
