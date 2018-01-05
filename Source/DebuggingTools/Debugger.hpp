//
// Created by derdro on 12/27/17.
//

#ifndef GBEMU_DEBUGGER_HPP
#define GBEMU_DEBUGGER_HPP


#include <SFML/Graphics/RenderWindow.hpp>
#include "../Components/Gpu.hpp"
#include "../Components/Memory.hpp"
#include "../Components/Cpu.hpp"

class Debugger{
private:
  sf::RenderWindow& m_debugWindow;
  Cpu& m_cpu;
  Memory& m_memory;
  Gpu& m_gpu;
public:
  Debugger(Cpu& cpu, Memory& memory, Gpu& gpu);
  void step();
};
#endif //GBEMU_DEBUGGER_HPP
