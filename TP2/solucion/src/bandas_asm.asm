extern fopen, fclose, fprintf
global bandas_asm

section .data
mascara_rouli: DQ 0x0000FFFFFFFFFFFF, 0x0000FFFFFFFFFFFF	; PARA SACAR ALFAS DE BRILLO
_96: DW 96, 96, 96 ,96, 96, 96 ,96, 96
_288: DW 288, 288, 288, 288, 288, 288, 288, 288
_480: DW 480, 480, 480, 480, 480, 480, 480, 480
_672: DW 672, 672, 672, 672, 672, 672, 672, 672
b64: DW 64, 64, 64, 64, 64, 64, 64, 64
b128: DW 128, 128, 128, 128, 128, 128, 128, 128
b192: DW 192, 192, 192, 192, 192, 192, 192, 192
b255: DW 255, 255, 255, 255, 255, 255, 255, 255
FF: DQ 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF
nombre: DB 'bandas_asm.time',0
formato: DB '%lu ',10,0

section .text
;void bandas_asm    (
	;unsigned char *src,	RDI
	;unsigned char *dst,	RSI
	;int filas,				EDX
	;int cols,				ECX
	;int src_row_size,		R8D
	;int dst_row_size)		R9D

bandas_asm:
		;1 Datos a procesar (filas * columnas en pix) (en bytes es *4 o *3)
		;2 recorro por filas y dsp por columnas
		;3 entran 16 char, que serian 4 pixeles, pero me conviene trabajar con 2,
		; sumar 3 y eso guardarlo en xmm como short q justamente entran 8. Paso xmm short
		;4 paso los 16 bytes en un xmm y de alguna forma sumo d a tres.
		;5 el resultado de los 2 short finales los tengo q pasar por los distintos 
		;CASOS, y de ahi hago que grabe en los 6 bytes (sin modificar brillo)
		; lo q corresponda para cada uno.
		;6 variables locales, tal vez necesite.
		; VER SI ES MEJOR AGARRAR DE A DOS PIXELES, Porq los tengo q pasar a short entonces me quedarian los 2 pixeles q en total vale 8, me queda en 16 y ahi puedo trabajar en eso directamente, en vez de tener q dividir en 2 registros con 4 pixeles. (guardando 2 es mas simple el ciclo, guardando 4 hago mas en un ciclo.) 
	push rbp
	mov rbp, rsp
	push rbx		;Contador de FILAS
	push r12		;Contador de COLUMNAS
	push r13		;Para usarlo en el Movdqu
	push r14
	sub rsp, 16	
	
	mov r14d, edx
	
	rdtsc				; imprime el tiempo en edx y eax
	mov r10d, edx
	shl r10, 32
	add r10d, eax
	
	xor rbx, rbx
	xor r12, r12
	xor r13, r13
	
	.ciclo_f:
		cmp ebx, ecx	;Comparo si ya termino las filas
		je .termine		;Creo que je esta bien
		
			.ciclo_c:
				cmp r12d, r14d
				je .sigo_f
				;R13=R12 * 4 + ebx * ancho
				mov eax, ebx
				mul r8d
				shl r12, 2
				add eax, r12d
				mov r13d, eax
				shr r12, 2
				; mov edx, r14d
				
				pmovzxbw xmm0, [rdi + r13]	; acá ya tengo los bytes en words 2 pix, xmm0 = original
				movdqu xmm7, [mascara_rouli]	; xmm7 = mascara
				movdqu xmm1, xmm0	; xmm1 = xmm0
				pand xmm1, xmm7		; xmm1 =  xmm0 sin los Alfa
				phaddw xmm1, xmm1 	; R+G y B+0
				phaddw xmm1, xmm1	; R+G+B+0 de los dos pixels en los dos short mas bajos en xmm1 (en el 00 y 01)
				
				movdqu xmm2, [_96]	; Para comparar con 96
				pcmpgtw xmm2, xmm1	; xmm2 > xmm1 A los q estan como 0xFFFF significa q son menores estrictos el de xmm1
				movdqu xmm3, [FF]	; xmm3 todos 1
				pxor xmm2, xmm3		; xmm2 negado
				pand xmm1, xmm2		; queda en cero los q cumplen, e igual los q no.
				
				movdqu xmm4, [_288]
				pcmpgtw xmm4, xmm1	; b < 288
				pand xmm2, xmm4		; los que cumplen las dos condiciones quedan en 0xFFFF (96 <= b < 288)
				movdqu xmm5, [b64]
				pand xmm5, xmm2		; deja en 64 el q cumple y 0 el q no
				pxor xmm2, xmm3		; xmm2 negado
				pand xmm1, xmm2		; va a dejar igual el q no cumple y el q si en 0x0000
				por xmm1, xmm5		; modifica solo el q cumple. xmm2 y xmm5 los puedo usar para la proxima
				
				pxor xmm4, xmm3		; b >= 288
				movdqu xmm2, [_480]
				pcmpgtw xmm2, xmm1	; b < 480
				pand xmm4, xmm2		; 288 <= b < 480
				movdqu xmm5, [b128]
				pand xmm5, xmm4
				pxor xmm4, xmm3
				pand xmm1, xmm4
				por xmm1, xmm5		; lo mismo q para el b entre 96 y 288. xmm4 y xmm5 los puedo usar para la proxima
				
				pxor xmm2, xmm3		; b >= 480
				movdqu xmm4, [_672]
				pcmpgtw xmm4, xmm1	; b < 672
				pand xmm2, xmm4		; 480 <= b < 672
				movdqu xmm5, [b192]
				pand xmm5, xmm2
				pxor xmm2, xmm3
				pand xmm1, xmm2
				por xmm1, xmm5
				
				pxor xmm4, xmm3		; b >= 672
				movdqu xmm5, [b255]
				pand xmm5, xmm4
				pxor xmm4, xmm3
				pand xmm1, xmm4
				por xmm1, xmm5
				
				movdqu xmm6, xmm0	;copia de xmm0
				pshuflw xmm6, xmm1, 0x00	; la parte baja quedo <b, b, b, b> y la alta se copio lo de la parte alta de xmm1
				pshufhw xmm0, xmm6, 0x55	; ahí me queda bien en el xmm0 la parte alta b1 y la baja con b0
				
				packuswb xmm0, xmm0
				movq [rsi + r13], xmm0
				
				add r12d, 2
				jmp .ciclo_c
				
	.sigo_f:	
		inc ebx		;incremento en 1 las filas
		xor r12, r12
		jmp .ciclo_f

	.termine:
	
		rdtsc				; imprime el tiempo en edx y eax
		mov r11d, edx
		shl r11, 32
		add r11d, eax
	
		sub r11, r10
		mov rbx, r11

		mov rdi, nombre
		mov qword [rsp], 'a'
		mov rsi, rsp
		call fopen	
		mov r12, rax
	
		mov rdi, r12 
		mov rsi, formato
		mov rdx, rbx
		call fprintf

		mov rdi, r12
		call fclose
	
		add rsp, 16
		pop r14
		pop r13
		pop r12
		pop rbx
		pop rbp
		ret
 
