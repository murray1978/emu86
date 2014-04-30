#ifndef __OPCODE_TABLE_H__
#define __OPCODE_TABLE_H__
#include "opcodes.h"

/*
 Opcode fuction prototype, each opcode returns a ip displacement with it the current segment.
*/
typedef void(*__opcode_handler_t)(void);
 
/*
 Our simple data structe for the opcodes.
*/
typedef struct opcode_table{
  //byte opcode;
  __opcode_handler_t opcode_handler;
} opcode_table_t;



//INC i think is where I am at
/*
 The opcode table should take upto 255 bytes.
 unless a call is 2 bytes then it will be about 512 bytes.
 By the way this bit was fun.........not
 may need to move this bit to another header file.
*/
opcode_table_t opcode_table[] = {
  //add reg/mem to eihter
  {add86},   //0 add from reg byte
  {add86},   //1 add from reg word
  {add86},   //2 add to reg byte
  {add86},   //3 add to reg word

  //add immediate to accumilator
  {add86},   //4 add byte
  {add86},   //5 add word

  //push and pop segment registers
  {push86},    //6   es, push segment register
  {pop86},     //7   es, pop segment register
  {push86},    //14  cs, push segment register
  {pop86},     //15  cs, pop segment register

  //adc
  {adc86},     //16  from reg, byte
  {adc86},     //17  from reg, word
  {adc86},     //18  to reg, byte
  {adc86},     //19  to reg, word

  //adc acumilator
  {adc86},     //20 byte
  {adc86},     //21 word

  //push and pop
  {push86},    //22  ss, push segment register
  {pop86},     //23  ss, pop segment register
  {noop86},      //24
  {noop86},      //25
  {noop86},      //26
  {noop86},      //27
  {noop86},      //28
  {noop86},      //29
  //push and pop
  {push86},    //30  ds, push segment register
  {pop86},     //31  ds, pop segment register
  {noop86},      //32
  {noop86},      //33
  {noop86},      //34
  {noop86},      //35
  {noop86},      //36
  {noop86},      //37
  {noop86},      //38
  {noop86},      //39
  {noop86},      //40
  {noop86},      //41
  {noop86},      //42
  {noop86},      //43
  {noop86},      //44
  {noop86},      //45
  {noop86},      //46
  {noop86},      //47
  {noop86},      //48
  {noop86},      //49
  {noop86},      //50
  {noop86},      //51
  {noop86},      //52
  {noop86},      //53
  {noop86},      //54
  {noop86},      //55
  {noop86},      //56
  {noop86},      //57
  {noop86},      //58
  {noop86},      //59
  {noop86},      //60
  {noop86},      //61
  {noop86},      //62
  {noop86},      //63
  {noop86},      //64
  {noop86},      //65
  {noop86},      //66
  {noop86},      //67
  {noop86},      //68
  {noop86},      //69
  {noop86},      //70
  {noop86},      //71
  {noop86},      //72
  {noop86},      //73
  {noop86},      //74
  {noop86},      //75
  {noop86},      //76
  {noop86},      //77
  {noop86},      //78
  {noop86},      //79
  //push register
  {push86},    //80  AX
  {push86},    //81  CX
  {push86},    //82  DX
  {push86},    //83  BX
  {push86},    //84  SP
  {push86},    //85  BP
  {push86},    //86  SI
  {push86},    //87  DI

  //pop register
  {pop86},    //88 AX
  {pop86},    //89 CX
  {pop86},    //90 DX
  {pop86},    //91 BX
  {pop86},    //92 SP
  {pop86},    //93 BP
  {pop86},    //94 SI
  {pop86},    //95 DI
  
  {noop86},    //96
  {noop86},    //97
  {noop86},    //98
  {noop86},    //99
  {noop86},    //100
  {noop86},    //101
  {noop86},     //102
  {noop86},    //103
  {noop86},    //104
  {noop86},    //105
  {noop86},    //106
  {noop86},    //107
  {noop86},    //108
  {noop86},    //109
  {noop86},    //110
  {noop86},    //111
  {noop86},    //112
  {noop86},    //113
  {noop86},    //114
  {noop86},    //115
  {noop86},    //116
  {noop86},    //117
  {noop86},    //118
  {noop86},    //119
  {noop86},    //120
  {noop86},    //121
  {noop86},    //122
  {noop86},    //123
  {noop86},    //124
  {noop86},    //125
  {noop86},    //126
  {noop86},    //127
  
  //add immediate to reg/mem, adc second byte of opcode.
  {add86},     //128 unsigned byte, valid?
  {add86},     //129 unsigned word
  {add86},     //130
  {add86},     //131
  
  {noop86},      //132
  {noop86},      //133  

  //exchange, reg/mem with reg
  {xchg86},    //134  byte
  {xchg86},    //135  word

  //mov, 7 types of mov
  // type 1 reg/mem to/from reg
  {mov86},     //136    from reg, byte inst
  {mov86},     //137    from reg, word inst
  {mov86},     //138    to   reg, byte inst
  {mov86},     //139    to   reg, word inst

  //type 7, segment to reg/mem
  {mov86},     //140

  //lea
  {lea86},     //141

  //type 6, reg/mem to segment
  {mov86},     //142

  //pop reg/mem
  {pop86},     //143

  //exchange reg with accumilator
  {xchg86},    //144 ax
  {xchg86},    //145 cx
  {xchg86},    //146 dx
  {xchg86},    //147 bx
  {xchg86},    //148 sp
  {xchg86},    //149 bp
  {xchg86},    //150 si
  {xchg86},    //151 di  

  {noop86},      //152
  {noop86},      //153
  {noop86},      //154
  {noop86},      //155

  //pushf
  {pushf86},   //156
  //popf
  {popf86},    //157
  //sahf
  {sahf86},    //158
  //lahf
  {lahf86},    //159

  //type 4, memory to accum
  {mov86},     //160    byte
  {mov86},     //161    word
  //type 5, accum to memory
  {mov86},    //162      byte
  {mov86},    //163      word

  {noop86},     //164
  {noop86},     //165
  {noop86},     //166
  {noop86},     //167
  {noop86},     //168
  {noop86},     //169
  {noop86},     //170
  {noop86},      //171
  {noop86},      //172
  {noop86},      //173
  {noop86},      //174
  {noop86},       //175
  
  // type 3 imediate to reg
  {mov86},     //176   byte, reg al    
  {mov86},     //177   byte, reg cl
  {mov86},     //178   byte, reg dl
  {mov86},     //179   byte, reg bl 
  {mov86},     //180   byte, reg ah
  {mov86},     //181   byte, reg ch
  {mov86},     //182   byte, reg dh
  {mov86},     //183   byte, reg bh
  {mov86},     //184   word, reg ax
  {mov86},     //185   word, reg cx
  {mov86},     //186   word, reg dx
  {mov86},     //187   word, reg bx
  {mov86},     //188   word, reg sp
  {mov86},     //189   word, reg bp
  {mov86},     //190   word, reg si
  {mov86},     //191   word, reg di

  {noop86},      //192
  {noop86},      //193
  {noop86},      //194
  {noop86},      //195
  
  //les
  {les86},    //196
  //lds
  {lds86},    //197

  // type 2 imediate to reg/memory
  {mov86},     //198    byte instr
  {mov86},     //199    word instr

  {noop86},      //200
  {noop86},      //201
  {noop86},      //202
  {noop86},      //203
  {noop86},      //204
  {noop86},      //205
  {noop86},      //206
  {noop86},      //207
  {noop86},      //208
  {noop86},      //209
  {noop86},      //210
  {noop86},      //211
  {noop86},      //212
  {noop86},      //213
  {noop86},      //214
 
  //xlat
  {xlat86},    //215
  
  {noop86},      //216
  {noop86},      //217
  {noop86},      //218
  {noop86},      //219
  {noop86},      //220
  {noop86},      //221
  {noop86},      //222
  {noop86},      //223
  {noop86},      //224
  {noop86},      //225
  {noop86},      //226
  {noop86},      //227
  
  //in fixed port
  {in86},      //228 byte
  {in86},      //229 word
  //out fixed port
  {out86},     //230 byte
  {out86},     //231 word

  {noop86},      //232
  {noop86},      //233
  {noop86},      //234
  {jmp86},      //235, Jump direct within segment short.

  //in variable port
  {in86},      //236 byte
  {in86},      //237 word
  //out variable port
  {out86},     //238 byte
  {out86},     //239 word 
  
  {noop86},      //240
  {noop86},      //241
  {noop86},      //242
  {noop86},      //243
  {noop86},      //244
  {noop86},      //245
  {noop86},      //246
  {noop86},      //247
  {noop86},      //248
  {noop86},      //249
  {noop86},      //250
  {noop86},      //251
  {noop86},      //252
  {noop86},      //253
  {noop86},      //254
  
  //push reg/mem, inc, also check 2nd opcode byte
  {push86}   //255
};

#endif
