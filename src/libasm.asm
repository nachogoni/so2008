
GLOBAL  read_msw,_lidt
GLOBAL  int_08_hand, int_09_hand, int_0c_hand
GLOBAL  int_80_hand, write, read, fork
GLOBAL  set_cursor_pos, init_cereal
GLOBAL  mascaraPIC1,mascaraPIC2,_Cli,_Sti
GLOBAL  debug
GLOBAL	beep
GLOBAL _invop_hand, _ssf_hand , _snp_hand , _div0_hand , _gpf_hand, _bounds_hand

GLOBAL  createStackFrame

EXTERN  int_08
EXTERN  int_09
EXTERN  int_0c
EXTERN  __write, __read, __fork

EXTERN _invop
EXTERN _div0
EXTERN _gpf
EXTERN _ssf
EXTERN _snp
EXTERN _bounds

EXTERN scheduler

SECTION .text

createStackFrame:
	push ebp
	; Backup de los flags
	pushf
	; Backup del stack propio
	mov ebp, esp
	; Stack pointer que viene por parametros
	mov eax, [ebp+16]
	; Cambia de stack por el que viene como parametro
	mov esp, eax
	; Puntero a la funcion que va a guardar en ip para ejecutar
	mov eax, [ebp+12]
	; Habilita las interrupciones, pushea los flags y las deshabilita
	;sti
	;pushf
	;cli
	mov ecx, 512
	push ecx
	; Push de CS y ESP (lo usa iret en el multitask)
	push cs
	push eax
	; Push de los demas registros del procesador
	pusha
	; Return de la nueva posicion del stack pointer -> 
	;  para guardarlo en la estructura de los procesos
	mov eax, esp
	; Restaura el stack pointer original
	mov esp, ebp
	; Restaura los flags y EBP
	popf
	pop ebp
	retn

_Cli:
	cli			; limpia flag de interrupciones
	ret

_Sti:
	sti			; habilita interrupciones por flag
	ret

mascaraPIC1:			; Escribe mascara del PIC 1
	push    ebp
	mov     ebp, esp
	mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
	out     21h,al
	pop     ebp
	retn

mascaraPIC2:			; Escribe mascara del PIC 2
	push    ebp
	mov     ebp, esp
	mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
	out	   0A1h,al
	pop     ebp
	retn

read_msw:
	smsw    ax		; Obtiene la Machine Status Word
	retn


_lidt:							; Carga el IDTR
	push    ebp
	mov     ebp, esp
	push    ebx
	mov     ebx, [ss: ebp + 6] 	; ds:bx = puntero a IDTR 
	rol	 ebx,16
	lidt    [ds: ebx]        	     ; carga IDTR
	pop     ebx
	pop     ebp
	retn

int_08_hand_back:						; Handler de INT 8 ( Timer tick)
	push    ds
	push    es                      ; Se salvan los registros
	pusha                           ; Carga de DS y ES con el valor del selector
	mov     ax, 10h				; a utilizar.
	mov     ds, ax
	mov     es, ax
	call    int_08
	mov	 al,20h				; Envio de EOI generico al PIC
	out	 20h,al
	popa
	pop     es
	pop     ds
	iret

; Handler de INT 8 (Timer tick) -> Multitasker
int_08_hand:
	; Guardo los registros del proceso actual en su stack
	pusha
	; Cargo el parametro para la funcion que guarda el stack pointer
	push	esp
	; Llamo al scheduler pasandole el stack pointer actual para recibir el nuevo stack
	call	scheduler
	pop	esp
	; Setea el stack pointer del nuevo proceso
	mov	esp, eax
	; Envio de EOI generico al PIC
	mov	 al, 20h
	out	 20h, al
	; Restauro los registros del nuevo proceso
	popa

	iret

int_09_hand:				; Handler de INT 8 ( Timer tick)
        push    ds
        push    es                      ; Se salvan los registros
        pusha                           ; Guardo a
;	mov	eax, 0
;	in	al, 60h			; Obtengo el scancode y lo paso como parametro
;	push	eax
;        mov     ax, 10h
;        mov     ds, ax
;        mov     es, ax
        call    int_09
;	pop	eax
        mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al
	popa
        pop     es
        pop     ds
        iret

int_0c_hand:					; Handler de INT 0c ( Serial Port )

        push    ds
        push    es              ; Se salvan los registros
        pusha                   ; Carga de DS y ES con el valor del selector
	push 	dx

        push	eax
        mov     ax, 10h			; a utilizar
        mov     ds, ax
        mov     es, ax
        call    int_0c
	pop	eax

	mov		al,20h			; Envio de EOI generico al PIC
	out		20h,al

	pop		dx
	popa
        pop     es
        pop     ds
        iret

; recibe parametros a traves de los registros
; eax   =   tipo
int_80_hand:
	   push    ds
	   push    es
	   cmp eax, 0             ; WRITE = 0
	   jz _pwrite
	   cmp eax, 1             ; READ = 1
	   jz _pread
	   cmp eax, 4             ; FORK = 4
	   jz _pfork

	   ;si no hay instruccion salgo
	   jmp _pend

; parametros para write
; ebx   =   file descriptor
; ecx   =   buffer a escribir
; edx   =   size a escribir
_pwrite:
	   push    edx             ; size
	   push    ecx             ; buffer
	   push    ebx             ; file descriptor

	   call    __write

	   pop     edx             ; quito los parametros de la pila
	   pop     edx
	   pop     edx
	   jmp	 _pend	       ; salgo

; parametros para read
; ebx   =   file descriptor
; ecx   =   buffer donde escribir
; edx   =   size total
_pread:
	   push    edx             ; size
	   push    ecx             ; buffer
	   push    ebx             ; file descriptor

	   call    __read

	   pop     edx             ; quito los parametros de la pila
	   pop     edx
	   pop     edx
	   jmp	 _pend	       	  ; salgo

; el fork no lleva parametros
_pfork:

		call __fork
		jmp	 _pend	       	  ; salgo

_pend:
	   pop     es			  ;salgo
	   pop     ds
	   iret


fork:
	push    ebp             ; arma stack frame
	mov     ebp, esp

	mov     eax, 4 		    ; pongo el selector en fork
	int     080h		    ; llamo a int 80

	mov     esp, ebp        ; destruye stack frame
	pop     ebp
	ret


; write coloca en 
; - ebx el file descriptor
; - ecx la direccion del buffer a escribir 
; - edx la cantidad de caracteres que contiene el buffer.
write:
	push    ebp             ; arma stack frame
	mov     ebp, esp

	push    ebx
	push    ecx
	push    edx

	mov     eax, 0 	    ; pongo el selector en write
	mov     ebx, [ebp+8]    ; file descriptor
	mov     ecx, [ebp+12]   ; buffer a escribir
	mov     edx, [ebp+16]   ; size

	int     080h		    ; llamo a int 80

	pop	   edx		    ; restauro
	pop	   ecx
	pop	   ebx

	mov     esp, ebp        ; destruye stack frame
	pop     ebp
	ret


; read coloca en 
; - ebx el file descriptor
; - ecx la direccion del buffer a escribir 
; - edx la cantidad de caracteres que contiene el buffer.
read:
	push    ebp             ; arma stack frame
	mov     ebp, esp

	push    ebx
	push    ecx
	push    edx

	mov     eax, 1 	    ; pongo el selector en read
	mov     ebx, [ebp+8]    ; file descriptor
	mov     ecx, [ebp+12]   ; buffer a escribir
	mov     edx, [ebp+16]   ; size

	int     080h		    ; llamo a int 80

	pop	   edx		    ; restauro
	pop	   ecx
	pop	   ebx

	mov     esp, ebp        ; destruye stack frame
	pop     ebp
	ret

;Es la funcion que mueve el cursor de pantalla
;Recibe por stack la posicion de pantalla a donde llevarlo
set_cursor_pos:
	push ebp
     mov     ebp, esp

	push eax
	push ecx
	push edx
	
	mov eax, [ss:ebp+8]

	mov edx, 0x3D4
	mov ecx, eax
	mov al, 0x0F
	out dx, al
	mov eax, ecx
	inc edx
	out dx, al
	mov al, 0x0E
	dec edx
	out dx, al
	mov eax, ecx
	mov al, ah
	inc edx
	out dx, al

	pop edx
	pop ecx
	pop eax
	pop ebp
	ret

beep:
	mov al, 182			; Prepare the speaker for the
	out 43h, al			; note.
	mov ax, 4560		; Frequency number (in decimal)
						;  for middle C.
	out 42h, al			; Output low byte.
	mov al, ah			; Output high byte.
	out 42h, al
	in al, 61h			; Turn on note (get value from
						; port 61h).
	or al, 00000011b	; Set bits 1 and 0.
	out 61h, al			; Send new value.
	mov bx, 25			; Pause for duration of note.
.pause1:
	mov cx, 65535
.pause2:
	dec cx
	jne .pause2
	dec bx
	jne .pause1
	in al, 61h			; Turn off note (get value from
						; port 61h).
	and al, 11111100b	; Reset bits 1 and 0.
	out 61h, al			; Send new value.
	retn


[global read_cr0]
read_cr0:
	mov eax, cr0
	retn

[global write_cr0]
write_cr0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0,  eax
	pop ebp
	retn

[global read_cr3]
read_cr3:
	mov eax, cr3
	retn

[global write_cr3]
write_cr3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	retn
	






;_div0_hand:				; Handler de excepxin "Divide by zero"
;	push ds
;	push es				; Se salvan los registros
;	pusha				; Carga de DS y ES con el valor del selector
;	pushf
;	mov ax, 10h			; a utilizar.
;	mov ds, ax
;	mov es, ax                  
;	call _div0                 
;	mov al,20h			; Envio de EOI generico al PIC
;	out 20h,al
;	popf
;	popa
;	pop es
;	pop ds
;	jmp $
;	iret
;
;_bounds_hand:			; Handler de excepcin "BOUND range exceeded"
;	push ds
;	push es				; Se salvan los registros
;	pusha				; Carga de DS y ES con el valor del selector
;	pushf
;	mov ax, 10h			; a utilizar.
;	mov ds, ax
;	mov es, ax
;	call _bounds
;	mov	al,20h			; Envio de EOI generico al PIC
;	out	20h,al
;	popf
;	popa
;	pop es
;	pop ds
;	jmp $
;	iret
;
;_gpf_hand:				; Handler de excepcin "General protection exception"
;	push ds
;	push es				; Se salvan los registros
;	pusha				; Carga de DS y ES con el valor del selector
;	pushf
;	mov eax, 666666h
;	mov ax, 10h			; a utilizar.
;	mov ds, ax
;	mov es, ax
;	call _gpf
;	mov	al,20h			; Envio de EOI generico al PIC
;	out	20h,al
;	popf
;	popa
;	pop ax
;	pop ax
;	jmp $
;	iret
;
;_ssf_hand:				; Handler de excepcin "Stack exception"
;	push ds
;	push es				; Se salvan los registros
;	pusha				; Carga de DS y ES con el valor del selector
;	pushf
;	mov ax, 10h			; a utilizar.
;	mov ds, ax
;	mov es, ax                  
;	call _ssf
;	mov	al,20h			; Envio de EOI generico al PIC
;	out	20h,al
;	popf
;	popa
;	pop ax
;	pop ax
;	jmp $
;	iret
;
;_snp_hand:				; Handler de excepcin "Segment not present"
;	push ds
;	push es				; Se salvan los registros
;	pusha				; Carga de DS y ES con el valor del selector
;	pushf
;	mov ax, 10h			; a utilizar.
;	mov ds, ax
;	mov es, ax
;	call _snp
;	mov	al,20h			; Envio de EOI generico al PIC
;	out	20h,al
;	popf
;	popa
;	pop ax
;	pop ax
;	jmp $
;	iret
;
;_invop_hand:				; Handler de excepcin "Invalid opcode"
;	push ds
;	push es				; Se salvan los registros
;	pusha				; Carga de DS y ES con el valor del selector
;	pushf
;	mov ax, 10h			; a utilizar.
;	mov ds, ax
;	mov es, ax
;	call _invop
;	mov	al,20h			; Envio de EOI generico al PIC
;	out	20h,al
;	pop ax
;	popa
;	pop ax
;	pop ax
;	jmp $
;	iret






; Debug para el BOCHS, detiene la ejecucin.
; Para continuar colocar en el BOCHSDBG: set $eax=0
;








debug:
        push    bp
        mov     bp, sp
        push	ax
vuelve:	mov     ax, 1
        cmp	ax, 0
	jne	vuelve
	pop	ax
	pop     bp
        retn




	
COM1 EQU 3f8h
