//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_GPUMEMORYINTERFACE_HPP
#define NEWGBEMU_GPUMEMORYINTERFACE_HPP
#include "Memory.hpp"

class GpuMemoryInterface
{
private:

public:
  GpuMemoryInterface();

  virtual byte readLcdStatus() = 0;
  virtual byte readLcdControl() = 0;
  virtual byte readLineY() = 0;
  virtual byte readLYC() = 0;
  virtual byte readBackgroundPalette() = 0;
  virtual byte readObjectPalette0() = 0;
  virtual byte readObjectPalette1() = 0;
  virtual byte readOam(byte index) = 0;
  virtual byte readVram(byte index) = 0;
  virtual byte readScrollX() = 0;
  virtual byte readScrollY() = 0;
  virtual byte readWindowX() = 0;
  virtual byte readWindowY() = 0;
  virtual void requestInterrupt(byte bit) = 0;
  virtual void writeLcdStatus(byte value) = 0;
  virtual void writeLineY(byte value) = 0;
};
#endif //NEWGBEMU_GPUMEMORYINTERFACE_HPP
