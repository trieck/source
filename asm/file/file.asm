;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;	FILE.ASM
;	
;	file utility
;
;	Copyright(c) 2001, Thomas A. Rieck
;

SECTION .data
	usage db 'usage: file filename', 10, 13, 0
	openerr	db 'unable to open file [%s].', 10, 13, 0
	readerr db 'error while reading file.', 10, 13, 0
	outputf db '0x%.2x', 0
SECTION .text

extern _printf
extern _putchar
extern _CreateFileA@28
extern _ReadFile@20
extern _CloseHandle@4

global _main

;
; main entry point
;
_main: 
	push ebp						; standard prolog
	mov	ebp, esp		
	
	mov eax, [ebp + 8]				; check argument count
	cmp eax, 2
	jl .usage
	
	mov ebx, [ebp + 12]				; filename
	push dword [ebx + 4] 
	call _read_file					; open the file
	add esp, byte 4					; cleanup argument stack
	
	xor eax, eax					; zero out eax

	jmp .teardown
	
;
; usage message
;
.usage
	push dword usage
	call _printf
	add esp, byte 4					; cleanup argument stack
	
.teardown

	mov	esp, ebp					; standard epilog
	pop	ebp

	ret

;
; read file routine
;
_read_file:
	push ebp						; standard prolog
	mov	ebp, esp		
	sub esp, byte 12				; space for local variables
	
	push dword 0					; handle to template file
	push dword 0x00000080			; file attributes, FILE_ATTRIBUTE_NORMAL
	push dword 3					; creation disposition, OPEN_EXISTING
	push dword 0					; security attributes
	push dword 1					; share mode, FILE_SHARE_READ
	push dword 0x80000000			; access mode, GENERIC_READ
	push dword [ebp + 8]			; file name
	
	call _CreateFileA@28			; open the file
									; no stack cleanup
									; this is __stdcall convention
									
	mov [ebp - 4], eax				; file handle
	cmp eax, 0xFFFFFFFF				; check for file open error
	jne .read
	
	push dword [ebp + 8]			
	push dword openerr
	call _printf
	add esp, byte 4
	jmp .teardown

.read
	xor ecx, ecx					; bytes written counter
	push ecx						; remember counter
.readloop
	push dword 0					; overlapped buffer
	lea eax, [ebp - 8]				; number of bytes read
	push eax						
	push dword 1					; number of bytes to read
	lea eax, [ebp - 12]				; data buffer
	push eax
	push dword [ebp - 4]			; file handle
	call _ReadFile@20				; read the file
									; no stack cleanup
									; this is __stdcall convention
	test eax, eax					; check for error return
	je .cleanup
	
	cmp dword [ebp - 8], 0			; check for zero bytes read
	je .cleanup
	
.output
	pop ecx							; restore counter
	inc ecx							; increment counter
	push ecx						; and store it again
	cmp dword ecx, 1				; first time there is no separator
	je .outbyte
	
	push dword ' '					; output separator character
	call _putchar
	add esp, byte 4

.outbyte
	push dword [ebp - 12]			; output byte read
	push dword outputf
	call _printf
	add esp, byte 8
	
	jmp .readloop
		
.cleanup
	push dword [ebp - 4]			; file handle 
	call _CloseHandle@4				; close the file handle
									; no stack cleanup
									; this is __stdcall convention
.teardown:	
									
	mov	esp, ebp					; standard epilog
	pop	ebp

	ret
