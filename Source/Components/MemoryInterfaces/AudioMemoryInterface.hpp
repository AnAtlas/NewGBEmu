//
// Created by derdro on 1/18/18.
//

#ifndef GBEMU_AUDIOMEMORYINTERFACE_HPP
#define GBEMU_AUDIOMEMORYINTERFACE_HPP
#include "../../Utilities/Types.hpp"

class AudioMemoryInterface{
private:

public:

  virtual byte readNR52() const = 0;
};
#endif //GBEMU_AUDIOMEMORYINTERFACE_HPP
