#include <stdio.h>
#include "tp2.h"
#include "tiempo.h"

#define MIN(x,y) ( x < y ? x : y )
#define MAX(x,y) ( x > y ? x : y )

#define P 2

void mblur_c    (
    unsigned char *src,
    unsigned char *dst,
    int cols,
    int filas,
    int src_row_size,
    int dst_row_size)
{
	unsigned long start, end;
    MEDIR_TIEMPO_START(start)

    unsigned char (*src_matrix)[src_row_size] = (unsigned char (*)[src_row_size]) src;
    unsigned char (*dst_matrix)[dst_row_size] = (unsigned char (*)[dst_row_size]) dst;

	
	for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < cols*4; j++)
        {	
        	dst_matrix[i][j] = 0;
        	dst_matrix[filas-i][j] = 0;
    	}
    }
    
    for (int i = 2; i < filas-2; i++)
    {
        for (int j = 0; j < 8; j++)
        {	
        	dst_matrix[i][j] = 0;
        	dst_matrix[i][cols-j] = 0;
    	}
    }
    
	
	for (int i = 2; i < filas-2; i++)
    {
        for (int j = 8; j < cols*4-8; j++)
        {
            dst_matrix[i][j] = src_matrix[i-2][j-8]*0.2 + src_matrix[i-1][j-4]*0.2 + src_matrix[i][j]*0.2 + src_matrix[i+1][j+4]*0.2 + src_matrix[i+2][j+8]*0.2;
            
            /*bgra_t *p_d = 0;
            bgra_t *p_s = 0;
            *p_d = *p_s;  */
        }
    }
	MEDIR_TIEMPO_STOP(end);
	unsigned long delta = end - start;
	FILE* archivo=fopen("mblur_c.time","a");
	fprintf(archivo,"%lu ciclos\n", delta);
	fclose(archivo);
}


