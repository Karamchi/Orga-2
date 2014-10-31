/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"


int pos_mapa(int x, int y) {
	return 0x400000+(x+78*y)*0x1000;
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
	return (0x100000+(contador_pags-1)*0x1000);
}

//IDENTITY MAPPING.
void mmu_inicializar_dir_zombi(char tipo, char jugador, int pos){
	page_dir_entry* pd = (page_dir_entry*) pedir_pagina();
	page_table_entry* pt = (page_table_entry*) pedir_pagina();
	
	pd[0] = (page_dir_entry) { 
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
	    (unsigned int)    pt,
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
		    (unsigned char)   0x00,
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
	// copiamos el codigo
	int* src;
	if (jugador=='A') {
		if (tipo=='G') src = (int*) 0x10000;
		if (tipo=='M') src = (int*) 0x11000;
		if (tipo=='C') src = (int*) 0x12000;
	} else {
		if (tipo=='G') src = (int*) 0x13000;
		if (tipo=='M') src = (int*) 0x14000;
		if (tipo=='C') src = (int*) 0x15000;
	}
	int* dst;
	if (jugador=='A') { 
		dst = (int*) pos_mapa(1, pos);
	} else {
		dst = (int*) pos_mapa(76, pos);
	}
	for (i=0; i<0x400; i++) {
		dst[i]=src[i];
	}
		
/*TODO*/
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
			(unsigned char)   0x00,
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
		(unsigned char)   0x00,
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













