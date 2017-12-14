//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_MEMORYMANAGER_HPP
#define GBEMU_MEMORYMANAGER_HPP

#include <memory>
#include "Memory.hpp"
#include "Cartridges/Cartridge.hpp"

class MemoryManager{
private:
  std::shared_ptr<ICartridge> cartridge;
  std::shared_ptr<Memory> memory;

public:
  MemoryManager(std::shared_ptr<)
};
#endif //GBEMU_MEMORYMANAGER_HPP
