; first x64 program
;
bits 64

extern MessageBoxA
extern ExitProcess

SECTION .data
title 	db 'The 64-bit world of Windows & assembler...', 0
message	db 'Hello World!', 0

SECTION .text
global main
main:
	sub rsp, 28h 		; shadow space, aligns stack
						; 4 params to MessageBox @8-bytes
						; + 8-byte return value
						; = 40d (28h).
						
	xor r9d, r9d		; uType = MB_OK
	mov r8, title		; LPCSTR lpCaption
	mov rdx, message	; LPCSTR lpText
	xor rcx, rcx		; hWnd = HWND_DESKTOP
	call MessageBoxA
	mov ecx, eax		; uExitCode = MessageBox(...)
	call ExitProcess
	
	ret
