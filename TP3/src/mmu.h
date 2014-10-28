/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"

void mmu_inicializar();
void mmu_inicializar_dir_kernel();

typedef struct str_page_dir_entry {
    unsigned char   p:1;
    unsigned char   rw:1;
    unsigned char   us:1;
	unsigned char   pwt:1;
    unsigned char   pcd:1;
    unsigned char   a:1;
    unsigned char   z:1;
    unsigned char   ps:1;
    unsigned char   g:1;
    unsigned char  	disp:3;
    unsigned int  	base:20;
} __attribute__((__packed__, aligned (4))) page_dir_entry;

typedef struct str_page_table_entry {
    unsigned char   p:1;
    unsigned char   rw:1;
    unsigned char   us:1;
	unsigned char   pwt:1;
    unsigned char   pcd:1;
    unsigned char   a:1;
    unsigned char   d:1;
    unsigned char   pat:1;
    unsigned char   g:1;
    unsigned char  	disp:3;
    unsigned int  	base:20;
} __attribute__((__packed__, aligned (4))) page_table_entry;



#endif	/* !__MMU_H__ */
