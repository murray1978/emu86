#ifndef __OPCODES_H__
#define __OPCODES_H__
#include "arduino.h"
#include "cpu.h"
#include "regs.h"
#include "memory.h"

extern cpu_t cpu86;

/*
*/
void set_cpu_opcodes( unsigned int displacment ){
  unsigned int old_ip = cpu86.regs.ip;
  
  cpu86.regs.ip += displacment;
  if( cpu86.regs.ip < 0 ){
    //trap seg fault?
    cpu86.regs.ip = 0;
  }else if( cpu86.regs.ip > 0xffff){
    //trap seg fault?
    cpu86.regs.ip = 0;
  }

  cpu86.i_q[0] = (byte)get_phys_byte(cpu86.regs.ip);
  cpu86.i_q[1] = (byte)get_phys_byte(cpu86.regs.ip + 1);
  cpu86.i_q[2] = (byte)get_phys_byte(cpu86.regs.ip + 2);
  cpu86.i_q[3] = (byte)get_phys_byte(cpu86.regs.ip + 3);
  cpu86.i_q[4] = (byte)get_phys_byte(cpu86.regs.ip + 4);
  cpu86.i_q[5] = (byte)get_phys_byte(cpu86.regs.ip + 5);
}

//opcode functions.
//if the cpu reads an invalid instruction.
unsigned int noop86(void){
  return 1;
};

/*
  There are seven types of mov each of which can be detected
  using the first byte of the opcode.
*/
unsigned int mov86(void){
  unsigned int val = 0;
  //i_q holds the six bytes of a potential instruction.
  switch( cpu86.i_q[0] ){
    /*
     Type 1 mov, register/mem to/from register
     Second byte contains, mod, reg, r/m
     Third and Fortrhg byte contain the displacement bytes, hi and low.
    */
  case 136: //from register, size byte
  case 137: //from register, size word   
  case 138: //to register, size byte
  case 139: //to register, size word
    //each of these mov's are 4 bytes in size.
    val = 4;
    break;

  /*
    type 2 mov, immediate to reg/mem
    First byte is opcode telling us if it is a word or byte.
    second byte mod, 000, r/m
    third and forth bytes are displacement from current (IP/EA?)
    fith byte is data, 
    sixith is data if w=1
  */
  case 196: //byte, fith byte only
  case 199: //word, fith and sixith bytes
    val = 6;
    break;

  /*
    type 3 mov, immediate to reg
    Very simple opcode, first byte tells us if it is a word or byte 
    data, and which register we are using.
    2nd and 3rd bytes are data
  */
  //byte, 2nd byte only
  case 176: //al
    cpu86.regs.ax = 0;
    cpu86.regs.ax = cpu86.i_q[2];
    val = 2;
    break; 
  case 177: //cl
    cpu86.regs.cx = 0;
    cpu86.regs.cx = cpu86.i_q[2];
    val = 2;
    break;
  case 178: //dl
    cpu86.regs.dx = 0;
    cpu86.regs.dx = cpu86.i_q[2];
    val = 2;
    break;
  case 179: //bl
    cpu86.regs.bx = 0;
    cpu86.regs.bx = cpu86.i_q[2];
    val = 2;
    break;
  case 180: //ah
    cpu86.regs.ax = 0;
    cpu86.regs.ax = cpu86.i_q[2] << 4;
    val = 2;
    break;
  case 181: //ch
    cpu86.regs.cx = 0;
    cpu86.regs.cx = cpu86.i_q[2] << 4;
    val = 2;
    break;
  case 182: //dh
    cpu86.regs.dx = 0;
    cpu86.regs.dx = cpu86.i_q[2] << 4;
    val = 2;
    break;
  case 183: //bh
    cpu86.regs.bx = 0;
    cpu86.regs.bx = cpu86.i_q[2] << 4;
    val = 2;
    break;
  //word, 2nd and 3rd byte
  case 184: //ax
    cpu86.regs.ax = cpu86.i_q[2] << 4;
    cpu86.regs.ax += cpu86.i_q[3];
    val = 3;
    break;
  case 185: //cx
    cpu86.regs.cx = cpu86.i_q[2] << 4;
    cpu86.regs.cx += cpu86.i_q[3];
    val = 3;
    break;
  case 186: //dx
    cpu86.regs.dx = cpu86.i_q[2] << 4;
    cpu86.regs.dx += cpu86.i_q[3];
    val = 3;
    break;
  case 187: //bx
    cpu86.regs.bx = cpu86.i_q[2] << 4;
    cpu86.regs.bx += cpu86.i_q[3];
    val = 3;
    break;
  case 188: //sp
    cpu86.regs.sp = cpu86.i_q[2] << 4;
    cpu86.regs.sp += cpu86.i_q[3];
    val = 3;
    break;
  case 189: //bp
    cpu86.regs.bp = cpu86.i_q[2] << 4;
    cpu86.regs.bp += cpu86.i_q[3];
    val = 3;
    break;
  case 190: //si
    cpu86.regs.si = cpu86.i_q[2] << 4;
    cpu86.regs.si += cpu86.i_q[3];
    val = 3;
    break;
  case 191: //di
    cpu86.regs.di = cpu86.i_q[2] << 4;
    cpu86.regs.di += cpu86.i_q[3];
    val = 3;
    break;

  /*
    type 4 mem to acc, 2nd and 3rd bytes point to a memory location.
  */
  //byte
  case 160:
    val = 3;
    break;
  //word
  case 161:
    val = 3;
    break;

  /*
   type 5 acc to mem, 2nd and 3rd bytes point to a memory location
  */
  //byte
  case 162:
    val = 3;
    break;
  //word
  case 163:
    val = 3;
    break;

  /*
    type 6 reg/mem to segment
  */
  case 142:
    val = 4;
    break;

  /*
   type 7 segment to reg/mem
  */
  case 140:
    val = 4;
    break;

  /*
    Should never get here. treat opcode as no-op.
  */
  default:
    val = 1;
    break;    
  }
  return val;
 };

//push reg/mem to stack
unsigned int push86(void){
  unsigned int val = 1;
  switch(cpu86.i_q[0]){
     //push reg/mem
     case 255:
       val = 4;
       break;
     case 80:
     case 81:
     case 82:
     case 83:
     case 84:
     case 85:
     case 86:
     case 87:
       val = 1;
       break;
     case 6:
     case 14:
       val = 1;
       break;
     default:
       break;
  }
  return val;
};

//pop reg/mem to stack, also adc type 3?
unsigned int pop86(void){
  unsigned int val = 0;
  switch( cpu86.i_q[0]){
      case 2:
      case 3:
      case 4:
      break;
      default:
      break;
    }
  val = 1;
  return val;
};

//exchange reg/mem with accumulator.
unsigned int xchg86(void){
  unsigned int val = 1;
    switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

//in from port, byte or word, fixed or variable port
unsigned int in86(void){
    unsigned int val= 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

//out to port, byte or word, fixed or variable length.
unsigned int out86(void){
    unsigned int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

/*
  translate byte to al???????
*/
unsigned int xlat86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return 1; //Known for sure.
};


/*
 Load EA to register.
*/
unsigned int lea86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return 4;
};

/*
  Load pointer to ds
*/
unsigned int lds86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return 4;
};

/*
 Load pointer to es
*/
unsigned int les86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return 4;
};

/*
 Load ah with flags
*/
unsigned int lahf86(void){
  cpu86.regs.ax = cpu86.psw << 4;
  return 1;
};

/*
 Store ah into flags
*/
unsigned int sahf86(void){
  cpu86.psw = cpu86.regs.ax >> 4;
  return 1;
};

/*
  Push flags onto stack
*/
unsigned int pushf86(void){
  return 1;
};

/*
  pop flags off stack
*/
unsigned int popf86(void){
  return 1;
};

/*
 Add
*/
unsigned int add86(void){
  unsigned int val = 1;
  switch( cpu86.i_q[0]){
     default:
      break;
    }
  return val;
};


/*
  Add with carry
*/
unsigned int adc86(void){
  unsigned int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};

/*
Inc
*/
unsigned int inc86(void){
  unsigned int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

/*
  ASCII adjust for add
*/
unsigned int aaa86(void){
  return 1;
};

/*
 Decimal adjust for add
*/
unsigned int daa86(void){
  return 1;
};

/*
 Subtract
*/
unsigned int sub86(void){
  int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

/*
  Decrement
*/ 
unsigned int dec86(void){
    int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

/*
 Negate
 */
unsigned int neg86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return 4;
};

/* 
  Compare
*/
unsigned int cmp86(void){
  unsigned int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

/*
 ASCII adjust for subtract
*/
unsigned int aas86(void){
  return 1;
};

/*
 Decimal adjust for subtraction.
*/
unsigned int das86(void){
  return 1;
};

/*
 Multily unsigned
*/
unsigned int mul86(void){
  return 4;
};

/*
 Integer Multiply 
*/
unsigned int imul86(void){
  return 4;
};

/*
 ASCII Adjust for multiply
*/
unsigned int aam86(void){
  return 2;
};

/*
 Divide unsigned
 */
unsigned int div86(void){
   return 4;
};

/* 
 Integer Divide signed
*/
unsigned int idiv86(void){
  return 4;
};

/*
 ASCII Adjust for devide
*/
unsigned int aad86(void){
 return 2;
};

/*
 Convert Byte to word
*/
unsigned int cbw86(void){
 return 1;
};

/*
 Convert word to double word
*/
unsigned int cwd86(void){
  return 1;
};

/* 
 LOGIC operations
*/
 /*
  NOT
*/
unsigned int not86(void){
  return 4;
};

/*
 Shift logical/arithmetical left
*/
unsigned int shl86(void){
  return 4;
}; 

/*
 Shift Logical right
*/
unsigned int shr86(void){  
return 4;
};

/*
 Shift arithmetical right
*/
unsigned int sar86(void){
  return 4;
};

/*
 Rotate Left
*/
unsigned int rol86(void){
   return 4;
};

/*
 Rotate right
*/
unsigned int ror86(void){
  return 4;
};

/*
 Rotate through carry left
*/
unsigned int rcl86(void){
  return 4;
};

/*
 Rotate through carry right
*/
unsigned int rcr86(void){
  return 4;
};

/*
 And
*/
unsigned int and86(void){
  unsigned int val = 1;
  switch( cpu86.i_q[0]){
      default:
      break;
  }
  return val;
};

/*
 Test, And function to flags no results
*/
unsigned int test86(void){
  unsigned int val = 1;
  
  switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

/*
 OR
*/
unsigned int or86(void){
  unsigned int val = 1;
  switch( cpu86.i_q[0]){
      default:
      break;
  }
  return val;
};

/*
XOR
*/
unsigned int xor86(void){
  unsigned int val = 1;
  switch( cpu86.i_q[0]){
      default:
      break;
  }
  return val;
};



//String manipulation
/*
 Repeat
*/
unsigned int rep86(void){
   return 1;
};


/*
 move byte word
*/
unsigned int movs86(void){
  return 1;
};

/*
  Compare byte word
*/
unsigned int cmps86(void){
  return 1;
};

/*
 scan byte/word
*/
unsigned int scas86(void){
  return 1;
};

/*
 load byte/word into al/ax
*/
unsigned int lods86(void){
  return 1;
};

/*
 Store byte/word from al/ax
*/
unsigned int stds86(void){
   return 1;
};

// CONTROL 
/*
 Call
*/
unsigned int call86(void){
  unsigned int val = 1;
  switch( cpu86.i_q[0]){
      default:
      break;
  }
  return val;
};

/*
 JMP
*/
unsigned int jmp86(void){
  //since we are modifing the IP we do not need to change the IP afterwards?
  unsigned int val = 0;  
  switch( cpu86.i_q[0]){
    case 235: //Jump direct with in segment short.
      cpu86.regs.ip = (unsigned int)cpu86.i_q[1];
      break;
    default:
    break;
  }
 return val;
};

/*
 return from call
*/
unsigned int ret86(void){
  unsigned int val = 1;
   switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

/*
  The jumps below would be with in the 65k boundry, unless it is a far jmp.
*/
/*
 JMP equal/zero
*/
unsigned int je86(void){
  return 2;
};

/*
 JMP less, not greater or equal
*/
unsigned int jl86(void){
  return 2;
};

/*
 JMP les or equal, no greater
*/
unsigned int jle86(void){
  return 2;
};

/*
 JMP below
*/ 
unsigned int jb86(void){
  return 2;
};

/*
JMP below or equal.
*/
unsigned int jbe86(void){
  return 2;
};

/*
 JMP parity bit set
*/
unsigned int jp86(void){
 return 2;
};

/*
 JMP overflow bit set
*/
unsigned int jo86(void){
return 2;
};

/*
 JMP sgn bit set
*/
unsigned int js86(void){
  return 2;
};

/*
 JMP not equal, zero
 */
unsigned int jne86(void){
 return 2;
};

/*
 JMP not less
*/
unsigned int jnl86(void){
  return 2;
};

unsigned int jnle86(void){
 return 2;
};

unsigned int jnb86(void){
  return 2;
};

unsigned int jnbe86(void){
   return 2;
};

unsigned int jnp86(void){
   return 2;
};

unsigned int jno86(void){
     return 2;
};

unsigned int jns86(void){
   return 2;
};

unsigned int loop86(void){
 return 2;
};

unsigned int loopz86(void){
   return 2;
};

unsigned int loopnz86(void){
      return 2;
};

unsigned int jcxz86(void){
 return 2;
};
//interupts, oh joy
unsigned int int86(void){
 return 2;
};

unsigned int int3(void){
  return 1;
};

unsigned int into86(void){
   return 1;
};

unsigned int iret86(void){
   return 1;
};

//processor controll
//clear carry flag
unsigned int clc86(void){
  clearFlagPSW( cpu86.psw, FLAG_CF );
  return 1;
};

//complement carry flag, NOT psw(FLAG_CF)
unsigned int cmc86(void){  
  return 1;
};

//Set carry flag, bitwise or
unsigned int stc86(void){
  return 1;
};

//Clear direction flag
unsigned int cld86(void){
  return 1;
};

//
unsigned int rstd86(void){
  return 1;
};

//Start interupts
unsigned int sti86(void){
  return 1;
};

//Clear interupts
unsigned int rcli86(void){
  return 1;
};

//Halt the processor
unsigned int hlt86(void){
  return 0;
};

//Wait for external device.
unsigned int wait86(void){
  if(0){ //extern device wakes us up
    return 1;
  }
  return 0;
};

//Let external device run
unsigned int esc86(void){
  return 1;
};

//Lock the bus, for us??
unsigned int lock86(void){
  return 1;
};

//Segment override 
unsigned int segment86(void){
  return 1;
};

#endif
