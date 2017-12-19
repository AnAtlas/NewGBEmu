//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_GPU_HPP
#define NEWGBEMU_GPU_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "GpuMemoryInterface.hpp"

const byte SCREEN_WIDTH = 160;
const byte SCREEN_HEIGHT = 144;

enum GPUMode {
  HBlank = 0x00,
  VBlank = 0x01,
  OAM = 0x02,
  VRAM = 0x03
};

enum Color {
  White,
  LightGray,
  DarkGray,
  Black
};

struct RGB {
  unsigned char r, g, b, a;
};

class Gpu
{
private:
  sf::RenderWindow& m_window;
  sf::Texture m_texture;
  GpuMemoryInterface& m_memory;
  RGB m_frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
public:
  Gpu(sf::RenderWindow& window, GpuMemoryInterface& memory);
};
#endif //NEWGBEMU_GPU_HPP
