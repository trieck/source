
TITLE test
.386
.MODEL flat, stdcall
.STACK 4096
ExitProcess PROTO, dwExitCode:DWORD

.code
main PROC

	INVOKE ExitProcess, 0
main ENDP
END main

