//
// Created by Derek on 12/17/2017.
//
#include <SFML/Graphics/Text.hpp>
#include <cassert>
#include <chrono>
#include <thread>
#include <iomanip>
#include "Gameboy.hpp"


Gameboy::Gameboy(sf::RenderWindow &window, bool runBios)
 : m_memory(runBios), m_cpu((CpuMemoryInterface&)m_memory, runBios), m_gpu(window,(GpuMemoryInterface&)m_memory),
   m_timer((TimerMemoryInterface&)m_memory), m_input((InputMemoryInterface&)m_memory),
   m_window(window), m_debugWindow(nullptr), m_cartridge(), m_cartFact(), m_running(false), m_paused(false), m_frameLimited(true)
{
  m_input.linkGameboy(this);
}

bool Gameboy::insertRom(const std::string &romPath) {
  m_cartridge = m_cartFact.generateCartridge(romPath);
  assert(m_cartridge && "ERROR LOADING CARTRIDGE AT SPECIFIED ROM PATH");
  m_cartridge->loadCartridge();
  m_memory.linkCartridge(m_cartridge);
  return true;
}

void Gameboy::play() {
  m_running = true;
  byte ticks;

  auto begin = std::chrono::steady_clock::now();

  while(m_running){
    if (m_paused){
      std::this_thread::sleep_for(std::chrono::milliseconds(25));
      continue;
    }
    ticks = m_cpu.step();
    m_timer.step(ticks);
    m_gpu.step(ticks);
    if (m_gpu.frameDone()){
      if (m_debugWindow != nullptr){
        writeDebugInfo();
      }
      if (m_frameLimited) {
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::this_thread::sleep_for(std::chrono::milliseconds(16) - duration);
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin);
        m_window.setTitle(std::to_string(duration.count()));
        begin = std::chrono::steady_clock::now();
      }
    }

  }
}

void Gameboy::setFrameLimit(bool on){
  m_frameLimited = on;
}

void Gameboy::shutDown() {
  m_cartridge->shutDown();
  m_running = false;
}

void Gameboy::startDebugger(sf::RenderWindow *debugWindow) {
  m_debugWindow = debugWindow;
  m_debugWindow->clear();
  debugFont.loadFromFile("../BebasNeue.otf");
  debugText.setFont(debugFont);
  debugText.setColor(sf::Color::Green);
  debugText.setString("TEST");
}

void Gameboy::writeDebugInfo() {
  m_debugWindow->clear();
  byte scrollX = ((GpuMemoryInterface*)(&m_memory))->readScrollX();
  debugText.setString(std::to_string(scrollX));
  m_debugWindow->draw(debugText);
  m_debugWindow->display();
}

void Gameboy::keyPressed(sf::Keyboard::Key key) {
  m_input.keyPressed(key);
}