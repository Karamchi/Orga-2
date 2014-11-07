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
	jugB.zep=8;
	jugA.zqq=20;
	jugA.tzl='M';
	
	jugB.pos=25;
	jugB.pts=0;
	jugB.zqq=20;
	jugB.zep=8;
	jugB.tzl='M';

	//print((char*)&(jugA.tzl),1,jugA.pos,0x40);
	//print((char*)&(jugB.tzl),79,jugB.pos,0x10);
	
	anteriorA=0;
	anteriorB=0;
	anteriorjug=0;
	int i;
	for (i=0;i<8;i++) {
		tareasA[i].vivo=0;
		tareasB[i].vivo=0;
	}
	//pintar_buffer_video_posta(jugA,jugB);
}

unsigned short sched_proximo_indice() {
	int i;
	if (anteriorjug!=1) {
		for (i=anteriorB+1;i<anteriorB+9;i++) {
			if (tareasB[i%8].vivo==1) {
				anteriorjug=0;
				anteriorB=i%8;
				return i%8+GDT_ZOMBI_B8;
			}
		} 
	} 
	for (i=anteriorA+1;i<anteriorA+9;i++) {
		if (tareasA[i%8].vivo==1) {
			anteriorjug=1;
			anteriorA=i%8;
			return i%8+GDT_ZOMBI_A8;
		}
	} 
	for (i=anteriorB+1;i<anteriorB+9;i++) {
		if (tareasB[i%8].vivo==1) {
			anteriorjug=0;
			anteriorB=i%8;
			return i%8+GDT_ZOMBI_B8;
		}
	} 
	anteriorjug=2;
  	return GDT_IDLE;
}

