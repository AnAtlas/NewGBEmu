//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_GPU_HPP
#define NEWGBEMU_GPU_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GpuMemoryInterface.hpp"

const byte SCREEN_WIDTH = 160;
const byte SCREEN_HEIGHT = 144;

enum GPUMode{
    H_BLANK = 0x00,
    V_BLANK = 0x01,
    OAM = 0x02,
    VRAM = 0x03
};

enum Color {
  WHITE,
  LIGHT_GRAY,
  DARK_GRAY,
  BLACK
};

enum SpriteAttribute{
  PRIORITY = 1 << 7,
  Y_FLIP = 1 << 6,
  X_FLIP = 1 << 5,
  PALETTE = 1 << 4
};

struct GPUTimings{
  enum{
    ACCESS_OAM = 0x50,
    ACCESS_VRAM = 0xAC,
    H_BLANK = 0xCC,
    V_BLANK = 0x1C8
  };
};

struct RGB {
  byte r, g, b, a;
  bool operator==(RGB rgb1){
    return (r == rgb1.r && g == rgb1.g && b == rgb1.b && a == rgb1.a);
  }
};

enum LCDControlFlags {
  DISPLAY_ENABLE                     = (1 << 7), //(0=Off, 1=On)
  WINDOW_TILE_MAP_SELECT             = (1 << 6), //(0=9800-9BFF, 1=9C00-9FFF)
  WINDOW_DISPLAY_ENABLE              = (1 << 5), //(0=Off, 1=On)
  BACKGROUND_WINDOW_TILE_DATA_SELECT = (1 << 4), //(0=8800-97FF, 1=8000-8FFF)
  BACKGROUND_TILE_MAP_SELECT         = (1 << 3), //(0=9800-9BFF, 1=9C00-9FFF)
  SPRITE_SIZE                        = (1 << 2), //Sprite Size (0=8x8, 1=8x16)
  SPRITE_DISPLAY_ENABLE              = (1 << 1), //(0=Off, 1=On)
  BACKGROUND_DISPLAY                 = (1 << 0) //(0=Off, 1=On)
};

class Gpu
{
private:
  sf::RenderWindow& m_window;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
  GpuMemoryInterface& m_memory;
  GPUMode m_gpuMode;
  word m_gpuClock;
  bool m_frameDone;
  RGB m_frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
  const byte m_spriteLimit;
  const byte m_spriteWidth;
  byte m_spriteHeight;

  void setLcdMode(GPUMode mode);
  void renderScanLine();
  void renderBackground();
  void renderSprites();
  Color getBackgroundPaletteShade(Color color);
  Color getObjectPaletteShade(bool palette1, Color color);
  RGB getPixelAt(byte x, byte y);
public:
  Gpu(sf::RenderWindow& window, GpuMemoryInterface& memory);
  void step(byte ticks);
  bool frameDone();
};
#endif //NEWGBEMU_GPU_HPP
