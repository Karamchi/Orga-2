
#include "tp2.h"

void bandas_c (
	unsigned char *src,
	unsigned char *dst,
	int m,	//cols
	int n,	//filas
	int src_row_size,
	int dst_row_size
) {
	unsigned char (*src_matrix)[src_row_size] = (unsigned char (*)[src_row_size]) src;
	unsigned char (*dst_matrix)[dst_row_size] = (unsigned char (*)[dst_row_size]) dst;

	// TODO: Implementar	
	
	int b;
	for (int i = 0; i < n ; i++){	// itero n filas
		for (int j = 0; j < m * 4; j = j + 4 ){	// itero m * 3 columnas porque son de 3 bytes cada pixel. OJO ver si es rgba en vez de rgb
			b = 0;	//reseteo el b
			b = b + src_matrix[i][j] + src_matrix[i][j+1] + src_matrix[i][j+2];
			b = ((b/96 + 1)/2) * 64;	//esto deberia dar segun espi, lo q hay q poner, excepto cuando deberia ser 256. Sin saltos Condicionales! (Ver si hay q probar con saltos)
			if (b == 256){
				b--;
			}
			dst_matrix[i][j] = b;
			dst_matrix[i][j+1] = b;
			dst_matrix[i][j+2] = b;
		}
	}

}
