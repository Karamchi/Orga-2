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

void pintar_buffer_video_posta(info_jug jug1, info_jug jug2);

void printint(int a, unsigned char pos_i, unsigned char pos_j, unsigned char color);

void printZombi(info_zombi z);

void game_print_debug(int eax, int ebx, int ecx, int edx, int esi, int edi, int ebp, int esp, int eip, short cs, short ds, short es, short fs, short gs, short ss, int eflags);

void recuperarPantalla();

#endif  /* !__SCREEN_H__ */
