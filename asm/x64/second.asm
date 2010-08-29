; second x64 program
;
bits 64
default rel

extern GetStdHandle
extern WriteConsoleA
extern lstrlen
extern ExitProcess

STD_OUTPUT equ 0xFFFFFFF5

[SECTION .data]
    msglen  dw 0
    written	dw 0
    msg     db  'Hello x64 World!', 13, 10, 0

[SECTION .text]
global main
main:
	sub rsp, 40				; shadow space, aligns stack

	mov rcx, msg
	call lstrlen			; find length of message
    mov [msglen], eax		; store message length

	mov ecx, STD_OUTPUT		; get standard handle
	call GetStdHandle	
	
    mov rcx, rax			; console handle
	mov rdx, msg			; message
    mov r9, written			; number of bytes written
	mov r8, [msglen]		; length of message
	
	call WriteConsoleA		; print message

	mov ecx, eax        	; exit code
	call ExitProcess		; exit process
	
	ret
