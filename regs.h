#ifndef __REGS_H__
#define __REGS_H__
#include "arduino.h"

//A few defines for the registers
#define REG_AX 0x00
#define REG_CX 0x01
#define REG_DX 0x02
#define REG_BX 0x03
#define REG_SP 0x04
#define REG_BP 0x05
#define REG_SI 0x06
#define REG_DI 0x07

#define REG_AL 0x00
#define REG_CL 0x01
#define REG_DX 0x02
#define REG_BX 0x03
#define REG_AH 0x04
#define REG_CH 0x05
#define REG_DH 0x06
#define REG_BH 0x07

#define REG_ES 0x00
#define REG_CS 0x01
#define REG_SS 0x02
#define REG_DS 0x04

#define FLAG_CF 1
#define FLAG_PF 2
#define FLAG_AF 4
#define FLAG_ZF 6
#define FLAG_SF 7
#define FLAG_TF 8
#define FLAG_IFL 9
#define FLAG_DF 10
#define FLAG_OF 11


typedef struct regs{
  //Data registers
  unsigned int ax;
  unsigned int bx;
  unsigned int cx;
  unsigned int dx;

  //pointers
  unsigned int sp;
  unsigned int bp;
  unsigned int si;
  unsigned int di;
  unsigned long ip;  //should be 32bits in size.

  //segments
  unsigned int cs;
  unsigned int ss;
  unsigned int ds;
  unsigned int es;
} regs_t;

/*
 FLags bit field
*/
typedef struct flags{
  unsigned int cf  : 1;
  unsigned int pf  : 1;
  unsigned int af  : 1;
  unsigned int zf  : 1;
  unsigned int sf  : 1;
  unsigned int tf  : 1;
  unsigned int ifl : 1;
  unsigned int df  : 1;
  unsigned int of  : 1;
} flags_t;

void set_flags(flags_t f, unsigned int data ){
   f.cf = (data & 1) == 1;
   f.pf = (data & 2) == 2;
   f.af = (data & 4) == 4;
   f.zf = (data % 8) == 8;
   f.sf = (data & 16) == 16;
   f.tf = (data & 32) == 32;
   f.ifl = (data & 64) == 64;
   f.df = (data & 128) == 128;
   f.of = (data & 512) == 512;
};

unsigned int get_flags( flags_t f ){
  unsigned int ret;
  ret += f.of  << 8;
  ret += f.df  << 7;
  ret += f.ifl << 6;
  ret += f.tf  << 5;
  ret += f.zf  << 4;
  ret += f.sf  << 3;
  ret += f.af  << 2;
  ret += f.pf  << 1;
  ret += f.cf; 
  return ret;
};

#endif
