/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "tss.h" // ojo manzana
char* tipos = "GCM";
void game_jugador_mover(unsigned int jugador, unsigned int value) {
	if (jugador==0) {
		print(" ",0,jugA.pos,0x40);
 		jugA.pos=(jugA.pos+value-2);
 		if (jugA.pos==0) {jugA.pos=44;}
 		if (jugA.pos==45) {jugA.pos=1;}

	    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
        p[(int)jugA.pos][0].c = (unsigned char) jugA.tzl;
        p[(int)jugA.pos][0].a = (unsigned char) 0x4f;
	} else {
		print(" ",79,jugB.pos,0x10);
 		jugB.pos=(jugB.pos+value-2);
 		if (jugB.pos==0) {jugB.pos=44;}
 		if (jugB.pos==45) {jugB.pos=1;}
		
	    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
        p[(int)jugB.pos][79].c = (unsigned char) jugB.tzl;
        p[(int)jugB.pos][79].a = (unsigned char) 0x1f;
	}
}
void game_lanzar_zombi(unsigned int jugador) {
	info_zombi z;
	z.jugador=jugador;
	z.vivo=1;
	int i;
	//int cr3;
	//breakpoint();
	if (jugador==0) {
		if (jugA.zqq>0 && jugA.zep<8) {
			jugA.zqq--;
			jugA.zep++;
			//cr3=mmu_inicializar_dir_zombi(jugA.tzl,0,jugA.pos);
			z.tipo=jugA.tzl;
			z.pos_i=jugA.pos;
			z.pos_j=2;
			for (i=0;i<8;i++) {
				if (tareasA[i].vivo==0) {
					tareasA[i]=z;
					break;
				}
			}
			tss_completar_libre(&(tss_zombisA[i]),jugA.tzl,0,jugA.pos);
			printZombi(z);
		}
	} else {
		if (jugB.zqq>0 && jugB.zep<8) {
			jugB.zqq--;
			jugB.zep++;
			//cr3=mmu_inicializar_dir_zombi(jugB.tzl,1,jugB.pos);
			z.tipo=jugB.tzl;
			z.pos_i=jugB.pos;
			z.pos_j=77;
			for (i=0;i<8;i++) {
				if (tareasB[i].vivo==0) {
					tareasB[i]=z;
					break;
				}
			}
						tss_completar_libre(&(tss_zombisB[i]),jugB.tzl,1,jugB.pos);
			printZombi(z);
		}
	} 
	
	pintar_buffer_video_posta(jugA, jugB);
	
}
void game_move_current_zombi(direccion dir) {
	unsigned int cr3 = rcr3() ;	
	
	info_zombi* z;
	if (anteriorjug == 0) {
		z = &tareasA[(int)anteriorA];
	} else {
		z = &tareasB[(int)anteriorB];
	}
	//breakpoint();
	print("X", z->pos_j, z->pos_i, C_FG_WHITE+C_BG_GREEN);
	
	int* src;
	mmu_unmapear_paginas_zombi(cr3, z->jugador, z->pos_j, z->pos_i);
	switch (dir) {
		case (IZQ):	{
			z->pos_i = (z->pos_i + 2*(anteriorjug-1) + 44) % 44 + 1; 
			src = (int*)0x8004000; 
			break;
		}
		case (DER): {
			z->pos_i = (z->pos_i - 2*anteriorjug + 44) % 44 + 1; 
			src = (int*)0x8005000; 
			break;
		}
		case (ADE):	{
			z->pos_j = z->pos_j - 2*anteriorjug + 1; 
			src = (int*)0x8006000;
			break;
		}
		case (ATR):	{
			z->pos_j = z->pos_j + 2*anteriorjug - 1; 
			src = (int*)0x8001000;
			break;
		}
	}
	int* dst = (int*)0x8000000;
	
	if (z->pos_j == 1 || z->pos_j==78) {
		game_chau_zombi();
	} else {
		mmu_mapear_paginas_zombi(cr3, z->jugador, z->pos_j, z->pos_i);
		printZombi(*z);
		int i;
		//breakpoint();
		for (i=0; i<1024; i++) dst[i]=src[i]; //copio el codigo
	}
	
	/*
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
	*/
	pintar_buffer_video_posta(jugA, jugB);
}
void game_cambiar_tipo_zombi(unsigned int jugador, unsigned int value){

	if (jugador==0) {
		unsigned int viejoval=(jugA.tzl=='C')+(jugA.tzl=='M')*2;
		unsigned int nuevoval=(viejoval+value+1)%3;
		jugA.tzl=tipos[nuevoval];
	    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
        p[(int)jugA.pos][0].c = (unsigned char) jugA.tzl;
        p[(int)jugA.pos][0].a = (unsigned char) 0x4f;
	} else {
		unsigned int viejoval=(jugB.tzl=='C')+(jugB.tzl=='M')*2;
		unsigned int nuevoval=(viejoval+value+1)%3;
		jugB.tzl=tipos[nuevoval];
	    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
        p[(int)jugB.pos][79].c = (unsigned char) jugB.tzl;
        p[(int)jugB.pos][79].a = (unsigned char) 0x1f;
	}
}

void game_chau_zombi() {
	if (anteriorjug == 0){
		tareasA[(int)anteriorA].vivo=0;
		jugB.pts++;
		jugA.zep--;
		printZombi(tareasA[(int)anteriorA]);
	} else {
		tareasB[(int)anteriorB].vivo=0;
		jugA.pts++;
		jugB.zep--;
		printZombi(tareasB[(int)anteriorB]);
	}
	pintar_buffer_video_posta(jugA, jugB);
}
