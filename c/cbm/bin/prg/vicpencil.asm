;
; vicpencil.asm
;
; The "VIC Pencil" for the expanded VIC-20
;
        *= $1200

;---------------------------------------
; basic program declaration
;---------------------------------------
        .byte $00       ; begin basic prg
        .byte <nextl    ; next link
        .byte >nextl
        .byte $00       ; line #
        .byte $00
        .byte $9e       ; sys token
        .byte '4621'    ; $120d
        .byte $00       ; end of line

.nextl  .byte $00       ; end of program
        .byte $00 

        jmp start       ; must be @ $120d

;---------------------------------------
; data declarations
;---------------------------------------
.title
        .byte 'vic pencil'
        .byte $0d
        .byte $0d
        .byte $0
.menu   
        .byte 'a - assembler'
        .byte $0d
        .byte 'd - disassemble mem'
        .byte $0d
        .byte 'f - disassemble file'
        .byte $0d
        .byte 'i - initialize drive'
        .byte $0d
        .byte 'l - list program'
        .byte $0d
        .byte 'm - view/edit memory'
        .byte $0d
        .byte 'r - read disk block'
        .byte $0d
        .byte 'v - validate disk'
        .byte $0d
        .byte '* - directory'
        .byte $0d
        .byte 'x - exit'
        .byte $0

.cols   .byte $0        ; number of columns
.rows   .byte $0        ; number of rows

;---------------------------------------
; code
;---------------------------------------
.start
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

.prmenu                 ; print the menu
        lda #$93        ; clear screen
        jsr $ffd2
        lda #<title
        ldy #>title
        jsr $cb1e       ; output title

        jsr loline      ; lower line sep.

        lda #<menu
        ldy #>menu
        jsr $cb1e       ; print menu

        jsr upline      ; upper line sep.

.me1
        jsr getchar     ; get character
        cmp #$58        ; is it "x"?
        bne me1
.end
        jmp $e467       ; basic warm start

;---------------------------------------
; lower line separator
;---------------------------------------
.loline
         jsr prnret     ; print return

         lda #$b9       ; lower line sep.
         ldx cols       ; # of cols.

.ll1
         jsr chrout     ; print sep.
         dex
         bne ll1

         rts

;---------------------------------------
; upper line separator
;---------------------------------------
.upline
         jsr prnret     ; print return

         lda #$b8       ; upper line sep.
         ldx cols       ; # of cols.
.ul1
         jsr chrout     ; print sep.
         dex
         bne ul1
         rts

;---------------------------------------
; print return conditionally
;---------------------------------------
.prnret
         lda $d7        ; last character printed

         cmp #$0d       ; is it return?
         beq pr1

         lda #$0d       ; print return
         jsr chrout
.pr1
         rts

;---------------------------------------
; get character from keyboard
; and blink the cursor
;---------------------------------------
.getchar
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

.gc1
        jsr getin       ; get character
        rts