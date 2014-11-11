/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "i386.h"



void tss_completar_libre(tss *t, char tipo, char jugador, int pos){
		int cr3 = mmu_inicializar_dir_zombi(tipo, jugador, pos);
		t->cr3 = cr3;
		// jugador A: 0, jugador B: 1 
		t->eip = 0x8000000;
		t->eflags=0x202;
		t->esp = 0x8001000;
		t->ebp = 0x8001000;
		short seg_dat = 0x5B;
		short seg_cod = 0x53;
		t->es = seg_dat;
		t->cs = seg_cod;
		t->ss = seg_dat;
		t->ds = seg_dat;
		t->fs = seg_dat;
		t->gs = seg_dat;
		t->ss0 = 0x48;
		t->esp0 = pedir_pagina() + 0x1000;
		t->iomap = 0xFFFF;

}

void tss_inicializar() { //bases
	gdt[GDT_TAREA_INICIAL].base_0_15 = (int)&tss_inicial & 0xFFFF;
	gdt[GDT_TAREA_INICIAL].base_23_16 = ((int)&tss_inicial >> 16) & 0xFF;
	gdt[GDT_TAREA_INICIAL].base_31_24 = (int)&tss_inicial >> 24;

	int i;	
	for (i=0;i<CANT_ZOMBIS;i++) {
		gdt[GDT_ZOMBI_A8+i].base_0_15 = (int)&(tss_zombisA[i]) & 0xFFFF;
		gdt[GDT_ZOMBI_A8+i].base_23_16 = ((int)&(tss_zombisA[i]) >> 16) & 0xFF;
		gdt[GDT_ZOMBI_A8+i].base_31_24 = (int)&(tss_zombisA[i]) >> 24;
	}
	
	for (i=0;i<CANT_ZOMBIS;i++) {
		gdt[GDT_ZOMBI_B8+i].base_0_15 = (int)&(tss_zombisB[i]) & 0xFFFF;
		gdt[GDT_ZOMBI_B8+i].base_23_16 = ((int)&(tss_zombisB[i]) >> 16) & 0xFF;
		gdt[GDT_ZOMBI_B8+i].base_31_24 = (int)&(tss_zombisB[i]) >> 24;
	}
}

void tss_inicializar_idle() {
	gdt[GDT_IDLE].base_0_15 = (int)&tss_idle & 0xFFFF;
	gdt[GDT_IDLE].base_23_16 = ((int)&tss_idle >> 16) & 0xFF;
	gdt[GDT_IDLE].base_31_24 = (int)&tss_idle >> 24;
	tss_idle = (tss) {
		(unsigned short)  0x00,	//ptl;
		(unsigned short)  0x00,	//unused0;
		(unsigned int)    0x00,	//esp0;
		(unsigned short)  0x00,	//ss0;
		(unsigned short)  0x00,	//unused1;
		(unsigned int)    0x00,	//esp1;
		(unsigned short)  0x00,	//ss1;
		(unsigned short)  0x00,	//unused2;
		(unsigned int)    0x00,	//esp2;
		(unsigned short)  0x00,	//ss2;
		(unsigned short)  0x00,	//unused3;
		(unsigned int)    0x27000,	//cr3;
		(unsigned int)    0x00016000,	//eip; MANZANA!
		(unsigned int)    0x00000202,	//eflags;
		(unsigned int)    0x00,	//eax;
		(unsigned int)    0x00,	//ecx;
		(unsigned int)    0x00,	//edx;
		(unsigned int)    0x00,	//ebx;
		(unsigned int)    0x26000,	//esp;
		(unsigned int)    0x26000,	//ebp;
		(unsigned int)    0x00,	//esi;
		(unsigned int)    0x00,	//edi;
		(unsigned short)  0x0048,	//es;
		(unsigned short)  0x00,	//unused4;
		(unsigned short)  0x40,	//cs;
		(unsigned short)  0x00,	//unused5;
		(unsigned short)  0x0048,	//ss;
		(unsigned short)  0x00,	//unused6;
		(unsigned short)  0x0048,	//ds;
		(unsigned short)  0x00,	//unused7;
		(unsigned short)  0x0060,	//fs;
		(unsigned short)  0x00,	//unused8;
		(unsigned short)  0x0048,	//gs;
		(unsigned short)  0x00,	//unused9;
		(unsigned short)  0x00,	//ldt;
		(unsigned short)  0x00,	//unused10;
		(unsigned short)  0x00,	//dtrap;
		(unsigned short)  0x00,	//iomap;
	};
}
