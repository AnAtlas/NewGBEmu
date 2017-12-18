//
// Created by Derek on 12/17/2017.
//

#ifndef NEWGBEMU_CPU_HPP
#define NEWGBEMU_CPU_HPP

#include <memory>
#include "../Utilities/Types.hpp"
#include "CpuMemoryInterface.hpp"

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
            word m = 0;
            word t = 0;
    };

    Registers m_registers;
    Clock m_clock;
    bool m_halted;
    bool m_stopped;
    bool m_cbMode;
    CpuMemoryInterface& m_memory;
public:
    Cpu(CpuMemoryInterface& memory);
    byte step();

private:
  void executeOpcode(byte opcode);
  void executeExtOpcode(byte opcode);
  void setFlag(Flags flag);
  bool checkFlag(Flags flag);
  void clearFlag(Flags flag);
  void clearAllFlags();

  void byteLoad(byte& reg);
  void byteLoad(byte& reg1, byte& reg2);
  void byteLoad(byte& reg, word& address);
  void byteLoadIoPort(byte& reg, byte& address);
  void wordLoad(word& reg);
  void writeMemoryByte(word& address, byte& reg);
  void writeIoPortByte(byte& address, byte& reg);
  void inc(byte& reg);
  void inc(word& reg);
  void dec(byte& reg);
  void dec(word& reg);
  void add(byte& reg);
  void add(word& reg1, word& reg2);
  void add(word& reg);
  void adc(byte& reg);
  void adc(word& reg);
  void sub(byte& reg);
  void sub(word& reg);
  void sbc(byte& reg);
  void sbc(word& reg);
  void And(byte& reg);
  void And(word& reg);
  void Xor(byte& reg);
  void Xor(word& reg);
  void Or(byte& reg);
  void Or(word& reg);
  void cp(byte& reg);
  void cp(word& reg);
  void jr(bool check, Flags flag = Flags::Z, bool condition = false);

  //Instruction functions
  void nop();			//0x00
  void ld_bc_nn();	//0x01
  void ld_bcp_a();	//0x02
  void inc_bc();
  void inc_b();
  void dec_b();
  void ld_b_n();
  void rlca();
  void ld_nnp_sp();
  void add_hl_bc();
  void ld_a_bcp();	//0x0A
  void dec_bc();
  void inc_c();
  void dec_c();
  void ld_c_n();
  void rrca();
  void stop();		//0x10
  void ld_de_nn();
  void ld_dep_a();
  void inc_de();
  void inc_d();
  void dec_d();
  void ld_d_n();
  void rla();
  void jr_n();
  void add_hl_de();
  void ld_a_dep();	//0x1A
  void dec_de();
  void inc_e();
  void dec_e();
  void ld_e_n();
  void rra();
  void jr_nz_n();		//0x20
  void ld_hl_nn();
  void ldi_hl_a();
  void inc_hl();
  void inc_h();
  void dec_h();
  void ld_h_n();
  void daa();
  void jr_z_n();
  void add_hl_hl();
  void ld_a_hlpi();	//0x2A
  void dec_hl();
  void inc_l();
  void dec_l();
  void ld_l_n();
  void cpl();
  void jr_nc_n();		//0x30
  void ld_sp_nn();
  void ldd_hlp_a();
  void inc_sp();
  void inc_hlp();
  void dec_hlp();
  void ld_hlp_n();
  void scf();
  void jr_c_n();
  void add_hl_sp();
  void ld_a_hlpd();	//0x3A
  void dec_sp();
  void inc_a();
  void dec_a();
  void ld_a_n();
  void ccf();
  void ld_b_b();		//0x40
  void ld_b_c();
  void ld_b_d();
  void ld_b_e();
  void ld_b_h();
  void ld_b_l();
  void ld_b_hlp();
  void ld_b_a();
  void ld_c_b();
  void ld_c_c();
  void ld_c_d();		//0x4A
  void ld_c_e();
  void ld_c_h();
  void ld_c_l();
  void ld_c_hlp();
  void ld_c_a();
  void ld_d_b();		//0x50
  void ld_d_c();
  void ld_d_d();
  void ld_d_e();
  void ld_d_h();
  void ld_d_l();
  void ld_d_hlp();
  void ld_d_a();
  void ld_e_b();
  void ld_e_c();
  void ld_e_d();		//0x5A
  void ld_e_e();
  void ld_e_h();
  void ld_e_l();
  void ld_e_hlp();
  void ld_e_a();
  void ld_h_b();		//0x60
  void ld_h_c();
  void ld_h_d();
  void ld_h_e();
  void ld_h_h();
  void ld_h_l();
  void ld_h_hlp();
  void ld_h_a();
  void ld_l_b();
  void ld_l_c();
  void ld_l_d();
  void ld_l_e();
  void ld_l_h();
  void ld_l_l();
  void ld_l_hlp();
  void ld_l_a();		//0x6F
  void ld_hlp_b();
  void ld_hlp_c();
  void ld_hlp_d();
  void ld_hlp_e();
  void ld_hlp_h();
  void ld_hlp_l();
  void halt();
  void ld_hlp_a();
  void ld_a_b();
  void ld_a_c();
  void ld_a_d();
  void ld_a_e();
  void ld_a_h();
  void ld_a_l();
  void ld_a_hlp();
  void ld_a_a();		//0x7F
  void add_a_b();
  void add_a_c();
  void add_a_d();
  void add_a_e();
  void add_a_h();
  void add_a_l();
  void add_a_hlp();
  void add_a_a();
  void adc_a_b();
  void adc_a_c();
  void adc_a_d();
  void adc_a_e();
  void adc_a_h();
  void adc_a_l();
  void adc_a_hlp();
  void adc_a_a();		//0x8F
  void sub_b();
  void sub_c();
  void sub_d();
  void sub_e();
  void sub_h();
  void sub_l();
  void sub_hlp();
  void sub_a();
  void sbc_a_b();
  void sbc_a_c();
  void sbc_a_d();
  void sbc_a_e();
  void sbc_a_h();
  void sbc_a_l();
  void sbc_a_hlp();
  void sbc_a_a();		//0x9F
  void and_b();
  void and_c();
  void and_d();
  void and_e();
  void and_h();
  void and_l();
  void and_hlp();
  void and_a();
  void xor_b();
  void xor_c();
  void xor_d();
  void xor_e();
  void xor_h();
  void xor_l();
  void xor_hlp();
  void xor_a();		//0xAF
  void or_b();
  void or_c();
  void or_d();
  void or_e();
  void or_h();
  void or_l();
  void or_hlp();
  void or_a();
  void cp_b();
  void cp_c();
  void cp_d();
  void cp_e();
  void cp_h();
  void cp_l();
  void cp_hlp();
  void cp_a();		//0xBF
  void ret_nz();
  void pop_bc();
  void jp_nz_nn();
  void jp_nn();
  void call_nz_nn();
  void push_bc();
  void add_a_n();
  void rst_0();
  void ret_z();
  void ret();
  void jp_z_nn();
  void cb();
  void call_z_nn();
  void call_nn();
  void adc_a_n();
  void rst_08();		//0xCF
  void ret_nc();
  void pop_de();
  void jp_nc_nn();
  void call_nc_nn();
  void push_de();
  void sub_n();
  void rst_10();
  void ret_c();
  void reti();
  void jp_c_nn();
  void call_c_nn();
  void sbc_a_n();
  void rst_18();		//0xDF
  void ld_ffnp_a();
  void pop_hl();
  void ld_cp_a();
  void push_hl();
  void and_n();
  void rst_20();
  void add_sp_n();
  void jp_hlp();
  void ld_nnp_a();
  void xor_n();
  void rst_28();		//0xEF
  void ld_a_ffnp();
  void pop_af();
  void ld_a_cp();
  void di();
  void push_af();
  void or_n();
  void rst_30();
  void ld_hl_sp_n();
  void ld_sp_hl();
  void ld_a_nnp();
  void ei();
  void cp_n();
  void rst_38();

  void null();

  //Instructions accessed through CB
  void rlc_b();
  void rlc_c();
  void rlc_d();
  void rlc_e();
  void rlc_h();
  void rlc_l();
  void rlc_hlp();
  void rlc_a();
  void rrc_b();
  void rrc_c();
  void rrc_d();
  void rrc_e();
  void rrc_h();
  void rrc_l();
  void rrc_hlp();
  void rrc_a();
  void rl_b();
  void rl_c();
  void rl_d();
  void rl_e();
  void rl_h();
  void rl_l();
  void rl_hlp();
  void rl_a();
  void rr_b();
  void rr_c();
  void rr_d();
  void rr_e();
  void rr_h();
  void rr_l();
  void rr_hlp();
  void rr_a();
  void sla_b();
  void sla_c();
  void sla_d();
  void sla_e();
  void sla_h();
  void sla_l();
  void sla_hlp();
  void sla_a();
  void sra_b();
  void sra_c();
  void sra_d();
  void sra_e();
  void sra_h();
  void sra_l();
  void sra_hlp();
  void sra_a();
  void swap_b();
  void swap_c();
  void swap_d();
  void swap_e();
  void swap_h();
  void swap_l();
  void swap_hlp();
  void swap_a();
  void srl_b();
  void srl_c();
  void srl_d();
  void srl_e();
  void srl_h();
  void srl_l();
  void srl_hlp();
  void srl_a();
  void bit0_b();
  void bit0_c();
  void bit0_d();
  void bit0_e();
  void bit0_h();
  void bit0_l();
  void bit0_hlp();
  void bit0_a();
  void bit1_b();
  void bit1_c();
  void bit1_d();
  void bit1_e();
  void bit1_h();
  void bit1_l();
  void bit1_hlp();
  void bit1_a();
  void bit2_b();
  void bit2_c();
  void bit2_d();
  void bit2_e();
  void bit2_h();
  void bit2_l();
  void bit2_hlp();
  void bit2_a();
  void bit3_b();
  void bit3_c();
  void bit3_d();
  void bit3_e();
  void bit3_h();
  void bit3_l();
  void bit3_hlp();
  void bit3_a();
  void bit4_b();
  void bit4_c();
  void bit4_d();
  void bit4_e();
  void bit4_h();
  void bit4_l();
  void bit4_hlp();
  void bit4_a();
  void bit5_b();
  void bit5_c();
  void bit5_d();
  void bit5_e();
  void bit5_h();
  void bit5_l();
  void bit5_hlp();
  void bit5_a();
  void bit6_b();
  void bit6_c();
  void bit6_d();
  void bit6_e();
  void bit6_h();
  void bit6_l();
  void bit6_hlp();
  void bit6_a();
  void bit7_b();
  void bit7_c();
  void bit7_d();
  void bit7_e();
  void bit7_h();
  void bit7_l();
  void bit7_hlp();
  void bit7_a();
  void res0_b();
  void res0_c();
  void res0_d();
  void res0_e();
  void res0_h();
  void res0_l();
  void res0_hlp();
  void res0_a();
  void res1_b();
  void res1_c();
  void res1_d();
  void res1_e();
  void res1_h();
  void res1_l();
  void res1_hlp();
  void res1_a();
  void res2_b();
  void res2_c();
  void res2_d();
  void res2_e();
  void res2_h();
  void res2_l();
  void res2_hlp();
  void res2_a();
  void res3_b();
  void res3_c();
  void res3_d();
  void res3_e();
  void res3_h();
  void res3_l();
  void res3_hlp();
  void res3_a();
  void res4_b();
  void res4_c();
  void res4_d();
  void res4_e();
  void res4_h();
  void res4_l();
  void res4_hlp();
  void res4_a();
  void res5_b();
  void res5_c();
  void res5_d();
  void res5_e();
  void res5_h();
  void res5_l();
  void res5_hlp();
  void res5_a();
  void res6_b();
  void res6_c();
  void res6_d();
  void res6_e();
  void res6_h();
  void res6_l();
  void res6_hlp();
  void res6_a();
  void res7_b();
  void res7_c();
  void res7_d();
  void res7_e();
  void res7_h();
  void res7_l();
  void res7_hlp();
  void res7_a();
  void set0_b();
  void set0_c();
  void set0_d();
  void set0_e();
  void set0_h();
  void set0_l();
  void set0_hlp();
  void set0_a();
  void set1_b();
  void set1_c();
  void set1_d();
  void set1_e();
  void set1_h();
  void set1_l();
  void set1_hlp();
  void set1_a();
  void set2_b();
  void set2_c();
  void set2_d();
  void set2_e();
  void set2_h();
  void set2_l();
  void set2_hlp();
  void set2_a();
  void set3_b();
  void set3_c();
  void set3_d();
  void set3_e();
  void set3_h();
  void set3_l();
  void set3_hlp();
  void set3_a();
  void set4_b();
  void set4_c();
  void set4_d();
  void set4_e();
  void set4_h();
  void set4_l();
  void set4_hlp();
  void set4_a();
  void set5_b();
  void set5_c();
  void set5_d();
  void set5_e();
  void set5_h();
  void set5_l();
  void set5_hlp();
  void set5_a();
  void set6_b();
  void set6_c();
  void set6_d();
  void set6_e();
  void set6_h();
  void set6_l();
  void set6_hlp();
  void set6_a();
  void set7_b();
  void set7_c();
  void set7_d();
  void set7_e();
  void set7_h();
  void set7_l();
  void set7_hlp();
  void set7_a();
};
#endif //NEWGBEMU_CPU_HPP
