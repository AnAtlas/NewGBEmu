//
// Created by derdro on 12/18/17.
//
#include "Cpu.hpp"

Cpu::Cpu(CpuMemoryInterface& memory): m_memory(memory){

}

byte Cpu::step() {
  m_clock.m = 0;
  m_clock.t = 0;
  if (!m_halted){
    byte nextOp = m_memory.readByte(m_registers.pc);

    if (m_cbMode)
      executeExtOpcode(nextOp);
    else
      executeOpcode(nextOp);
  }
}

void Cpu::setFlag(Flags flag) {
  m_registers.f |= flag;
}

void Cpu::clearFlag(Flags flag){
  m_registers.f& = ~flag;
}

bool Cpu::checkFlag(Flags flag){
  return (m_registers.f&  flag);
}

void Cpu::clearAllFlags() {
  m_registers.f = 0;
}

//Load next byte into register Flags(-,-,-,-)
void Cpu::byteLoad(byte& reg) {
  reg = m_memory.readByte((word)(m_registers.pc+1));
  m_clock.m = 2;
  m_clock.t = 8;
}

//Load byte from reg2 to reg1 Flags(-,-,-,-)
void Cpu::byteLoad(byte& reg1, byte& reg2) {
  reg1 = reg2;
  m_clock.m = 1;
  m_clock.t = 4;
}
//Load byte from address into register Flags(-,-,-,-)
void Cpu::byteLoad(byte& reg, word& address) {
  reg = m_memory.readByte(address);
  m_clock.m = 1;
  m_clock.t = 8;
}

//Load byte from IO Port addresses 0xFFxx Flags(-,-,-,-)
void Cpu::byteLoadIoPort(byte& reg, byte& address) {
  word add = (word)0xFF00 + address;
  reg = m_memory.readByte(add);
  m_clock.m = 1;
  m_clock.t = 8;
}

//Load next word into register Flags(-,-,-,-)
void Cpu::wordLoad(word& reg){
  reg = m_memory.readShort((word)(m_registers.pc+1));
  m_clock.m = 3;
  m_clock.t = 12;
}

//Write byte into memory Flags(-,-,-,-)
void Cpu::writeMemoryByte(word& address, byte& reg) {
  m_memory.writeByte(address, reg);
  m_clock.m = 1;
  m_clock.t = 8;
}

//Write register into IO Port address 0xFFxx Flags(-,-,-,-)
void Cpu::writeIoPortByte(byte& address, byte& reg) {
  word add = (word)0xFF00 + address;
  m_memory.writeByte(add, reg);
  m_clock.m = 1;
  m_clock.t = 8;
}

//Increment register Flags(Z,0,H,-)
void Cpu::inc(byte& reg){
  (reg&  0xF)==0xF ? setFlag(Flags::C) : clearFlag(Flags::C);
  reg++;
  clearFlag(Flags::S);
  reg ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_clock.m = 1;
  m_clock.t = 4;
}

//Increment register Flags(-,-,-,-)
void Cpu::inc(word& reg){
  reg++;
  m_clock.m = 1;
  m_clock.t = 8;
}

//Decrement register Flags(Z,1,H,-)
void Cpu::dec(byte& reg){
  (reg&  0xF) == 0 ? setFlag(Flags::H) : clearFlag(Flags::H);
  reg--;
  (reg) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  setFlag(Flags::S);
  m_clock.m = 1;
  m_clock.t = 4;
}

//Decrement register Flags(-,-,-,-)
void Cpu::dec(word& reg) {
  reg--;
  m_clock.m = 1;
  m_clock.t = 8;
}

//Add byte register into register.a Flags(Z,0,H,C)
void Cpu::add(byte& reg) {
  clearFlag(Flags::S);
  ((m_registers.a & 0xF) + (reg & 0xF)) & 0x10 ? setFlag(Flags::H) : clearFlag(Flags::H);
  (m_registers.a + reg) & 0x100 ? setFlag(Flags::C) : clearFlag(Flags::C);
  (m_registers.a + reg) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_registers.a += reg;
  m_clock.m = 1;
  m_clock.t = 4;
}

//Add byte at register with register.a Flags(Z,0,H,C)
void Cpu::add(word& reg){
  byte val = m_memory.readByte(m_registers.hl);
  add(val);
  m_clock.t = 8;
}

//Add word registers Flags(-,0,H,C)
void Cpu::add(word& reg1, word& reg2) {
  clearFlag(Flags::S);
  ((reg1&  0xFFF) + (reg2&  0xFFF))&  0x1000 ? setFlag(Flags::H) : clearFlag(Flags::H);
  (reg1 + reg2)&  0x10000 ? setFlag(Flags::C) : clearFlag(Flags::C);
  reg1 += reg2;
  m_clock.m = 1;
  m_clock.t = 8;
}

//Add byte register into register.a with Carry Flags(Z,0,H,C)
void Cpu::adc(byte& reg) {
  word tempReg = m_registers.a + reg + (checkFlag(Flags::C) ? (byte)1 : (byte)0);
  clearFlag(Flags::S);
  (tempReg & 0xFF00) ? setFlag(Flags::C) : clearFlag(Flags::C);
  (m_registers.a ^ reg ^ (tempReg & 0xFF)) & 0x10 ? setFlag(Flags::H) : clearFlag(Flags::H);
  (tempReg & 0xFF) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_registers.a = (byte)(tempReg & 0xFF);
  m_clock.m = 1;
  m_clock.t = 4;
}

//Add byte at register with register a with Carry Flags(Z,0,H,C)
void Cpu::adc(word& reg) {
  byte val = m_memory.readByte(m_registers.hl);
  adc(val);
  m_clock.t = 8;
}

//Subtract register from/into register.a Flags(Z,1,H,C)
void Cpu::sub(byte& reg) {
  (reg > m_registers.a) ? setFlag(Flags::C) : clearFlag(Flags::C);
  ((reg & 0xF) > (m_registers.a & 0xF)) ? setFlag(Flags::H) : clearFlag(Flags::H);
  setFlag(Flags::S);
  m_registers.a -= reg;
  (m_registers.a) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_clock.m = 1;
  m_clock.t = 4;
}

//Subtract value at register from register a Flags(Z,1,H,C)
void Cpu::sub(word& reg) {
  byte val = m_memory.readByte(m_registers.hl);
  sub(val);
  m_clock.t = 8;
}

//Subtract register from/into register.a with Carry Flags(Z,1,H,C)
void Cpu::sbc(byte& reg) {
  word tempReg = m_registers.a - reg - (checkFlag(Flags::C) ? (byte)1 : (byte)0);
  setFlag(Flags::S);
  (tempReg & 0xFF00) ? setFlag(Flags::C) : clearFlag(Flags::C);
  ((m_registers.a ^ reg ^ (tempReg & 0xFF)) & 0x10) ? setFlag(Flags::H) : clearFlag(Flags::H);
  m_registers.a = (byte)(tempReg & 0xFF);
  (m_registers.a) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_clock.m = 1;
  m_clock.t = 4;
}

//Subtract value at register from register.a with carry Flags(Z,1,H,C)
void Cpu::sbc(word& reg) {
  byte val = m_memory.readByte(m_registers.hl);
  sbc(val);
  m_clock.t = 8;
}

//And register with/into register.a Flags(Z,0,1,0)
void Cpu::And(byte& reg) {
  clearFlag(Flags::S);
  clearFlag(Flags::C);
  setFlag(Flags::H);
  (m_registers.a &= reg) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_clock.m = 1;
  m_clock.t = 4;
}

//And value at register with reg a Flags(Z,0,1,0)
void Cpu::And(word& reg) {
  byte val = m_memory.readByte(reg);
  And(val);
  m_clock.t = 8;
}

//xor register with/into register.a Flags(Z,0,0,0)
void Cpu::Xor(byte& reg) {
  clearAllFlags();
  !(m_registers.a ^= reg) ? setFlag(Flags::Z);
  m_clock.m = 1;
  m_clock.t = 4;
}

void Cpu::Xor(word& reg) {
  byte val = m_memory.readByte(reg);
  Xor(val);
  m_clock.t = 8;
}

//or register with/into register.a Flags(Z,0,0,0)
void Cpu::Or(byte& reg) {
  clearAllFlags();
  !(m_registers.a |= reg) ? setFlag(Flags::Z);
  m_clock.m = 1;
  m_clock.t = 4;
}

void Cpu::Or(word& reg) {
  byte val = m_memory.readByte(reg);
  Or(val);
  m_clock.t = 8;
}
//compare register with register.a Flags(Z,1,H,C)
void Cpu::cp(byte& reg) {
  setFlag(Flags::S);
  m_registers.a < reg ? setFlag(Flags::C) : clearFlag(Flags::C);
  ((m_registers.a & 0xF) < (reg & 0xF)) ? setFlag(Flags::H) : clearFlag(Flags::H);
  m_registers.a == reg ? setFlag(Flags::Z) : clearFlag(Flags::Z);
  m_clock.m = 1;
  m_clock.t = 4;
}

//compare value at reg with register.a Flags(Z,1,H,C)
void Cpu::cp(word& reg) {
  byte val = m_memory.readByte(reg);
  cp(val);
  m_clock.t = 8;
}

//Jump relative to PC if conditions are met
void Cpu::jr(bool check, Flags flag, bool condition) {
  byte jump = m_memory.readByte(m_registers.pc+(word)1);

  if (!check){
    m_registers.pc += jump;
    m_clock.m = 0;
    m_clock.t = 12;
  }
  if (check){
    if ((checkFlag(flag) && condition) || (!checkFlag(flag) && !condition)) {
      m_registers.pc += m_memory.readByte(m_registers.pc + (word) 1);
      m_clock.m = 0;
      m_clock.t = 12;
    }
  }
  m_clock.m = 2;
  m_clock.t = 8;
}