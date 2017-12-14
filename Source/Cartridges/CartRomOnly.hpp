//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_CARTROMONLY_HPP
#define GBEMU_CARTROMONLY_HPP

#include "Cartridge.hpp"

class CartRomOnly : public Cartridge
{
private:

public:
  explicit CartRomOnly(std::string romPath);

  bool loadCartridge() override;
  byte readByte(word address) override;
  bool writeByte(word address, byte value) override;
};
#endif //GBEMU_CARTROMONLY_HPP
