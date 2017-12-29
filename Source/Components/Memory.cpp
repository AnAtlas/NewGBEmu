//
// Created by derdro on 12/17/17.
//
#include <cstring>
#include "Memory.hpp"
#include "../Utilities/Bios.hpp"

enum InterruptFlags{
  VBLANK = 1,
  LCD_STAT = 1 << 1,
  TIMER = 1 << 2,
  SERIAL = 1 << 3,
  JOYPAD = 1 << 4
};

Memory::Memory(bool runBios) : m_memory{0}, m_inBios(runBios), m_divRegister(0),
  m_romRange(Cartridge::CartAddress::ROM_BANK0, Cartridge::CartAddress::ROM_BANKX_END),
  m_ramRange(Cartridge::CartAddress::RAM_BANK, Cartridge::CartAddress::RAM_BANK_END),
  m_wRamRange(Address::Wram, Address::Wram + 0x1FFF),
  m_echoRange(Address::Echo, Address::Echo + 0x1DFF)
{
  memcpy(m_memory, bios, sizeof(bios));
  if (runBios) {
    m_memory[0xFF00] = 0xFF; //P1
    m_memory[0xFF05] = 0x00;
    m_memory[0xFF06] = 0x00;
    m_memory[0xFF07] = 0x00;
    m_memory[0xFF10] = 0x80;
    m_memory[0xFF11] = 0x00;
    m_memory[0xFF12] = 0x00;
    m_memory[0xFF14] = 0x00;
    m_memory[0xFF16] = 0x00;
    m_memory[0xFF17] = 0x00;
    m_memory[0xFF19] = 0x00;
    m_memory[0xFF1A] = 0x00;
    m_memory[0xFF1B] = 0x00;
    m_memory[0xFF1C] = 0x00;
    m_memory[0xFF1E] = 0x00;
    m_memory[0xFF20] = 0x00;
    m_memory[0xFF21] = 0x00;
    m_memory[0xFF22] = 0x00;
    m_memory[0xFF23] = 0x00;
    m_memory[0xFF24] = 0x00;
    m_memory[0xFF25] = 0x00;
    m_memory[0xFF26] = 0x00;
    m_memory[0xFF40] = 0x00; //LCDC
    m_memory[0xFF42] = 0x00; //SCY
    m_memory[0xFF43] = 0x00; //SCX
    m_memory[0xFF45] = 0x00; //LYC
    m_memory[0xFF47] = 0x00; //BGP
    m_memory[0xFF48] = 0x00; //OBP0
    m_memory[0xFF49] = 0x00; //OBP1
    m_memory[0xFF4A] = 0x00; //WY
    m_memory[0xFF4B] = 0x00; //WX
    m_memory[0xFFFF] = 0x00; //IE
  }
  else {
    m_memory[0xFF00] = 0xFF;
    m_memory[0xFF05] = 0x00;
    m_memory[0xFF06] = 0x00;
    m_memory[0xFF07] = 0x00;
    m_memory[0xFF10] = 0x80;
    m_memory[0xFF11] = 0xBF;
    m_memory[0xFF12] = 0xF3;
    m_memory[0xFF14] = 0xBF;
    m_memory[0xFF16] = 0x3F;
    m_memory[0xFF17] = 0x00;
    m_memory[0xFF19] = 0xBF;
    m_memory[0xFF1A] = 0x7F;
    m_memory[0xFF1B] = 0xFF;
    m_memory[0xFF1C] = 0x9F;
    m_memory[0xFF1E] = 0xBF;
    m_memory[0xFF20] = 0xFF;
    m_memory[0xFF21] = 0x00;
    m_memory[0xFF22] = 0x00;
    m_memory[0xFF23] = 0xBF;
    m_memory[0xFF24] = 0x77;
    m_memory[0xFF25] = 0xF3;
    m_memory[0xFF26] = 0xF1;
    m_memory[0xFF40] = 0x91; //LCDC
    m_memory[0xFF42] = 0x00; //SCY
    m_memory[0xFF43] = 0x00; //SCX
    m_memory[0xFF45] = 0x00; //LYC
    m_memory[0xFF47] = 0xFC; //BGP
    m_memory[0xFF48] = 0xFF; //OBP0
    m_memory[0xFF49] = 0xFF; //OBP1
    m_memory[0xFF4A] = 0x00; //WY
    m_memory[0xFF4B] = 0x00; //WX
    m_memory[0xFFFF] = 0x00; //IE
    m_divRegister = 0xABCC;
  }
}

void Memory::linkCartridge(std::shared_ptr<Cartridge>cartridge) {
  m_cartridge = cartridge;
}

void Memory::writeByte(word address, byte value) {
  if (addressOnCartridge(address)) {
    m_cartridge->writeByte(address, value);
    return;
  }
  else if (m_wRamRange.contains(address)) {
    if (address <= 0xDDFF)
      m_memory[address + 0x2000] = value;
  }
  else if (m_echoRange.contains(address))
    m_memory[address - 0x2000] = value;
  else if (address == Address::LineY)
    value = 0;
  else if (address == Address::DivReg){
    m_divRegister = 0;
    return;
  }
  else if (address == Address::DMA) {
    word newAddress = (word) value << 8;
    for (word i = 0; i < 0xA0; ++i)
      m_memory[0xFE00 + i] = m_cartridge->readByte(newAddress + i);
    return;
  }
  else if (address == Address::ExitBios){
    m_inBios = false;
    return;
  }
  else if (address == Address::P1){
    value &= 0x30;
    value |= 0xC0;
    m_memory[address] &= 0b00001111;
    m_memory[address] |= value;
    return;
  }

  m_memory[address] = value;
}

byte Memory::readByte(word address) const {
  if (addressOnCartridge(address)){
    if (!m_inBios || address >= 0x100)
      return m_cartridge->readByte(address);
  }
  if (address == Address::DivReg)
    return (byte)((m_divRegister >> 8) & (word)0x00FF);
  return m_memory[address];
}

void Memory::writeShort(word address, word value) {
  writeByte(address, (byte)(value & 0x00FF));
  writeByte(address + (word)1, (byte)((value & 0xFF00) >> 8));
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

byte Memory::readOam(word address) const{
  return m_memory[address];
}

byte Memory::readVram(word address) const{
  return m_memory[address];
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

void Memory::requestVBlankInterrupt() {
  writeByte(Address::IntFlags, readByte(Address::IntFlags) | InterruptFlags::VBLANK);
}

void Memory::requestLcdStatInterrupt() {
  writeByte(Address::IntFlags, readByte(Address::IntFlags) | InterruptFlags::LCD_STAT);
}

//Timer functions
void Memory::incDivRegister(byte ticks) {
  m_divRegister += ticks;
}

byte Memory::incTimerCounter() {
  return m_memory[Address::TimerCounter]++;
}

void Memory::writeTimerCounter(byte value) {
  m_memory[Address::TimerCounter] = value;
}

byte Memory::readTimerCounter() {
  return m_memory[Address::TimerCounter];
}

byte Memory::readTimerModulo() {
  return m_memory[Address::TimerModulo];
}

byte Memory::readTimerControl() {
  return m_memory[Address::TimerControl];
}

void Memory::requestTimerInterrupt() {
  writeByte(Address::IntFlags, readByte(Address::IntFlags) | InterruptFlags::TIMER);
}

//Input functions
byte Memory::readP1(){
  return m_memory[Address::P1];
}

void Memory::writeP1Inputs(byte value) {
  value &= 0x0F;
  byte p1 = readP1();
  p1 &= 0xF0;
  m_memory[Address::P1] = p1 | value;
}

void Memory::requestInputInterrupt() {
  writeByte(Address::IntFlags, readByte(Address::IntFlags) | InterruptFlags::JOYPAD);
}

