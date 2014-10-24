/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void mmu_inicializar() {
}

void mmu_inicializar_dir_kernel() {
	page_dir_entry* pdep =(page_dir_entry*)0x27000;
	*pdep = (page_dir_entry) { 
	    (unsigned int)    0x28000,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x00,
	    (unsigned char)   0x01,
	    (unsigned char)   0x01,
	};
/*	page_table_entry* ptep =(page_table_entry*)0x28000;
	int i;
	for (i=0; i <1024; i=i+1) {
		*ptep = (page_table_entry) { 
		    (unsigned int)    i*0x1000,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x00,
		    (unsigned char)   0x01,
		    (unsigned char)   0x01,
		};
	}*/
}

void pedir_pagina(){
}

//IDENTITY MAPPING.


