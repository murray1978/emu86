#ifndef __CPU_H__
#define __CPU_H__

typedef struct cpu{
  //cpu register's including IP.
  regs_t regs;
  //Program status word. ie flags.
  byte psw;
  //Instruction queue, some instructions are 6 bytes in length.
  byte i_q[6];
  unsigned int dataBus;
  unsigned int addressBus;
} cpu_t;

#endif