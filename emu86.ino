/*
 emu86, 86 emulator for arduino,
 Microcomputer systems: the 8088/8086 family, 2nd Ed, Prentice-Hall
 used as a refrence.
 Murray Smith, 4/4/14
 */
#include "regs.h"
#include "cpu.h"
#include "opcodes.h"

cpu_t cpu86;

typedef void (*__opcode_handler_t)(void);

typedef struct opcode_table{
  // byte opcode;
  __opcode_handler_t opcode_handler;
} opcode_table_t;


void setFlagPSW( byte &psw, byte flag){
  psw |= flag;
}

//Decode and return true if a flag is set.
boolean decodePSW( byte psw, byte flag ){
  byte temp = psw;
  if( flag == FLAG_CF ){
    return temp & 1;
  }
  return (( temp >> flag ) & 1);
}



//By the way this bit was fun.........not
opcode_table_t opcode_table[] = {
  //add reg/mem to eihter
  add86,   //0 add from reg byte
  add86,   //1 add from reg word
  add86,   //2 add to reg byte
  add86,   //3 add to reg word

  //add immediate to accumilator
  add86,   //4 add byte
  add86,   //5 add word

  //push and pop segment registers
  push86,    //6   es, push segment register
  pop86,     //7   es, pop segment register
  push86,    //14  cs, push segment register
  pop86,     //15  cs, pop segment register

  //adc
  adc86,     //16  from reg, byte
  adc86,     //17  from reg, word
  adc86,     //18  to reg, byte
  adc86,     //19  to reg, word

  //adc acumilator
  adc86,     //20 byte
  adc86,     //21 word

  //push and pop
  push86,    //22  ss, push segment register
  pop86,     //23  ss, pop segment register
  push86,    //30  ds, push segment register
  pop86,     //31  ds, pop segment register

  //push register
  push86,    //80  AX
  push86,    //81  CX
  push86,    //82  DX
  push86,    //83  BX
  push86,    //84  SP
  push86,    //85  BP
  push86,    //86  SI
  push86,    //87  DI

  //pop register
  pop86,    //88 AX
  pop86,    //89 CX
  pop86,    //90 DX
  pop86,    //91 BX
  pop86,    //92 SP
  pop86,    //93 BP
  pop86,    //94 SI
  pop86,    //95 DI

  //add immediate to reg/mem, adc second byte of opcode.
  add86,     //128 unsigned byte, valid?
  add86,     //129 unsigned word
  add86,     //130
  add86,     //131

  //exchange, reg/mem with reg
  xchg86,    //134  byte
  xchg86,    //135  word

  //mov, 7 types of mov
  // type 1 reg/mem to/from reg
  mov86,     //136    from reg, byte inst
  mov86,     //137    from reg, word inst
  mov86,     //138    to   reg, byte inst
  mov86,     //139    to   reg, word inst

  //type 7, segment to reg/mem
  mov86,     //140

  //lea
  lea86,     //141

  //type 6, reg/mem to segment
  mov86,     //142

  //pop reg/mem
  pop86,     //143

  //exchange reg with accumilator
  xchg86,    //144 ax
  xchg86,    //145 cx
  xchg86,    //146 dx
  xchg86,    //147 bx
  xchg86,    //148 sp
  xchg86,    //149 bp
  xchg86,    //150 si
  xchg86,    //151 di  

  //pushf
  pushf86,   //156
  //popf
  popf86,    //157
  //sahf
  sahf86,    //158
  //lahf
  lahf86,    //159

  //type 4, memory to accum
  mov86,     //160    byte
  mov86,     //161    word
  //type 5, accum to memory
  mov86,    //162      byte
  mov86,    //163      word

  // type 3 imediate to reg
  mov86,     //176   byte, reg al    
  mov86,     //177   byte, reg cl
  mov86,     //178   byte, reg dl
  mov86,     //179   byte, reg bl 
  mov86,     //180   byte, reg ah
  mov86,     //181   byte, reg ch
  mov86,     //182   byte, reg dh
  mov86,     //183   byte, reg bh
  mov86,     //184   word, reg ax
  mov86,     //185   word, reg cx
  mov86,     //186   word, reg dx
  mov86,     //187   word, reg bx
  mov86,     //188   word, reg sp
  mov86,     //189   word, reg bp
  mov86,     //190   word, reg si
  mov86,     //191   word, reg di

  //les
  les86,    //196
  //lds
  lds86,    //197

  // type 2 imediate to reg/memory
  mov86,     //198    byte instr
  mov86,     //199    word instr

  //xlat
  xlat86,    //215

  //in fixed port
  in86,      //228 byte
  in86,      //229 word
  //out fixed port
  out86,     //230 byte
  out86,     //231 word

  //in variable port
  in86,      //236 byte
  in86,      //237 word
  //out variable port
  out86,     //238 byte
  out86,     //239 word 
  //push reg/mem, inc, also check 2nd opcode byte
  push86   //255
};



//emulate a power on reset.
//could use rand for most of these.
void cpu_reset(){
  //clear registers, program status word.
  cpu86.psw = 0;

  //general purpose
  cpu86.regs.ax = 0;
  cpu86.regs.bx = 0;
  cpu86.regs.cx = 0;
  cpu86.regs.dx = 0;

  //ponters
  cpu86.regs.sp = 0;
  cpu86.regs.bp = 0;
  cpu86.regs.si = 0;
  cpu86.regs.di = 0;
  cpu86.regs.ip = 0;

  //segments
  cpu86.regs.cs = 0;
  cpu86.regs.ss = 0;
  cpu86.regs.ds = 0;
  cpu86.regs.es = 0;
}

//
void genAddress(){
  //cpu86.addressBus = 0;
}

void setup(){
  //Serial.begin(9600); //about 1k of code.
  cpu_reset();
  //genAddress(cpu86);
}

byte opcode = 0;
void loop(){

  //get 6 bytes of code into cpu86.i_q
  //decode first byte, via
  //genAddress(cpu86);
  inc_ip();
  opcode = cpu86.i_q[0];
  opcode_table[opcode];
  //shift data via data/address/status pins
}



