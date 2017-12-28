//
// Created by derdro on 12/14/17.
//
#include "Cartridge.hpp"

Cartridge::Cartridge(std::string &romPath)
  : m_romPath(romPath),
   m_romRange(CartAddress::ROM_BANK0, CartAddress::ROM_BANKX_END),
    m_rom{}
{

}

bool Cartridge::loadRomBank0(){
  loadRomBankX(0);
}

bool Cartridge::loadRomBankX(word romBankIndex){
  bool retVal = false;

  std::ifstream romFile;
  romFile.open(m_romPath, std::ios::binary);
  if (romFile.is_open()){
    romFile.seekg(romBankIndex * 0x4000);
    if (romBankIndex == 0)
      romFile.read((char*)m_romBank0, 0x4000);
    else
      romFile.read((char*)m_romBankX, 0x4000);
    romFile.close();
    retVal = true;
  }
  else{
    std::cout << "Error Opening File: " << m_romPath << std::endl;
  }
  return retVal;
}

const std::string Cartridge::getRomName() const {
  char tempName[16];
  for (int i = 0; i < 16; i++)
    tempName[i] = (char)(m_romBank0[CartAddress::ROM_NAME + i]);
  return std::string(tempName);
}