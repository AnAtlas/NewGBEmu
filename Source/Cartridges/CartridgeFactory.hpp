//
// Created by derdro on 12/14/17.
//

#ifndef GBEMU_CARTRIDGEFACTORY_HPP
#define GBEMU_CARTRIDGEFACTORY_HPP

#include <memory>
#include "Cartridge.hpp"
#include "CartMBC1.hpp"
#include "CartMBC3.hpp"
#include "CartRomOnly.hpp"

class CartridgeFactory
{
private:

public:
  CartridgeFactory(){};
  std::shared_ptr<Cartridge> generateCartridge(std::string romPath){
    std::shared_ptr<Cartridge> cartPtr = nullptr;
    byte romHeaderBuffer[0x150]{0};
    std::ifstream romFile(romPath, std::ios::binary);
    if (romFile.is_open()){
      romFile.read((char*)romHeaderBuffer, 0x150);
      Cartridge::CartType cartType = (Cartridge::CartType)romHeaderBuffer[Cartridge::CartAddress::CART_TYPE];
      RamModule::RamSize ramSize = (RamModule::RamSize)romHeaderBuffer[Cartridge::CartAddress::RAM_SIZE];
      if (cartType == Cartridge::CartType::ROM_ONLY)
        cartPtr = std::make_shared<CartRomOnly>(romPath);
      else if (cartType >= Cartridge::CartType::MBC1 && cartType <= Cartridge::CartType::MBC1_RAM_BATTERY)
        cartPtr = std::make_shared<CartMBC1>(cartType, romPath, ramSize);
      else if (cartType >= Cartridge::CartType::MBC3_TIMER_BATTERY && cartType <= Cartridge::CartType::MBC3_RAM_BATTERY)
        cartPtr = std::make_shared<CartMBC3>(cartType, romPath, ramSize);
      romFile.close();
    }
    return cartPtr;
  }
};
#endif //GBEMU_CARTRIDGEFACTORY_HPP
