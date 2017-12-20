//
// Created by derdro on 12/19/17.
//
#include <cstring>
#include "Gpu.hpp"



const RGB palette[4] = {
  { 255,255,255, 255 },
  { 192,192,192, 255 },
  {  96, 96,96, 255  },
  {  0 , 0 , 0, 255  }
};

Gpu::Gpu(sf::RenderWindow& window, GpuMemoryInterface& memory)
  : m_window(window),m_memory(memory), m_gpuMode(GPUMode::H_BLANK), m_sprite() {
  for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
    m_frameBuffer[i] = palette[Color::WHITE];

  m_texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
  m_texture.setSmooth(false);
  m_texture.update((const sf::Uint8*)m_frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  m_sprite.setTexture(m_texture);
}


void Gpu::step(byte ticks){
  byte lcdControlReg = m_memory.readLcdControl();
  byte lcdStatus = m_memory.readLcdStatus();
  byte lineY = m_memory.readLineY();

  if (!(lcdControlReg & LCDControlFlags::DISPLAY_ENABLE)){
    m_memory.writeLineY(0);
    setLcdMode(GPUMode::V_BLANK);
    return;
  }

  m_gpuClock += ticks;
  auto mode = (GPUMode)(m_memory.readLcdStatus() & 0b11);
  bool reqInt = false;

  switch (mode){
    case GPUMode::H_BLANK:
      if (m_gpuClock >= GPUTimings::H_BLANK){
        m_gpuClock = 0;
        m_memory.writeLineY(m_memory.readLineY() + (byte)1);
        if (m_memory.readLineY() == 143){
          //Enter VBlank
          setLcdMode(GPUMode::V_BLANK);
          reqInt = (lcdStatus & ((byte)1 << 4));

          //Push framebuffer to screen
          m_texture.update((const sf::Uint8*)m_frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT,0,0);
          m_window.clear();
          m_window.draw(m_sprite);
          m_window.display();
        }
        else{
          setLcdMode(GPUMode::OAM);
          reqInt = lcdStatus & ((byte)1 << 5);
        }
      }
      break;

    case GPUMode::V_BLANK:
      if (m_gpuClock >= GPUTimings::V_BLANK){
        m_gpuClock = 0;
        m_memory.writeLineY(m_memory.readLineY() + (byte)1);
        if (m_memory.readLineY() > 153){
          setLcdMode(GPUMode::OAM);
          reqInt = lcdStatus & ((byte)1 << 5);
          m_memory.writeLineY(0);
        }
      }
      break;

    case GPUMode::OAM:
      if (m_gpuClock >= GPUTimings::ACCESS_OAM){
        m_gpuClock = 0;
        setLcdMode(GPUMode::VRAM);
      }
      break;

    case GPUMode::VRAM:
      if (m_gpuClock >= GPUTimings::ACCESS_VRAM){
        m_gpuClock = 0;
        setLcdMode(GPUMode::H_BLANK);
        reqInt = lcdStatus & ((byte)1 << 3);

        renderScanLine();
      }
      break;
  }

  //Check for coincidence flag
  if (lineY == m_memory.readLYC()){
    lcdStatus = m_memory.readLcdStatus() | ((byte)1 << 2);

    if (lcdStatus & ((byte)1 << 6))
      reqInt = true;
  }
  else
    lcdStatus = m_memory.readLcdStatus() & (byte)0b11111011;

  if (reqInt)
    m_memory.requestInterrupt(1);

  m_memory.writeLcdStatus(lcdStatus);
}

void Gpu::setLcdMode(GPUMode mode) {
  byte status = m_memory.readLcdStatus();
  //Keep interrupt status
  status &= 0xFC;
  m_memory.writeLcdStatus(status | (mode & 0b11));
}

void Gpu::renderScanLine() {
  renderBackground();
}

void Gpu::renderBackground() {

  byte lcdControl = m_memory.readLcdControl();

  if (!(lcdControl & LCDControlFlags::BACKGROUND_DISPLAY))
    return;

  bool unsignedIndex = true;
  bool usingWindow = false;
  word tileData = 0;
  word backgroundMemory = 0;
  byte scrollX = m_memory.readScrollX();
  byte scrollY = m_memory.readScrollY();
  byte windowX = m_memory.readWindowX() - (byte)7;
  byte windowY = m_memory.readWindowY();
  byte lineY = m_memory.readLineY();

  if (lcdControl & LCDControlFlags::WINDOW_DISPLAY_ENABLE){
    if (windowY <= lineY)
      usingWindow = true;
  }
  else
    usingWindow = false;

  //Which tile data are we using
  if (lcdControl & LCDControlFlags::BACKGROUND_WINDOW_TILE_DATA_SELECT)
    tileData = 0x8000;
  else{
    tileData = 0x8800;
    unsignedIndex = false;
  }

  //Which background memory?
  if (usingWindow == false){
    if (lcdControl & LCDControlFlags::BACKGROUND_TILE_MAP_SELECT)
      backgroundMemory = 0x9C00;
    else
      backgroundMemory = 0x9800;
  }
  else{
    if (lcdControl & LCDControlFlags::WINDOW_TILE_MAP_SELECT)
      backgroundMemory = 0x9C00;
    else
      backgroundMemory = 0x9800;
  }

  byte yPos = 0;
  !usingWindow ? yPos = scrollY + lineY : yPos = lineY - windowY;

  word tileRow = ((word)(yPos / 8)) * (word)32;

  for (byte pixel = 0; pixel < 160; ++pixel){
    byte xPos = pixel + scrollX;

    if (usingWindow){
      if (pixel >= windowX)
        xPos = pixel - windowX;
    }
    word tileCol = (xPos / (byte)8);

    short tileNum = 0;

    if (unsignedIndex)
      tileNum = (byte)(m_memory.readVram(backgroundMemory + tileRow + tileCol));
    else
      tileNum = (char)(m_memory.readVram(backgroundMemory + tileRow + tileCol));

    word tileLocation = tileData;

    (unsignedIndex) ? tileLocation += (tileNum * 16) : tileLocation += ((tileNum + 128) * 16);

    word line = yPos % (byte)8;

    line *= 2;
    byte data1 = m_memory.readVram(tileLocation + line);
    byte data2 = m_memory.readVram(tileLocation + line + (word)1);

    int colorBit = xPos % 8;
    colorBit -= 7;
    colorBit *= -1;

    int colorNum = data2 & (1 << colorBit);
    colorNum >>= colorBit;
    colorNum <<= 1;
    colorNum |= ((data1 & (1 << colorBit)) >> colorBit);

    Color color = (Color)(colorNum);

    m_frameBuffer[lineY * SCREEN_WIDTH + pixel] = palette[getBackgroundPaletteShade(color)];
  }
}

Color Gpu::getBackgroundPaletteShade(Color color) {
  byte bgPaletteData = m_memory.readBackgroundPalette();
  if (color == Color::WHITE)
    return (Color)((bgPaletteData) & 0x3);
  if (color == Color::LIGHT_GRAY)
    return (Color)(((bgPaletteData) & 0xC) >> 2);
  if (color == Color::DARK_GRAY)
    return (Color)(((bgPaletteData) & 0x30) >> 4);
  if (color == Color::BLACK)
    return (Color)(((bgPaletteData) & 0xC0) >> 6);

  return Color::WHITE;
}