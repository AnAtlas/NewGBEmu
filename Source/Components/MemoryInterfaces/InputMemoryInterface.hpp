//
// Created by derdro on 12/28/17.
//

#ifndef GBEMU_INPUTMEMORYINTERFACE_HPP
#define GBEMU_INPUTMEMORYINTERFACE_HPP

#include "../../Utilities/Types.hpp"

class InputMemoryInterface
{
public:
  virtual byte readP1() = 0;
  virtual void writeP1Inputs(byte value) = 0;
  virtual void requestInputInterrupt() = 0;
};
#endif //GBEMU_INPUTMEMORYINTERFACE_HPP
