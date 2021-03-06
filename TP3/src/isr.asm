; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"
%define TIEMPO_FIN 1023
BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00
chars: db 'wasdijklslsry'
int_msg: db 'Divide error(DE)RESERVED(DB)    NMI Interrupt   Breakpoint(BP)  Overflow(OF)    BOUND R.E(BR)   Invalid Opcode  Device NA(NM)   DOUBLE FAULT(DF)CSO             Invalid TSS(TS) Segment Not Pr. Stack S Fault   General Protect Page Fault(PF)  RESERVED        Math Fault(MF)  AlignmentCheck  Machine Check F Point Except    '
offset: dd 0
selector: dw 0x70
debug: db 0
mostrando: db 0
contador: dd 0
;; PIC
extern fin_intr_pic1

;; GAME
extern game_move_current_zombi
extern game_jugador_mover
extern game_cambiar_tipo_zombi
extern game_lanzar_zombi
extern game_chau_zombi
extern recuperarPantalla
extern game_print_debug
extern cambiar_modo_debug
extern pintar_relojes
extern game_terminar

;; Sched
extern sched_proximo_indice

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
		%if %1=8 || %1=10 || %1=11 || %1=12 || %1=13 || %1=14 || %1=17
		add esp, 4
		%endif 
    cmp byte [mostrando], 1			; Si estoy mostrando la información de debug, dejo solo la interrupción de la y
    je SoloY
    pushad
    ;pushfd
    mov ecx, eax					; guardo para el sys66
    mov eax, %1						; numero de interrupcion
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
	call game_chau_zombi
    
	
        cmp byte [debug], 1
        jne .sinDebug
	        mov byte [mostrando], 1
        
        	popad					;recupero originales
        	pushad					; pero no los piso
        
            mov [esp-20], eax       ;push manual
            mov eax, cr4
            push eax
            mov eax, cr3
            push eax
            mov eax, cr2
            push eax
            mov eax, cr0
            push eax
            sub esp, 4
            pop eax
            
            pushfd
            push ss
            push gs
            push fs
            push es
            push ds
            push cs
            call .picaron
            .picaron:
            push esp
            push ebp
            push edi
            push esi
            push edx
            push ecx
            push ebx
            push eax
            push esp

            call game_print_debug

		.sinDebug:
		cmp byte [selector], 0x70 ; si no estoy en la idle, salto a idle
		je .fin
		mov word [selector], 0x70
    	jmp 0x70:0
    .fin:
	popad
    ;popfd
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
	add dword [contador], 1
	cmp dword [contador], TIEMPO_FIN
	jne .sigue_el_baile
	call game_terminar
	.sigue_el_baile:
	call proximo_reloj
	call sched_proximo_indice
	;shl ax, 3
	cmp ax, [selector]
	je .end
		mov [selector], ax
		jmp far [offset]
	    call pintar_relojes
		jmp .end
		
	.end:
	;popfd
	popad
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
	cmp al, 0x36
	je .imprimirSR
	cmp al, 0x2A
	je .imprimirSL
	cmp al, 0x15
	je .imprimirY
	jmp .finposta
    .imprimirW:
    push 1
    push 0
    call game_jugador_mover
	jmp .fin
    .imprimirA:
    push 1
    push 0
    call game_cambiar_tipo_zombi
	add ebx, 1
	jmp .fin
    .imprimirS:
    push 3
    push 0
    call game_jugador_mover
	add ebx, 2
	jmp .fin
    .imprimirD:
    push 3
    push 0
    call game_cambiar_tipo_zombi
	add ebx, 3
	jmp .fin
    .imprimirI:
    push 1
    push 1
    call game_jugador_mover
	add ebx, 4
	jmp .fin
    .imprimirJ:
    push 1
    push 1
	add ebx, 5
    call game_cambiar_tipo_zombi
	jmp .fin
    .imprimirK:
    push 3
    push 1
    call game_jugador_mover
	add ebx, 6
	jmp .fin
    .imprimirL:
    push 3
    push 1
    call game_cambiar_tipo_zombi
	add ebx, 7
	jmp .fin
    .imprimirSR:
    push 1
    call game_lanzar_zombi
	add ebx, 8
	jmp .fin2
    .imprimirSL:
    push 0
    call game_lanzar_zombi
	add ebx, 10
	jmp .fin2
    .imprimirY:
	cmp byte [debug], 0
    jne .enDebug
	    mov byte [debug], 1
        jmp .finY
    .enDebug:
        cmp byte [mostrando], 0
        jne .recuperar
            mov byte [debug], 0
            jmp .finY
        .recuperar:
            mov byte [mostrando], 0
			pushad
          	call recuperarPantalla
			popad

    .finY:
    add ebx, 12
	imprimir_texto_mp ebx, 1, 0x0f, 0, 79	
    jmp .finposta

    .fin:
    pop eax
    pop eax
	imprimir_texto_mp ebx, 1, 0x0f, 0, 79	
	jmp .finposta
    .fin2:
    pop eax
	imprimir_texto_mp ebx, 2, 0x0f, 0, 78	
    .finposta:
	popad
	;popfd
	iret
	
SoloY:
	;cmp eax, 33
    ;jne .fin
	pushad
	call fin_intr_pic1
    in al, 0x60
    cmp al, 0x15
    je Teclado.imprimirY
	;jmp 0x70:0
    ;.fin: 
	popad
	;popfd
	iret
;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
sys66:	;ecx numero de la interrupcion
	call fin_intr_pic1
	push ecx
	mov dword[contador], 0			;reseteo timer
	call game_move_current_zombi
	mov word [selector], 0x70
	jmp 0x70:0
	pop ecx
	popad
	;popfd
	;mov eax, 0x42	;Esto es del ejercicio de Interrupciones
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
        
        
