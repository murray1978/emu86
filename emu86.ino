/*
 emu86, 86 emulator for arduino,
 Microcomputer systems: the 8088/8086 family, 2nd Ed, Prentice-Hall
 used as a refrence.
 Murray Smith, 4/4/14
 */
#include "regs.h"
#include "cpu.h"
#include "opcodes.h"
#include "memory.h"
#include "bc.h"
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);

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

/*
  Reset the cpu to a known state.
  CS, DS, SS, ES need to point to a valid segment ie ROM_SEGMENT
  SP, BP, SI, DI, IP need the correct values for the cpu to find 
  data/code/stack at start up
*/
void cpu_reset(){
  //clear registers, program status word. ie flags
  //cpu86.flags = 0;

  //general purpose
  cpu86.regs.ax = 0;    //Accumulator, AH+AL, and,or,xor,shl,shr etc
  cpu86.regs.bx = 0;    //Base BH+BL,  translate
  cpu86.regs.cx = 0;    //Count CH+CL, string and loop operations
  cpu86.regs.dx = 0;    //Data DH+DL

  //segments
  cpu86.regs.cs = 0xffff;    //current code segment, ip,mov? 
  cpu86.regs.ss = 0x03ff;          //current stack segment
  cpu86.regs.ds = 0xffff;          //current data segment, mov,
  cpu86.regs.es = 0xffff;          //current extra segment
  
   //ponters
             //Stack operations
  cpu86.regs.sp = 0;     //stack pointer
  cpu86.regs.bp = 0;     //base pointer
             //String operations
  cpu86.regs.si = 0;     //source index
  cpu86.regs.di = 0;     //destination index
             //Instruction pointer
  cpu86.regs.ip = 0;    //offset from cs, so physical address is ((cs << 4) + ip)?
  
  //data in i_q
  cpu86.i_q[0] = 100;    //should equate to a noop 
  cpu86.i_q[1] = 0;
  cpu86.i_q[2] = 0;
  cpu86.i_q[3] = 0;
  cpu86.i_q[4] = 0;
  cpu86.i_q[5] = 0;
  
}

/*
 Initalise a section of ram to a known state.
*/
void init_ram( byte *ram, int len ){
  int i = 0;
  for( i = 0; i < len; i++ ){
    ram[i] = 22;
  }
}

void setup(){
  //Startup the lcd driver.
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("emu86 V0.05");
  lcd.setCursor(0,1);
  
  //resetCpu to a known state.
  cpu_reset();
  lcd.print("cpu86 reset");
  delay(600);
  
  //reset code ram to a known state.
  init_ram( mem_ram256, 255);
  lcd.setCursor(0,1);
  lcd.print("ram 256b init");
  delay(600);
  
  //reset IVT ram to a known state
  init_ram( mem_low1024, 1023);
  lcd.setCursor(0,1);
  lcd.print("IVT ram 1024b set");
  delay(1200);
 
  //Inform the user that the processor is running 
  lcd.setCursor(0,1);
  lcd.print("cpu86 started");
  delay(1200);
  
}

void loop(){

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("OC   IP    MEM");
  lcd.setCursor(0,1);
  lcd.print( (unsigned int)cpu86.i_q[0] );
  
  //get 6 bytes of code into cpu86.i_q
  set_cpu_opcodes();
  cpuloop((unsigned int)cpu86.i_q[0]);
  //shift data via data/address/status pins
 

  lcd.setCursor(5,1);
  lcd.print( cpu86.regs.ip );
  lcd.setCursor(8,1);
  delay(750);
}



