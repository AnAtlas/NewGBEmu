//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_CPUMEMORYINTERFACE_HPP
#define NEWGBEMU_CPUMEMORYINTERFACE_HPP
#include "Memory.hpp"

class CpuMemoryInterface
{
private:

public:
  CpuMemoryInterface();

  virtual void writeByte(word address, byte value) = 0;
  virtual void writeShort(word address, word value) = 0;

  virtual byte readByte(word address) = 0;
  virtual word readShort(word address) = 0;

  virtual void requestInterrupt(byte bit) = 0;
};
#endif //NEWGBEMU_CPUMEMORYINTERFACE_HPP
