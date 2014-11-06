/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

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
	if (jugador==1) {
		if (jugA.zqq>0 && jugA.zep<8) {
			jugA.zqq--;
			juga.zep++;
			//(lanzar zombi)
			//(imprimir zombie)
		}
	} else {
		if (jugB.zqq>0 && jugB.zep<8) {
			jugB.zqq--;
			//(lanzar zombi)
 			//(imprimir zombie)
		}
	}
}
void game_move_current_zombi(direccion dir) {
	
	switch (dir) {
		case (IZQ):
			if (anteriorjug == 0){		//Jugador actual A
				print("X", tareasA[(int)anteriorA].pos_j , tareasA[(int)anteriorA].pos_i, C_FG_WHITE+C_BG_GREEN);
				tareasA[(int)anteriorA].pos_i = (tareasA[(int)anteriorA].pos_i - 2)%44 + 1; 	//ZombieA actual
				printZombi(tareasA[(int)anteriorA]);
			} else {			//Jugador actual B
				print("X", tareasB[(int)anteriorB].pos_j , tareasB[(int)anteriorB].pos_i, C_FG_WHITE+C_BG_GREEN);
				tareasB[(int)anteriorB].pos_i = (tareasB[(int)anteriorB].pos_i)%44 + 1;
				printZombi(tareasB[(int)anteriorB]);
			}
			break;
		
		case (DER):
			if (anteriorjug == 0){		//Jugador actual A
				print("X", tareasA[(int)anteriorA].pos_j , tareasA[(int)anteriorA].pos_i, C_FG_WHITE+C_BG_GREEN);
				tareasA[(int)anteriorA].pos_i = (tareasA[(int)anteriorA].pos_i)%44 + 1; 	//ZombieA actual
				printZombi(tareasA[(int)anteriorA]);
			} else {			//Jugador actual B
				print("X", tareasB[(int)anteriorB].pos_j , tareasB[(int)anteriorB].pos_i, C_FG_WHITE+C_BG_GREEN);
				tareasB[(int)anteriorB].pos_i = (tareasB[(int)anteriorB].pos_i - 2)%44 + 1;
				printZombi(tareasB[(int)anteriorB]);
			} 
			break;
		
		case (ADE):
			if (anteriorjug == 0){		//Jugador actual A
				print("X", tareasA[(int)anteriorA].pos_j , tareasA[(int)anteriorA].pos_i, C_FG_WHITE+C_BG_GREEN);
				tareasA[(int)anteriorA].pos_j = (tareasA[(int)anteriorA].pos_j) + 1; 	//ZombieA actual
				if (tareasA[(int)anteriorA].pos_j == 78){
					tareasA[(int)anteriorA].vivo = 0;
					jugA.pts++;
					jugA.zep--;
				}
				printZombi(tareasA[(int)anteriorA]);
			} else {			//Jugador actual B
				print("X", tareasB[(int)anteriorB].pos_j , tareasB[(int)anteriorB].pos_i, C_FG_WHITE+C_BG_GREEN);
				tareasB[(int)anteriorB].pos_j = (tareasB[(int)anteriorB].pos_j) - 1;
				if (tareasB[(int)anteriorB].pos_j == 1){
					tareasB[(int)anteriorB].vivo = 0;
					jugB.pts++;
					jugB.zep--;
				}
				printZombi(tareasB[(int)anteriorB]);
			}
			break;
		
		case (ATR):
			if (anteriorjug == 0){		//Jugador actual A
				print("X", tareasA[(int)anteriorA].pos_j , tareasA[(int)anteriorA].pos_i, C_FG_WHITE+C_BG_GREEN);
				tareasA[(int)anteriorA].pos_j = (tareasA[(int)anteriorA].pos_j) - 1; 	//ZombieA actual
				if (tareasA[(int)anteriorA].pos_j == 1){
					tareasA[(int)anteriorA].vivo = 0;
					jugA.pts--;
					jugA.zep--;
				}
				printZombi(tareasA[(int)anteriorA]);
			} else {			//Jugador actual B
				print("X", tareasB[(int)anteriorB].pos_j , tareasB[(int)anteriorB].pos_i, C_FG_WHITE+C_BG_GREEN);
				tareasB[(int)anteriorB].pos_j = (tareasB[(int)anteriorB].pos_j) + 1;
				if (tareasB[(int)anteriorB].pos_j == 78){
					tareasB[(int)anteriorB].vivo = 0;
					jugB.pts--;
					jugB.zep--;
				}
				printZombi(tareasB[(int)anteriorB]);
			} 
			break;
	}
	pintar_buffer_video_posta(jugA, jugB);
	//Remapear Paginas 
}
void game_cambiar_tipo_zombi(unsigned int jugador, unsigned int value){

	if (jugador==1) {
		unsigned int nuevoval=(jugA.tzl+value-2)%3;
		jugA.tzl=tipos[nuevoval];
		print((char*)&(jugA.tzl),0,jugA.pos,0x40);
	} else {
		unsigned int nuevoval=(jugB.tzl+value-2)%3;
		jugB.tzl=tipos[nuevoval];
		print((char*)&(jugB.tzl),79,jugA.pos,0x10);
	}
}
