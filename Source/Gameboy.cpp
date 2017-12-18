//
// Created by Derek on 12/17/2017.
//
#include "Gameboy.hpp"
#include "Components/GpuMemoryInterface.hpp"
#include "Components/CpuMemoryInterface.hpp"

Gameboy::Gameboy(sf::RenderWindow &window, bool runBios)
 : m_memory(false), m_cpu((CpuMemoryInterface)&m_memory), m_gpu((GpuMemoryInterface)&m_memory), m_timer(&m_memory)
{

}
