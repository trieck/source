;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;   BOOTSECT.ASM
;
;   PixieOS bootstrap program
;   Copyright (c)2001 Thomas A. Rieck, All Rights Reserved
;

bits 16
org 0

jmp start           ; skip over data

bootdrv db 0
copymsg db '[PixieOS] Copyright (c)2001 Thomas A. Rieck', 13, 10, 0
checkmsg db 'Checking processor...', 13, 10, 0
chkmdmsg db 'Checking CPU mode...', 13, 10, 0
no386msg db 'Sorry, at least an 80386 processor is required.', 13, 10, 0
v86msg db 'System can not run in V86 mode.', 13, 10, 0
bootmsg db 'Booting System...', 13, 10, 0
rebootmsg db 'Press any key to reboot', 13, 10, 0
readmsg db 'Loading superblock image...', 13, 10, 0

; main entry point
;
start:

    mov ax, 0x7c0       ; bios puts us at 0:0x7c00h so set ds
    mov ds, ax          ; accordingly
	
    mov [bootdrv], dl   ; save drive we booted from

    cli                 ; clear interrupts while we setup stack
    mov ax, 0x9000      ; typical place for a stack; says who?
    mov ss, ax
    mov sp, 0xffff      ; use whole segment; good idea?
    sti                 ; set interrupts back on

    call clear_scn      ; clear the screen
	
    xor dx, dx          ; home the cursor
    call set_cursor
	
    mov si, copymsg     ; display copyright message
    call put_str

    mov si, checkmsg    ; display checking cpu message
    call put_str

    call check_cpu      ; check for 386

    mov si, chkmdmsg    ; display checking cpu mode message
    call put_str
											
    call check_mode     ; check cpu mode

    mov si, readmsg     ; read superblock
    call put_str
    call read

    jmp halt

; print zero terminated string on screen
;
put_str:
    lodsb               ; load byte at ds:si into al
    or al, al           ; set zero flag if al = 0
    jz putstrd          ; jump if zero flag is set
    mov ah, 0x0e        ; video function 0eh
    xor bh, bh          ; page number
    int 0x10            ; display character
    jmp put_str         ; keep looping
putstrd:
    retn

; check for 386+ processor
;
check_cpu:
    pushf               ; save flags
    xor ah, ah          ; clear high byte
    push ax             ; push ax onto the stack
    popf                ; pop this value into the flag register
    pushf               ; push flags onto the stack
    pop ax              ; and get flags into ax
    and ah, 0x0f0       ; try to set high nibble
    cmp ah, 0x0f0       ; the nibble is never 0f0h on an 80386
    je no386
    mov ah, 0x70        ; try to set NT and IOPL
    push ax             ; need to understand this better
    popf
    pushf
    pop ax
    and ah, 0x70        ; if they could not be modified, there is
    jz no386            ; no 80386 installed
    popf
    retn
no386:
    mov si, no386msg
    call put_str
    jmp halt
    
; checks whether we are running in real mode
;
check_mode:
    mov eax, cr0        ; get control register 0 in eax
    and al, 1           ; check if PM bit is set
    jnz not_real_mode
    retn
not_real_mode:
    mov si, v86msg
    call put_str
    jmp halt

read:
    xor ax, ax          ; reset disk controller
    int 0x13
    jc reboot           ; reboot on error

    mov ax, 0x09000     ; load superblock at 9000:0000 (above stack)
    mov es, ax          ; need to understand this better
    xor bx, bx

    mov ax,0x0201       ; load one sector
    mov cx, 0x0002      ; cylinder = 0, sector = 2
    xor dh, dh          ; head = 0; side one
    mov dl, [bootdrv]   ; drive we booted from
    jc read             ; this is sick, we should attempt three times
						; then fail; potential infinite loop
    retn
	
reboot:
    mov si, rebootmsg   ; state we are rebooting
    call put_str
    call get_key        ; and wait for a key
    db 0xea             ; machine code to jump to ffff:0000
    dw 0x0000
    dw 0xffff
    ; no ret required; we're rebooting

; get key from keyboard
;
get_key:
    xor ah, ah          ; wait for a key
    int 0x16
    retn

; clear the screen
;
clear_scn:
    xor al, al          ; clear display window
    xor cx, cx          ; upper left corner
    mov dx, 0x184f      ; lower right corner
    mov bh, 0x02        ; attribute; black bgnd, green fgnd
    mov ah, 0x07        ; scroll down
    int 0x10

; set cursor position in dx
;
set_cursor:
    mov ah, 0x02        ; set cursor position
    xor bh, bh          ; page number
    int 0x10
    retn

; hide the cursor
;
hide_cursor:
    mov ah, 0x02        ; move cursor off screen
    mov dh, 0x19        ; row 25
    mov dl, 0x50        ; column 80
    xor bh, bh          ; page number
    int 0x10
    retn

; halt the system
;
halt:
    jmp halt

times 510-($-$$) db 0
    dw 0xaa55