#ifndef __OPCODES_H__
#define __OPCODES_H__
#include "arduino.h"
#include "cpu.h"
#include "regs.h"
#include "memory.h"

extern cpu_t cpu86;

/*
*/
void set_cpu_opcodes( /*unsigned int displacment */){
  //unsigned int old_ip = cpu86.regs.ip;
  
  //cpu86.regs.ip += displacment;
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
void noop86(void){
cpu86.regs.ip += 1;
};

/*
  There are seven types of mov each of which can be detected
  using the first byte of the opcode.
*/
void mov86(void){
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
    cpu86.regs.ax = (unsigned int)cpu86.i_q[1];
    val = 2;
    break; 
  case 177: //cl
    cpu86.regs.cx = 0;
    cpu86.regs.cx = (unsigned int)cpu86.i_q[1];
    val = 2;
    break;
  case 178: //dl
    cpu86.regs.dx = 0;
    cpu86.regs.dx = (unsigned int)cpu86.i_q[1];
    val = 2;
    break;
  case 179: //bl
    cpu86.regs.bx = 0;
    cpu86.regs.bx = (unsigned int)cpu86.i_q[1];
    val = 2;
    break;
  case 180: //ah
    cpu86.regs.ax = 0;
    cpu86.regs.ax = (unsigned int)(cpu86.i_q[1] << 4);
    val = 2;
    break;
  case 181: //ch
    cpu86.regs.cx = 0;
    cpu86.regs.cx = (unsigned int)(cpu86.i_q[1] << 4);
    val = 2;
    break;
  case 182: //dh
    cpu86.regs.dx = 0;
    cpu86.regs.dx = (unsigned int)(cpu86.i_q[1] << 4);
    val = 2;
    break;
  case 183: //bh
    cpu86.regs.bx = 0;
    cpu86.regs.bx = (unsigned int)(cpu86.i_q[1] << 4);
    val = 2;
    break;
  //word, 2nd and 3rd byte
  case 184: //ax
    cpu86.regs.ax = (unsigned int)(cpu86.i_q[1] << 4);
    cpu86.regs.ax += (unsigned int)cpu86.i_q[2];
    val = 3;
    break;
  case 185: //cx
    cpu86.regs.cx = (unsigned int)(cpu86.i_q[1] << 4);
    cpu86.regs.cx += (unsigned int)cpu86.i_q[2];
    val = 3;
    break;
  case 186: //dx
    cpu86.regs.dx = (unsigned int)(cpu86.i_q[1] << 4);
    cpu86.regs.dx += (unsigned int)cpu86.i_q[2];
    val = 3;
    break;
  case 187: //bx
    cpu86.regs.bx = (unsigned int)(cpu86.i_q[1] << 4);
    cpu86.regs.bx += (unsigned int)cpu86.i_q[2];
    val = 3;
    break;
  case 188: //sp
    cpu86.regs.sp = (unsigned int)(cpu86.i_q[1] << 4);
    cpu86.regs.sp += (unsigned int)cpu86.i_q[2];
    val = 3;
    break;
  case 189: //bp
    cpu86.regs.bp = (unsigned int)(cpu86.i_q[1] << 4);
    cpu86.regs.bp += (unsigned int)cpu86.i_q[2];
    val = 3;
    break;
  case 190: //si
    cpu86.regs.si = (unsigned int)(cpu86.i_q[1] << 4);
    cpu86.regs.si += (unsigned int)cpu86.i_q[2];
    val = 3;
    break;
  case 191: //di
    cpu86.regs.di = (unsigned int)(cpu86.i_q[1] << 4);
    cpu86.regs.di += (unsigned int)cpu86.i_q[2];
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
    switch(cpu86.i_q[1]){
      //mod 0 sr r/m
      case 0: //disp = 0, val = 2, ES?, EA= bx + si + DISP
        val = 2;
        break;
      case 192: //1100 0000, val = 2, ES = AX
        cpu86.regs.es = cpu86.regs.ax;
        val = 2;
        break;
      case 193: //1100 0001, val = 2, ES = CX
        cpu86.regs.es = cpu86.regs.cx;
        val = 2;
        break;
      case 194: //1100 0010 val = 2, ES = DX
        cpu86.regs.es = cpu86.regs.dx;
        val = 2;
        break;
      case 195: //1100 0011 val = 2, ES = BX
        cpu86.regs.es = cpu86.regs.bx;
        val = 2;
        break;
      case 196: //1100 0100, val= 2, ES = SP
         cpu86.regs.es = cpu86.regs.sp;
         val = 2;
         break;
      case 197:  //1100 0101,  val = 2, ES = BP
          cpu86.regs.es = cpu86.regs.bp;
          val = 2;
          break;
      case 198: //1100 0110, val = 2, ES = SI
          cpu86.regs.es = cpu86.regs.si;    
          val = 2;
          break;
      case 199: //1100 0111, val = 2, ES = DI
          cpu86.regs.es = cpu86.regs.di;
          val = 2;
          break;
      case 200:  //1100 1000, val = 2, CS = AX
          cpu86.regs.cs = cpu86.regs.ax;
          val  = 2;
          break;
      case 201: //1100 1001, val = 2, CS = CX
          cpu86.regs.cs = cpu86.regs.cx;
          val = 2;
          break;
      case 216:
            //disp = 0, val = 2, r/m = reg, 11 = DS, 000 = AX
        cpu86.regs.ds = cpu86.regs.ax;
        val = 2;
        break;
        //case
      default:
        val = 2;
        break;
    }
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
  cpu86.regs.ip +=  val;
 };

//push reg/mem to stack
void push86(void){
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
  cpu86.regs.ip +=  val;
};

//pop reg/mem to stack, also adc type 3?
void pop86(void){
  unsigned int val = 1;
  switch( cpu86.i_q[0]){
      break;
      default:
      break;
    }
cpu86.regs.ip +=  val;
};

//exchange reg/mem with accumulator.
void xchg86(void){
  unsigned int val = 1;
    switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip += val;
};

//in from port, byte or word, fixed or variable port
void in86(void){
    unsigned int val= 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip +=  val;
};

//out to port, byte or word, fixed or variable length.
void out86(void){
    unsigned int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip += val;
};

/*
  translate byte to al???????
*/
void xlat86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip +=  1; //Known for sure.
};


/*
 Load EA to register.
*/
void lea86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip +=  4;
};

/*
  Load pointer to ds
*/
void lds86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip += 4;
};

/*
 Load pointer to es
*/
void les86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip += 4;
};

/*
 Load ah with flags
*/
void lahf86(void){
  cpu86.regs.ax = get_flags(cpu86.flags);
 cpu86.regs.ip += 1;
};

/*
 Store ah into flags
*/
void sahf86(void){
  set_flags( cpu86.flags, (cpu86.regs.ax >> 4)); 
  cpu86.regs.ip += 1;
};

/*
  Push flags onto stack
*/
void pushf86(void){
  cpu86.regs.ip +=  1;
};

/*
  pop flags off stack
*/
void popf86(void){
  cpu86.regs.ip +=  1;
};

/*
 Add
*/
void add86(void){
  unsigned int val = 1;
  switch( cpu86.i_q[0]){
     default:
      break;
    }
  cpu86.regs.ip += val;
};


/*
  Add with carry
*/
void adc86(void){
  unsigned int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip += 1;
};

/*
Inc
*/
void inc86(void){
  unsigned int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip +=  val;
};

/*
  ASCII adjust for add
*/
void aaa86(void){
cpu86.regs.ip += 1;
};

/*
 Decimal adjust for add
*/
void daa86(void){
cpu86.regs.ip +=  1;
};

/*
 Subtract
*/
void sub86(void){
  int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip +=  val;
};

/*
  Decrement
*/ 
void dec86(void){
    int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip += val;
};

/*
 Negate
 */
void neg86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip +=  4;
};

/* 
  Compare
*/
void cmp86(void){
  unsigned int val = 1;
      switch( cpu86.i_q[0]){
      default:
      break;
    }
cpu86.regs.ip +=  val;
};

/*
 ASCII adjust for subtract
*/
void aas86(void){
cpu86.regs.ip += 1;
};

/*
 Decimal adjust for subtraction.
*/
void das86(void){
cpu86.regs.ip += 1;
};

/*
 Multily unsigned
*/
void mul86(void){
 cpu86.regs.ip += 4;
};

/*
 Integer Multiply 
*/
void imul86(void){
  cpu86.regs.ip += 4;
};

/*
 ASCII Adjust for multiply
*/
void aam86(void){
  cpu86.regs.ip += 2;
};

/*
 Divide unsigned
 */
void div86(void){
   cpu86.regs.ip += 4;
};

/* 
 Integer Divide signed
*/
void idiv86(void){
  cpu86.regs.ip += 4;
};

/*
 ASCII Adjust for devide
*/
void aad86(void){
cpu86.regs.ip += 1;
};

/*
 Convert Byte to word
*/
void cbw86(void){
cpu86.regs.ip += 1;
};

/*
 Convert word to double word
*/
void cwd86(void){
  cpu86.regs.ip += 1;
};

/* 
 LOGIC operations
*/
 /*
  NOT
*/
void not86(void){
  cpu86.regs.ip += 4;
};

/*
 Shift logical/arithmetical left
*/
void shl86(void){
  cpu86.regs.ip += 4;
}; 

/*
 Shift Logical right
*/
void shr86(void){  
cpu86.regs.ip += 4;
};

/*
 Shift arithmetical right
*/
void sar86(void){
  cpu86.regs.ip += 4;
};

/*
 Rotate Left
*/
void rol86(void){
   cpu86.regs.ip += 4;
};

/*
 Rotate right
*/
void ror86(void){
  cpu86.regs.ip += 4;
};

/*
 Rotate through carry left
*/
void rcl86(void){
  cpu86.regs.ip += 4;
};

/*
 Rotate through carry right
*/
void rcr86(void){
  cpu86.regs.ip += 4;
};

/*
 And
*/
void and86(void){
  unsigned int val = 1;
  switch( cpu86.i_q[0]){
      default:
      break;
  }
  cpu86.regs.ip += val;
};

/*
 Test, And function to flags no results
*/
void test86(void){
  unsigned int val = 1;
  
  switch( cpu86.i_q[0]){
      default:
      break;
    }
 cpu86.regs.ip += val;
};

/*
 OR
*/
void or86(void){
  unsigned int val = 1;
  switch( cpu86.i_q[0]){
      default:
      break;
  }
  cpu86.regs.ip += val;
};

/*
XOR
*/
void xor86(void){
  unsigned int val = 1;
  switch( cpu86.i_q[0]){
      default:
      break;
  }
  cpu86.regs.ip += val;
};



//String manipulation
/*
 Repeat
*/
void rep86(void){
   cpu86.regs.ip += 1;
};


/*
 move byte word
*/
void movs86(void){
  cpu86.regs.ip += 1;
};

/*
  Compare byte word
*/
void cmps86(void){
  cpu86.regs.ip += 1;
};

/*
 scan byte/word
*/
void scas86(void){
  cpu86.regs.ip += 1;
};

/*
 load byte/word into al/ax
*/
void lods86(void){
  cpu86.regs.ip += 1;
};

/*
 Store byte/word from al/ax
*/
void stds86(void){
   cpu86.regs.ip += 1;
};

// CONTROL 
/*
 Call
*/
void call86(void){
  unsigned int val = 2;
  switch( cpu86.i_q[0]){
      default:
      break;
  }
  cpu86.regs.ip += val;
};

/*
 JMP
*/
void jmp86(void){
  //since we are modifing the IP we do not need to change the IP afterwards?
  unsigned int val = 1;  
  switch( cpu86.i_q[0]){
    case 235: //Jump direct with in segment short.
      val = (unsigned int)cpu86.i_q[1];
      break;
    default:
    break;
  }
 cpu86.regs.ip += val;
};

/*
 return from call
*/
void ret86(void){
  unsigned int val = 1;
   switch( cpu86.i_q[0]){
      default:
      break;
    }
  cpu86.regs.ip += val;
};

/*
  The jumps below would be with in the 65k boundry, unless it is a far jmp.
*/
/*
 JMP equal/zero
*/
void je86(void){
  cpu86.regs.ip += 2;
};

/*
 JMP less, not greater or equal
*/
void jl86(void){
 cpu86.regs.ip += 2;
};

/*
 JMP les or equal, no greater
*/
void jle86(void){
  cpu86.regs.ip += 2;
};

/*
 JMP below
*/ 
void jb86(void){
  cpu86.regs.ip += 2;
};

/*
JMP below or equal.
*/
void jbe86(void){
  cpu86.regs.ip += 2;
};

/*
 JMP parity bit set
*/
void jp86(void){
 cpu86.regs.ip += 2;
};

/*
 JMP overflow bit set
*/
void jo86(void){
  cpu86.regs.ip += 2;
};

/*
 JMP sgn bit set
*/
void js86(void){
  cpu86.regs.ip += 2;
};

/*
 JMP not equal, zero
 */
void jne86(void){
 cpu86.regs.ip += 2;
};

/*
 JMP not less
*/
void jnl86(void){
  cpu86.regs.ip += 2;
};

void jnle86(void){
 cpu86.regs.ip += 2;
};

void jnb86(void){
  cpu86.regs.ip += 2;
};

void jnbe86(void){
   cpu86.regs.ip += 2;
};

void jnp86(void){
   cpu86.regs.ip += 2;
};

void jno86(void){
     cpu86.regs.ip += 2;
};

void jns86(void){
   cpu86.regs.ip += 2;
};

void loop86(void){
 cpu86.regs.ip += 2;
};

void loopz86(void){
   cpu86.regs.ip += 2;
};

void loopnz86(void){
      cpu86.regs.ip += 2;
};

void jcxz86(void){
 cpu86.regs.ip += 2;
};
//interupts, oh joy
void int86(void){
 cpu86.regs.ip += 2;
};

void int3(void){
  cpu86.regs.ip += 1;
};

void into86(void){
   cpu86.regs.ip += 1;
};

void iret86(void){
   cpu86.regs.ip += 1;
};

//processor controll
//clear carry flag
void clc86(void){
  //clearFlagPSW( cpu86.psw, FLAG_CF );
  cpu86.flags.cf = 0;
  cpu86.regs.ip += 1;
};

//complement carry flag, NOT psw(FLAG_CF)
void cmc86(void){  
  cpu86.regs.ip += 1;
};

//Set carry flag, bitwise or
void stc86(void){
  cpu86.regs.ip += 1;
};

//Clear direction flag
void cld86(void){
  cpu86.regs.ip += 1;
};

//
void rstd86(void){
  cpu86.regs.ip += 1;
};

//Start interupts
void sti86(void){
  cpu86.regs.ip += 1;
};

//Clear interupts
void rcli86(void){
  cpu86.regs.ip += 1;
};

//Halt the processor
void hlt86(void){
  cpu86.regs.ip += 0;
};

//Wait for external device.
void wait86(void){
  if(0){ //extern device wakes us up
    cpu86.regs.ip += 1;
  }
  cpu86.regs.ip += 0;
};

//Let external device run
void esc86(void){
  cpu86.regs.ip += 1;
};

//Lock the bus, for us??
void lock86(void){
  cpu86.regs.ip += 1;
};

//Segment override 
void segment86(void){
  cpu86.regs.ip += 1;
};

#endif
