//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_GAMEBOY_HPP
#define NEWGBEMU_GAMEBOY_HPP

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "Components/Input.hpp"
#include "Components/Memory.hpp"
#include "Components/Cpu.hpp"
#include "Components/Gpu.hpp"
#include "Components/Timer.hpp"
#include "Cartridges/Cartridge.hpp"
#include "Cartridges/CartridgeFactory.hpp"
#include "DebuggingTools/TilesetViewer.hpp"

class Gameboy
{
private:
  Memory m_memory;
  Cpu m_cpu;
  Gpu m_gpu;
  Timer m_timer;
  Input m_input;
  CartridgeFactory m_cartFact;
  std::shared_ptr<Cartridge> m_cartridge;
  TilesetViewer* m_tilesetViewer;

  bool m_running;
  bool m_paused;
  bool m_frameLimited;
  sf::RenderWindow& m_window;
  sf::RenderWindow* m_debugWindow;

  void writeDebugInfo();
  sf::Font debugFont;
  sf::Text debugText;

public:
  Gameboy(sf::RenderWindow& window, bool runBios);

  bool insertRom(const std::string& romPath);
  void play();
  void pause(){ m_paused = true; }
  void unpause(){ m_paused = false; }
  void togglePause() { m_paused = !m_paused; }
  void toggleFrameLimit() { m_frameLimited = !m_frameLimited; }
  void shutDown();
  void setFrameLimit(bool on);
  void startDebugger(sf::RenderWindow* debugWindow);
  void keyPressed(sf::Keyboard::Key key);
  void joystickButtonPressed(int buttonCode);
};
#endif //NEWGBEMU_GAMEBOY_HPP
