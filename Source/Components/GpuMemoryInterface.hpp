//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_GPUMEMORYINTERFACE_HPP
#define NEWGBEMU_GPUMEMORYINTERFACE_HPP

#include "../Utilities/Types.hpp"

class GpuMemoryInterface
{
private:

public:
  virtual byte readLcdStatus() const = 0;
  virtual byte readLcdControl() const = 0;
  virtual byte readLineY() const = 0;
  virtual byte readLYC() const = 0;
  virtual byte readBackgroundPalette() const = 0;
  virtual byte readObjectPalette0() const = 0;
  virtual byte readObjectPalette1() const = 0;
  virtual byte readOam(byte index) const = 0;
  virtual byte readVram(byte index) const = 0;
  virtual byte readScrollX() const = 0;
  virtual byte readScrollY() const = 0;
  virtual byte readWindowX() const = 0;
  virtual byte readWindowY() const = 0;
  virtual void requestInterrupt(byte bit) = 0;
  virtual void writeLcdStatus(byte value) = 0;
  virtual void writeLineY(byte value) = 0;
};
#endif //NEWGBEMU_GPUMEMORYINTERFACE_HPP
