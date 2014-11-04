/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "i386.h"

tss tss_inicial;
tss tss_idle;

tss tss_zombisA[CANT_ZOMBIS];
tss tss_zombisB[CANT_ZOMBIS];

void tss_completar_libre(tss t, char tipo, char jugador, int pos/*, bool interr*/){
		breakpoint();
		int cr3 = mmu_inicializar_dir_zombi(tipo, jugador, pos);
		t.cr3 = cr3;
		jugador -= 65; // jugador A: 0, jugador B: 1 
		t.eip = pos_mapa(1+jugador*75, pos);
		t.eflags=0x02/*+interr*(0x200)*/; //VER Q ONDA DSD EL ASM COMO VER SI ESTÁ HABILITADO LAS INTERRUP
		t.esp = t.eip; //CONFUSOOO!! PREGUNTAR (Tiene q ser la base de la tarea o pedir una nueva pagina?)
		t.ebp = t.eip; //CONFUSOOO!! PREGUNTAR (Tiene q ser la base de la tarea o pedir una nueva pagina?)
}

void tss_inicializar() {
	gdt[GDT_TAREA_INICIAL].base_0_15 = (int)&tss_inicial & 0xFFFF;
	gdt[GDT_TAREA_INICIAL].base_23_16 = ((int)&tss_inicial >> 16) & 0xFF;
	gdt[GDT_TAREA_INICIAL].base_31_24 = (int)&tss_inicial >> 24;
	/*tss_inicial = (tss) {
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
		(unsigned int)    0x00,	//cr3;
		(unsigned int)    0x00,	//eip;
		(unsigned int)    0x00,	//eflags;
		(unsigned int)    0x00,	//eax;
		(unsigned int)    0x00,	//ecx;
		(unsigned int)    0x00,	//edx;
		(unsigned int)    0x00,	//ebx;
		(unsigned int)    0x00,	//esp;
		(unsigned int)    0x00,	//ebp;
		(unsigned int)    0x00,	//esi;
		(unsigned int)    0x00,	//edi;
		(unsigned short)  0x00,	//es;
		(unsigned short)  0x00,	//unused4;
		(unsigned short)  0x00,	//cs;
		(unsigned short)  0x00,	//unused5;
		(unsigned short)  0x00,	//ss;
		(unsigned short)  0x00,	//unused6;
		(unsigned short)  0x00,	//ds;
		(unsigned short)  0x00,	//unused7;
		(unsigned short)  0x00,	//fs;
		(unsigned short)  0x00,	//unused8;
		(unsigned short)  0x00,	//gs;
		(unsigned short)  0x00,	//unused9;
		(unsigned short)  0x00,	//ldt;
		(unsigned short)  0x00,	//unused10;
		(unsigned short)  0x00,	//dtrap;
		(unsigned short)  0x00,	//iomap;
	};*/
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
