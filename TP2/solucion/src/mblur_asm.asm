global mblur_asm
extern fopen, fclose, fprintf

section .data
align 16
mascara_negra: DB 0,0,0,255,0,0,0,255
mascara_mul: DD 3277, 3277, 3277, 3277
nombre: DB 'mblur_asm.time',0
formato: DB '%lu ',10,0


section .text
;void mblur_asm    (
	;unsigned char *src,
	;unsigned char *dst,
	;int filas,
	;int cols,
	;int src_row_size,
	;int dst_row_size)

mblur_asm:
	;rdi <- *src,  rsi <- *dst,  ecx <- filas,  edx <- cols,  r8d <- src_row_size,  r9d <- dst_row_size
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13
	sub rsp, 8

	mov ebx, edx	; guardo filas en rbx para que no me lo borre mul

	
	rdtsc				; imprime el tiempo en edx y eax
	mov r13d, edx
	shl r13, 32
	add r13d, eax
	
	mov r8d, r8d
	movdqu xmm14, [mascara_mul]

	mov ecx, ecx
	
	
	;pongo en 0 los bordes
	
	xor r10, r10
	mov r11, [mascara_negra]
	.cicloh:
		
		
		mov qword[rsi+r10*4], r11
		lea rax, [r9+r10*4]
		mov qword[rsi+rax], r11
		
		mov rax, rcx
		sub rax, 2
		mul r9d
		add rax, rsi
		mov qword[rax+r10*4], r11
		add rax, r9
		mov qword[rax+r10*4], r11
		
		
		add r10, 2
		cmp r10, rbx
		jl .cicloh
	
	xor r10, r10
	
	.ciclov:
		
		mov rax, r10
		mul r9d
		mov qword[rsi+rax], r11
		lea rax, [rax + r9 - 8]
		mov qword[rsi+rax], r11
		
		inc r10
		cmp r10, rcx
		jl .ciclov
		


	sub ecx, 4		; le resto 4 a filas y cols para facilitar la comparacion
	sub ebx, 4

	xor r10, r10

	.loopi:				;for i=0...filas-4
		
		xor r11, r11

		.loopj:			;for j=0...cols-4
			
			; cargo los datos. Vamos a procesar de a 4 pixeles por ciclo
			mov rax, r10
			mul r8d
			lea rax, [rax+r11*4]
			add rax, rdi
			movdqu xmm1, [rax]
			lea rax, [rax+r8+4]
			movdqu xmm2, [rax]
			lea rax, [rax+r8+4]
			movdqu xmm3, [rax]
			movdqu xmm4, [rax+r8+4]
			movdqu xmm5, [rax+2*r8+8]

			; copio a xmm6..10

			movdqa xmm6, xmm1
			movdqa xmm7, xmm2
			movdqa xmm8, xmm3
			movdqa xmm9, xmm4
			movdqa xmm10, xmm5

			; desempaqueto los low a xmm1..5, highs a xmm6..10
			pxor xmm11, xmm11

			
			punpcklbw xmm1, xmm11
			punpcklbw xmm2, xmm11
			punpcklbw xmm3, xmm11
			punpcklbw xmm4, xmm11
			punpcklbw xmm5, xmm11

			punpckhbw xmm6, xmm11
			punpckhbw xmm7, xmm11
			punpckhbw xmm8, xmm11
			punpckhbw xmm9, xmm11
			punpckhbw xmm10, xmm11

			; sumo en xmm1 y xmm6

			paddw xmm1, xmm2
			paddw xmm1, xmm3
			paddw xmm1, xmm4
			paddw xmm1, xmm5

			paddw xmm6, xmm7
			paddw xmm6, xmm8
			paddw xmm6, xmm9
			paddw xmm6, xmm10
			
			; divido por 5

			; uso que n/5=(n*3277)/(2^14) para n<=255*5
			; para almacenar 1275*3277 necesito 22b,
			; necesito una dword para hacer cada division por 5
			; para eso copio xmm1 en xmm12 y xmm6 en xmm13,
			; desempaqueto lows en xmm1 y 6 y highs en xmm12 y 13
			; multiplico y shifteo a derecha
			movdqa xmm12, xmm1
			movdqa xmm13, xmm6
			punpcklwd xmm1, xmm11
			punpcklwd xmm6, xmm11
			punpckhwd xmm12, xmm11
			punpckhwd xmm13, xmm11
			
			pmulld xmm12, xmm14
			pmulld xmm13, xmm14
			
			pmulld xmm1, xmm14
			pmulld xmm6, xmm14
			
			psrld xmm1, 14
			psrld xmm6, 14
			psrld xmm12, 14
			psrld xmm13, 14
			
			; ahora tengo, en los bytes menos significativos de las dwords de xmm1, xmm12, wmm6, xmm13 (en ese orden) los nuevos valores de rgba de cada uno de los 4 pixeles que procese. Hay que empaquetar de nuevo.
			packusdw xmm1, xmm12
			packusdw xmm6, xmm13
			
			packuswb xmm1, xmm6

			; ahora tengo en xmm1 el resultado listo para ser copiado de vuelta
			mov rax, r10
			mul r8d
			lea rax, [rax+r11*4]
			lea rax, [rax+r8*2+8]
			add rax, rsi
			movdqu [rax], xmm1
			
			add r11, 4
			cmp r11, rbx
			jl .loopj
		inc r10
		cmp r10, rcx
		jl .loopi
					
	rdtsc				; imprime el tiempo en edx y eax
	mov ebx, edx
	shl rbx, 32
	add ebx, eax
	
	sub rbx, r13			;y r13 por donde me lo meto?
	
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
			
	add rsp, 8
	pop r13
	pop r12
	pop rbx
	pop rbp
    ret
 
