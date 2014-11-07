/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"


void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void pintar_buffer_video() {
	/*Esta funcion pinta el buffer de video que esta en la posicion 0xb8000 (80x50) con la parte inferior y una línea negra arriba 
	va a haber que modificarla para adaptarse a cualquier entrada de datos
	*/
	ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
	int i;
	int j;
	for(i=0;i<80;i++) {
		p[0][i] = (ca){' ',0};
		
		p[45][i] = (ca){' ',0};
		p[46][i] = (ca){' ',0};
		p[47][i] = (ca){' ',0};
		p[48][i] = (ca){' ',0};
		p[49][i] = (ca){' ',0};
	}
	for (i=1; i<9; i++) {
		p[46][4+i*2] = (ca){i+48,0x0f};
		p[46][60+i*2] = (ca){i+48,0x0f};
	}
	for(i=35; i<40; i++) {
		for (j=45; j<50; j++) {
			p[j][i]=(ca){' ',0x40};
			p[j][i+5]=(ca){' ',0x10};
		}
	}
	p[47][37]=(ca){'0',0x4f};//si dejamos esta funcion como "Inicializacion", esto puede ir acá
	p[47][42]=(ca){'0',0x1f};
	p[47][31]=(ca){'8',0x4f};
	p[47][48]=(ca){'8',0x1f};
	p[25][0]=(ca){'M',0x4f};
	p[25][79]=(ca){'M',0x1f};


	/*
		aca faltaría escribir la info de los relojes 
	*/
}

void printint(int a, unsigned char pos_i, unsigned char pos_j, unsigned char color) {
	ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
	unsigned char d=a/10;
	unsigned char u=a%10;	
		p[pos_i][pos_i] = (ca){d+'0',color};	
		p[pos_i][pos_j] = (ca){u+'0',color};
}


void pintar_buffer_video_posta(info_jug jug1, info_jug jug2) {
	printint(jug1.pts,47,36,0x40);
	printint(jug2.pts,47,41,0x10);
	printint(jug1.zqq,47,36,0x40);
	printint(jug2.zqq,47,41,0x10);
}

void printZombi(info_zombi z){
	if (z.vivo == 0){
		print("X", z.pos_j, z.pos_i, C_FG_RED+C_BG_GREEN);
	} else {
		switch(z.tipo){
			case ('G'):
				if (z.jugador == 0){print("G", z.pos_j, z.pos_i, C_FG_WHITE+C_BG_RED);}
				else {print("G", z.pos_j, z.pos_i, C_FG_WHITE+C_BG_BLUE);}
				break;
			case ('C'):
				if (z.jugador == 0){print("C", z.pos_j, z.pos_i, C_FG_WHITE+C_BG_RED);}
				else {print("C", z.pos_j, z.pos_i, C_FG_WHITE+C_BG_BLUE);}				
				break;
			case ('M'):
				if (z.jugador == 0){print("M", z.pos_j, z.pos_i, C_FG_WHITE+C_BG_RED);}
				else {print("M", z.pos_j, z.pos_i, C_FG_WHITE+C_BG_BLUE);}
				break;
		}
	}	
}
