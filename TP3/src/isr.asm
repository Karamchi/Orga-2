; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00
chars: db 'wasdijklslsr'
int_msg: db 'Divide error(DE)RESERVED(DB)    NMI Interrupt   Breakpoint(BP)  Overflow(OF)    BOUND R.E(BR)   Invalid Opcode  Device NA(NM)   DOUBLE FAULT(DF)CSO             Invalid TSS(TS) Segment Not Pr. Stack S Fault   General Protect Page Fault(PF)  RESERVED        Math Fault(MF)  AlignmentCheck  Machine Check F Point Except    '
;; PIC
extern fin_intr_pic1

;; GAME
extern game_move_current_zombi
extern game_jugador_mover
extern game_cambiar_tipo_zombi
extern game_lanzar_zombi

;; Sched
extern sched_proximo_indice

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    cli
    pushad
    mov ecx, %1		; guardo para el sys66
    mov eax, %1		; numero de interrupcion
    cmp eax, 32
    je Reloj
    cmp eax, 33
    je Teclado
    cmp eax, 102
    je sys66
    mov edi, int_msg
    mov esi, 16
    mul esi
    add edi, eax
    imprimir_texto_mp edi, 16, 0x07, 0, 0
    xchg bx, bx
    ;mov edi, 0xb8000 ; pantalla
    ;mov esi, 0x0F4E0F49	; 'IN' al reves (por little endian). Vamos a imprimir esto por pantalla.
    ;mov [edi], esi
    
    ;mov esi, 0x043A0F54	; 'T:'
    ;mov [edi+4], esi
    
    ;add eax, 65				; eax era el numero de interrupcion, lo pasamos a letra para imprimirlo en un solo caracter (esta en al)
    ;mov [edi+8], al
    ;mov byte[edi+9], 0x0F	; 0F es el color blanco
    popad
    
    iret

%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
ISR 32
ISR 33
ISR 102
;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;
Reloj:
	call fin_intr_pic1
	call proximo_reloj
	popad
	sti
	iret
;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
Teclado:
	
	call fin_intr_pic1
	in al, 0x60
	mov ebx, chars
	cmp al, 0x11
	je .imprimirW
	cmp al, 0x1E
	je .imprimirA
	cmp al, 0x1F
	je .imprimirS
	cmp al, 0x20
	je .imprimirD
	cmp al, 0x17		
	je .imprimirI
	cmp al, 0x24
	je .imprimirJ
	cmp al, 0x25
	je .imprimirK
	cmp al, 0x26
	je .imprimirL
	cmp al, 0x2A
	je .imprimirSR
	cmp al, 0x36
	je .imprimirSL
	jmp .finposta
    .imprimirW:
    push 1
    push 1
    call game_jugador_mover
	jmp .fin
    .imprimirA:
    push 0xFFFFFFFF
    push 1
    call game_cambiar_tipo_zombi
	add ebx, 1
	jmp .fin
    .imprimirS:
    push 0xFFFFFFFF
    push 1
    call game_jugador_mover
	add ebx, 2
	jmp .fin
    .imprimirD:
    push 1
    push 1
    call game_cambiar_tipo_zombi
	add ebx, 3
	jmp .fin
    .imprimirI:
    push 1
    push 2
    call game_jugador_mover
	add ebx, 4
	jmp .fin
    .imprimirJ:
    push 0xFFFFFFFF
    push 2
	add ebx, 5
    call game_cambiar_tipo_zombi
	jmp .fin
    .imprimirK:
    push 0xFFFFFFFF
    push 2
    call game_jugador_mover
	add ebx, 6
	jmp .fin
    .imprimirL:
    push 1
    push 2
    call game_cambiar_tipo_zombi
	add ebx, 7
	jmp .fin
    .imprimirSR:
    push 2
    call game_lanzar_zombi
	add ebx, 8
	jmp .fin2
    .imprimirSL:
    push 1
    call game_lanzar_zombi
	add ebx, 10
    
    .fin:
	imprimir_texto_mp ebx, 1, 0x0f, 0, 79	
	jmp .finposta
    .fin2:
	imprimir_texto_mp ebx, 2, 0x0f, 0, 78	
    .finposta:
	popad
	sti
	iret

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
sys66:	;ecx numero de la interrupcion
	call fin_intr_pic1
	popad
	push ecx
	call game_move_current_zombi
	pop ecx
	mov eax, 0x42	;Esto es del ejercicio de Interrupciones
	sti
	iret
	
%define IZQ 0xAAA
%define DER 0x441
%define ADE 0x83D
%define ATR 0x732


;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximo_reloj:
	
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret
        
        
