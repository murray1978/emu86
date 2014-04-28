#ifndef __REGS_H__
#define __REGS_H__

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
  unsigned long ip;  //should be 20bits in size.

  //segments
  unsigned int cs;
  unsigned int ss;
  unsigned int ds;
  unsigned int es;
} regs_t;

#endif