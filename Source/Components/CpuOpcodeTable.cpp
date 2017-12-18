//
// Created by derdro on 12/18/17.
//
#include <assert.h>
#include "Cpu.hpp"

void Cpu::executeOpcode(byte opcode){
  switch(opcode){
    case 0x00: nop(); break;
    case 0x10: stop(); break;

      //load byte from pc into register
    case 0x06: byteLoad(m_registers.b);break;
    case 0x0E: byteLoad(m_registers.c);break;
    case 0x16: byteLoad(m_registers.d);break;
    case 0x1E: byteLoad(m_registers.e);break;
    case 0x26: byteLoad(m_registers.h);break;
    case 0x2E: byteLoad(m_registers.l);break;
    case 0x3E: byteLoad(m_registers.a);break;

      //load word from pc into register
    case 0x01: wordLoad(m_registers.bc);break;
    case 0x11: wordLoad(m_registers.de);break;
    case 0x21: wordLoad(m_registers.hl);break;
    case 0x31: wordLoad(m_registers.sp);break;

      //write byte into memory, parms(address, source)
    case 0x02: writeMemoryByte(m_registers.bc, m_registers.a);break;
    case 0x12: writeMemoryByte(m_registers.de, m_registers.a);break;
    case 0x70: writeMemoryByte(m_registers.hl, m_registers.b);break;
    case 0x71: writeMemoryByte(m_registers.hl, m_registers.c);break;
    case 0x72: writeMemoryByte(m_registers.hl, m_registers.d);break;
    case 0x73: writeMemoryByte(m_registers.hl, m_registers.e);break;
    case 0x74: writeMemoryByte(m_registers.hl, m_registers.h);break;
    case 0x75: writeMemoryByte(m_registers.hl, m_registers.l);break;
    case 0x77: writeMemoryByte(m_registers.hl, m_registers.a);break;
    case 0xE2: writeIoPortByte(m_registers.c, m_registers.a);break;

      //Increment byte register
    case 0x04: inc(m_registers.b);break;
    case 0x0C: inc(m_registers.c);break;
    case 0x14: inc(m_registers.d);break;
    case 0x1C: inc(m_registers.e);break;
    case 0x24: inc(m_registers.h);break;
    case 0x2C: inc(m_registers.l);break;
    case 0x3C: inc(m_registers.a);break;

      //Increment word register
    case 0x03: inc(m_registers.bc);break;
    case 0x13: inc(m_registers.de);break;
    case 0x23: inc(m_registers.hl);break;
    case 0x33: inc(m_registers.sp);break;

      //Decrement byte register
    case 0x05: dec(m_registers.b);break;
    case 0x0D: dec(m_registers.c);break;
    case 0x15: dec(m_registers.d);break;
    case 0x1D: dec(m_registers.e);break;
    case 0x25: dec(m_registers.h);break;
    case 0x2D: dec(m_registers.l);break;
    case 0x3D: dec(m_registers.a);break;

      //Decrement word register
    case 0x0B: dec(m_registers.bc);break;
    case 0x1B: dec(m_registers.de);break;
    case 0x2B: dec(m_registers.hl);break;
    case 0x3B: dec(m_registers.sp);break;

      //Add word registers
    case 0x09: add(m_registers.hl, m_registers.bc);break;
    case 0x19: add(m_registers.hl, m_registers.de);break;
    case 0x29: add(m_registers.hl, m_registers.hl);break;
    case 0x39: add(m_registers.hl, m_registers.sp);break;

      //Load byte from memory address into register
    case 0x0A: byteLoad(m_registers.a, m_registers.bc);break;
    case 0x1A: byteLoad(m_registers.a, m_registers.de);break;
    case 0x2A: byteLoad(m_registers.a, m_registers.hl);m_registers.hl++;break;
    case 0x3A: byteLoad(m_registers.a, m_registers.hl);m_registers.hl--;break;
    case 0x46: byteLoad(m_registers.b, m_registers.hl);break;
    case 0x4E: byteLoad(m_registers.c, m_registers.hl);break;
    case 0x56: byteLoad(m_registers.d, m_registers.hl);break;
    case 0x5E: byteLoad(m_registers.e, m_registers.hl);break;
    case 0x66: byteLoad(m_registers.h, m_registers.hl);break;
    case 0x6E: byteLoad(m_registers.l, m_registers.hl);break;
    case 0x7E: byteLoad(m_registers.a, m_registers.hl);break;
    case 0xF2: byteLoadIoPort(m_registers.a, m_registers.c);break;

      //Load byte from register2 to register 1
    case 0x40: byteLoad(m_registers.b, m_registers.b);break;
    case 0x41: byteLoad(m_registers.b, m_registers.c);break;
    case 0x42: byteLoad(m_registers.b, m_registers.d);break;
    case 0x43: byteLoad(m_registers.b, m_registers.e);break;
    case 0x44: byteLoad(m_registers.b, m_registers.h);break;
    case 0x45: byteLoad(m_registers.b, m_registers.l);break;
    case 0x47: byteLoad(m_registers.b, m_registers.a);break;
    case 0x48: byteLoad(m_registers.c, m_registers.b);break;
    case 0x49: byteLoad(m_registers.c, m_registers.c);break;
    case 0x4A: byteLoad(m_registers.c, m_registers.d);break;
    case 0x4B: byteLoad(m_registers.c, m_registers.e);break;
    case 0x4C: byteLoad(m_registers.c, m_registers.h);break;
    case 0x4D: byteLoad(m_registers.c, m_registers.l);break;
    case 0x4F: byteLoad(m_registers.c, m_registers.a);break;
    case 0x50: byteLoad(m_registers.d, m_registers.b);break;
    case 0x51: byteLoad(m_registers.d, m_registers.c);break;
    case 0x52: byteLoad(m_registers.d, m_registers.d);break;
    case 0x53: byteLoad(m_registers.d, m_registers.e);break;
    case 0x54: byteLoad(m_registers.d, m_registers.h);break;
    case 0x55: byteLoad(m_registers.d, m_registers.l);break;
    case 0x57: byteLoad(m_registers.d, m_registers.a);break;
    case 0x58: byteLoad(m_registers.e, m_registers.b);break;
    case 0x59: byteLoad(m_registers.e, m_registers.c);break;
    case 0x5A: byteLoad(m_registers.e, m_registers.d);break;
    case 0x5B: byteLoad(m_registers.e, m_registers.e);break;
    case 0x5C: byteLoad(m_registers.e, m_registers.h);break;
    case 0x5D: byteLoad(m_registers.e, m_registers.l);break;
    case 0x5F: byteLoad(m_registers.e, m_registers.a);break;
    case 0x60: byteLoad(m_registers.h, m_registers.b);break;
    case 0x61: byteLoad(m_registers.h, m_registers.c);break;
    case 0x62: byteLoad(m_registers.h, m_registers.d);break;
    case 0x63: byteLoad(m_registers.h, m_registers.e);break;
    case 0x64: byteLoad(m_registers.h, m_registers.h);break;
    case 0x65: byteLoad(m_registers.h, m_registers.l);break;
    case 0x67: byteLoad(m_registers.h, m_registers.a);break;
    case 0x68: byteLoad(m_registers.l, m_registers.b);break;
    case 0x69: byteLoad(m_registers.l, m_registers.c);break;
    case 0x6A: byteLoad(m_registers.l, m_registers.d);break;
    case 0x6B: byteLoad(m_registers.l, m_registers.e);break;
    case 0x6C: byteLoad(m_registers.l, m_registers.h);break;
    case 0x6D: byteLoad(m_registers.l, m_registers.l);break;
    case 0x6F: byteLoad(m_registers.l, m_registers.a);break;
    case 0x78: byteLoad(m_registers.a, m_registers.b);break;
    case 0x79: byteLoad(m_registers.a, m_registers.c);break;
    case 0x7A: byteLoad(m_registers.a, m_registers.d);break;
    case 0x7B: byteLoad(m_registers.a, m_registers.e);break;
    case 0x7C: byteLoad(m_registers.a, m_registers.h);break;
    case 0x7D: byteLoad(m_registers.a, m_registers.l);break;
    case 0x7F: byteLoad(m_registers.a, m_registers.a);break;

      //Add reg into reg.a
    case 0x80: add(m_registers.b);break;
    case 0x81: add(m_registers.c);break;
    case 0x82: add(m_registers.d);break;
    case 0x83: add(m_registers.e);break;
    case 0x84: add(m_registers.h);break;
    case 0x85: add(m_registers.l);break;
    case 0x86: add(m_registers.hl);break;
    case 0x87: add(m_registers.a);break;

      //Add reg into reg.a with carry
    case 0x88: adc(m_registers.b);break;
    case 0x89: adc(m_registers.c);break;
    case 0x8A: adc(m_registers.d);break;
    case 0x8B: adc(m_registers.e);break;
    case 0x8C: adc(m_registers.h);break;
    case 0x8D: adc(m_registers.l);break;
    case 0x8E: adc(m_registers.hl);break;
    case 0x8F: adc(m_registers.a);break;

      //Sub reg from reg.a
    case 0x90: sub(m_registers.b);break;
    case 0x91: sub(m_registers.c);break;
    case 0x92: sub(m_registers.d);break;
    case 0x93: sub(m_registers.e);break;
    case 0x94: sub(m_registers.h);break;
    case 0x95: sub(m_registers.l);break;
    case 0x96: sub(m_registers.hl);break;
    case 0x97: sub(m_registers.a);break;

      //Sub reg from reg.a with carry
    case 0x98: sbc(m_registers.b);break;
    case 0x99: sbc(m_registers.c);break;
    case 0x9A: sbc(m_registers.d);break;
    case 0x9B: sbc(m_registers.e);break;
    case 0x9C: sbc(m_registers.h);break;
    case 0x9D: sbc(m_registers.l);break;
    case 0x9E: sbc(m_registers.hl);break;
    case 0x9F: sbc(m_registers.a);break;

      //And reg with reg.a
    case 0xA0: And(m_registers.b);break;
    case 0xA1: And(m_registers.c);break;
    case 0xA2: And(m_registers.d);break;
    case 0xA3: And(m_registers.e);break;
    case 0xA4: And(m_registers.h);break;
    case 0xA5: And(m_registers.l);break;
    case 0xA6: And(m_registers.hl);break;
    case 0xA7: And(m_registers.a);break;

      //XOR reg with reg.a
    case 0xA8: Xor(m_registers.b);break;
    case 0xA9: Xor(m_registers.c);break;
    case 0xAA: Xor(m_registers.d);break;
    case 0xAB: Xor(m_registers.e);break;
    case 0xAC: Xor(m_registers.h);break;
    case 0xAD: Xor(m_registers.l);break;
    case 0xAE: Xor(m_registers.hl);break;
    case 0xAF: Xor(m_registers.a);break;

      //Or reg with reg.a
    case 0xB0: Or(m_registers.b);break;
    case 0xB1: Or(m_registers.c);break;
    case 0xB2: Or(m_registers.d);break;
    case 0xB3: Or(m_registers.e);break;
    case 0xB4: Or(m_registers.h);break;
    case 0xB5: Or(m_registers.l);break;
    case 0xB6: Or(m_registers.hl);break;
    case 0xB7: Or(m_registers.a);break;

      //CP reg with reg.a
    case 0xB8: cp(m_registers.b);break;
    case 0xB9: cp(m_registers.c);break;
    case 0xBA: cp(m_registers.d);break;
    case 0xBB: cp(m_registers.e);break;
    case 0xBC: cp(m_registers.h);break;
    case 0xBD: cp(m_registers.l);break;
    case 0xBE: cp(m_registers.hl);break;
    case 0xBF: cp(m_registers.a);break;

      //Jumps
    case 0x18: jr(false);break;
    case 0x20: jr(true, Flags::Z, false);
    case 0x28: jr(true, Flags::Z, true);
    case 0x30: jr(true, Flags::C, false);
    case 0x38: jr(true, Flags::C, true);
    default: assert(false); break;
  }
}

void Cpu::executeExtOpcode(byte opcode) {

}

//0x00 Do nothing
void Cpu::nop(){

}

//0x01 Store 2 byte value, nn, into the bc register
void Cpu::ld_bc_nn(){

}
