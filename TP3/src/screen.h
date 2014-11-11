/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80

#include "colors.h"
#include "sched.h"
#include "defines.h"
/* Estructura de para acceder a memoria de video */ 
typedef struct ca_s {
    unsigned char c;
    unsigned char a;
} ca;

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr);

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr);

void pintar_buffer_video();

void pintar_puntajes();

void printint(int a, unsigned char pos_i, unsigned char pos_j, unsigned char color);

void printZombi(info_zombi z);

void game_print_debug(int eax);

void recuperarPantalla();

void print_relojes();

#endif  /* !__SCREEN_H__ */
