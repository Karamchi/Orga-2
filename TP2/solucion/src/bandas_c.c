#include <stdio.h>
#include "tp2.h"
#include "tiempo.h"

void bandas_c (
	unsigned char *src,
	unsigned char *dst,
	int m,	//cols
	int n,	//filas
	int src_row_size,
	int dst_row_size
) {
	unsigned long start, end;
	MEDIR_TIEMPO_START(start)
	unsigned char (*src_matrix)[src_row_size] = (unsigned char (*)[src_row_size]) src;
	unsigned char (*dst_matrix)[dst_row_size] = (unsigned char (*)[dst_row_size]) dst;

	// TODO: Implementar	
	
	int b;
	for (int i = 0; i < n ; i++){	// itero n filas
		for (int j = 0; j < m; j ++ ){	// itero m * 4 columnas porque son de 4 bytes cada pixel. (rgba)
			b = 0;	//reseteo el b
			b = src_matrix[i][j*4] + src_matrix[i][j*4+1] + src_matrix[i][j*4+2];
			if (b<96) {
				b=0;
			} else if (b<288) {
				b=64;
			} else if (b<480) {
				b=128;
			} else if (b<672) {
				b=192;
			} else {
				b=255;
			}
			/*b = ((b/96 + 1)/2) * 64;
			if (b == 256){
				b--;
			}*/
			dst_matrix[i][j*4] = b;
			dst_matrix[i][j*4 + 1] = b;
			dst_matrix[i][j*4 + 2] = b;
		}
	}
	MEDIR_TIEMPO_STOP(end);
	unsigned long delta = end - start;
	FILE* archivo=fopen("bandas_c.time","a");
	fprintf(archivo,"%lu ciclos\n", delta);
	fclose(archivo);
}
