//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_CPUMEMORYINTERFACE_HPP
#define NEWGBEMU_CPUMEMORYINTERFACE_HPP

class CpuMemoryInterface
{
private:

public:
  virtual void writeByte(word address, byte value) = 0;
  virtual void writeShort(word address, word value) = 0;

  virtual byte readByte(word address) const = 0;
  virtual word readShort(word address) const = 0;

  virtual byte getIntFlags() const = 0;
  virtual void resetIntFlag(byte bitIndex) = 0;
  virtual byte getIntsEnabled() const = 0;

  virtual void requestInterrupt(byte bit) = 0;
};
#endif //NEWGBEMU_CPUMEMORYINTERFACE_HPP
