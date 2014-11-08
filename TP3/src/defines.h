/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_ZOMBIS             8

#define SIZE_W                  78
#define SIZE_H                  44


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 31

#define GDT_CODIGO_0		8  //0x40
#define GDT_DATOS_0		9		 //0x48
#define GDT_CODIGO_3		10 //0x50
#define GDT_DATOS_3		11   //0x58
#define GDT_PANTALLA	12
#define GDT_TAREA_INICIAL	13
#define GDT_IDLE	14       //0x70
#define GDT_ZOMBI_A8	15   //0x78
#define GDT_ZOMBI_A7	16
#define GDT_ZOMBI_A6	17
#define GDT_ZOMBI_A5	18
#define GDT_ZOMBI_A4	19
#define GDT_ZOMBI_A3	20
#define GDT_ZOMBI_A2	21
#define GDT_ZOMBI_A1	22
#define GDT_ZOMBI_B8	23
#define GDT_ZOMBI_B7	24
#define GDT_ZOMBI_B6	25
#define GDT_ZOMBI_B5	26
#define GDT_ZOMBI_B4	27
#define GDT_ZOMBI_B3	28
#define GDT_ZOMBI_B2	29
#define GDT_ZOMBI_B1	30

#define GDT_IDX_NULL_DESC        0

/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */

#endif  /* !__DEFINES_H__ */
