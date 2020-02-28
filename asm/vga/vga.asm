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
    push ax
    push bx
    push cx
    push dx
    xor di, di
    mov ax, dx      ; get 80 * dx
    shl dx, 1
    shl dx, 1
    add dx, ax
    mov ax, cx
    mov cl, 4
    shl dx, cl      ; dx now multiplied by 80 (16*5)
    push dx         ; put into index
    pop di
    mov dx, ax      ; get column no.
    and dx, 7       ; find col. no mod 7
    mov cl, 3
    shr ax, cl      ; cx / 8
    add di, ax      ; di now holds byte addr in video buffer
    neg dl
    add dl, 7
    mov cl, dl      ; get bit to turn on
    mov al, 1
    shl al, cl
    mov cl, al      ; bit set in cl is bit to turn on (for ORing)
    mov ch, 0ffh
    sub ch, cl      ; ch has same bit turned off (for ANDing).

blue:

    retn