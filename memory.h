#ifndef __MEMORY_H__
#define __MEMORY_H__
#include "arduino.h"
#include "cpu.h"

/*
 Jump Rom Memory.
*/
#define JMP_START 0xffff0
#define JMP_END   0xfffff

/*
 Boot Rom
*/
#define ROM_SIZE  0x64
#define ROM_START JMP_START - ROM_SIZE
#define ROM_END   JMP_START

/*
 Interupt vector table RAM
*/
#define IVT_START 0
#define IVT_END   0x3ff

/*
 System Ram, could be external EEPROM, FLash etc.
*/
#define RAM_START 0x400
#define RAM_SIZE  0xff
#define RAM_END   RAM_START + RAM_SIZE

//Ram starts at low address 0x400
byte mem_ram256[255];
//IVT and GDT ram. starts at 0x0000. ends at 0x3ff
byte mem_low1024[1023];

//Rom starts at ,
//filled with 0x64 noops for now
byte mem_rom256[] = { 
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
};


/* 
 15bytes to make a jump,
 */
byte jmp_rom[] = {
  /*
   Test code for jmp rom
     mov ax, ROM_START      184, 256, 256, ( 0xb8, 0xff, 0xff)
     immediate to register, word, 
     mov cs, ax             142, 200, ( 0x8E, 0xC8 )
     reg to segment        
     jmp 0                 233, 249 (0xE9, 0xF9)             
    reset ip.
  */
  0xB8, 0xff, 0xff, 0x8E, 0xC8, 
  0xE9, 0xF9, 0x64, 0x00, 0x00, 
  0x00, 0x00, 0x64, 0x64, 0xff, 
  0xff
};

/*
  use up about 1k of precious ram
  64k segments.
  16 byte 
  For starter's.
  	Rom starts at processor initalisation point, for 1/4 segment?
  	Ram starts at 0x0000 for IVT (and GDT?)
  Memory map...
     0x0 -> 0x3ff
     	IVT
     0xfffff0 -> 0xfffff
     	Boot strap / BIOS
     0x400 -> 0xfffef
     	RAM 
*/
  /*typedef struct mem_s{
  		int size;
  		byte *data;
  }mem_t;

mem_t mem_ram256;

mem_t mem_rom256 = {
	2,
	{0x00,0x00}
}*/

/*
  Return a byte of memory from the loction provided by the Code Segment and Instruction Pointers.
*/
byte get_phys_byte( unsigned int ip){
  unsigned long mem = ( unsigned long )cpu86.regs.cs;
  mem = (mem << 4);
  mem += ip;
  
  /*
   is memory in IVT ?
  */
  if( mem <= IVT_END ){
    if( mem >= 0){
       return mem_low1024[mem];   
    }
  }
  
  /*
    TODO
    Is the location in external eeprom memory
  */
  
  
  /*
   test for location mem_rom256, at location ROM_START
  */
  if( mem >= ROM_START){
  	if( mem < ROM_END ){
  	 	if( ( mem - ROM_START ) < ROM_SIZE ){ 
  			return (byte)mem_rom256[mem - ROMSTART];
  	 	}
  	}
  }
  
  /*
   is the location in jmp rom, last address to check, at location 0xffff0 - 0xfffff
  */
  if( mem >= JMP_START ){
    if( mem <= JMP_END ){
         if( ( mem - JMP_START ) < 16 ){
           return (byte)jmp_rom[mem - JMP_START];
         }
      }
    }
  
  /*
    Return a noop86 instruction.
    TODO confirm we can use 0x0f as a noop.
  */
  return 0x0f;
}



#endif
