//
// Created by derdro on 12/14/17.
//
#include "CartRomOnly.hpp"

CartRomOnly::CartRomOnly(std::string romPath): Cartridge(romPath) {

}

bool CartRomOnly::loadCartridge() {
  return (loadRomBank0() && loadRomBankX(1));
}

byte CartRomOnly::readByte(word address) const {
  if (m_romRange.contains(address))
    return m_rom[address];
  else
    return 0xFF;
}

void CartRomOnly::writeByte(word address, byte value) {

}


