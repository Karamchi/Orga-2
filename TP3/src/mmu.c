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
	for (int i = 0; i <1024; i++){
		page_directory[i] = (page_dir_entry) { 
		    unsigned int    i;
		    unsigned char   0x00;
		    unsigned char   0x00;
		    unsigned char   0x00;
		    unsigned char   0x00;
		    unsigned char   0x00;
		    unsigned char   0x00;
		    unsigned char   0x00;
		    unsigned char   0x00;
		    unsigned char   0x01;
		    unsigned char   0x01;
		},
	}
}


//TIENE Q ESTAR CREADA EN LA DIRECCION 0x27000
page_dir_entry page_directory[1024]{
}

//IDENTITY MAPPING.


