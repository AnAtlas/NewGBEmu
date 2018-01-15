//
// Created by derdro on 1/8/18.
//

#ifndef GBEMU_TILESETVIEWER_HPP
#define GBEMU_TILESETVIEWER_HPP

#include <cstring>
#include "../Components/Gpu.hpp"
#include "../Components/Memory.hpp"
const byte TILESET_WIDTH = 192;
const byte TILESET_HEIGHT = 128;

class TilesetViewer{
private:
  sf::RenderWindow* m_window;
  Memory& m_memory;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
  RGB m_frameBuffer[TILESET_WIDTH * TILESET_HEIGHT];
  std::vector<std::vector<RGB>> m_tiles;

public:
  enum TileMode{

  };
  TilesetViewer(sf::RenderWindow* window, Memory& memory) : m_window(window), m_memory(memory){
    for (int i = 0; i < TILESET_HEIGHT * SCREEN_WIDTH; i++)
      m_frameBuffer[i] = Palette[Color::WHITE];

    m_texture.create(TILESET_WIDTH, TILESET_HEIGHT);
    m_texture.setSmooth(false);
    m_texture.update((const sf::Uint8*)m_frameBuffer, TILESET_WIDTH, TILESET_HEIGHT, 0, 0);
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(sf::Vector2f(2.0,2.0));
  }

  void addTileToBuffer(int index, RGB tile[64]){
    int xTilePos = index %24;
    int yTilePos = index / 24;
    for (int i = 0; i < 8; ++i){
      for (int j = 0; j < 8; ++j){
        m_frameBuffer[(yTilePos * 8 * TILESET_WIDTH) + (i * TILESET_WIDTH) + (xTilePos * 8) + j] = tile[i * 8 + (7-j)];
      }
    }
  }

  void draw(){
    //384 tiles in vram
    int index = 0x8000;
    int tileIndex = 0;
    RGB tile [64];
    int tilePixel = 0;
    while (index < 0x9C00){
      for (int i = 0 ; i < 8; i++){
        byte low8 = m_memory.readByte(index + (i*2));
        byte high8 = m_memory.readByte(index + (i*2) + 1);
        for (int k = 7; k >= 0; --k){
          int colorNum = ((1 << k) & low8) | (((1 << k) & high8) << 1);
          auto color = (Color)colorNum;
          byte bgPaletteData = m_memory.readBackgroundPalette();
          switch (color){
            case Color::WHITE: color =  (Color)((bgPaletteData) & 0x3); break;
            case Color::LIGHT_GRAY: color =  (Color)(((bgPaletteData) & 0xC) >> 2); break;
            case Color::DARK_GRAY: color =  (Color)(((bgPaletteData) & 0x30) >> 4); break;
            case Color::BLACK: color =  (Color)(((bgPaletteData) & 0xC0) >> 6); break;
            default: ;
          }
          tile[i * 8 + k] = Palette[color];
        }
      }
      addTileToBuffer(tileIndex, tile);
      if (tileIndex == 120){
        int val = 0;
        for (auto v : tile){
          val += v.a;
          val += v.b;
          val += v.g;
          val += v.r;
        }
        if (val == 47972)
          val--;
      }
      tileIndex++;
      index += 16;
    }
    //Push framebuffer to screen
    m_texture.update((const sf::Uint8*)m_frameBuffer, TILESET_WIDTH, TILESET_HEIGHT,0,0);
    m_window->draw(m_sprite);
  }
};
#endif //GBEMU_TILESETVIEWER_HPP
