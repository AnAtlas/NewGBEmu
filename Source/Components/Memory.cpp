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

byte Memory::readByte(word address) const {
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

void Memory::writeShort(word address, word value) {
  writeByte(address, (byte)(value & 0x00FF));
  writeByte(address + (word)1, (byte)(value & 0xFF00) >> 8);
}

word Memory::readShort(word address) const {
  return (word)readByte(address) | (word)(readByte(address + (word)1) << 8);
}

bool Memory::addressOnCartridge(word address) const {
  return m_romRange.contains(address) || m_ramRange.contains(address);
}

void Memory::requestInterrupt(byte bit) {
  writeByte(Address::IntFlags, readByte(Address::IntFlags) | ((byte)1 << bit));
}

//Cpu Functions
byte Memory::getIntFlags() const {
  return m_memory[Address::IntFlags];
}

void Memory::resetIntFlag(byte bitIndex) {
  byte val = ((byte)1 << bitIndex);
  val = ~val;
  val &= m_memory[Address::IntFlags];
  m_memory[Address::IntFlags] = val;
}

byte Memory::getIntsEnabled() const {
  return m_memory[Address::IeRegister];
}

//Gpu functions
byte Memory::readLcdStatus() const{
  return m_memory[Address::LcdStatus];
}

byte Memory::readLcdControl() const{
  return m_memory[Address::LcdControl];
}

byte Memory::readLineY() const{
  return m_memory[Address::LineY];
}

byte Memory::readLYC() const{
  return m_memory[Address::LYC];
}

byte Memory::readBackgroundPalette() const{
  return m_memory[Address::BackgroundPalette];
}

byte Memory::readObjectPalette0() const {
  return m_memory[Address::ObjectPalette0];
}

byte Memory::readObjectPalette1() const{
  return m_memory[Address::ObjectPalette1];
}

byte Memory::readOam(const byte index) const{
  return m_oam[index];
}

byte Memory::readVram(const byte index) const{
  return m_vRam[index];
}

byte Memory::readScrollX() const{
  return m_memory[Address::ScrollX];
}

byte Memory::readScrollY() const{
  return m_memory[Address::ScrollY];
}

byte Memory::readWindowX() const{
  return m_memory[Address::WindowX];
}

byte Memory::readWindowY() const{
  return m_memory[Address::WindowY];
}

void Memory::writeLcdStatus(byte value){
  m_memory[Address::LcdStatus] = value;
}
void Memory::writeLineY(byte value){
  m_memory[Address::LineY] = value;
}