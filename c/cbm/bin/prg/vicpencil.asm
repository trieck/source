;
; vicpencil.asm
;
; The "VIC Pencil" for the expanded VIC-20
;
        *= $1200

rvs     = $c7
status  = $90

prtstr  = $cb1e
prtfix  = $ddcd
warmbas = $e467
cclrch  = $ffcc

;---------------------------------------
; basic program declaration
;---------------------------------------
        .byte $00       ; begin basic prg
        .byte <nextl    ; next link
        .byte >nextl
        .byte $00       ; line #
        .byte $00
        .byte $9e       ; sys token
        .text '4621'    ; $120d
        .byte $00       ; end of line

nextl  
        .byte $00       ; end of program
        .byte $00 

        jmp start       ; must be @ $120d

;---------------------------------------
; data declarations
;---------------------------------------
title
        .text 'vic pencil'
        .byte $0d
        .byte $0d
        .byte $0
menu   
        .text 'a - assembler'
        .byte $0d
        .text 'd - disassemble mem'
        .byte $0d
        .text 'f - disassemble file'
        .byte $0d
        .text 'i - initialize drive'
        .byte $0d
        .text 'l - list program'
        .byte $0d
        .text 'm - view/edit memory'
        .byte $0d
        .text 'r - read disk block'
        .byte $0d
        .text 'v - validate disk'
        .byte $0d
        .text '* - directory'
        .byte $0d
        .ztext 'x - exit'

dprmpt  .ztext 'drive:'
prspc   .ztext 'press space'

dirname  .text '$0'
dirlen   = *-dirname

drive   .byte $08       ; current drive#
cols    .byte $0        ; number of columns
rows    .byte $0        ; number of rows
filenum .byte $01       ; open file number

;---------------------------------------
; code
;---------------------------------------
start
        lda #$02        ; red character
        sta $0286
        lda #$19        ; white border, rvs, white background
        sta $900f
        lda #$e
        jsr $e742       ; lowercase
        lda #$8
        jsr $e742       ; dis. shft/cmdr

        jsr $e505       ; # of rows/cols
        stx cols
        sty rows

prmenu                  ; print the menu
        lda #$93        ; clear screen
        jsr chrout
        lda #<title
        ldy #>title
        jsr prtstr      ; output title

        jsr loline      ; lower line sep.

        lda #<menu
        ldy #>menu
        jsr prtstr      ; print menu

        jsr upline      ; upper line sep.

me1
        jsr getchar     ; get character
        cmp #$2a        ; is it "*"?
        beq me2         ; directory
        cmp #$58        ; is it "x"?
        beq end
        jmp me1
me2     jmp dir         ; directory
        jmp prmenu      ; menu
end
        jmp warmbas     ; basic warm start

;---------------------------------------
; lower line separator
;---------------------------------------
loline
         jsr prnret     ; print return

         lda #$b9       ; lower line sep.
         ldx cols       ; # of cols.

ll1
         jsr chrout     ; print sep.
         dex
         bne ll1

         rts

;---------------------------------------
; upper line separator
;---------------------------------------
upline
         jsr prnret     ; print return

         lda #$b8       ; upper line sep.
         ldx cols       ; # of cols.
ul1
         jsr chrout     ; print sep.
         dex
         bne ul1
         rts

;---------------------------------------
; print return conditionally
;---------------------------------------
prnret
         lda $d7        ; last character printed

         cmp #$0d       ; is it return?
         beq pr1

         lda #$0d       ; print return
         jsr chrout
pr1
         rts

;---------------------------------------
; get character from keyboard
; and blink the cursor
;---------------------------------------
getchar
        lda #$0
        sta $cc         ; turn on cursor
        lda $c6         ; number of characters in the keyboard buffer
        beq getchar

        lda #$1         ; turn off the cursor
        sta $cc

        lda $cf         ; check blink status
        beq gc1         ; get if non-reversed

        lda #$0         ; set blink status to non-reversed
        sta $cf

        ldy $d3         ; cursor position within logical line
        lda $ce         ; character under cursor
        sta ($d1), y    ; store .A to current screen line

        lda $287        ; color of character under cursor
        sta ($f3), y    ; store .A to current physical line color map

gc1
        jsr getin       ; get character
        rts

;---------------------------------------
; directory
;---------------------------------------
dir                     ; directory
        jsr getdrive    ; get drive
        lda #$93        ; clear screen
        jsr chrout
        jsr loline      ; lower line sep.

        jsr cmdopen     ; open cmd. ch.
        bcc dir2
dir3
        jmp dirio       ; i/o error
dir2
        lda #<dirlen    ; len. of file
        ldx #<dirname   ; filename
        ldy #>dirname
        jsr fopen
        bcc dir4
dir5
        jmp dirio       ; i/o error
dir4
        ldx filenum     ; file number
        jsr chkin       ; open channel

        jsr chrin       ; discard load
        jsr chrin       ; address
        lda status      ; check status
        bne direrr

dir6    
        jsr chrin       ; discard line
        jsr chrin       ; link
        jsr chrin       ; retrieve number
                        ; of blocks used
        sta $fc         ; store to zero
        jsr chrin       ; page in low,
                        ; high format
        sta $fb        
        lda status      ; read i/o status
        bne dirclean    ; eof
        lda $fb         ; retrieve number
        ldx $fc         ; of blocks
        jsr prtfix      ; output int in
                        ; .a, .x
        lda #$20        ; print space
        jsr chrout      ; after blocks
        jsr chrin
dir7
        jsr chrout

dir8    ldx $028d       ; check for shift
        bne dir8
        ldx $91         ; check for stop
        cpx #$7f
        beq dirclean
        jsr chrin
        bne dir7
        lda #$0d
        jsr chrout     ; print return
        jmp dir6
direrr
        jsr diskerr    ; print disk error
        jmp dirclean

dirio
        jsr ioerr     ; drive i/o error
dirclean
        jsr fclose    ; close file
        jsr cmdclose  ; close cmd. ch.

        jsr upline    ; upper line sep.

        jsr waitsp    ; wait for space
        jmp prmenu    ; menu

;---------------------------------------
; get drive
;---------------------------------------
getdrive                ; get drive
        lda #$0d
        jsr chrout      ; print return

        lda #<dprmpt    ; drive prompt
        ldy #>dprmpt
        jsr prtstr
gd1
        lda drive
        cmp #$0a
        bcs gd2         ; drive >= 10
        lda #$00
        ldx #$00
        jsr prtfix      ; output lead 0

gd2
        lda #$00        ; high byte
        ldx drive       ; lo byte
        jsr prtfix      ; output integer
        lda #$9d
        jsr chrout      ; backup twice
        jsr chrout
gd3
        jsr getchar     ; get char
        cmp #$11        ; is it cr. down?
        beq gd4
        cmp #$0d        ; is it return?
        beq gd5
        jmp gd3
gd4
        inc drive       ; next drive
        lda drive
        cmp #$0c
        bcc gd1         ; drive < 12
        lda #$08
        sta drive       ; reset drive #
        jmp gd1
gd5
        rts

;---------------------------------------
; wait for space
;---------------------------------------
waitsp                ; wait for space
         lda #$01
         sta $c7      ; enable rev.
         lda #<prspc
         ldy #>prspc
         jsr prtstr
         lda #$00
         sta $c7      ; disable rev.

wsp1     jsr getin
         cmp #$20     ; space
         bne wsp1
         rts

;---------------------------------------
; disk error
;---------------------------------------
diskerr
         ldx #$0f     ; open channel
         jsr chkin    ; for input
de1
         jsr chrin
         ldx status
         bne de2
         jsr chrout
         jmp de1
de2
         rts

;---------------------------------------
; i/o error
;---------------------------------------
ioerr
         ldy #$01     ; move past cr.
         pha
         jsr $f12f    ; print i/o err.#
         pla
         ora #$30     ; make err. ascii
         jsr chrout   ; print it
         rts

;---------------------------------------
; open command channel
;---------------------------------------
cmdopen
         lda #$00     ; len. of file
         jsr setnam   ; set filename
         lda #$0f     ; command channel
         ldx drive    ; device number
         tay          ; secondary addr.
         jsr setlfs   ; set file params
         jsr open     ; open
         rts

;---------------------------------------
; open file
; length of filename in .a
; lsb of filename in .x
; msb of filename in .y
;---------------------------------------
fopen
         jsr setnam   ; set filename
         lda filenum  ; file number
         ldx drive    ; device number
         ldy #$00     ; secondary addr.
         jsr setlfs   ; set file params
         jsr open     ; open file
         rts

;---------------------------------------
; close file
;---------------------------------------
fclose
         lda filenum
         jsr close    ; close file
         rts

;---------------------------------------
; close command channel
;---------------------------------------
cmdclose
         lda #$0f     ; close command
         jsr close    ; channel
         jsr cclrch   ; close channels
         rts
