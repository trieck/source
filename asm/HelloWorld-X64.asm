extrn MessageBoxA : proc
extrn ExitProcess : proc

.data
body db 'Hello World!', 0
capt db 'My First x64 Application', 0

.code
Main proc
sub rsp, 28h
xor r9d, r9d        ; uType = 0
lea r8, capt        ; lpCaption
lea rdx, body       ; lpText
xor rcx, rcx        ; hWnd = NULL
call MessageBoxA
xor ecx, ecx        ; exit code = 0
call ExitProcess
Main endp

end