;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;	ARGS.ASM
;	
;	count and display arguments on command line
;
;	Copyright(c) 2001, Thomas A. Rieck
;

SECTION .data
	argcountmsg db 'The number of args is [%d]!', 10, 13, 0
	argmsg db 'Argument #%d is [%s]!', 10, 13, 0
	
SECTION .text

extern _printf 
global _main

_main: 
	push ebp						; standard prolog
	mov	ebp, esp		
	
	push dword [ebp + 8]			; echo the argument count
	push dword argcountmsg
	call _printf
	add esp, byte 8         		; cleanup args
	
	mov ecx, dword [ebp + 8]		; loop counter

;
; argument loop
;

.loop:
	
	push dword ecx					; remember the counter
	
	mov eax, [ebp + 8]				; which argument are we at ?	
	sub eax, ecx
	
	mov ebx, [ebp + 12]				; string to display
	push dword [ebx + eax * 4] 
	
	push dword eax					; the argument number
	
	push dword argmsg				; message to display
	
	call _printf					
	add esp, byte 12         		; cleanup args
	
	pop ecx							; restore counter
			
	dec ecx							; decrement it 
	jnz .loop						; are we done ?

; exit routine

	xor eax, eax					; zero out eax
	
	mov	esp, ebp					; standard epilog
	pop	ebp

	ret	0

