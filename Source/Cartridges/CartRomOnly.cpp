//
// Created by derdro on 12/14/17.
//
#include "CartRomOnly.hpp"

CartRomOnly::CartRomOnly(std::string romPath): Cartridge(romPath) {

}

bool CartRomOnly::loadCartridge() {
  return (loadRomBank0() && loadRomBankX(1));
}
byte CartRomOnly::readByte(word address) {
  if (address < 0x7FFF)
    return m_rom[address];
  else
    return 0xFF;
}

bool CartRomOnly::writeByte(word address, byte value) {
  return false;
}


