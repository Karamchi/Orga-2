global sierpinski_asm

section .data

section .text

;void sierpinski_asm (unsigned char *src,
;                     unsigned char *dst,
;                     int cols, int rows,
;                     int src_row_size,
;                     int dst_row_size)

sierpinski_asm:
        push rbp
        mov rbp, rsp
        push rbx
        push r12
        push r13
        push r14
        push r15
        sub rsp, 16
        mov dword [rsp], 255
        mov dword [rsp+8], 4

        mov r12d, edx ; cols
        mov r13d, ecx ; rows
        mov r14d, r8d ; src_row_size
        mov r15d, r9d ; dst_row_size

        xor rdx, rdx
        mov ecx, 0 ;i
    .ciclof:
        mov r8d, 0 ;j
    .cicloc:
        mov eax, ecx
        mul dword [rsp] ; [rsp]=255, no te deja dividir directo por un nº
        div r12d 
        mov r10d, eax ;r10=i*255/filas

        mov eax, r8d 
        div dword [rsp+8]
        mul dword [rsp]
        div r13d 
        mov r11d, eax ;r11=i*255/filas

        xor r10d, r11d 
        cvtsi2sd xmm0, r10d
        cvtsi2sd xmm1, [rsp]; divido por 255
        divsd xmm0, xmm1 ; xmm0=coef

        mov eax, ecx
        mul r14d
        mov r10d, eax ; escala*fila (src)

        mov eax, ecx
        mul r15d
        mov r11d, eax ; escala*fila (dst)

        add edi, r10d
        add edi, r8d

        add esi, r11d
        add esi, r8d

        cvtsi2sd xmm1, [rdi] ; rdi = inicio + escala*fila + columna (src)
        mulsd xmm0, xmm1
        cvtsd2si r10d, xmm0
		mov [rsi], r10b ; rsi = inicio + escala*fila + columna (dst)

        cvtsi2sd xmm1, [rdi+1]
        mulsd xmm0, xmm1
        cvtsd2si r10d, xmm0
		mov [rsi+1], r10b

        cvtsi2sd xmm1, [rdi+2]
        mulsd xmm0, xmm1
        cvtsd2si r10d, xmm0
		mov [rsi+2], r10b

        sub edi, r10d ; si, ya sé que modifiqué r10, ahora me importa que compile
        sub edi, r8d

        sub esi, r11d
        sub esi, r8d

        add r8d, 4 ; j+=4
        mov eax, edx
        mul dword [rsp+8] ; fuuuu
        cmp r8d, eax 
        jne .cicloc

        inc ecx ; i++
        cmp ecx, r13d
        jne .ciclof

        add rsp, 16
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbx
        pop rbp
        ret
