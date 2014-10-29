/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void mmu_inicializar() {
	contador_pags = 0;
}

void mmu_inicializar_dir_kernel() {
	page_dir_entry* pdep =(page_dir_entry*)0x27000;
	int i;
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
	//pdep = pdep + 1; //Aumento al siguiente elemento
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
			//ptep = ptep + 1;
		}
		
	}
}

int pedir_pagina(){
	contador_pags++;
	return 0x100000+(contador_pags-1)*0x1000;
}

//IDENTITY MAPPING.
void mmu_inicializar_dir_zombi(){
	

/*TODO*/
}
void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica); {
	cr3 >> 12;
	
	/*TODO*/
}
void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3);{/*TODO*/}











