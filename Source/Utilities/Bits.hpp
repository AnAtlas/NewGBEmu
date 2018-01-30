//
// Created by derdro on 1/18/18.
//

#ifndef GBEMU_BITS_HPP
#define GBEMU_BITS_HPP

#include "Types.hpp"

namespace{
  bool bitOn(byte num, int bit){
    return (num & (1 << bit) != 0);
  }

  bool bitOff(byte num, int bit){
    return (num & (1 << bit) == 0);
  }

  byte bitSetOff(byte num, int bit){
    return (num & ~((byte)1 << bit));
  }

  byte bitSetOn(byte num, int bit){
    return (num | ((byte)1 << bit));
  }
}

#endif //GBEMU_BITS_HPP
