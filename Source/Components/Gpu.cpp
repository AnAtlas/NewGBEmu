//
// Created by derdro on 12/19/17.
//
#include <cstring>
#include <cassert>
#include "Gpu.hpp"

const RGB Palette[4] = {
  { 255,255,255, 255 },
  { 192,192,192, 255 },
  {  96, 96,96, 255  },
  {  0 , 0 , 0, 255  }
};

enum LcdStat{
  LYC_EQUALS_LY = 1 << 2,
  H_BLANK_INT = 1 << 3,
  V_BLANK_INT = 1 << 4,
  OAM_INT = 1 << 5,
  LYC_LY_INT = 1 << 6
};

Gpu::Gpu(sf::RenderWindow& window, GpuMemoryInterface& memory)
  : m_window(window),m_memory(memory), m_gpuMode(GPUMode::H_BLANK), m_sprite(),
    m_spriteWidth(8), m_spriteHeight(8), m_spriteLimit(40)
{
  for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
    m_frameBuffer[i] = Palette[Color::WHITE];

  m_texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
  m_texture.setSmooth(false);
  m_texture.update((const sf::Uint8*)m_frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  m_sprite.setTexture(m_texture);
  m_sprite.setScale(window.getSize().x / SCREEN_WIDTH, window.getSize().y / SCREEN_HEIGHT);
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
        m_gpuClock -= GPUTimings::H_BLANK;
        m_memory.writeLineY(m_memory.readLineY() + (byte)1);
        if (m_memory.readLineY() == 144){
          //Enter VBlank
          setLcdMode(GPUMode::V_BLANK);
          m_memory.requestVBlankInterrupt();

          reqInt = (lcdStatus & LcdStat::V_BLANK_INT);

          //Push framebuffer to screen
          m_texture.update((const sf::Uint8*)m_frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT,0,0);
          m_window.clear();
          m_window.draw(m_sprite);
          m_window.display();
        }
        else{
          setLcdMode(GPUMode::OAM);
          reqInt = (lcdStatus & LcdStat::OAM_INT);
        }
      }
      break;

    case GPUMode::V_BLANK:
      if (m_gpuClock >= GPUTimings::V_BLANK){
        m_gpuClock -= GPUTimings::V_BLANK;
        m_memory.writeLineY(m_memory.readLineY() + (byte)1);
        if (m_memory.readLineY() > 153){
          setLcdMode(GPUMode::OAM);
          reqInt = (lcdStatus & LcdStat::OAM_INT);
          m_memory.writeLineY(0);
          m_frameDone = true;
        }
      }
      break;

    case GPUMode::OAM:
      m_frameDone = false;
      if (m_gpuClock >= GPUTimings::ACCESS_OAM){
        m_gpuClock -= GPUTimings::ACCESS_OAM;
        setLcdMode(GPUMode::VRAM);
      }
      break;

    case GPUMode::VRAM:
      if (m_gpuClock >= GPUTimings::ACCESS_VRAM){
        m_gpuClock -= GPUTimings::ACCESS_VRAM;
        setLcdMode(GPUMode::H_BLANK);
        reqInt = (lcdStatus & LcdStat::H_BLANK_INT);

        renderScanLine();
      }
      break;
  }

  //Check for coincidence flag
  if (lineY == m_memory.readLYC()){
    lcdStatus = m_memory.readLcdStatus() | LcdStat::LYC_EQUALS_LY;

    if (lcdStatus & LcdStat::LYC_LY_INT)
      reqInt = true;
  }
  else
    lcdStatus = m_memory.readLcdStatus() & ~LcdStat::LYC_EQUALS_LY;

  if (reqInt)
    m_memory.requestLcdStatInterrupt();

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
  renderSprites();
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
  int windowX = m_memory.readWindowX() - (byte)7;
  byte windowY = m_memory.readWindowY();
  byte lineY = m_memory.readLineY();

  if (lcdControl & LCDControlFlags::WINDOW_DISPLAY_ENABLE){
    if (windowY <= lineY)
      usingWindow = true;
  }

  //Which tile data are we using
  if (lcdControl & LCDControlFlags::BACKGROUND_WINDOW_TILE_DATA_SELECT)
    tileData = 0x8000;
  else{
    tileData = 0x8800;
    unsignedIndex = false;
  }

  //Which background memory?
  if (!usingWindow){
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

    auto color = (Color)(colorNum);

    m_frameBuffer[lineY * SCREEN_WIDTH + pixel] = Palette[getBackgroundPaletteShade(color)];
  }
}

void Gpu::renderSprites() {
  byte lcdControl = m_memory.readLcdControl();
  byte lineY = m_memory.readLineY();

  //Check if sprites are enabled
  if (!(lcdControl & LCDControlFlags::SPRITE_DISPLAY_ENABLE))
    return;

  m_spriteHeight = (lcdControl & LCDControlFlags::SPRITE_SIZE) ? (byte)16 : (byte)8;

  byte index = 0;
  int yPos = 0;
  int xPos = 0;
  byte charCode = 0;
  byte attrData = 0;

  bool priority = false;
  bool yFlip = false;
  bool xFlip = false;
  bool palette = false; //Can be object palette 0 or 1 depending on the palette sprite attribute

  //Gameboy only has space for 40 sprites at a time
  for (int i = 0; i < m_spriteLimit; i++){
    //Each sprite has 4 bytes of data
    index = (byte)(i*4);
    yPos = m_memory.readOam(index) - (byte)16; //the - 16 just is

    //Check if this scanline will even touch this sprite
    if (lineY < yPos || lineY >= (yPos + m_spriteHeight))
      continue;

    xPos = m_memory.readOam(index + (byte)1) - (byte)8; //the - 8 just is
    //Check if Sprite is on screen
    if (xPos < -7 || xPos >= SCREEN_WIDTH)
      continue;

    charCode = m_memory.readOam(index + (byte)2); //Specifies tile number 0x00-0xFF from tile memory at 0x8000 - 0x8FFF
    attrData = m_memory.readOam(index + (byte)3); //Flags according to the sprite

    //If sprites are 16 pixels tall, sprites take up twice the amount of ram, so drop the last bit so only even number
    //Of tiles are left
    if (m_spriteHeight == 16)
      charCode &= (~1);

    priority = (attrData & SpriteAttribute::PRIORITY);
    yFlip = (attrData & SpriteAttribute::Y_FLIP);
    xFlip = (attrData & SpriteAttribute::X_FLIP);
    palette = (attrData & SpriteAttribute::PALETTE);// ? (word)0xFF49 :(word)0xFF48;

    //Line is the line in the sprite, each sprite is 16 bytes, for 8 lines, so this will always be even
    byte line = (yFlip) ? ((((lineY - yPos - m_spriteHeight) + (byte)1) * (char)-1) * (byte)2) : ((lineY - yPos) * (byte)2);
    byte pixelData1 = m_memory.readVram((word)0x8000 + ((word)charCode * (word)16) + line);
    byte pixelData2 = m_memory.readVram((word)0x8000 + ((word)charCode * (word)16) + line + (word)1);

    //Sprites at position (0,0) are not drawn
    if (xPos == 0 && yPos == 0)
      continue;

    for (byte pixel = 0; pixel < 8; pixel++){
      byte x = xPos + pixel;

      if (x >= 160)
        continue;
      byte spritePixel = (xFlip) ? (pixel - (byte)7) * (char)-1 : pixel;
      bool backgroundPixelIsWhite = getPixelAt(x, lineY) == Palette[Color::WHITE];
      //Color num is the corresponding pair of bits from pixelData1 and pixelData2
      byte colorNum = (getBit(pixelData1, (byte)7-spritePixel)) | (getBit(pixelData2, (byte)7-spritePixel) << 1);

      //ColorNum of 0 means pixel is transparent
      if (!colorNum)
        continue;
      //with priority 0x01 if the background pixel isn't white, the sprite isn't drawn
      if (priority && !backgroundPixelIsWhite)
        continue;
      RGB pixelColor = Palette[getObjectPaletteShade(palette, (Color)colorNum)];
      m_frameBuffer[lineY * SCREEN_WIDTH + x] = pixelColor;
    }
  }
}

RGB Gpu::getPixelAt(byte x, byte y) {
  return m_frameBuffer[(y * SCREEN_WIDTH + x)];
}

Color Gpu::getObjectPaletteShade(bool palette1, Color color){
  byte objPaletteData = (palette1) ? m_memory.readObjectPalette1() : m_memory.readObjectPalette0();
  switch (color){
    case Color::WHITE: return (Color)((objPaletteData) & 0x3);
    case Color::LIGHT_GRAY: return (Color)(((objPaletteData) & 0xC) >> 2);
    case Color::DARK_GRAY: return (Color)(((objPaletteData) & 0x30) >> 4);
    case Color::BLACK: return (Color)(((objPaletteData) & 0xC0) >> 6);
    default: assert(false);
  }
}

Color Gpu::getBackgroundPaletteShade(Color color) {
  byte bgPaletteData = m_memory.readBackgroundPalette();
  switch (color){
    case Color::WHITE: return (Color)((bgPaletteData) & 0x3);
    case Color::LIGHT_GRAY: return (Color)(((bgPaletteData) & 0xC) >> 2);
    case Color::DARK_GRAY: return (Color)(((bgPaletteData) & 0x30) >> 4);
    case Color::BLACK: return (Color)(((bgPaletteData) & 0xC0) >> 6);
    default: assert(false);
  }
}

bool Gpu::frameDone() {
  return m_frameDone;
}

byte Gpu::getBit(byte value, byte bitIndex) {
  if (value & (1 << bitIndex))
    return 1;
  return 0;
}