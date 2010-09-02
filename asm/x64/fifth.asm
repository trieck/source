; fifth x64 program
;


STD_OUTPUT equ 0xFFFFFFF5

.data
	msg 	db 'Hello x64 World!', 13, 10, 0
	msglen  dd 0
	written	dd 0
	
.code
_MAIN__:

	sub rsp, 40				; shadow space, aligns stack
	
	mov rcx, ADDR msg
	call lstrlen			; find length of message
    mov [msglen], eax		; store message length
    
    mov ecx, STD_OUTPUT		; get standard handle
	call GetStdHandle	
	
    mov rcx, rax			; console handle
	mov rdx, ADDR msg		; message
    mov r9, ADDR written	; number of bytes written
	mov r8, [msglen]		; length of message
	
	call WriteConsoleA		; print message

	mov ecx, eax        	; exit code
	call ExitProcess		; exit process
	    
	ret