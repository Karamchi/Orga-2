/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
// pos_mapa devuelve la direccion de la pagina correspondiente a la posicion del mapa pasada. fila=1..44, col= 1..78
int pos_mapa(int fila, int col) {
	return 0x400000+(col-1+78*(fila-1))*0x1000;
}

void mmu_inicializar() {
	contador_pags = 0;
}

void mmu_inicializar_dir_kernel() {
	page_dir_entry* pdep =(page_dir_entry*)0x27000;
	int i;
	// el page dir tiene 4 entries para mapear el kernel, el area libre y el mapa
	for (i=0; i<4 ; i++){	
		pdep[i] = (page_dir_entry) { 
		    (unsigned char)   0x01,
		    (unsigned char)   0x01,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned int)    0x28+i,
		};
	}
	for (i=4; i<1024; i = i+1){
		pdep[i] = (page_dir_entry) {			
			(unsigned int)    0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
		};
	    //pdep = pdep +1;
	}
	int j;
	for (j=0; j<4 ; j++){
		page_table_entry* ptep =(page_table_entry*)((0x28+j)*0x1000);
		for (i=0; i <1024; i=i+1) {
			ptep[i] = (page_table_entry) { 
			    (unsigned char)   0x01,
			    (unsigned char)   0x01,
			    (unsigned char)   0x00,
			    (unsigned char)   0x00,
			    (unsigned char)   0x00,
			    (unsigned char)   0x00,
			    (unsigned char)   0x00,
			    (unsigned char)   0x00,
			    (unsigned char)   0x00,
			    (unsigned char)   0x00,
			    (unsigned int)    i+j*1024,
			};
			
		}
		
	}
}

int pedir_pagina(){
	contador_pags++;
	//breakpoint();
	return (0x100000+(contador_pags-1)*0x1000);
}

//IDENTITY MAPPING.
unsigned int mmu_inicializar_dir_zombi(char tipo, char jugador, int pos){
	/*
	tipo: 'G', 'C' o 'M'
	jugador: '0' o '1'
	*/
	page_dir_entry* pd = (page_dir_entry*) pedir_pagina();
	page_table_entry* pt = (page_table_entry*) pedir_pagina();
	
	pd[0] = (page_dir_entry) { 
	    (unsigned char)   0x01,
	    (unsigned char)   0x01,
	    (unsigned char)   0x01,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned int)    pt >> 12,
	};
	int i;
	for (i=1; i<1024; i++){
		pd[i] = (page_dir_entry) {			
			(unsigned int)    0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
		};
	}
	for (i=0; i <1024; i=i+1) {
		pt[i] = (page_table_entry) { 
		    (unsigned char)   0x01,
		    (unsigned char)   0x01,
		    (unsigned char)   0x01,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned int)    i,
		};
		
	}
	//breakpoint();
	// copiamos el codigo
	int* src;
	if (tipo=='G') src = (int*) 0x10000 + jugador*0x3000;
	if (tipo=='M') src = (int*) 0x11000 + jugador*0x3000;
	if (tipo=='C') src = (int*) 0x12000 + jugador*0x3000; //el jugador B esta 0x3000 mas adelante
	
	//el mapa tiene 44x78 posiciones
	int* dst = (int*) pos_mapa(pos,2+jugador*75); // A va a col 2 y B a col 77
	
	mmu_mapear_pagina((unsigned int) dst, rcr3(), (unsigned int) dst);
	for (i=0; i<1024; i++) {
		dst[i]=src[i];
	}
	//mmu_unmapear_pagina((unsigned int) dst, rcr3());
	//mapeamos las paginas:
	/*  Jug A:         Jug B:
	    8 6 4   		3 5 9
	    7 1 2          2 1 7
	    9 5 3          4 5 8
	*/
	mmu_mapear_paginas_zombi((unsigned int) pd, jugador, 2+jugador*75, pos);
	
	return (unsigned int)pd;
}

//pre: asumimos que virtual y fisica terminan en 0s (apuntan a una pagina)
void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica){
	cr3 = cr3 & 0xFFFFF000;
	page_dir_entry* pd =(page_dir_entry*) cr3;
	int off = virtual >> 22; // directory
	page_table_entry* pt;
	if (pd[off].p == 0) {
		pt = (page_table_entry*) pedir_pagina();
		int i;
		for (i=0; i<1024; i = i+1){
			pt[i] = (page_table_entry) {
				(unsigned int)    0x00,
				(unsigned char)   0x00,
				(unsigned char)   0x00,
				(unsigned char)   0x00,
				(unsigned char)   0x00,
				(unsigned char)   0x00,
				(unsigned char)   0x00,
				(unsigned char)   0x00,
				(unsigned char)   0x00,
				(unsigned char)   0x00,
				(unsigned char)   0x00,
			};
		}
		
		pd[off] = (page_dir_entry){
			(unsigned char)   0x01,
			(unsigned char)   0x01,
			(unsigned char)   0x01,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned char)   0x00,
			(unsigned int)    pt >> 12,
		};
	} else {
		pt=(page_table_entry*) (pd[off].base << 12);
	}
	off = (virtual >> 12) & 0x000003FF; //table
	pt[off] = (page_table_entry){
		(unsigned char)   0x01,
		(unsigned char)   0x01,
		(unsigned char)   0x01,
		(unsigned char)   0x00,
		(unsigned char)   0x00,
		(unsigned char)   0x00,
		(unsigned char)   0x00,
		(unsigned char)   0x00,
		(unsigned char)   0x00,
		(unsigned char)   0x00,
		(unsigned int)    fisica >> 12,
	};
	tlbflush();
}

// pre: asumimos que la pagina esta mapeada
void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3){
	cr3 = cr3 & 0xFFFFF000;
	page_dir_entry* pd =(page_dir_entry*) cr3;
	int off = virtual >> 22; // directory
	page_table_entry* pt = (page_table_entry*) (pd[off].base << 12);
	off = (virtual >> 12) & 0x000003FF;
	pt[off].p = 0;
	tlbflush();
}

void mmu_mapear_paginas_zombi(unsigned int cr3, char jugador, unsigned char x, unsigned char y) {
	// x e y empiezan de 1
	//y--;x--; 
	mmu_mapear_pagina(0x8000000, cr3, pos_mapa( y                               , x));
	mmu_mapear_pagina(0x8001000, cr3, pos_mapa( y                               , x-2*jugador+1)); 
	mmu_mapear_pagina(0x8002000, cr3, pos_mapa((y - 2*jugador     + 44) % 44 + 1, x-2*jugador+1));
	mmu_mapear_pagina(0x8003000, cr3, pos_mapa((y + 2*jugador - 2	+ 44) % 44 + 1, x-2*jugador+1));
	mmu_mapear_pagina(0x8004000, cr3, pos_mapa((y - 2*jugador     + 44) % 44 + 1, x));
	mmu_mapear_pagina(0x8005000, cr3, pos_mapa((y + 2*jugador - 2 + 44) % 44 + 1, x));
	mmu_mapear_pagina(0x8006000, cr3, pos_mapa( y	                              , x+2*jugador-1));
	mmu_mapear_pagina(0x8007000, cr3, pos_mapa((y + 2*jugador - 2	+ 44) % 44 + 1, x+2*jugador-1));
	mmu_mapear_pagina(0x8008000, cr3, pos_mapa((y - 2*jugador    	+ 44) % 44 + 1, x+2*jugador-1));
	
}

void mmu_unmapear_paginas_zombi(unsigned int cr3, char jugador, unsigned char x, unsigned char y) {
	mmu_unmapear_pagina(0x8000000, cr3);
	mmu_unmapear_pagina(0x8001000, cr3);
	mmu_unmapear_pagina(0x8002000, cr3);
	mmu_unmapear_pagina(0x8003000, cr3);
	mmu_unmapear_pagina(0x8004000, cr3);
	mmu_unmapear_pagina(0x8005000, cr3);
	mmu_unmapear_pagina(0x8006000, cr3);
	mmu_unmapear_pagina(0x8007000, cr3);
	mmu_unmapear_pagina(0x8008000, cr3);
	
}
