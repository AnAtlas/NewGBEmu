//
// Created by Derek on 12/17/2017.
//
#include <SFML/System.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cassert>
#include "Gameboy.hpp"
#include "Components/GpuMemoryInterface.hpp"
#include "Components/CpuMemoryInterface.hpp"


Gameboy::Gameboy(sf::RenderWindow &window, bool runBios)
 : m_memory(runBios), m_cpu((CpuMemoryInterface&)m_memory, runBios), m_gpu(window,(GpuMemoryInterface&)m_memory),
   m_timer((TimerMemoryInterface&)m_memory), m_window(window), m_cartridge(), m_cartFact(), m_running(false), m_paused(false)
{

}

bool Gameboy::insertRom(const std::string &romPath) {
  m_cartridge = m_cartFact.generateCartridge(romPath);
  if (!m_cartridge){
    std::cout << "ERROR: Cannot find rom at " << romPath << std::endl;
  }
  assert(m_cartridge);
  m_cartridge->loadCartridge();
  m_memory.linkCartridge(m_cartridge);
}

void Gameboy::play() {
  m_running = true;
  m_frameTimer.restart();
  byte ticks;
  while(m_running){
    if (m_paused){
      sf::sleep(sf::milliseconds(25));
      continue;
    }
    ticks = m_cpu.step();
    m_timer.step(ticks);
    m_gpu.step(ticks);
    if (m_gpu.frameDone()){
      sf::sleep(sf::seconds((float)0.01667) - m_frameTimer.restart());
    }
  }
}

void Gameboy::shutDown() {
  m_running = false;
}