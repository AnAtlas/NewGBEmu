//
// Created by derdro on 12/14/17.
//
#include "Cartridge.hpp"

bool Cartridge::loadRomBank0(){
  loadRomBankX(0);
};

bool Cartridge::loadRomBankX(byte romBankIndex){
  bool retVal = false;

  std::basic_fstream<byte> romFile;
  romFile.open(m_romPath, std::ios::in | std::ios::binary);
  if (romFile.is_open()){
    romFile.seekp(romBankIndex * 0x4000);
    if (romBankIndex == 0)
      romFile.read(m_romBank0, 0x4000);
    else
      romFile.read(m_romBankX, 0x4000);
    romFile.close();
    retVal = true;
  }
  else{
    std::cout << "Error Opening File: " << m_romPath << std::endl;
  }
  return retVal;
};

const std::string Cartridge::getRomName() const {
  char tempName[16];
  for (int i = 0; i < 16; i++)
    tempName[i] = (char)(m_romBank0[CartAddress::ROM_NAME + i]);
  return std::string(tempName);
};