global sierpinski_asm

section .data
unodostres: DD 0,1,2,3
doscincocinco: DD 255,255,255,255

section .text

;void sierpinski_asm (unsigned char *src,	;rdi=src
;                     unsigned char *dst,	;rsi=dst (si, fueron molestos)
;                     int cols, int rows,	;edx=cols ; ecx=rows
;                     int src_row_size,		;r8d=src_row_size
;                     int dst_row_size)		;r9d=dst_row_size

sierpinski_asm:
        push rbp
        mov rbp, rsp
        push rbx
        push r12
        push r13
        sub rsp, 16
        mov dword [rsp], 255

        mov r12d, 0 			;i
    .ciclof:
        mov r13d, 0 			;j (PIXEL)
    .cicloc:
	xor rbx, rbx
	mov ebx, r12d			; en realidad, r12d*r8d+r13d*4
	movdqu xmm1, [rdi+rbx] 		; pongo en xmm1 4 pixeles
	movdqu xmm2, xmm1
	pxor xmm7, xmm7
	punpckhwd xmm1, xmm7 		; xmm1=r0|g0|b0|a0|r1|g1|b1|a1
	punpcklwd xmm2, xmm7 		; xmm2=r2|g2|b2|a2|r3|g3|b3|a3 

					; xmm0=r0|g0|b0|a0 (float)	
					; xmm1=r1|g1|b1|a1 (float)
					; xmm2=r2|g2|b2|a2 (float)
					; xmm3=r3|g3|b3|a3 (float)
	
	mov eax, r12d
	mul dword [rsp]
        xor rdx, rdx			; porlas
	div ecx				; eax=i*255/filas
	
	movd xmm4, eax 			; xmm4=0|0|0|eax
	pshufd xmm4, xmm7, 0	 	; xmm4=i*255/filas|i*255/filas|i*255/filas|i*255/filas (int)

	movd xmm5, r13d
	pshufd xmm5, xmm7, 0		; xmm5=r13d|r13d|r13d|r13d
	paddd xmm5, [unodostres] 	; xmm5=j|j+1|j+2|j+3

	movd xmm6, edx 			; xmm6=0|0|0|edx
	pshufd xmm6, xmm7, 0	 	; xmm6=edx|edx|edx|edx=cols|cols|cols|cols

	pmulld xmm5, [doscincocinco]	; xmm5=j*255|(j+1)*255|(j+2)*255|(j+3)*255
	divps xmm5, xmm6 		; xmm5=j*255/cols|(j+1)*255/cols|(j+2)*255/cols|(j+3)*255/cols (float)
	cvtps2dq xmm5, xmm5 		; ahora son int
	pxor xmm4, xmm6 		; xmm4=coef(i,j)*255|coef(i,j+1)*255|coef(i,j+2)*255|coef(i,j+3)*255 (int)

	;pshufb				; xmm5=coef(i,j)*255|coef(i,j)*255|coef(i,j)*255|coef(i,j)*255 (int)
					; xmm0->int
					; xmm0*xmm5
					; xmm0->float
					; xmm0/255
					; xmm0->int
					; repetir para los 3 registros
					; volver a empaquetar todo en xmm0
					; mov rbx, r12d*r8d+r13d*4 (que convenientemente tengo guardado en algún lado)
	movdqu [rsi+rbx], xmm0 		; pongo en el destino

        inc r13d 			; j++
        cmp r13d, edx 
        jne .cicloc

        inc r12d 			; i++
        cmp r12d, ecx
        jne .ciclof

        add rsp, 16
        pop r13
        pop r12
        pop rbx
        pop rbp
        ret 				;gg
