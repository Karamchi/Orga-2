/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "colors.h"
#include "defines.h"
#include "game.h"
#include "syscall.h" 

void task() {
    /* Tarea */
  int i;
  for(i=0;i<4;i++)
  syscall_mover(ADE);
  int j=0;
  int* src = (int*)0x8000248;
  while(1) {
    syscall_mover(ADE);
    for (i=1; i<9; i++) {
    	int* dst = (int*)(0x8000000+i*0x1000);
    	for (j=0; j<300; j++) {
    		dst[j] = src[j];
    	}
    }
    syscall_mover(DER);
    for (i=1; i<9; i++) {
    	int* dst = (int*)(0x8000000+i*0x1000);
    	for (j=0; j<400; j++) {
    		dst[j] = src[j];
    	}
    }
    
	syscall_mover(ATR);
	for (i=1; i<9; i++) {
    	int* dst = (int*)(0x8000000+i*0x1000);
    	for (j=0; j<400; j++) {
    		dst[j] = src[j];
    	}
    }
    
	syscall_mover(IZQ);
	for (i=1; i<9; i++) {
    	int* dst = (int*)(0x8000000+i*0x1000);
    	for (j=0; j<400; j++) {
    		dst[j] = src[j];
    	}
    }
    
	syscall_mover(ADE);
	for (i=1; i<9; i++) {
    	int* dst = (int*)(0x8000000+i*0x1000);
    	for (j=0; j<400; j++) {
    		dst[j] = src[j];
    	}
    }
    
  }
  
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  syscall_mover(ATR);
  /*while(1) {
    int i;
    for(i=0;i<10;i++)
    syscall_mover(ADE);
    for(i=0;i<10;i++)
    syscall_mover(DER);
    for(i=0;i<5;i++)
    syscall_mover(ATR);
    for(i=0;i<5;i++)
    syscall_mover(IZQ);
    for(i=0;i<500;i++)
    syscall_mover(ATR);
  } 
  while(1) { __asm __volatile("mov $2, %%eax":::"eax"); }
  */
}
