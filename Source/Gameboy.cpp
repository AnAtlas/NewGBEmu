//
// Created by Derek on 12/17/2017.
//
#include "Gameboy.hpp"
#include "Components/GpuMemoryInterface.hpp"
#include "Components/CpuMemoryInterface.hpp"

Gameboy::Gameboy(sf::RenderWindow &window, bool runBios)
 : m_memory(false), m_cpu((CpuMemoryInterface&)m_memory), m_gpu(window,(GpuMemoryInterface&)m_memory),
   m_window(window), m_cartridge(), m_cartFact()
{

}

bool Gameboy::insertRom(const std::string &romPath) {
  m_cartridge = m_cartFact.generateCartridge(romPath);
  m_memory.linkCartridge(m_cartridge);
}
