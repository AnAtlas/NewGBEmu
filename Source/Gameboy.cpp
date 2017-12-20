//
// Created by Derek on 12/17/2017.
//
#include "Gameboy.hpp"
#include "Components/GpuMemoryInterface.hpp"
#include "Components/CpuMemoryInterface.hpp"


Gameboy::Gameboy(sf::RenderWindow &window, bool runBios)
 : m_memory(runBios), m_cpu((CpuMemoryInterface&)m_memory, runBios), m_gpu(window,(GpuMemoryInterface&)m_memory),
   m_timer((TimerMemoryInterface&)m_memory), m_window(window), m_cartridge(), m_cartFact(), m_running(false)
{

}

bool Gameboy::insertRom(const std::string &romPath) {
  m_cartridge = m_cartFact.generateCartridge(romPath);
  m_cartridge->loadCartridge();
  m_memory.linkCartridge(m_cartridge);
}

void Gameboy::play() {
  m_running = true;
  byte ticks;
  while(m_running){
    ticks = m_cpu.step();
    m_timer.step(ticks);
    m_gpu.step(ticks);
  }
}

void Gameboy::shutDown() {
  m_running = false;
}
