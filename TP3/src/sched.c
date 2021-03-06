/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

void sched_inicializar(){ 
	jugA.pos=25;
	jugA.pts=0;
	jugB.zep=0;
	jugA.zqq=20;
	jugA.tzl='M';
	
	jugB.pos=25;
	jugB.pts=0;
	jugB.zqq=20;
	jugB.zep=0;
	jugB.tzl='M';

	anteriorA=0;
	anteriorB=0;
	anteriorjug=0;
	int i;
	for (i=0;i<8;i++) {
		tareasA[i].reloj=0;
		tareasB[i].reloj=0;
		tareasA[i].vivo=0;
		tareasB[i].vivo=0;
	}
}

unsigned short sched_proximo_indice() {
	int i;
	if (anteriorjug!=1) {
		for (i=anteriorB+1;i<anteriorB+9;i++) {
			if (tareasB[i%8].vivo==1) {
				anteriorjug=1;
				anteriorB=i%8;
                tareasB[i%8].reloj=(tareasB[i%8].reloj+1)%4;
				return ((i%8+GDT_ZOMBI_B8) << 3) + 3;
			}
		} 
	} 
	for (i=anteriorA+1;i<anteriorA+9;i++) {
		if (tareasA[i%8].vivo==1) {
			anteriorjug=0;
			anteriorA=i%8;
            tareasA[i%8].reloj=(tareasA[i%8].reloj+1)%4;
			return ((i%8+GDT_ZOMBI_A8) << 3) + 3;
		}
	} 
	for (i=anteriorB+1;i<anteriorB+9;i++) {
		if (tareasB[i%8].vivo==1) {
			anteriorjug=1;
			anteriorB=i%8;
            tareasB[i%8].reloj=(tareasB[i%8].reloj+1)%4;
			return ((i%8+GDT_ZOMBI_B8) << 3) + 3;
		}
	} 
	anteriorjug=2;
  	return GDT_IDLE << 3;
}
