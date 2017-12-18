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

  byte readLcdStatus();
  byte readLcdControl();
  byte readLineY();
  byte readLYC();
  byte readBackgroundPalette();
  byte readObjectPalette0();
  byte readObjectPalette1();
  byte readOam(byte index);
  byte readVram(byte index);
  byte readScrollX();
  byte readScrollY();
  byte readWindowX();
  byte readWindowY();
  void requestInterrupt(byte bit);
  void writeLcdStatus(byte value);
  void writeLineY(byte value);
};
#endif //NEWGBEMU_GPUMEMORYINTERFACE_HPP
