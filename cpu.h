#ifndef __CPU_H__
#define __CPU_H__
#include "arduino.h"

//increment intstruction pointer.
//needs to take last instruction into account.
byte last_inst_size;

void clearFlagPSW( byte &psw, byte flag){
  psw ^= flag;
}

typedef struct cpu{
  //cpu register's including IP.
  regs_t regs;
  //Program status word. ie flags.
  byte psw;
  //Instruction queue, some instructions are 6 bytes in length.
  byte i_q[6];
  unsigned int dataBus;
  unsigned long addressBus;
} cpu_t;

//having this variable global is very bad, but.
//we should only change it once per loop, ie
//when an opcode is about to return a change in ip is
// made
cpu_t cpu86;

#endif
