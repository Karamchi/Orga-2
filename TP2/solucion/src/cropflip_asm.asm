global cropflip_asm

section .text
;void tiles_asm(unsigned char *src,
;              unsigned char *dst,
;		int cols, rows
;              int src_row_size,
;              int dst_row_size,
;		int tamx, int tamy,
;		int offsetx, int offsety);


cropflip_asm:
	; rdi<-*src, rsi<-*dst, edx<-cols, ecx<-rows, r8d<-src_row_size, r9d<-dst_row_size, 
	; tamx<-[rbp+16], tamy<-[rbp+24], offsetx<-[rbp+32], offsety<-[rbp+40]
	
	push rbp
	mov rbp, rsp
	push r12
	push r13
	push r14
	push r15

	mov r12d, [rbp + 16] 	;r12 <-tamx
	mov r13d, [rbp + 24]	;r13 <-tamy
	mov r14d, [rbp + 32] 	;r14 <-offsetx
	mov r15d, [rbp + 40] 	;r15 <-offsety
	
	xor r10, r10					; i
	
	.loopi:
		
		xor r11, r11				; j
		
		.loopj: 
			
			; en rax va el puntero a la posicion de src
			xor rax, rax
			mov rax, r13 		; rax = tamy
			add rax, r15 	; rax += offsety
			sub rax, r10			; rax -= i
			dec rax					; rax = tamy+offsety-i-1
			mul r8d					; ubique la fila
			lea rax, [rax + 4 * r14]
			lea rax, [rax + r11 * 4]			; rax = (tamy + offsety - i - 1) * src_row_size + (offsetx+j) * 4
			add rax, rdi
			movdqu xmm0, [rax]
			mov rax, r10
			mul r9d
			lea rax, [rax + r11 * 4]			; rax = i*dst_row_size+j*4
			add rax, rsi
			movdqu [rax], xmm0

			add r11, 4
			cmp r11, r13
			jl .loopj
		inc r10
		cmp r10, r12
		jl .loopi

			;%endif

		
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	ret
