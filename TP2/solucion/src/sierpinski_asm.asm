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
        sub rsp, 8
        mov dword [rsp], 255

        mov r12d, 0 			;i
    .ciclof:
        mov r13, 0 			;j (PIXEL) (y limpio la parte alta)
    .cicloc:

	xor rbx, rbx
	mov eax, r12d
	mul r8d
	mov ebx, eax
	shl r13, 2
	add ebx, r13d
	mov ebx, r12d			; ebx=r12d*r8d+r13d*4
	shr r13, 2

	movdqu xmm1, [rdi+rbx] 		; pongo en xmm1 4 pixeles
	movdqu xmm2, xmm1
	pxor xmm7, xmm7
	punpckhwd xmm1, xmm7 		; xmm1=r0|g0|b0|a0|r1|g1|b1|a1
	punpcklwd xmm2, xmm7 		; xmm2=r2|g2|b2|a2|r3|g3|b3|a3 

	movdqu xmm0, xmm1		
	punpckhdq xmm0, xmm7		; xmm0=r0|g0|b0|a0 (unsigned int)
	punpckldq xmm1, xmm7		; xmm1=r1|g1|b1|a1 (unsigned int)
	movdqu xmm3, xmm2
	punpckhdq xmm2, xmm7		; xmm2=r2|g2|b2|a2 (unsigned int)
	punpckldq xmm3, xmm7		; xmm3=r3|g3|b3|a3 (unsigned int)
					
	mov eax, r12d
	mul dword [rsp]
        xor rdx, rdx			; porlas
	div ecx				; eax=i*255/filas
	
	movd xmm4, eax 			; xmm4=0|0|0|eax
	pshufd xmm4, xmm7, 0	 	; xmm4=i*255/filas|i*255/filas|i*255/filas|i*255/filas (unsigned int)

	movd xmm5, r13d
	pshufd xmm5, xmm5, 0		; xmm5=r13d|r13d|r13d|r13d
	paddd xmm5, [unodostres] 	; xmm5=j|j+1|j+2|j+3

	movd xmm6, edx 			; xmm6=0|0|0|edx
	pshufd xmm6, xmm7, 0	 	; xmm6=edx|edx|edx|edx=cols|cols|cols|cols

	pmulld xmm5, [doscincocinco]	; xmm5=j*255|(j+1)*255|(j+2)*255|(j+3)*255 (unsigned int)
	cvtdq2ps xmm5, xmm5		; pasar a float porque no hay div entera con packs
	divps xmm5, xmm6 		; xmm5=j*255/cols|(j+1)*255/cols|(j+2)*255/cols|(j+3)*255/cols (float)
	cvtps2dq xmm5, xmm5 		; ahora son unsigned int
	pxor xmm4, xmm6 		; xmm4=coef(i,j)*255|coef(i,j+1)*255|coef(i,j+2)*255|coef(i,j+3)*255 (unsigned int)

	movdqu xmm5, xmm4
	pshufd xmm5, xmm5, 0		; xmm5=coef(i,j)*255|coef(i,j)*255|coef(i,j)*255|coef(i,j)*255 (unsigned int)
	pmulld xmm0, xmm5		; xmm0*xmm5
	cvtdq2ps xmm0, xmm0		; xmm0->float
	divps xmm0, [doscincocinco]	; xmm0/255
	cvtps2dq xmm0, xmm0		; xmm0->unsigned int

	movdqu xmm5, xmm4
	pshufd xmm5, xmm5, 0x55		; xmm5=coef(i,j+1)*255|coef(i,j+1)*255|coef(i,j+1)*255|coef(i,j+1)*255 (unsigned int)
	pmulld xmm1, xmm5		; xmm1*xmm5
	cvtdq2ps xmm1, xmm1		; xmm1->float
	divps xmm1, [doscincocinco]	; xmm1/255
	cvtps2dq xmm1, xmm1		; xmm1->unsigned int

	movdqu xmm5, xmm4
	pshufd xmm5, xmm5, 0xaa		; xmm5=coef(i,j+2)*255|coef(i,j+2)*255|coef(i,j+2)*255|coef(i,j+2)*255 (unsigned int)
	pmulld xmm2, xmm5		; xmm2*xmm5
	cvtdq2ps xmm2, xmm2		; xmm2->float
	divps xmm2, [doscincocinco]	; xmm2/255
	cvtps2dq xmm2, xmm2		; xmm2->unsigned int

	movdqu xmm5, xmm4
	pshufd xmm5, xmm5, 0xff		; xmm5=coef(i,j+3)*255|coef(i,j+3)*255|coef(i,j+3)*255|coef(i,j+3)*255 (unsigned int)
	pmulld xmm3, xmm5		; xmm3*xmm5
	cvtdq2ps xmm3, xmm2		; xmm3->float
	divps xmm3, [doscincocinco]	; xmm3/255
	cvtps2dq xmm3, xmm3		; xmm3->unsigned int

	packusdw xmm0, xmm1		; volver a empaquetar todo en xmm0
	packusdw xmm2, xmm3
	packuswb xmm0, xmm2

	movdqu [rsi+rbx], xmm0 		; pongo en el destino (rbx no lo toqué)

        inc r13d 			; j++
        cmp r13d, edx 
        jne .cicloc

        inc r12d 			; i++
        cmp r12d, ecx
        jne .ciclof

        add rsp, 8
        pop r13
        pop r12
        pop rbx
        pop rbp
        ret 				;gg
