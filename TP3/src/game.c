/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
char* tipos = "GCM";
void game_jugador_mover(unsigned int jugador, unsigned int value) {
	if (jugador==1) {
		print(" ",0,jugA.pos,0x40);
 		jugA.pos=(jugA.pos+value-2)%44+1;
		print((char*)&(jugA.tzl),0,jugA.pos,0x40);
	} else {
		print(" ",79,jugB.pos,0x10);
 		jugB.pos=(jugB.pos+value-2)%44+1;
		print((char*)&(jugB.tzl),79,jugB.pos,0x10);
	}
}
void game_lanzar_zombi(unsigned int jugador) {
	info_zombi z;
	z.jugador=jugador;
	z.vivo=1;
	int i;
	if (jugador==0) {
		if (jugA.zqq>0 && jugA.zep<8) {
			jugA.zqq--;
			jugA.zep++;
			mmu_inicializar_dir_zombi(jugA.tzl,2,jugA.pos);
			z.tipo=jugA.tzl;
			z.pos_i=2;
			z.pos_j=jugA.pos;
			for (i=0;i<8;i++) {
				if (tareasA[i].vivo==0) {
					tareasA[i]=z;
				}
			}
			printZombi(z);
		}
	} else {
		if (jugB.zqq>0 && jugB.zep<8) {
			jugB.zqq--;
			mmu_inicializar_dir_zombi(jugB.tzl,78,jugB.pos);
			z.tipo=jugB.tzl;
			z.pos_i=78;
			z.pos_j=jugB.pos;
			for (i=0;i<8;i++) {
				if (tareasB[i].vivo==0) {
					tareasB[i]=z;
				}
			}
			printZombi(z);
		}
	}
}
void game_move_current_zombi(direccion dir) {
	unsigned int cr3 = rcr3() ;	
	switch (dir) {
		case (IZQ):
			if (anteriorjug == 0){		//Jugador actual A
				print("X", tareasA[(int)anteriorA].pos_j , tareasA[(int)anteriorA].pos_i, C_FG_WHITE+C_BG_GREEN);
				mmu_unmapear_paginas_zombi(cr3, tareasA[(int)anteriorA].jugador, tareasA[(int)anteriorA].pos_j, tareasA[(int)anteriorA].pos_i);
				tareasA[(int)anteriorA].pos_i = (tareasA[(int)anteriorA].pos_i - 2)%44 + 1; 	//ZombieA actual
				mmu_mapear_paginas_zombi(cr3, tareasA[(int)anteriorA].jugador, tareasA[(int)anteriorA].pos_j, tareasA[(int)anteriorA].pos_i);
				printZombi(tareasA[(int)anteriorA]);
			} else {			//Jugador actual B
				print("X", tareasB[(int)anteriorB].pos_j , tareasB[(int)anteriorB].pos_i, C_FG_WHITE+C_BG_GREEN);
				mmu_unmapear_paginas_zombi(cr3, tareasB[(int)anteriorB].jugador, tareasB[(int)anteriorB].pos_j, tareasB[(int)anteriorB].pos_i);
				tareasB[(int)anteriorB].pos_i = (tareasB[(int)anteriorB].pos_i)%44 + 1;
				mmu_mapear_paginas_zombi(cr3, tareasB[(int)anteriorB].jugador, tareasB[(int)anteriorB].pos_j, tareasB[(int)anteriorB].pos_i);
				printZombi(tareasB[(int)anteriorB]);
			}
			break;
		
		case (DER):
			if (anteriorjug == 0){		//Jugador actual A
				print("X", tareasA[(int)anteriorA].pos_j , tareasA[(int)anteriorA].pos_i, C_FG_WHITE+C_BG_GREEN);
				mmu_unmapear_paginas_zombi(cr3, tareasA[(int)anteriorA].jugador, tareasA[(int)anteriorA].pos_j, tareasA[(int)anteriorA].pos_i);
				tareasA[(int)anteriorA].pos_i = (tareasA[(int)anteriorA].pos_i)%44 + 1; 	//ZombieA actual
				mmu_mapear_paginas_zombi(cr3, tareasA[(int)anteriorA].jugador, tareasA[(int)anteriorA].pos_j, tareasA[(int)anteriorA].pos_i);
				printZombi(tareasA[(int)anteriorA]);
			} else {			//Jugador actual B
				print("X", tareasB[(int)anteriorB].pos_j , tareasB[(int)anteriorB].pos_i, C_FG_WHITE+C_BG_GREEN);
				mmu_unmapear_paginas_zombi(cr3, tareasB[(int)anteriorB].jugador, tareasB[(int)anteriorB].pos_j, tareasB[(int)anteriorB].pos_i);
				tareasB[(int)anteriorB].pos_i = (tareasB[(int)anteriorB].pos_i - 2)%44 + 1;
				mmu_mapear_paginas_zombi(cr3, tareasB[(int)anteriorB].jugador, tareasB[(int)anteriorB].pos_j, tareasB[(int)anteriorB].pos_i);
				printZombi(tareasB[(int)anteriorB]);
			} 
			break;
		
		case (ADE):
			if (anteriorjug == 0){		//Jugador actual A
				print("X", tareasA[(int)anteriorA].pos_j , tareasA[(int)anteriorA].pos_i, C_FG_WHITE+C_BG_GREEN);
				mmu_unmapear_paginas_zombi(cr3, tareasA[(int)anteriorA].jugador, tareasA[(int)anteriorA].pos_j, tareasA[(int)anteriorA].pos_i);
				tareasA[(int)anteriorA].pos_j = (tareasA[(int)anteriorA].pos_j) + 1; 	//ZombieA actual
				if (tareasA[(int)anteriorA].pos_j == 78){
					game_chau_zombi();
				} else {mmu_mapear_paginas_zombi(cr3, tareasA[(int)anteriorA].jugador, tareasA[(int)anteriorA].pos_j, tareasA[(int)anteriorA].pos_i);}
				printZombi(tareasA[(int)anteriorA]);
			} else {			//Jugador actual B
				print("X", tareasB[(int)anteriorB].pos_j , tareasB[(int)anteriorB].pos_i, C_FG_WHITE+C_BG_GREEN);
				mmu_unmapear_paginas_zombi(cr3, tareasB[(int)anteriorB].jugador, tareasB[(int)anteriorB].pos_j, tareasB[(int)anteriorB].pos_i);
				tareasB[(int)anteriorB].pos_j = (tareasB[(int)anteriorB].pos_j) - 1;
				if (tareasB[(int)anteriorB].pos_j == 1){
					tareasB[(int)anteriorB].vivo = 0;

				} else {mmu_mapear_paginas_zombi(cr3, tareasB[(int)anteriorB].jugador, tareasB[(int)anteriorB].pos_j, tareasB[(int)anteriorB].pos_i);}
				printZombi(tareasB[(int)anteriorB]);
			}
			break;
		
		case (ATR):
			if (anteriorjug == 0){		//Jugador actual A
				print("X", tareasA[(int)anteriorA].pos_j , tareasA[(int)anteriorA].pos_i, C_FG_WHITE+C_BG_GREEN);
				mmu_unmapear_paginas_zombi(cr3, tareasA[(int)anteriorA].jugador, tareasA[(int)anteriorA].pos_j, tareasA[(int)anteriorA].pos_i);
				tareasA[(int)anteriorA].pos_j = (tareasA[(int)anteriorA].pos_j) - 1; 	//ZombieA actual
				if (tareasA[(int)anteriorA].pos_j == 1){
					game_chau_zombi();
				} else {mmu_mapear_paginas_zombi(cr3, tareasA[(int)anteriorA].jugador, tareasA[(int)anteriorA].pos_j, tareasA[(int)anteriorA].pos_i);}
				printZombi(tareasA[(int)anteriorA]);
			} else {			//Jugador actual B
				print("X", tareasB[(int)anteriorB].pos_j , tareasB[(int)anteriorB].pos_i, C_FG_WHITE+C_BG_GREEN);
				mmu_unmapear_paginas_zombi(cr3, tareasB[(int)anteriorB].jugador, tareasB[(int)anteriorB].pos_j, tareasB[(int)anteriorB].pos_i);
				tareasB[(int)anteriorB].pos_j = (tareasB[(int)anteriorB].pos_j) + 1;
				if (tareasB[(int)anteriorB].pos_j == 78){
					game_chau_zombi();
				} else {mmu_mapear_paginas_zombi(cr3, tareasB[(int)anteriorB].jugador, tareasB[(int)anteriorB].pos_j, tareasB[(int)anteriorB].pos_i);}
				printZombi(tareasB[(int)anteriorB]);
			} 
	}
	pintar_buffer_video_posta(jugA, jugB);
}
void game_cambiar_tipo_zombi(unsigned int jugador, unsigned int value){

	if (jugador==0) {
		unsigned int nuevoval=(jugA.tzl+value-2)%3;
		jugA.tzl=tipos[nuevoval];
		print((char*)&(jugA.tzl),0,jugA.pos,0x40);
	} else {
		unsigned int nuevoval=(jugB.tzl+value-2)%3;
		jugB.tzl=tipos[nuevoval];
		print((char*)&(jugB.tzl),79,jugA.pos,0x10);
	}
}

void game_chau_zombi() {
	if (anteriorjug == 0){
		tareasA[(int)anteriorA].vivo=0;
		jugB.pts++;
		jugA.zep--;
	} else {
		tareasB[(int)anteriorB].vivo=0;
		jugA.pts++;
		jugB.zep--;
	}
	//y faltaria imprimir cadáver
}
