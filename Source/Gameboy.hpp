//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_GAMEBOY_HPP
#define NEWGBEMU_GAMEBOY_HPP

#include <SFML/Window/Keyboard.hpp>
#include "SFML/Graphics/RenderWindow.hpp"
#include "Components/Memory.hpp"
#include "Components/Cpu.hpp"
#include "Components/Gpu.hpp"
#include "Components/Timer.hpp"
#include "Cartridges/Cartridge.hpp"
#include "Cartridges/CartridgeFactory.hpp"

class Gameboy
{
private:
  Memory m_memory;
  Cpu m_cpu;
  Gpu m_gpu;
  Timer m_timer;
  CartridgeFactory m_cartFact;
  std::shared_ptr<Cartridge> m_cartridge;

  bool m_running;
  bool m_paused;
  sf::RenderWindow& m_window;
  sf::Clock m_frameTimer;

public:
  Gameboy(sf::RenderWindow& window, bool runBios);

  bool insertRom(const std::string& romPath);
  void play();
  void shutDown();
  void buttonDown(sf::Keyboard::Key);
  void buttonUp(sf::Keyboard::Key);
};
#endif //NEWGBEMU_GAMEBOY_HPP
