/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "screen.h"
#include "tss.h"

typedef struct info_zombi_struct {
	unsigned char tipo;
	unsigned char pos_i;
	unsigned char pos_j;
	unsigned char vivo:1;
	unsigned char jugador:1;
	
} __attribute__((__packed__)) info_zombi; 

typedef struct info_jug_struct {
	unsigned char pos;
	unsigned char pts;
	unsigned char zqq; //zombies que quedan
	unsigned char zep; //zombies en pantalla
	unsigned char tzl; //tipo de zombi a lanzar
} __attribute__((__packed__)) info_jug;

info_jug jugA;
info_jug jugB;

info_zombi tareasA[CANT_ZOMBIS];
info_zombi tareasB[CANT_ZOMBIS];
char anteriorA;
char anteriorB;
char anteriorjug;

void sched_inicializar();
unsigned short sched_proximo_indice();


#endif	/* !__SCHED_H__ */
