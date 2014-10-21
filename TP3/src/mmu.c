/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void mmu_inicializar() {
}

void mmu_inicializar_dir_kernel(){	
	page_directory[0] = (page_dir_entry) {		//ACA SERÍA 
		
	},
}

page_dir_entry page_directory[1024]{
}




