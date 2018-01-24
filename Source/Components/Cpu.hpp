//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_CPU_HPP
#define NEWGBEMU_CPU_HPP

#include <memory>
#include <fstream>
#include "../Utilities/Types.hpp"
#include "MemoryInterfaces/CpuMemoryInterface.hpp"

class Memory;

class Cpu
{
private:
  enum Flags{
    Z = (1 << 7), //Zero
    S = (1 << 6), //Subtract
    H = (1 << 5), //HalfCarry
    C = (1 << 4) //Carry
  };

  struct Registers{
    //Registers a and f
    struct {
        union {
            struct {
                byte f;
                byte a;
            };
            word af;
        };
    };

    //Registers b and c
    struct {
        union {
            struct {
                byte c;
                byte b;
            };
            word bc;
        };
    };

    //Registers d and e
    struct {
        union {
            struct {
                byte e;
                byte d;
            };
            word de;
        };
    };

    //Registers h and l
    struct {
        union {
            struct {
                byte l;
                byte h;
            };
            word hl;
        };
    };
    word sp;
    word pc;
  };
  struct Clock{
    byte ticks = 0;
  };

  Registers m_registers;
  Clock m_clock;
  bool m_halted;
  bool m_stopped;
  bool m_cbMode;
  bool m_pendingMasterInterruptEnable;
  bool m_masterInterruptEnabled;
  CpuMemoryInterface& m_memory;

  //Debug
  int opsRan = 0;
  std::ofstream logFile;
public:
  Cpu(CpuMemoryInterface& memory, bool runBios);
  ~Cpu();
  byte step();

private:
  byte readByteFromPC();
  word readWordFromPC();
  void initializeRegisters();
  void executeOpcode(byte opcode);
  void executeExtOpcode(byte opcode);
  void checkInterrupts();
  void serviceInterrupt(byte bit);
  void setFlag(Flags flag);
  bool checkFlag(Flags flag);
  void clearFlag(Flags flag);
  void clearAllFlags();
  void pushWordToStack(word value);
  word popWordFromStack();

  void null(byte opcode);
  void nop();
  void stop();
  void halt();
  void di();
  void cb();
  void ei();

  void byteLoad(byte& reg);
  void byteLoad(byte& reg1, byte& reg2);
  void byteLoad(byte& reg, word& address);
  void byteLoadIoPort(byte& reg, byte& address);
  void wordLoad(word& reg);
  void writeMemoryByte(word& address, byte& reg);
  void writeIoPortByte(byte& address, byte& reg);
  void inc(byte& reg);
  void inc(word& reg);
  void incAtHL();
  void dec(byte& reg);
  void dec(word& reg);
  void decAtHL();
  void add();
  void add(byte& reg);
  void add(word& reg1, word& reg2);
  void add(word& reg);
  void adc();
  void adc(byte& reg);
  void adc(word& reg);
  void sub();
  void sub(byte& reg);
  void sub(word& reg);
  void sbc();
  void sbc(byte& reg);
  void sbc(word& reg);
  void And();
  void And(byte& reg);
  void And(word& reg);
  void Xor();
  void Xor(byte& reg);
  void Xor(word& reg);
  void Or();
  void Or(byte& reg);
  void Or(word& reg);
  void cp();
  void cp(byte& reg);
  void cp(word& reg);
  void jr(bool check, Flags flag = Flags::Z, bool condition = false);
  void pop(word& reg);
  void pop_af();
  void push(word& reg);
  void rlca();
  void rla();
  void rrca();
  void rra();
  void ld_nnp_sp();
  void daa();
  void cpl();
  void ld_hlp_n();
  void scf();
  void ccf();
  void ret(bool check, Flags flag, bool condition);
  void reti();
  void jmp(bool check, Flags flag, bool condition);
  void call(bool check, Flags flag, bool condition);
  void rst(byte offset);
  void ld_ffnp_a();
  void ld_a_ffnp();
  void add_sp_n();
  void jmp_hl();
  void ld_nnp_a();
  void ld_a_nnp();
  void ld_hl_spn();
  void ld_sp_hl();

  void null();

  //Instructions accessed through CB
  void rlc(byte& reg);
  void rlc(word& reg);
  void rrc(byte& reg);
  void rrc(word& reg);
  void rl(byte& reg);
  void rl(word& reg);
  void rr(byte& reg);
  void rr(word& reg);
  void sla(byte& reg);
  void sla(word& reg);
  void sra(byte& reg);
  void sra(word& reg);
  void swap(byte& reg);
  void swap(word& reg);
  void srl(byte& reg);
  void srl(word& reg);
  void bit(byte& reg, byte bit);
  void bit(word& reg, byte bit);
  void res(byte& reg, byte bit);
  void res(word& reg, byte bit);
  void set(byte& reg, byte bit);
  void set(word& reg, byte bit);
};
#endif //NEWGBEMU_CPU_HPP
