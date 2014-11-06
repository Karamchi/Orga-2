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
			if (anteriorjug == 0){		//Jugador actual A
				tareasA[(int)anteriorA].pos_i = (tareasA[(int)anteriorA].pos_i - 2)%44 + 1; 	//ZombieA actual
			} else {			//Jugador actual B
				tareasB[(int)anteriorB].pos_i = (tareasB[(int)anteriorB].pos_i)%44 + 1;
			} 
			break;
		
		case (DER):
			if (anteriorjug == 0){		//Jugador actual A
				tareasA[(int)anteriorA].pos_i = (tareasA[(int)anteriorA].pos_i)%44 + 1; 	//ZombieA actual
			} else {			//Jugador actual B
				tareasB[(int)anteriorB].pos_i = (tareasB[(int)anteriorB].pos_i - 2)%44 + 1;
			} 
			break;
		
		case (ADE):
			if (anteriorjug == 0){		//Jugador actual A
				tareasA[(int)anteriorA].pos_j = (tareasA[(int)anteriorA].pos_j) + 1; 	//ZombieA actual
				if (tareasA[(int)anteriorA].pos_j == 78){
					tareasA[(int)anteriorA].vivo = 0;
					//Hacer los cambios en los datos del jugador
				}
				
			} else {			//Jugador actual B
				tareasB[(int)anteriorB].pos_j = (tareasB[(int)anteriorB].pos_j) - 1;
				if (tareasB[(int)anteriorB].pos_j == 1){
					tareasB[(int)anteriorB].vivo = 0;
					//Hacer los cambios en los datos del jugador
				}
			} 
			break;
		
		case (ATR):
			if (anteriorjug == 0){		//Jugador actual A
				tareasA[(int)anteriorA].pos_j = (tareasA[(int)anteriorA].pos_j) - 1; 	//ZombieA actual
				if (tareasA[(int)anteriorA].pos_j == 1){
					tareasA[(int)anteriorA].vivo = 0;
					//Hacer los cambios en los datos del jugador
				}
				
			} else {			//Jugador actual B
				tareasB[(int)anteriorB].pos_j = (tareasB[(int)anteriorB].pos_j) + 1;
				if (tareasB[(int)anteriorB].pos_j == 78){
					tareasB[(int)anteriorB].vivo = 0;
					//Hacer los cambios en los datos del jugador
				}
			} 
			break;
	}
	//Remapear Paginas
	//Hay q pintar el caminito que va haciendo el zombi.
	//No me acuerdo nada mas. Espero q esto quede guardado para mñn.
}
void game_cambiar_tipo_zombi(unsigned int jugador, unsigned int value){}
