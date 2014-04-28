#ifndef __OPCODES_H__
#define __OPCODES_H__
#include "arduino.h"
#include "cpu.h"
#include "regs.h"

extern cpu_t cpu86;

void inc_ip(void){
  //reg_ip += (i_mod % 3 + 2*(!i_mod * i_rm == 6));
};


//opcode functions.
//if the cpu reads an invalid instruction.
int noop86(void){
  return 1;
};

/*
  There are seven types of mov each of which can be detected
  using the first byte of the opcode.
*/
int mov86(void){
  int val = 0;
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
    cpu86.ax = 0;
    cpu86.ax = cpu86.i_q[2];
    val = 2;
    break; 
  case 177: //cl
    cpu86.cx = 0;
    cpu86.cx = cpu86.i_q[2];
    val = 2;
    break;
  case 178: //dl
    cpu86.dx = 0;
    cpu86.dx = cpu86.i_q[2];
    val = 2;
    break;
  case 179: //bl
    cpu86.bx = 0;
    cpu86.bx = cpu86.i_q[2];
    val = 2;
    break;
  case 180: //ah
    cpu86.ax = 0;
    cpu86.ax = cpu86.i_q[2]; << 4;
    val = 2;
    break;
  case 181: //ch
    cpu86.cx = 0;
    cpu86.ax = cpu86.i_q[2] << 4;
    val = 2;
    break;
  case 182: //dh
    cpu86.dx = 0;
    cpu86.dx = cpu86.i_q[2] << 4;
    val = 2;
    break;
  case 183: //bh
    cpu86.bx = 0;
    cpu86.bx = cpu86.i_q[2] << 4;
    val = 2;
    break;
  //word, 2nd and 3rd byte
  case 184: //ax
    cpu86.ax = cpu86.i_q[2] << 4;
    cpu86.ax += cpu86.i_q[3];
    val = 3;
    break;
  case 185: //cx
    cpu86.cx = cpu86.i_q[2] << 4;
    cpu86.cx += cpu86.i_q[3];
    val = 3;
    break;
  case 186: //dx
    cpu86.dx = cpu86.i_q[2] << 4;
    cpu86.dx += cpu86.i_q[3];
    val = 3;
    break;
  case 187: //bx
    cpu86.bx = cpu86.i_q[2] << 4;
    cpu86.bx += cpu86.i_q[3];
    val = 3;
    break;
  case 188: //sp
    cpu86.sp = cpu86.i_q[2] << 4;
    cpu86.sp += cpu86.i_q[3];
    val = 3;
    break;
  case 189: //bp
    cpu86.bp = cpu86.i_q[2] << 4;
    cpu86.bp += cpu86.i_q[3];
    val = 3;
    break;
  case 190: //si
    cpu86.si = cpu86.i_q[2] << 4;
    cpu86.si += cpi86.i_q[3];
    val = 3
    break;
  case 191: //di
    cpu86.di = cpu86.i_q[2] << 4;
    cpu86.di += cpu86.i_q[3];
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
int push86(void){
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
int pop86(void){
  int val = 0;
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
int xchg86(void){
  int val = 1;
    switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

//in from port, byte or word, fixed or variable port
int in86(void){
    int val= 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

//out to port, byte or word, fixed or variable length.
int out86(void){
    int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

/*
  translate byte to al???????
*/
int xlat86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return 1; //Known for sure.
};


/*
 Load EA to register.
*/
int lea86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return 4;
};

/*
  Load pointer to ds
*/
int lds86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return 4;
};

/*
 Load pointer to es
*/
int les86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return 4;
};

/*
 Load ah with flags
*/
int lahf86(void){
  cpu86.ax = cpu86.psw << 4;
  return 1;
};

/*
 Store ah into flags
*/
int sahf86(void){
  cpu86.psw = cpu86.ax >> 4;
  return 1;
};

/*
  Push flags onto stack
*/
int pushf86(void){
  return 1;
};

/*
  pop flags off stack
*/
int popf86(void){
  return 1;
};

/*
 Add
*/
int add86(void){
  int val = 1;
  switch( cpu86.i_q[0]){
     default:
      break;
    }
  return val;
};


/*
  Add with carry
*/
int adc86(void){
  int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};

/*
Inc
*/
int inc86(void){
  int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

/*
  ASCII adjust for add
*/
int aaa86(void){
  return 1;
};

/*
 Decimal adjust for add
*/
int daa86(void){
  return 1;
};

/*
 Subtract
*/
int sub86(void){
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
int dec86(void){
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
int neg86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return 4;
};

/* 
  Compare
*/
int cmp86(void){
  int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  return val;
};

/*
 ASCII adjust for subtract
*/
int aas86(void){
  return 1;
};

/*
 Decimal adjust for subtraction.
*/
int das86(void){
  return 1;
};

/*
 Multily unsigned
*/
int mul86(void){
  return 4;
};

/*
 Integer Multiply 
*/
int imul86(void){
  return 4;
};

/*
 ASCII Adjust for multiply
*/
int aam86(void){
  return 2;
};

/*
 Divide unsigned
 */
int div86(void){
   return 4;
};

/* 
 Integer Divide signed
*/
int idiv86(void){
  return 4;
};

/*
 ASCII Adjust for devide
*/
int aad86(void){
 return 2;
};

/*
 Convert Byte to word
*/
int cbw86(void){
 return 1;
};

/*
 Convert word to double word
*/
int cwd86(void){
return 1;
};

/* 
 LOGIC operations
*/
 /*
  NOT
*/
int not86(void){
return 4;
};

/*
 Shift logical/arithmetical left
*/
int shl86(void){
  return 4;
}; 

/*
 Shift Logical right
*/
int shr86(void){  
return 4;
};

/*
 Shift arithmetical right
*/
int sar86(void){
  return 4;
};

/*
 Rotate Left
*/
int rol86(void){
   return 4;
};

/*
 Rotate right
*/
int ror86(void){
   return 4;
};
void rcl86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void rcr86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void and86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void test86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void or86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void xor86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
//String manipulation
void rep86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void movs86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void cmps86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void scas86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void lods86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void stds86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void call86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jmp86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void ret86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void je86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jl86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jle86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jb86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jbe86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jp86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jo86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void js86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jne86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jnl86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jnle86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jnb86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jnbe86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jnp86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jno86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jns86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void loop86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void loopz86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void loopnz86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void jcxz86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
//interupts, oh joy
void int86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void into86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};
void iret86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  val = 1;
};

//processor controll
//clear carry flag
void clc86(void){
  clearFlagPSW( cpu86.psw, FLAG_CF );
  val = 1;
};

//complement carry flag, NOT psw(FLAG_CF)
void cmc86(void){  
  val = 1;
};

//Set carry flag, bitwise or
void stc86(void){
  val = 1;
};

//Clear direction flag
void cld86(void){
  val = 1;
};

//
void rstd86(void){
  val = 1;
};

//Start interupts
void sti86(void){
  val = 1;
};

//Clear interupts
void rcli86(void){
  val = 1;
};

//Halt the processor
void hlt86(void){
  val = 1;
};

//Wait for external device.
void wait86(void){
  val = 1;
};

//Let external device run
void esc86(void){
  val = 1;
};

//
void lock86(void){
  val = 1;
};

//
void segment86(void){
  val = 1;
};

#endif
