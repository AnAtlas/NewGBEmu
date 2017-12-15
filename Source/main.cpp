#include <iostream>
#include "Cartridges/CartridgeFactory.hpp"

int main() {
  CartridgeFactory cartFact;


  CartridgePtr cart = cartFact.generateCartridge("T.gb");

  cart->loadCartridge();

  std::cout << "You are playing: " << cart->getRomName() << std::endl;

  cart->writeByte(0x00FF, 0x0A);
  cart->writeByte(0x5000, 0x08);
  std::cout << "Seconds: " << (int)cart->readByte(0xA001) << std::endl;

  cart->writeByte(0x6001,0);
  cart->writeByte(0x6001,1);

  std::cout << "Seconds: " << (int)cart->readByte(0xA001) << std::endl;
  if (!cart)
    std::cout << "ERROR" << std::endl;
  return 0;
}