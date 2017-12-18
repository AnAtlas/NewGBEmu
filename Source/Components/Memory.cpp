//
// Created by derdro on 12/17/17.
//
#include "Memory.hpp"

Memory::Memory(bool runBios) : m_memory{0}, m_inBios(runBios),
  m_romRange(Cartridge::CartAddress::ROM_BANK0, Cartridge::CartAddress::ROM_BANK0_END),
    m_ramRange(Cartridge::CartAddress::RAM_BANK, Cartridge::CartAddress::RAM_BANK_END)
{

}

void Memory::linkCartridge(std::shared_ptr<Cartridge>cartridge) {
  m_cartridge = cartridge;
}

void Memory::writeByte(word address, byte value) {
  if (addressOnCartridge(address))
    m_cartridge->writeByte(address, value);
  else if (address == Address::LineY)
    value = 0;
  else if (address == Address::DivReg)
    value = 0;
  else if (address == Address::P1){
    value &= 0x30;
    value |= 0xC0;
    m_memory[address] &= 0b00001111;
    m_memory[address] |= value;
  }
  m_memory[address] = value;
}

byte Memory::readByte(word address) {
  if (addressOnCartridge(address) && ((m_inBios && address >= 0x1000) || !m_inBios))
    return m_cartridge->readByte(address);

  if (address == Address::P1){
    byte ret = 0b11000000;
    byte keyReq = m_memory[Address::P1];
    ret |= (keyReq & 0b00110000);
    if (!(keyReq & (1 << 5))){
      //Directionals selected, row 2
      ret |= (m_inputRow2 & 0xF);
    }
    else if (!(keyReq & (1 << 5))){
      ret |= (m_inputRow1 & 0xF);
    }
    return ret;
  }
  return m_memory[address];
}
bool Memory::addressOnCartridge(word address) {
  return m_romRange.contains(address) || m_ramRange.contains(address);
}