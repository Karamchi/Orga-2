/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

void sched_inicializar(){ 
	for (int i=0;i<8;i++) {
		tareasA[i].vivo=0;
		tareasB[i].vivo=0;
	}
}

unsigned short sched_proximo_indice() {
	int res;
	if (anterior.jugador==1) {
		for (int i=0;i<8;i++) {
			if (tareasB.vivo==1) {
				anterior=i+GDT_ZOMBIE_B8;
				return anterior;
			}
		} 
	} for (int i=0;i<8;i++) {
		if (tareasA.vivo==1) {
			anterior=i+GDT_ZOMBIE_A8;
			return anterior;
		}
	} 
  	return GDT_IDLE;
}

