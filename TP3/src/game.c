/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

void game_jugador_mover(unsigned int jugador, unsigned int value) {
}
void game_lanzar_zombi(unsigned int jugador) {
}
void game_move_current_zombi(direccion dir) {
	switch (dir) {
		case (IZQ):
			if (anteriorJug == 0){		//Jugador actual A
				tareasA[anteriorA].pos_i = (tareasA[anteriorA].pos_i - 2)%44 + 1; 	//ZombieA actual
			} else {			//Jugador actual B
				tareasB[anteriorB].pos_i = (tareasB[anteriorB].pos_i)%44 + 1;
			} 
			break;
		
		case (DER):
			if (anteriorJug == 0){		//Jugador actual A
				tareasA[anteriorA].pos_i = (tareasB[anteriorB].pos_i)%44 + 1; 	//ZombieA actual
			} else {			//Jugador actual B
				tareasB[anteriorB].pos_i = (tareasA[anteriorA].pos_i - 2)%44 + 1;
			} 
			break;
		
		case (ADE):
			
			break;
		
		case (ATR):
			
			break;	
	
	
	}
	//Remapear Paginas
}
void game_cambiar_tipo_zombi(unsigned int jugador, unsigned int value){}
