emu86
=====

8086 emulation on an arduino.

The arduino I plan on using this code with is a freetronics etherten, which is uno compatible.

I am using microcomputer systems: the 8086/8088 family, prentice-hall, 1986 as a guide.
Page's 129-134 list the opcode,s in a binary format.

Main code sections. (These may/will change)

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

To save space I will only be using one cpu_t type.