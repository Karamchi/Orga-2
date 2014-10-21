; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start
extern GDT_DESC
		
;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0
    ; Habilitar A20
	call habilitar_A20    

    ; Cargar la GDT
	lgdt [GDT_DESC]

    ; Setear el bit PE del registro CR0
	mov eax, cr0
	or eax, 1
	mov cr0, eax
    
    ; Saltar a modo protegido
	jmp 0x40:mp

    ; Establecer selectores de segmentos
BITS 32	
	mp:
	xor eax, eax
	mov ax, 1001000b
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov gs, ax
	mov ax, 1100000b
	mov fs, ax

    ; Establecer la base de la pila
	mov ebp, 0x27000
	mov esp, ebp

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0

    ; Inicializar pantalla. NO HAY LOS REGISTROS R!

	push ebp
	mov ebp, 0x160
	xor ecx, ecx				; columna
	inc ecx
    	mov esi, 0xB8000		        ; lugar donde empieza la pantalla

    .col_roja:
	mov eax, 0
	mul ebp
	add eax, esi
	lea edi, [eax+ecx*2]

	mov word [edi], 0x4

	inc ebx
	cmp ebx, 49
	jne .col_roja

    .cicloi:
   	xor ebx, ebx				; fila

    .cicloj:
	mov eax, ebx
	mul ebp
	add eax, esi
	lea edi, [eax+ecx*2]

	mov dword [edi], 0x2

	inc ebx

	cmp ebx, 49
	jne .cicloj

	inc ecx
	cmp ecx, 79
	jne .cicloi

    .col_azul:
	mov eax, ebx
	mul ebp
	add eax, esi
	lea edi, [eax+ecx*2]

	mov dword [edi], 0x1

	inc ebx
	cmp ebx, 49
	jne .col_azul
	
	pop ebp
   
	; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas

    ; Cargar directorio de paginas

    ; Habilitar paginacion
    
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    
    ; Cargar IDT
 
    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
