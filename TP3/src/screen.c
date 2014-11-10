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

void game_print_debug(int eax) {
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
		for (j = x + 1; j < x + width - 1; j++) p[i][j] = (ca){' ',(i==8)*0x10+0x70};
	}
	//guardar pantalla
	ca* fin=(ca*) 0xb8fa0;
	for (i=0;i<4000;i++) {
		fin[i]=p[i/50][i%50];
	}

	if (anteriorjug==0) {
		print("Zombi A",26,8,0x1f);
		if ((tareasA[(int)anteriorA]).tipo=='G') {
			print("Guerrero",35,8,0x1f);
		} else if ((tareasA[(int)anteriorA]).tipo=='M') {
			print("Mago",35,8,0x1f);
		} else {
			print("Clerigo",35,8,0x1f);
		}
	} else {
		print("Zombi B",26,8,0x1f);
		if ((tareasB[(int)anteriorB]).tipo=='G') {
			print("Guerrero",35,8,0x1f);
		} else if ((tareasB[(int)anteriorB]).tipo=='M') {
			print("Mago",35,8,0x1f);
		} else {
			print("Clerigo",35,8,0x1f);
		}
	}
	//al llamar queda:

	//		<-esp
	//dir ret
	//eax (ultima cosa pusheada por la fn anterior, lo ve como parámetro)
	//b,c,d,si,di
	//rbp (viejo, dice donde empieza la pila de la funcion que llama)

	int* pos=&eax;
	int* base=(int*)(*(pos-6*4));
	char* cosasAimprimir[]={"eax","ebx","ecx","edx","esi","edi","ebp","esp","eip","cs","ds","es","fs","gs","ss","cr0","cr2","cr3","cr4"};
	
	for (i=0;i<9;i++) {
		print (cosasAimprimir[i],27,i*2+10,0x80);
		print_hex (*pos,8,31,i*2+10,0x80);
		pos-=4;
	}
	for (i=9;i<14;i++) {
		print (cosasAimprimir[i],27,i*2+10,0x80);
		print_hex (*pos,4,31,i*2+10,0x80);
		pos-=4; //?
	}
	print ("eflags",40,28,0x80);
	print_hex(*pos,28,34,40,0x8f);
	for (i=0;i<4;i++) {
		print (cosasAimprimir[i+15],40,i*2+10,0x80);
		print_hex (*pos,8,44,i*2+10,0x80);
		pos-=4;
	}
	print ("stack",40,27,0x8f);
	for (i=0;pos>=base;i++) {
		print_hex(*pos,8,40,i*2+10,0x80);
		pos-=8; //?
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
