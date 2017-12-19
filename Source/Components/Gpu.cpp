//
// Created by derdro on 12/19/17.
//
#include "Gpu.hpp"



const RGB palette[4] = {
  { 255,255,255, 255 },
  { 192,192,192, 255 },
  {  96, 96,96, 255  },
  {  0 , 0 , 0, 255  }
};

Gpu::Gpu(sf::RenderWindow& window, GpuMemoryInterface& memory)
  : m_window(window),m_memory(memory) {
  for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
    m_frameBuffer[i] = palette[Color::White];

  m_texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
  m_texture.setSmooth(false);
  m_texture.update()
}