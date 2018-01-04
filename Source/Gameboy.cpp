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
   m_timer((TimerMemoryInterface&)m_memory),
   m_window(window), m_cartridge(), m_cartFact(), m_running(false), m_paused(false), m_frameLimited(true)
{
}

bool Gameboy::insertRom(const std::string &romPath) {
  m_cartridge = m_cartFact.generateCartridge(romPath);
  assert(m_cartridge && "ERROR LOADING CARTRIDGE AT SPECIFIED ROM PATH");
  m_cartridge->loadCartridge();
  m_memory.linkCartridge(m_cartridge);
}

void Gameboy::play() {
  m_running = true;
  byte ticks;

  auto begin = std::chrono::high_resolution_clock::now();

  while(m_running){
    if (m_paused){
      std::this_thread::sleep_for(std::chrono::milliseconds(25));
      continue;
    }
    ticks = m_cpu.step();
    m_timer.step(ticks);
    m_gpu.step(ticks);
    if (m_gpu.frameDone()){
      if (m_frameLimited) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::this_thread::sleep_for(std::chrono::milliseconds(16) - duration);
        begin = std::chrono::high_resolution_clock::now();
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

//Debug
void Gameboy::printOam() {
  std::cout << "Sprite YPos XPos CharCode Attr" << std::endl;
  for (int i = 0; i < 40; i++){
    std::cout << std::setw(4) <<  i;
    for (int j = 0; j < 4; j++){
      std::cout << std::setw(6) << (int)m_memory.readByte((word)0xFE00 + (word)i * (word)4 + (word)j) ;
    }
    std::cout << std::endl;
  }
}