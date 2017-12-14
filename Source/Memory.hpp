//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_MEMORY_HPP
#define GBEMU_MEMORY_HPP
#include "Utilities/Types.hpp"

class Memory {
private:
  byte memory[0xFFFF];

  void copy(word destination, word source, word length);
  bool addressOnCartridge(word address);

public:
  Memory(bool runBios);
};
#endif //GBEMU_MEMORY_HPP
