; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start
extern IDT_DESC
extern GDT_DESC
extern idt_inicializar
extern mmu_inicializar_dir_kernel
extern page_directory
		
;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

grupo_msg db     'Aires Criollos - Parrillada completa'
grupo_len equ    $ - grupo_msg

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
    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0

    ; Inicializar pantalla. 

    	mov esi, 0xB8000		        ; lugar donde empieza la pantalla
	
	; pinto todo de verde 
   	xor ebx, ebx				

    .ciclo:
	mov dword [esi+ebx], 0x20202020
	add ebx, 4
	
	cmp ebx, 8000
	jl .ciclo

	
	;pinto bordes	
	mov word [esi], 0x4020	;rojo, espacio
	mov eax, 158

    .col_bordes:
	mov dword [eax + esi], 0x40201020	;rojo, espacio, azul, espacio

	add eax, 160
	cmp eax, 7840	; 49*160
	jl .col_bordes
	mov word [esi+eax], 0x1020	;azul, espacio
	
	pop ebp

	imprimir_texto_mp grupo_msg, grupo_len, 0x07, 0, 80-grupo_len
	
	
	; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas
       	     xchg bx, bx
		call mmu_inicializar_dir_kernel
		
    ; Cargar directorio de paginas

	 mov eax, page_directory
	 mov cr3, eax
		
    ; Habilitar paginacion

	 mov eax, cr0
	 or eax, 0x80000000 ;habilitamos paginacion
	 mov cr0, eax

    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT

	call idt_inicializar
	
    ; Cargar IDT
    lidt [IDT_DESC]
   	int 0x06
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
