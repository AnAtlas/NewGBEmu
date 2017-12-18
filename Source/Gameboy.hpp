//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_GAMEBOY_HPP
#define NEWGBEMU_GAMEBOY_HPP

#include "SFML/Graphics/RenderWindow.hpp"
#include "Components/Memory.hpp"
#include "Components/Cpu.hpp"
#include "Components/Gpu.hpp"
#include "Components/Timer.hpp"

class Gameboy
{
private:
  Memory m_memory;
  Cpu m_cpu;
  Gpu m_gpu;
  Timer m_timer;

  bool running;
  sf::RenderWindow& window;
public:
  Gameboy(sf::RenderWindow& window, bool runBios);

  bool insertRom(std::string& romPath);
  void play();
  void shutDown();
  void buttonDown(sf::Keyboard::Key);
  void buttonUp(sf::Keyboard::Key);
};
#endif //NEWGBEMU_GAMEBOY_HPP
