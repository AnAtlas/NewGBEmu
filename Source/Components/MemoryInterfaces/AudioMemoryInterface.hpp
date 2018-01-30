//
// Created by derdro on 1/18/18.
//

#ifndef GBEMU_AUDIOMEMORYINTERFACE_HPP
#define GBEMU_AUDIOMEMORYINTERFACE_HPP
#include "../../Utilities/Types.hpp"

class AudioMemoryInterface{
private:

public:

  virtual byte readNR10() const = 0;
  virtual byte readNR11() const = 0;
  virtual byte readNR12() const = 0;
  virtual byte readNR13() const = 0;
  virtual byte readNR14() const = 0;
  virtual byte readNR21() const = 0;
  virtual byte readNR22() const = 0;
  virtual byte readNR23() const = 0;
  virtual byte readNR24() const = 0;
  virtual byte readNR31() const = 0;
  virtual byte readNR32() const = 0;
  virtual byte readNR33() const = 0;
  virtual byte readNR34() const = 0;
  virtual byte readNR41() const = 0;
  virtual byte readNR42() const = 0;
  virtual byte readNR43() const = 0;
  virtual byte readNR44() const = 0;
  virtual byte readNR50() const = 0;
  virtual byte readNR51() const = 0;
  virtual byte readNR52() const = 0;

  virtual byte readWaveRAM(int index) const = 0;
  virtual void writeNR52(byte value) = 0;
};
#endif //GBEMU_AUDIOMEMORYINTERFACE_HPP
