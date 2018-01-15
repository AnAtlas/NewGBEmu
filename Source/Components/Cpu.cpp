//
// Created by derdro on 12/18/17.
//
#include <iostream>
#include <cassert>
#include <iomanip>
#include "Cpu.hpp"
#include "Memory.hpp"

//#define DEBUG 1

Cpu::Cpu(CpuMemoryInterface& memory, bool runBios)
  :m_memory(memory), m_pendingMasterInterruptEnable(false), m_halted(false), m_cbMode(false), m_stopped(false)
{
  initializeRegisters();
  if (runBios)
    m_registers.pc = 0;
#ifdef DEBUG
  logFile.open("MYLOGFILE", std::ios::out);
#endif
}

Cpu::~Cpu(){
#ifdef DEBUG
  logFile.close();
#endif
}

byte Cpu::step() {
  m_clock.ticks = 0;
  opsRan++;
  if (!m_halted){
    if (m_registers.pc == 0xfe)
      opsRan = 0;
#ifdef DEBUG
    std::cout << std::hex << std::setfill('0') << std::setw(10) << opsRan << "  ";
    std::cout << std::hex << std::setfill('0') << std::setw(4) << (int) m_registers.pc;
    //logFile << std::hex << (int) m_registers.pc;
#endif
    byte nextOp = readByteFromPC();
#ifdef DEBUG
    std::cout << std::hex <<std::setfill('0') <<  " OP = " << std::setw(4) << (int)nextOp << " AF = " << std::setw(4) << (int)m_registers.af << " BC = " << std::setw(4) << (int)m_registers.bc << " DE = " << std::setw(4) << (int)m_registers.de << " HL = " << std::setw(4) << (int)m_registers.hl << " SP = " << std::setw(4) << (int)m_registers.sp;
    //logFile << std::hex <<  " OP = " << (int)nextOp << " AF = " << (int)m_registers.af << " BC = " << (int)m_registers.bc << " DE = " << (int)m_registers.de << " HL = " << (int)m_registers.hl;

    std::cout << "    Z:" << checkFlag(Flags::Z) << "   S:" << checkFlag(Flags::S) << "   C:" << checkFlag(Flags::C) << "   H:" << checkFlag(Flags::H) << std::endl;
    //std::cout << std::endl;
#endif
    (m_cbMode) ? executeExtOpcode(nextOp) : executeOpcode(nextOp);
  }
  else
    m_clock.ticks = 4;

  checkInterrupts();
  return m_clock.ticks;
}

byte Cpu::readByteFromPC() {
  m_registers.pc++;
  return m_memory.readByte(m_registers.pc-(word)1);
}

word Cpu::readWordFromPC() {
  m_registers.pc+=2;
  return m_memory.readShort(m_registers.pc-(word)2);
}

void Cpu::initializeRegisters() {
  m_registers.af = 0x01B0;
  m_registers.bc = 0x0013;
  m_registers.de = 0x00D8;
  m_registers.hl = 0x014D;
  m_registers.pc = 0x0100;
  m_registers.sp = 0xFFFE;
}

void Cpu::checkInterrupts() {
  //Enabling interrupts happens after the next opcode is finished
  if (m_pendingMasterInterruptEnable){
    if (m_memory.readByte(m_registers.pc -(byte)1) != 0xFB){
      m_pendingMasterInterruptEnable = false;
      m_masterInterruptEnabled = true;
    }
  }

  if (m_masterInterruptEnabled || m_halted){
    byte flags = m_memory.getIntFlags();
    if (flags){
      //Interrupts with lower bit have higher priority
      //Ex. Vblank = 0, joypad = 4, Vblank happens first
      byte enabledInts = m_memory.getIntsEnabled();
      for (byte bit = 0; bit < 8; bit++){
        if (flags & (1 << bit)){
          if (enabledInts & (1 << bit)){
            serviceInterrupt(bit);
          }
        }
      }
    }
  }
}

void Cpu::serviceInterrupt(byte bit) {
  m_halted = false;
  if (!m_masterInterruptEnabled)
    return;
  if (m_cbMode){
    m_registers.pc--;
    m_cbMode = false;
  }
  pushWordToStack(m_registers.pc);

  switch(bit){
    case 0: m_registers.pc = Address::IntVBlank;break;
    case 1: m_registers.pc = Address::IntLCDState;break;
    case 2: m_registers.pc = Address::IntTimer;break;
    case 3: m_registers.pc = Address::IntSerial;break;
    case 4: m_registers.pc = Address::IntJoypad;break;
    default: assert(false);break;
  }
  m_masterInterruptEnabled = false;
  m_memory.resetIntFlag(bit);
  //Add twenty ticks to the current clock to account for the interrupt
  m_clock.ticks += 20;
}


void Cpu::pushWordToStack(word value) {
  m_registers.sp -= 2;
  m_memory.writeShort(m_registers.sp, value);
}

word Cpu::popWordFromStack() {
  word val = m_memory.readShort(m_registers.sp);
  m_registers.sp += 2;
  return val;
}

void Cpu::setFlag(Flags flag) {
  m_registers.f |= flag;
}

void Cpu::clearFlag(Flags flag){
  m_registers.f &= ~flag;
}

bool Cpu::checkFlag(Flags flag){
  return (m_registers.f&  flag);
}

void Cpu::clearAllFlags() {
  m_registers.f = 0;
}

//Null instruction, means error occurred
void Cpu::null(byte opcode) {
  std::cout << std::hex << "ERROR: Unknown OPCode - " << (int)opcode << std::endl;
}
//Nop Instruction do nothing
void Cpu::nop() {
  m_clock.ticks = 4;
}

//Stop the cpu til an interrupt occurs
void Cpu::stop() {
  m_stopped = true;
  m_clock.ticks = 4;
}

//Halt the cpu
void Cpu::halt() {
  m_halted = true;
  m_clock.ticks = 4;
}

//Disable interrupts after the next opcode
void Cpu::di() {
  m_masterInterruptEnabled = false;
  m_clock.ticks = 4;
}

//Next Opcode is an extended opcode
void Cpu::cb() {
  m_cbMode = true;
  m_clock.ticks = 4;
}

//Enable interrupts after the next opcode
void Cpu::ei() {
  m_pendingMasterInterruptEnable = true;
  m_clock.ticks = 4;
}
//Load next byte into register Flags(-,-,-,-)
void Cpu::byteLoad(byte& reg) {
  reg = readByteFromPC();
  m_clock.ticks = 8;
}

//Load byte from reg2 to reg1 Flags(-,-,-,-)
void Cpu::byteLoad(byte& reg1, byte& reg2) {
  reg1 = reg2;
  m_clock.ticks = 4;
}
//Load byte from address into register Flags(-,-,-,-)
void Cpu::byteLoad(byte& reg, word& address) {
  reg = m_memory.readByte(address);
  m_clock.ticks = 8;
}

//Load byte from IO Port addresses 0xFFxx Flags(-,-,-,-)
void Cpu::byteLoadIoPort(byte& reg, byte& address) {
  word add = (word)0xFF00 + address;
  reg = m_memory.readByte(add);
  m_clock.ticks = 8;
}

//Load next word into register Flags(-,-,-,-)
void Cpu::wordLoad(word& reg){
  reg = readWordFromPC();
  m_clock.ticks = 12;
}

//Write byte into memory Flags(-,-,-,-)
void Cpu::writeMemoryByte(word& address, byte& reg) {
  m_memory.writeByte(address, reg);
  m_clock.ticks = 8;
}

//Write register into IO Port address 0xFFxx Flags(-,-,-,-)
void Cpu::writeIoPortByte(byte& address, byte& reg) {
  word add = (word)0xFF00 + address;
  m_memory.writeByte(add, reg);
  m_clock.ticks = 8;
}

//Increment register Flags(Z,0,H,-)
void Cpu::inc(byte& reg){
  ((reg & 0xF) == 0xF) ? setFlag(Flags::H) : clearFlag(Flags::H);
  reg++;
  clearFlag(Flags::S);
  reg ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_clock.ticks = 4;
}

//Increment register Flags(-,-,-,-)
void Cpu::inc(word& reg){
  reg++;
  m_clock.ticks = 8;
}

//Decrement register Flags(Z,1,H,-)
void Cpu::dec(byte& reg){
  ((reg & 0xF) == 0) ? setFlag(Flags::H) : clearFlag(Flags::H);
  reg--;
  (reg) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  setFlag(Flags::S);
  m_clock.ticks = 4;
}

//Decrement register Flags(-,-,-,-)
void Cpu::dec(word& reg) {
  reg--;
  m_clock.ticks = 8;
}

//Add next byte into register a Flags(Z,0,H,C)
void Cpu::add() {
  byte value = readByteFromPC();
  add(value);
  m_clock.ticks = 8;
}

//Add byte register into register.a Flags(Z,0,H,C)
void Cpu::add(byte& reg) {
  clearFlag(Flags::S);
  ((m_registers.a & 0xF) + (reg & 0xF)) & 0x10 ? setFlag(Flags::H) : clearFlag(Flags::H);
  (m_registers.a + reg) & 0x100 ? setFlag(Flags::C) : clearFlag(Flags::C);
  (byte)(m_registers.a + reg) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_registers.a += reg;
  m_clock.ticks = 4;
}

//Add byte at register with register.a Flags(Z,0,H,C)
void Cpu::add(word& reg){
  byte val = m_memory.readByte(reg);
  add(val);
  m_clock.ticks = 8;
}

//Add word registers Flags(-,0,H,C)
void Cpu::add(word& reg1, word& reg2) {
  clearFlag(Flags::S);
  ((reg1 & 0xFFF) + (reg2 & 0xFFF)) & 0x1000 ? setFlag(Flags::H) : clearFlag(Flags::H);
  (reg1 + reg2) &  0x10000 ? setFlag(Flags::C) : clearFlag(Flags::C);
  reg1 += reg2;
  m_clock.ticks = 8;
}

//Add byte register into register.a with Carry Flags(Z,0,H,C)
void Cpu::adc(){
  byte value = readByteFromPC();
  adc(value);
  m_clock.ticks = 8;
}

//Add byte register into register.a with Carry Flags(Z,0,H,C)
void Cpu::adc(byte& reg) {
  word tempReg = m_registers.a + reg + (checkFlag(Flags::C) ? (byte)1 : (byte)0);
  clearFlag(Flags::S);
  (tempReg & 0xFF00) ? setFlag(Flags::C) : clearFlag(Flags::C);
  (m_registers.a ^ reg ^ (tempReg & 0xFF)) & 0x10 ? setFlag(Flags::H) : clearFlag(Flags::H);
  (tempReg & 0xFF) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_registers.a = (byte)(tempReg & 0xFF);
  m_clock.ticks = 4;
}

//Add byte at register with register a with Carry Flags(Z,0,H,C)
void Cpu::adc(word& reg) {
  byte val = m_memory.readByte(m_registers.hl);
  adc(val);
  m_clock.ticks = 8;
}

//Subtract next byte from/into register.a Flags(Z,1,H,C)
void Cpu::sub() {
  byte value = readByteFromPC();
  sub(value);
  m_clock.ticks = 8;
}

//Subtract register from/into register.a Flags(Z,1,H,C)
void Cpu::sub(byte& reg) {
  (reg > m_registers.a) ? setFlag(Flags::C) : clearFlag(Flags::C);
  ((reg & 0xF) > (m_registers.a & 0xF)) ? setFlag(Flags::H) : clearFlag(Flags::H);
  setFlag(Flags::S);
  m_registers.a -= reg;
  (m_registers.a) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_clock.ticks = 4;
}

//Subtract value at register from register a Flags(Z,1,H,C)
void Cpu::sub(word& reg) {
  byte val = m_memory.readByte(m_registers.hl);
  sub(val);
  m_clock.ticks = 8;
}

//Subtract next byte from/into register.a with Carry Flags(Z,1,H,C)
void Cpu::sbc() {
  byte value = readByteFromPC();
  sbc(value);
  m_clock.ticks = 8;
}
//Subtract register from/into register.a with Carry Flags(Z,1,H,C)
void Cpu::sbc(byte& reg) {
  word tempReg = m_registers.a - reg - (checkFlag(Flags::C) ? (byte)1 : (byte)0);
  setFlag(Flags::S);
  (tempReg & 0xFF00) ? setFlag(Flags::C) : clearFlag(Flags::C);
  ((m_registers.a ^ reg ^ (tempReg & 0xFF)) & 0x10) ? setFlag(Flags::H) : clearFlag(Flags::H);
  m_registers.a = (byte)(tempReg & 0xFF);
  (m_registers.a) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_clock.ticks = 4;
}

//Subtract value at register from register.a with carry Flags(Z,1,H,C)
void Cpu::sbc(word& reg) {
  byte val = m_memory.readByte(m_registers.hl);
  sbc(val);
  m_clock.ticks = 8;
}

//And next byte with/into register a Flags(Z,0,1,0)
void Cpu::And() {
  byte value = readByteFromPC();
  And(value);
  m_clock.ticks = 8;
}
//And register with/into register.a Flags(Z,0,1,0)
void Cpu::And(byte& reg) {
  clearFlag(Flags::S);
  clearFlag(Flags::C);
  setFlag(Flags::H);
  (m_registers.a &= reg) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  m_clock.ticks = 4;
}

//And value at register with reg a Flags(Z,0,1,0)
void Cpu::And(word& reg) {
  byte val = m_memory.readByte(reg);
  And(val);
  m_clock.ticks = 8;
}

//xor next byte with/into register.a Flags(Z,0,0,0)
void Cpu::Xor() {
  byte value = readByteFromPC();
  Xor(value);
  m_clock.ticks = 8;
}

//xor register with/into register.a Flags(Z,0,0,0)
void Cpu::Xor(byte& reg) {
  clearAllFlags();
  if (!(m_registers.a ^= reg))
    setFlag(Flags::Z);
  m_clock.ticks = 4;
}

void Cpu::Xor(word& reg) {
  byte val = m_memory.readByte(reg);
  Xor(val);
  m_clock.ticks = 8;
}

//or next byte with/into register a Flags(Z,0,0,0)
void Cpu::Or() {
  byte value = readByteFromPC();
  Or(value);
  m_clock.ticks = 8;
}

//or register with/into register.a Flags(Z,0,0,0)
void Cpu::Or(byte& reg) {
  clearAllFlags();
  if (!(m_registers.a |= reg))
    setFlag(Flags::Z);
  m_clock.ticks = 4;
}

void Cpu::Or(word& reg) {
  byte val = m_memory.readByte(reg);
  Or(val);
  m_clock.ticks = 8;
}

//compare next byte with register.a Flags(Z,1,H,C)
void Cpu::cp() {
  byte value = readByteFromPC();
  cp(value);
  m_clock.ticks = 8;
}

//compare register with register.a Flags(Z,1,H,C)
void Cpu::cp(byte& reg) {
  setFlag(Flags::S);
  m_registers.a < reg ? setFlag(Flags::C) : clearFlag(Flags::C);
  ((m_registers.a & 0xF) < (reg & 0xF)) ? setFlag(Flags::H) : clearFlag(Flags::H);
  m_registers.a == reg ? setFlag(Flags::Z) : clearFlag(Flags::Z);
  m_clock.ticks = 4;
}

//compare value at reg with register.a Flags(Z,1,H,C)
void Cpu::cp(word& reg) {
  byte val = m_memory.readByte(reg);
  cp(val);
  m_clock.ticks = 8;
}

//Jump next byte, relative to PC if conditions are met
void Cpu::jr(bool check, Flags flag, bool condition) {
  m_clock.ticks = 8;
  char jump = readByteFromPC();
  if ((!check) || (checkFlag(flag) == condition)) {
    m_registers.pc += jump;
    m_clock.ticks = 12;
  }
}

//Pop word off stack and put into register Flags(-,-,-,-) or Flags(Z,N,H,C)
void Cpu::pop(word& reg) {
  reg = popWordFromStack();
  m_clock.ticks = 12;
}
//Pop word into AF register, can only write to the top 4 bits of F Flags(Z,N,H,C)
void Cpu::pop_af() {
  word val = popWordFromStack() & (word)0xFFF0;
  m_registers.af = val;
  m_clock.ticks = 12;
}
//Push register unto stack Flags(-,-,-,-)
void Cpu::push(word& reg) {
  pushWordToStack(reg);
  m_clock.ticks = 16;
}

//Rotate register a left old bit 7 to Carry Flag. Flags(0,0,0,C)
void Cpu::rlca(){
  clearAllFlags();
  byte carry = (m_registers.a & (byte)0b10000000) >> 7;
  if (carry)
    setFlag(Flags::C);
  m_registers.a <<= 1;
  m_registers.a += carry;
  m_clock.ticks = 4;
}

//Rotate register a left carry flag to bit 0. Flags(0,0,0,C)
void Cpu::rla() {
  bool carry = checkFlag(Flags::C);
  clearAllFlags();
  if (m_registers.a & 0x80)
    setFlag(Flags::C);
  m_registers.a <<= 1;
  if (carry)
    m_registers.a += 1;
  m_clock.ticks = 4;
}

//Rotate register a right old bit 0 to carry flag. Flags(0,0,0,C)
void Cpu::rrca(){
  byte carry = m_registers.a & (byte)1;
  clearAllFlags();
  m_registers.a >>= 1;
  if (carry) {
    setFlag(Flags::C);
    m_registers.a |= 0x80;
  }
  m_clock.ticks = 4;
}

//Rotate register a right carry flag to bit 7
void Cpu::rra(){
  bool carry = checkFlag(Flags::C);
  clearAllFlags();
  if (m_registers.a & 0x01)
    setFlag(Flags::C);
  m_registers.a >>= 1;
  if (carry)
    m_registers.a |= 0x80;
  m_clock.ticks = 4;
}

//Store sp into address at nn Flags(-,-,-,-)
void Cpu::ld_nnp_sp() {
  m_memory.writeShort(readWordFromPC(), m_registers.sp);
  m_clock.ticks = 20;
}

//Decimal Adjust register a Flags(Z,-,0,C)
void Cpu::daa() {
  int s = m_registers.a;
  if (checkFlag(Flags::S)){
    if (checkFlag(Flags::H))
      s = (s - 0x06) & 0xFF;
    if (checkFlag(Flags::C))
      s -= 0x60;
  }
  else{
    if (checkFlag(Flags::H) || (s & 0x0F) > 9)
      s += 0x06;
    if (checkFlag(Flags::C) || s > 0x9F)
      s += 0x60;
  }
  m_registers.a = (byte)s;
  clearFlag(Flags::H);
  (m_registers.a) ? clearFlag(Flags::Z) : setFlag(Flags::Z);
  if (s >= 0x100)
    setFlag(Flags::C);
  m_clock.ticks = 4;
}

//Complement register a Flags(-,1,1,-)
void Cpu::cpl() {
  m_registers.a = ~m_registers.a;
  setFlag(Flags::S);
  setFlag(Flags::H);
  m_clock.ticks = 4;
}

//Increment value at register hl Flags(Z,0,H,-)
void Cpu::incAtHL() {
  byte val = m_memory.readByte(m_registers.hl);
  inc(val);
  m_memory.writeByte(m_registers.hl, val);
  m_clock.ticks = 12;
}

//Decrement value at register hl Flags(Z,1,H,-)
void Cpu::decAtHL() {
  byte val = m_memory.readByte(m_registers.hl);
  dec(val);
  m_memory.writeByte(m_registers.hl, val);
  m_clock.ticks = 12;
}

//Load next byte into address at hl Flags(-,-,-,-)
void Cpu::ld_hlp_n() {
  m_memory.writeByte(m_registers.hl, readByteFromPC());
  m_clock.ticks = 12;
}

//set carry flag Flags(-,0,0,1)
void Cpu::scf() {
  setFlag(Flags::C);
  clearFlag(Flags::S);
  clearFlag(Flags::H);
  m_clock.ticks = 4;
}

//Complement Carry Flag Flags(-,0,0,C)
void Cpu::ccf() {
  clearFlag(Flags::S);
  clearFlag(Flags::H);
  checkFlag(Flags::C) ? clearFlag(Flags::C) : setFlag(Flags::C);
  m_clock.ticks = 4;
}

//Return if conditions are met Flags(-,-,-,-)
void Cpu::ret(bool check, Flags flag, bool condition) {
  m_clock.ticks = 8;
  if ((!check) || (checkFlag(flag) == condition)){
    m_registers.pc = popWordFromStack();
    m_clock.ticks = 20;
  }
}

//Pop short off stack, jump to that address, enable interrupts Flags(-,-,-,-)
void Cpu::reti() {
  m_registers.pc = popWordFromStack();
  m_pendingMasterInterruptEnable = true;
  m_clock.ticks = 16;
}

//Jump if conditions are met Flags(-,-,-,-)
void Cpu::jmp(bool check, Flags flag, bool condition) {
  m_clock.ticks = 12;
  word address = readWordFromPC();
  if ((!check) || (checkFlag(flag) == condition)){
    m_registers.pc = address;
    m_clock.ticks = 16;
  }
}

//Call if conditions are met Flags(-,-,-,-)
void Cpu::call(bool check, Flags flag, bool condition) {
  m_clock.ticks = 12;
  word address = readWordFromPC();
  if ((!check) || (checkFlag(flag) == condition)){
    pushWordToStack(m_registers.pc);
    m_registers.pc = address;
    m_clock.ticks = 24;
  }
}

//Restart, push pc onto stack and jump to address 0xXX Flags(-,-,-,-)
void Cpu::rst(byte offset) {
  pushWordToStack(m_registers.pc);
  m_registers.pc = offset;
  m_clock.ticks = 16;
}

//Put register a into address 0xFF+n Flags(-,-,-,-)
void Cpu::ld_ffnp_a() {
  m_memory.writeByte((word)0xFF00 + readByteFromPC(), m_registers.a);
  m_clock.ticks = 12;
}

//Put value at address 0xFF+n into register a Flags(-,-,-,-)
void Cpu::ld_a_ffnp() {
  m_registers.a = m_memory.readByte((word)0xFF00 + readByteFromPC());
  m_clock.ticks = 12;
}

//Add signed byte to stack pointer Flags(0,0,H,C)
void Cpu::add_sp_n() {
  clearAllFlags();
  char offset = readByteFromPC();
  word temp = m_registers.sp + offset;
  if ((m_registers.sp ^ offset ^ temp) & 0x100)
    setFlag(Flags::C);
  if ((m_registers.sp ^ offset ^ temp) & 0x10)
    setFlag(Flags::H);
  m_registers.sp = temp;
  m_clock.ticks = 16;
}

//Jump to address in register hl Flags(-,-,-,-)
void Cpu::jmp_hl() {
  m_registers.pc = m_registers.hl;
  m_clock.ticks = 4;
}

//write register a into address from next two bytes Flags(-,-,-,-)
void Cpu::ld_nnp_a() {
  m_memory.writeByte(readWordFromPC(), m_registers.a);
  m_clock.ticks = 16;
}

//Write value at address nn into register a Flags(-,-,-,-)
void Cpu::ld_a_nnp() {
  m_registers.a = m_memory.readByte(readWordFromPC());
  m_clock.ticks = 16;
}

//Load value at register.sp + n into register hl Flags(0,0,H,C)
void Cpu::ld_hl_spn() {
  char offset = readByteFromPC();
  word temp = m_registers.sp + offset;
  clearAllFlags();
  if ((m_registers.sp ^ offset ^ temp) & 0x100)
    setFlag(Flags::C);
  if ((m_registers.sp ^ offset ^ temp) & 0x10)
    setFlag(Flags::H);
  m_registers.hl = temp;
  m_clock.ticks = 12;
}

//Load value of register hl into register sp Flags(-,-,-,-)
void Cpu::ld_sp_hl() {
  m_registers.sp = m_registers.hl;
  m_clock.ticks = 8;
}

//Extended opcodes
//Rotate Left Carry, Flags(Z,0,0,C)
void Cpu::rlc(byte& reg) {
  clearAllFlags();
  byte carry = (reg & (byte)0b10000000) >> 7;
  if (carry)
    setFlag(Flags::C);
  reg <<= 1;
  reg += carry;
  if (!reg)
    setFlag(Flags::Z);
  m_clock.ticks = 8;
}

void Cpu::rlc(word& reg) {
  byte value = m_memory.readByte(reg);
  rlc(value);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}

void Cpu::rrc(byte& reg) {
  clearAllFlags();
  byte carry = reg & (byte)0b1;
  if (carry)
    setFlag(Flags::C);
  reg >>= 1;
  reg += (carry << 7);
  if (!reg)
    setFlag(Flags::Z);
  m_clock.ticks = 8;
}

void Cpu::rrc(word& reg) {
  byte value = m_memory.readByte(reg);
  rrc(value);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}

void Cpu::rl(byte& reg) {
  byte carry = checkFlag(Flags::C) ? (byte)1 : (byte)0;
  clearAllFlags();

  if (reg & (byte)0b10000000)
    setFlag(Flags::C);
  reg <<= 1;
  reg += carry;

  if (!reg)
    setFlag(Flags::Z);
  m_clock.ticks = 8;
}

void Cpu::rl(word& reg) {
  byte value = m_memory.readByte(reg);
  rl(value);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}

void Cpu::rr(byte& reg) {
  byte carry = checkFlag(Flags::C) ? (byte)0b10000000 : (byte)0;
  clearAllFlags();

  if (reg & (byte)0b1)
    setFlag(Flags::C);
  reg >>= 1;
  reg += carry;

  if (!reg)
    setFlag(Flags::Z);
  m_clock.ticks = 8;
}

void Cpu::rr(word& reg) {
  byte value = m_memory.readByte(reg);
  rr(value);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}

void Cpu::sla(byte& reg) {
  clearAllFlags();
  if (reg & (byte)0b10000000)
    setFlag(Flags::C);
  reg <<= 1;
  if (!reg)
    setFlag(Flags::Z);
  m_clock.ticks = 8;
}

void Cpu::sla(word& reg) {
  byte value = m_memory.readByte(reg);
  sla(value);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}

//Shift byte right into Carry, MSB doesn't change
void Cpu::sra(byte& reg) {
  clearAllFlags();
  byte msb = reg & (byte)0b10000000;

  if (reg & (byte)0b1)
    setFlag(Flags::C);
  reg >>= 1;
  reg |= msb;

  if (!reg)
    setFlag(Flags::Z);
  m_clock.ticks = 8;
}

void Cpu::sra(word& reg) {
  byte value = m_memory.readByte(reg);
  sra(value);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}


void Cpu::swap(byte& reg) {
  byte lower = reg & (byte)0xF;

  reg >>= 4;
  reg |= (lower << 4);
  clearAllFlags();
  if (!reg)
    setFlag(Flags::Z);
  m_clock.ticks = 8;
}

void Cpu::swap(word& reg) {
  byte value = m_memory.readByte(reg);
  swap(value);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}

//Shift byte right into Carry, MSB set to 0
void Cpu::srl(byte& reg) {
  clearAllFlags();

  if (reg & (byte)0b1)
    setFlag(Flags::C);
  reg >>= 1;
  if (!reg)
    setFlag(Flags::Z);

  m_clock.ticks = 8;
}

void Cpu::srl(word& reg) {
  byte value = m_memory.readByte(reg);
  srl(value);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}

//Test bit in register if true = 0
void Cpu::bit(byte& reg, byte bit) {
  byte b = ((byte)1 << bit);
  if (b & reg)
    clearFlag(Flags::Z);
  else
    setFlag(Flags::Z);
  clearFlag(Flags::S);
  setFlag(Flags::H);
  m_clock.ticks = 8;
}

void Cpu::bit(word& reg, byte bitI) {
  byte value = m_memory.readByte(reg);
  bit(value, bitI);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}

void Cpu::res(byte& reg, byte bit) {
  reg &= (~((byte)1 << bit));
  m_clock.ticks = 8;
}

void Cpu::res(word& reg, byte bit) {
  byte value = m_memory.readByte(reg);
  res(value, bit);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}

void Cpu::set(byte& reg, byte bit) {
  reg |= ((byte)1 << bit);
  m_clock.ticks = 8;
}

void Cpu::set(word& reg, byte bit) {
  byte value = m_memory.readByte(reg);
  set(value, bit);
  m_memory.writeByte(reg, value);
  m_clock.ticks = 16;
}