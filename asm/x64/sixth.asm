; sixth x64 program
;
.const

MSGBOXPARAMS STRUCT
	cbSize		dd 0	; +4 cbSize				
	hwndOwner	dq 0	; +12 hwndOwner
	hInstance	dq 0	; +20 hInstance
	lpszText	dq 0	; +28 lpszText
	lpszCaption	dq 0	; +36 lpszCaption
	dwStyle		dd 0	; +40 dwStyle				
	lpszIcon	dq 0	; +48 lpszIcon
				dq 0	; +56 dwContextHelpId
				dq 0	; +64 lpfnMsgBoxCallback
				dd 0	; +68 dwLanguageId
ENDS

.data
	title 	db 'The 64-bit world of Windows & assembler...', 0
	message	db 'Hello World!', 0

ALIGN 8	; ensure all the following data elements are 8-byte aligned
	params MSGBOXPARAMS

.code
_MAIN__:
	invoke GetModuleHandleA, 0
	
	mov D[params.cbSize], 68d
	mov [params.hInstance], rax
	
	mov rax, ADDR message
	mov [params.lpszText], rax
	
	mov rax, ADDR title
	mov [params.lpszCaption], rax
	
	invoke MessageBoxIndirectA, ADDR params
	
	invoke ExitProcess, eax	; exit process
	    
	ret
