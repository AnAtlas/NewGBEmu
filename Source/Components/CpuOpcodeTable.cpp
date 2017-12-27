//
// Created by derdro on 12/18/17.
//
#include <assert.h>
#include "Cpu.hpp"

void Cpu::executeOpcode(byte opcode){
  switch(opcode){

      //Unique opcodes
    case 0x00: nop();break;
    case 0x08: ld_nnp_sp();break;
    case 0x10: stop();break;
    case 0x27: daa();break;
    case 0x2F: cpl();break;
    case 0x36: ld_hlp_n();break;
    case 0x37: scf();break;
    case 0x3F: ccf();break;
    case 0x76: halt();break;
    case 0xF3: di();break;
    case 0xCB: cb();break;
    case 0xE0: ld_ffnp_a();break;
    case 0xF0: ld_a_ffnp();break;
    case 0xE8: add_sp_n();break;
    case 0xFB: ei();break;
    case 0xEA: ld_nnp_a();break;
    case 0xFA: ld_a_nnp();break;
    case 0xF8: ld_hl_spn();break;
    case 0xF9: ld_sp_hl();break;

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
    case 0x22: writeMemoryByte(m_registers.hl, m_registers.a);m_registers.hl++;break;
    case 0x32: writeMemoryByte(m_registers.hl, m_registers.a);m_registers.hl--;break;
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
    case 0x34: incAtHL();break;
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
    case 0x35: decAtHL();break;
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
    case 0xC6: add();break;

      //Add reg into reg.a with carry
    case 0x88: adc(m_registers.b);break;
    case 0x89: adc(m_registers.c);break;
    case 0x8A: adc(m_registers.d);break;
    case 0x8B: adc(m_registers.e);break;
    case 0x8C: adc(m_registers.h);break;
    case 0x8D: adc(m_registers.l);break;
    case 0x8E: adc(m_registers.hl);break;
    case 0x8F: adc(m_registers.a);break;
    case 0xCE: adc();break;

      //Sub reg from reg.a
    case 0x90: sub(m_registers.b);break;
    case 0x91: sub(m_registers.c);break;
    case 0x92: sub(m_registers.d);break;
    case 0x93: sub(m_registers.e);break;
    case 0x94: sub(m_registers.h);break;
    case 0x95: sub(m_registers.l);break;
    case 0x96: sub(m_registers.hl);break;
    case 0x97: sub(m_registers.a);break;
    case 0xD6: sub();break;

      //Sub reg from reg.a with carry
    case 0x98: sbc(m_registers.b);break;
    case 0x99: sbc(m_registers.c);break;
    case 0x9A: sbc(m_registers.d);break;
    case 0x9B: sbc(m_registers.e);break;
    case 0x9C: sbc(m_registers.h);break;
    case 0x9D: sbc(m_registers.l);break;
    case 0x9E: sbc(m_registers.hl);break;
    case 0x9F: sbc(m_registers.a);break;
    case 0xDE: sbc();break;

      //And reg with reg.a
    case 0xA0: And(m_registers.b);break;
    case 0xA1: And(m_registers.c);break;
    case 0xA2: And(m_registers.d);break;
    case 0xA3: And(m_registers.e);break;
    case 0xA4: And(m_registers.h);break;
    case 0xA5: And(m_registers.l);break;
    case 0xA6: And(m_registers.hl);break;
    case 0xA7: And(m_registers.a);break;
    case 0xE6: And();break;

      //XOR reg with reg.a
    case 0xA8: Xor(m_registers.b);break;
    case 0xA9: Xor(m_registers.c);break;
    case 0xAA: Xor(m_registers.d);break;
    case 0xAB: Xor(m_registers.e);break;
    case 0xAC: Xor(m_registers.h);break;
    case 0xAD: Xor(m_registers.l);break;
    case 0xAE: Xor(m_registers.hl);break;
    case 0xAF: Xor(m_registers.a);break;
    case 0xEE: Xor();break;

      //Or reg with reg.a
    case 0xB0: Or(m_registers.b);break;
    case 0xB1: Or(m_registers.c);break;
    case 0xB2: Or(m_registers.d);break;
    case 0xB3: Or(m_registers.e);break;
    case 0xB4: Or(m_registers.h);break;
    case 0xB5: Or(m_registers.l);break;
    case 0xB6: Or(m_registers.hl);break;
    case 0xB7: Or(m_registers.a);break;
    case 0xF6: Or();break;

      //CP reg with reg.a
    case 0xB8: cp(m_registers.b);break;
    case 0xB9: cp(m_registers.c);break;
    case 0xBA: cp(m_registers.d);break;
    case 0xBB: cp(m_registers.e);break;
    case 0xBC: cp(m_registers.h);break;
    case 0xBD: cp(m_registers.l);break;
    case 0xBE: cp(m_registers.hl);break;
    case 0xBF: cp(m_registers.a);break;
    case 0xFE: cp();break;

      //Jump relatives
    case 0x18: jr(false);break;
    case 0x20: jr(true, Flags::Z, false);break;
    case 0x28: jr(true, Flags::Z, true);break;
    case 0x30: jr(true, Flags::C, false);break;
    case 0x38: jr(true, Flags::C, true);break;

      //Pop word off stack into register
    case 0xC1: pop(m_registers.bc);break;
    case 0xD1: pop(m_registers.de);break;
    case 0xE1: pop(m_registers.hl);break;
    case 0xF1: pop_af();break;

      //Push register unto stack
    case 0xC5: push(m_registers.bc);break;
    case 0xD5: push(m_registers.de);break;
    case 0xE5: push(m_registers.hl);break;
    case 0xF5: push(m_registers.af);break;

      //Rotate A opcodes
    case 0x07: rlca();break;
    case 0x0F: rrca();break;
    case 0x17: rla();break;
    case 0x1F: rra();break;
      
      //Returns
    case 0xC0: ret(true, Flags::Z, false);break;
    case 0xC8: ret(true, Flags::Z, true);break;
    case 0xC9: ret(false, Flags::Z, false);break;
    case 0xD0: ret(true, Flags::C, false);break;
    case 0xD8: ret(true, Flags::C, true);break;
    case 0xD9: reti();break;

      //Jumps
    case 0xC2: jmp(true, Flags::Z, false);break;
    case 0xC3: jmp(false,Flags::Z, false);break;
    case 0xCA: jmp(true, Flags::Z, true);break;
    case 0xD2: jmp(true, Flags::C, false);break;
    case 0xDA: jmp(true, Flags::C, true);break;
    case 0xE9: jmp_hl();break;

      //Calls
    case 0xC4: call(true, Flags::Z, false);break;
    case 0xCC: call(true, Flags::Z, true);break;
    case 0xCD: call(false, Flags::Z, false);break;
    case 0xD4: call(true, Flags::C, false);break;
    case 0xDC: call(true, Flags::C, true);break;

      //Resets
    case 0xC7: rst(0x00);break;
    case 0xCF: rst(0x08);break;
    case 0xD7: rst(0x10);break;
    case 0xDF: rst(0x18);break;
    case 0xE7: rst(0x20);break;
    case 0xEF: rst(0x28);break;
    case 0xF7: rst(0x30);break;
    case 0xFF: rst(0x38);break;

    default: null(opcode); break;
  }
}

void Cpu::executeExtOpcode(byte opcode) {
  m_cbMode = false;
  switch (opcode){
    //rotate left through carry
    case 0x0: rlc(m_registers.b);break;
    case 0x1: rlc(m_registers.c);break;
    case 0x2: rlc(m_registers.d);break;
    case 0x3: rlc(m_registers.e);break;
    case 0x4: rlc(m_registers.h);break;
    case 0x5: rlc(m_registers.l);break;
    case 0x6: rlc(m_registers.hl);break;
    case 0x7: rlc(m_registers.a);break;
      
      //rotate right through carry
    case 0x8: rrc(m_registers.b);break;
    case 0x9: rrc(m_registers.c);break;
    case 0xA: rrc(m_registers.d);break;
    case 0xB: rrc(m_registers.e);break;
    case 0xC: rrc(m_registers.h);break;
    case 0xD: rrc(m_registers.l);break;
    case 0xE: rrc(m_registers.hl);break;
    case 0xF: rrc(m_registers.a);break;

      //rotate left
    case 0x10: rl(m_registers.b);break;
    case 0x11: rl(m_registers.c);break;
    case 0x12: rl(m_registers.d);break;
    case 0x13: rl(m_registers.e);break;
    case 0x14: rl(m_registers.h);break;
    case 0x15: rl(m_registers.l);break;
    case 0x16: rl(m_registers.hl);break;
    case 0x17: rl(m_registers.a);break;

      //rotate right
    case 0x18: rr(m_registers.b);break;
    case 0x19: rr(m_registers.c);break;
    case 0x1A: rr(m_registers.d);break;
    case 0x1B: rr(m_registers.e);break;
    case 0x1C: rr(m_registers.h);break;
    case 0x1D: rr(m_registers.l);break;
    case 0x1E: rr(m_registers.hl);break;
    case 0x1F: rr(m_registers.a);break;

      //shift left into carry lsb set to 0
    case 0x20: sla(m_registers.b);break;
    case 0x21: sla(m_registers.c);break;
    case 0x22: sla(m_registers.d);break;
    case 0x23: sla(m_registers.e);break;
    case 0x24: sla(m_registers.h);break;
    case 0x25: sla(m_registers.l);break;
    case 0x26: sla(m_registers.hl);break;
    case 0x27: sla(m_registers.a);break;

      //shift right into carry msb set to 0
    case 0x28: sra(m_registers.b);break;
    case 0x29: sra(m_registers.c);break;
    case 0x2A: sra(m_registers.d);break;
    case 0x2B: sra(m_registers.e);break;
    case 0x2C: sra(m_registers.h);break;
    case 0x2D: sra(m_registers.l);break;
    case 0x2E: sra(m_registers.hl);break;
    case 0x2F: sra(m_registers.a);break;

      //swap nibbles
    case 0x30: swap(m_registers.b);break;
    case 0x31: swap(m_registers.c);break;
    case 0x32: swap(m_registers.d);break;
    case 0x33: swap(m_registers.e);break;
    case 0x34: swap(m_registers.h);break;
    case 0x35: swap(m_registers.l);break;
    case 0x36: swap(m_registers.hl);break;
    case 0x37: swap(m_registers.a);break;

      //shift right into carry msb set to 0
    case 0x38: srl(m_registers.b);break;
    case 0x39: srl(m_registers.c);break;
    case 0x3A: srl(m_registers.d);break;
    case 0x3B: srl(m_registers.e);break;
    case 0x3C: srl(m_registers.h);break;
    case 0x3D: srl(m_registers.l);break;
    case 0x3E: srl(m_registers.hl);break;
    case 0x3F: srl(m_registers.a);break;

      //Test Bits
    case 0x40: bit(m_registers.b,0);break;
    case 0x41: bit(m_registers.c,0);break;
    case 0x42: bit(m_registers.d,0);break;
    case 0x43: bit(m_registers.e,0);break;
    case 0x44: bit(m_registers.h,0);break;
    case 0x45: bit(m_registers.l,0);break;
    case 0x46: bit(m_registers.hl,0);break;
    case 0x47: bit(m_registers.a,0);break;
      
    case 0x48: bit(m_registers.b,1);break;
    case 0x49: bit(m_registers.c,1);break;
    case 0x4A: bit(m_registers.d,1);break;
    case 0x4B: bit(m_registers.e,1);break;
    case 0x4C: bit(m_registers.h,1);break;
    case 0x4D: bit(m_registers.l,1);break;
    case 0x4E: bit(m_registers.hl,1);break;
    case 0x4F: bit(m_registers.a,1);break;

    case 0x50: bit(m_registers.b,2);break;
    case 0x51: bit(m_registers.c,2);break;
    case 0x52: bit(m_registers.d,2);break;
    case 0x53: bit(m_registers.e,2);break;
    case 0x54: bit(m_registers.h,2);break;
    case 0x55: bit(m_registers.l,2);break;
    case 0x56: bit(m_registers.hl,2);break;
    case 0x57: bit(m_registers.a,2);break;

    case 0x58: bit(m_registers.b,3);break;
    case 0x59: bit(m_registers.c,3);break;
    case 0x5A: bit(m_registers.d,3);break;
    case 0x5B: bit(m_registers.e,3);break;
    case 0x5C: bit(m_registers.h,3);break;
    case 0x5D: bit(m_registers.l,3);break;
    case 0x5E: bit(m_registers.hl,3);break;
    case 0x5F: bit(m_registers.a,3);break;

    case 0x60: bit(m_registers.b,4);break;
    case 0x61: bit(m_registers.c,4);break;
    case 0x62: bit(m_registers.d,4);break;
    case 0x63: bit(m_registers.e,4);break;
    case 0x64: bit(m_registers.h,4);break;
    case 0x65: bit(m_registers.l,4);break;
    case 0x66: bit(m_registers.hl,4);break;
    case 0x67: bit(m_registers.a,4);break;

    case 0x68: bit(m_registers.b,5);break;
    case 0x69: bit(m_registers.c,5);break;
    case 0x6A: bit(m_registers.d,5);break;
    case 0x6B: bit(m_registers.e,5);break;
    case 0x6C: bit(m_registers.h,5);break;
    case 0x6D: bit(m_registers.l,5);break;
    case 0x6E: bit(m_registers.hl,5);break;
    case 0x6F: bit(m_registers.a,5);break;

    case 0x70: bit(m_registers.b,6);break;
    case 0x71: bit(m_registers.c,6);break;
    case 0x72: bit(m_registers.d,6);break;
    case 0x73: bit(m_registers.e,6);break;
    case 0x74: bit(m_registers.h,6);break;
    case 0x75: bit(m_registers.l,6);break;
    case 0x76: bit(m_registers.hl,6);break;
    case 0x77: bit(m_registers.a,6);break;

    case 0x78: bit(m_registers.b,7);break;
    case 0x79: bit(m_registers.c,7);break;
    case 0x7A: bit(m_registers.d,7);break;
    case 0x7B: bit(m_registers.e,7);break;
    case 0x7C: bit(m_registers.h,7);break;
    case 0x7D: bit(m_registers.l,7);break;
    case 0x7E: bit(m_registers.hl,7);break;
    case 0x7F: bit(m_registers.a,7);break;
      
      //Reset bit
    case 0x80: res(m_registers.b,0);break;
    case 0x81: res(m_registers.c,0);break;
    case 0x82: res(m_registers.d,0);break;
    case 0x83: res(m_registers.e,0);break;
    case 0x84: res(m_registers.h,0);break;
    case 0x85: res(m_registers.l,0);break;
    case 0x86: res(m_registers.hl,0);break;
    case 0x87: res(m_registers.a,0);break;

    case 0x88: res(m_registers.b,1);break;
    case 0x89: res(m_registers.c,1);break;
    case 0x8A: res(m_registers.d,1);break;
    case 0x8B: res(m_registers.e,1);break;
    case 0x8C: res(m_registers.h,1);break;
    case 0x8D: res(m_registers.l,1);break;
    case 0x8E: res(m_registers.hl,1);break;
    case 0x8F: res(m_registers.a,1);break;

    case 0x90: res(m_registers.b,2);break;
    case 0x91: res(m_registers.c,2);break;
    case 0x92: res(m_registers.d,2);break;
    case 0x93: res(m_registers.e,2);break;
    case 0x94: res(m_registers.h,2);break;
    case 0x95: res(m_registers.l,2);break;
    case 0x96: res(m_registers.hl,2);break;
    case 0x97: res(m_registers.a,2);break;

    case 0x98: res(m_registers.b,3);break;
    case 0x99: res(m_registers.c,3);break;
    case 0x9A: res(m_registers.d,3);break;
    case 0x9B: res(m_registers.e,3);break;
    case 0x9C: res(m_registers.h,3);break;
    case 0x9D: res(m_registers.l,3);break;
    case 0x9E: res(m_registers.hl,3);break;
    case 0x9F: res(m_registers.a,3);break;

    case 0xA0: res(m_registers.b,4);break;
    case 0xA1: res(m_registers.c,4);break;
    case 0xA2: res(m_registers.d,4);break;
    case 0xA3: res(m_registers.e,4);break;
    case 0xA4: res(m_registers.h,4);break;
    case 0xA5: res(m_registers.l,4);break;
    case 0xA6: res(m_registers.hl,4);break;
    case 0xA7: res(m_registers.a,4);break;

    case 0xA8: res(m_registers.b,5);break;
    case 0xA9: res(m_registers.c,5);break;
    case 0xAA: res(m_registers.d,5);break;
    case 0xAB: res(m_registers.e,5);break;
    case 0xAC: res(m_registers.h,5);break;
    case 0xAD: res(m_registers.l,5);break;
    case 0xAE: res(m_registers.hl,5);break;
    case 0xAF: res(m_registers.a,5);break;

    case 0xB0: res(m_registers.b,6);break;
    case 0xB1: res(m_registers.c,6);break;
    case 0xB2: res(m_registers.d,6);break;
    case 0xB3: res(m_registers.e,6);break;
    case 0xB4: res(m_registers.h,6);break;
    case 0xB5: res(m_registers.l,6);break;
    case 0xB6: res(m_registers.hl,6);break;
    case 0xB7: res(m_registers.a,6);break;

    case 0xB8: res(m_registers.b,7);break;
    case 0xB9: res(m_registers.c,7);break;
    case 0xBA: res(m_registers.d,7);break;
    case 0xBB: res(m_registers.e,7);break;
    case 0xBC: res(m_registers.h,7);break;
    case 0xBD: res(m_registers.l,7);break;
    case 0xBE: res(m_registers.hl,7);break;
    case 0xBF: res(m_registers.a,7);break;

      //Set bit
    case 0xC0: set(m_registers.b,0);break;
    case 0xC1: set(m_registers.c,0);break;
    case 0xC2: set(m_registers.d,0);break;
    case 0xC3: set(m_registers.e,0);break;
    case 0xC4: set(m_registers.h,0);break;
    case 0xC5: set(m_registers.l,0);break;
    case 0xC6: set(m_registers.hl,0);break;
    case 0xC7: set(m_registers.a,0);break;

    case 0xC8: set(m_registers.b,1);break;
    case 0xC9: set(m_registers.c,1);break;
    case 0xCA: set(m_registers.d,1);break;
    case 0xCB: set(m_registers.e,1);break;
    case 0xCC: set(m_registers.h,1);break;
    case 0xCD: set(m_registers.l,1);break;
    case 0xCE: set(m_registers.hl,1);break;
    case 0xCF: set(m_registers.a,1);break;

    case 0xD0: set(m_registers.b,2);break;
    case 0xD1: set(m_registers.c,2);break;
    case 0xD2: set(m_registers.d,2);break;
    case 0xD3: set(m_registers.e,2);break;
    case 0xD4: set(m_registers.h,2);break;
    case 0xD5: set(m_registers.l,2);break;
    case 0xD6: set(m_registers.hl,2);break;
    case 0xD7: set(m_registers.a,2);break;

    case 0xD8: set(m_registers.b,3);break;
    case 0xD9: set(m_registers.c,3);break;
    case 0xDA: set(m_registers.d,3);break;
    case 0xDB: set(m_registers.e,3);break;
    case 0xDC: set(m_registers.h,3);break;
    case 0xDD: set(m_registers.l,3);break;
    case 0xDE: set(m_registers.hl,3);break;
    case 0xDF: set(m_registers.a,3);break;

    case 0xE0: set(m_registers.b,4);break;
    case 0xE1: set(m_registers.c,4);break;
    case 0xE2: set(m_registers.d,4);break;
    case 0xE3: set(m_registers.e,4);break;
    case 0xE4: set(m_registers.h,4);break;
    case 0xE5: set(m_registers.l,4);break;
    case 0xE6: set(m_registers.hl,4);break;
    case 0xE7: set(m_registers.a,4);break;

    case 0xE8: set(m_registers.b,5);break;
    case 0xE9: set(m_registers.c,5);break;
    case 0xEA: set(m_registers.d,5);break;
    case 0xEB: set(m_registers.e,5);break;
    case 0xEC: set(m_registers.h,5);break;
    case 0xED: set(m_registers.l,5);break;
    case 0xEE: set(m_registers.hl,5);break;
    case 0xEF: set(m_registers.a,5);break;

    case 0xF0: set(m_registers.b,6);break;
    case 0xF1: set(m_registers.c,6);break;
    case 0xF2: set(m_registers.d,6);break;
    case 0xF3: set(m_registers.e,6);break;
    case 0xF4: set(m_registers.h,6);break;
    case 0xF5: set(m_registers.l,6);break;
    case 0xF6: set(m_registers.hl,6);break;
    case 0xF7: set(m_registers.a,6);break;

    case 0xF8: set(m_registers.b,7);break;
    case 0xF9: set(m_registers.c,7);break;
    case 0xFA: set(m_registers.d,7);break;
    case 0xFB: set(m_registers.e,7);break;
    case 0xFC: set(m_registers.h,7);break;
    case 0xFD: set(m_registers.l,7);break;
    case 0xFE: set(m_registers.hl,7);break;
    case 0xFF: set(m_registers.a,7);break;
  }
}
