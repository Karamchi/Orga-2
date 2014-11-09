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
	p[47][31]=(ca){'2',0x4f};
	p[47][32]=(ca){'0',0x4f};
	p[47][47]=(ca){'2',0x1f};
	p[47][48]=(ca){'0',0x1f};
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
		p[pos_i][pos_j] = (ca){d+'0',color};	
		p[pos_i][pos_j+1] = (ca){u+'0',color};
}


void pintar_buffer_video_posta(info_jug jug1, info_jug jug2) {
	printint(jug1.zqq,47,31,0x4f);
	printint(jug2.zqq,47,47,0x1f);
	printint(jug1.pts,47,36,0x4f);
	printint(jug2.pts,47,41,0x1f);
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

char bool_debug(){return debug;}

void game_print_debug(int eax, int ebx, int ecx, int edx, int esi, int edi, int ebp, int esp, int eip, short cs, short ds, short es, short fs, short gs, short ss, int eflags) {
	if (debug) {
		ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
		int x=25;
		int y=7;
		int width=50;
		int height=36;
	
		int i;
		int j;
		for (i = x; i < x + width; i++) {
			p[y][i] = (ca){' ',0};
			p[y+height][i] = (ca){' ',0};
		}
		for (i = y+1; i < y + height -1; i++) {
			p[i][x] = (ca){' ',0};
			p[i][x+width] = (ca){' ',0};
			for (j = x + 1; j < x + width - 1; j++) p[i][j] = (ca){' ', 0x80};
		}
		//guardar pantalla
		ca* fin=(ca*) 0xb8fa0;
		for (i=0;i<4000;i++) {
			fin[i]=p[i/50][i%50];
		}
		print ("eax",27,10,0x80);
		print_hex(eax, 8,31,10,0x8f);
		print ("ebx",27,12,0x80);
		print_hex(ebx, 8,31,12,0x8f);
		print ("ecx",27,14,0x80);
		print_hex(ecx, 8,31,14,0x8f);
		print ("edx",27,16,0x80);
		print_hex(edx, 8,31,16,0x8f);
		print ("esi",27,18,0x80);
		print_hex(esi, 8,31,18,0x8f);
		print ("edi",27,20,0x80);
		print_hex(edi, 8,31,20,0x8f);
		print ("ebp",27,22,0x80);
		print_hex(ebp, 8,31,22,0x8f);
		print ("esp",27,24,0x80);
		print_hex(esp, 8,31,24,0x8f);
		print ("eip",27,26,0x80);
		print_hex(eip, 8,31,26,0x8f);
		print ("cs",28,28,0x80);
		print_hex(cs, 8,31,28,0x8f);
		print ("ds",28,30,0x80);
		print_hex(ds, 4,31,30,0x8f);
		print ("es",28,32,0x80);
		print_hex(es, 4,31,32,0x8f);
		print ("fs",28,34,0x80);
		print_hex(fs, 4,31,34,0x8f);
		print ("gs",28,36,0x80);
		print_hex(gs, 4,31,36,0x8f);
		print ("ss",28,38,0x80);
		print_hex(ss, 4,31,38,0x8f);
		print ("eflags",28,40,0x80);
		print_hex(eflags, 28,34,40,0x8f);
	}
}

void recuperarPantalla(){
	int i;
	ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
	ca* fin=(ca*) 0xb8fa0;
	for (i=0;i<4000;i++) {
		p[i/50][i%50]=fin[i];
	}
}
