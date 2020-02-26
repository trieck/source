; VGA COM program
;

and_or_reg equ 3ceh
plane_reg equ 3c4h

bits 16
org 100h

start:
    mov ax, 0a000h  ; set ES to EGA video segment
    mov es, ax

    mov ax, 0010h   ; set video mode 10
    int 10h

    mov ax, 200
    mov bx, 4       ; color value red
    xor dx, dx      ; row
    xor cx, cx      ; column

r_loop:
    call ega_pixel
    inc cx
    inc dx
    dec ax
    jnz r_loop

    mov ah, 7       ; wait for a key
    int 21h

    mov ax, 100
    mov bx, 1       ; colr value (blue)
    xor dx, dx      ; row
    xor cx, cx      ; column

b_loop:
    call ega_pixel
    inc cx
    inc dx
    dec ax
    jnz b_loop

    int 20h         ; end


; supply bx = color value, dx = row, cx = column
; assumes es = a0000h

ega_pixel:
    retn