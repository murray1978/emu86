#ifndef __OPCODES_H__
#define __OPCODES_H__
void inc_ip(void){
  //reg_ip += (i_mod % 3 + 2*(!i_mod * i_rm == 6));
};


//opcode functions.
//if the cpu reads an invalid instruction.
void noop86(void){
  last_inst_size = 1;
};

//There are Seven types of mov,
//Each can be detected via the opcode.
void mov86(void){
  //i_q holds the six bytes of a potential instruction.
  switch( cpu86.i_q[0] ){
    //Type 1, reg/mem mov.
  case 136:
  case 137:
  case 138:
  case 139:
    last_inst_size = 4;
    break;
    //type 2 immediate to reg/mem
    //byte
  case 196:
    //word
  case 199:
    last_inst_size = 6;
    break;
    //case 3 immediate to reg
    //byte
  case 176:
  case 177:
  case 178:
  case 179:
  case 180:
  case 181:
  case 182:
  case 183:
    //word
  case 184:
  case 185:
  case 186:
  case 187:
  case 188:
  case 189:
  case 190:
  case 191:
    last_inst_size = 3;
    break;
  //case 4 mem to acc
  //byte
  case 160:
  //word
  case 161:
    last_inst_size = 3;
    break;
  //case 5 acc to mem
  //byte
  case 162:
  //word
  case 163:
    last_inst_size = 3;
    break;
  //case 6 reg/mem to segment
  case 142:
    last_inst_size = 4;
    break;
  //case 7 segment to reg/mem
  case 140:
    last_inst_size = 4;
    break;  
  default:
    break;    
  }
  last_inst_size = 6;
};

//push reg/mem to stack
void push86(void){
  switch(cpu86.i_q[0]){
     //push reg/mem
     case 255:
       last_inst_size = 4;
       break;
     case 80:
     case 81:
     case 82:
     case 83:
     case 84:
     case 85:
     case 86:
     case 87:
       last_inst_size = 1;
       break;
     case 6:
     case 14:
       last_inst_size = 1;
       break;
     default:
       break;
  }
};

//pop reg/mem to stack, also adc type 3?
void pop86(void){
  switch( cpu86.i_q[0]){
      case 2:
      case 3:
      case 4:
      break;
      default:
      break;
    }
  last_inst_size = 1;
};

//exchange reg/mem with accumulator.
void xchg86(void){
    switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};

//in from port, byte or word, fixed or variable port
void in86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};

//out to port, byte or word, fixed or variable length.
void out86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void xlat86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void lea86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void lds86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void les86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void lahf86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void sahf86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void pushf86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void popf86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void add86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  //need to check bit 4 to see if this is a adc
  last_inst_size = 1;
};
void adc86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void inc86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void aaa86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void daa86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void sub86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void dec86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void neg86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void cmp86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void aas86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void das86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void mul86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void imul86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void aam86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void div86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void idiv86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void aad86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void cbw86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void cwd86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void not86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void shl86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
}; //sal
void shr86(void){  
  switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void sar86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void rol86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void ror86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void rcl86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void rcr86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void and86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void test86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void or86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void xor86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
//String manipulation
void rep86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void movs86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void cmps86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void scas86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void lods86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void stds86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void call86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jmp86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void ret86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void je86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jl86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jle86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jb86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jbe86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jp86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jo86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void js86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jne86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jnl86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jnle86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jnb86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jnbe86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jnp86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jno86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jns86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void loop86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void loopz86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void loopnz86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void jcxz86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
//interupts, oh joy
void int86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void into86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};
void iret86(void){
      switch( cpu86.i_q[0]){
      default:
      break;
    }
  last_inst_size = 1;
};

//processor controll
//clear carry flag
void clc86(void){
  clearFlagPSW( cpu86.psw, FLAG_CF );
  last_inst_size = 1;
};

//complement carry flag, NOT psw(FLAG_CF)
void cmc86(void){  
  last_inst_size = 1;
};

//Set carry flag, bitwise or
void stc86(void){
  last_inst_size = 1;
};

//Clear direction flag
void cld86(void){
  last_inst_size = 1;
};

//
void rstd86(void){
  last_inst_size = 1;
};

//Start interupts
void sti86(void){
  last_inst_size = 1;
};

//Clear interupts
void rcli86(void){
  last_inst_size = 1;
};

//Halt the processor
void hlt86(void){
  last_inst_size = 1;
};

//Wait for external device.
void wait86(void){
  last_inst_size = 1;
};

//Let external device run
void esc86(void){
  last_inst_size = 1;
};

//
void lock86(void){
  last_inst_size = 1;
};

//
void segment86(void){
  last_inst_size = 1;
};

#endif
