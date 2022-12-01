;
; vicpencil.asm
;
; The "VIC Pencil" for the expanded VIC-20
;
    *= $1200

;---------------------------------------
; BASIC PROGRAM DECLARATION
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

        jmp start	; must be @ $120d

.title
        .byte 'vic pencil'
        .byte $0

.start
        lda #$02
        sta $0286
        lda #$19
        sta $900f
        lda #$93
        jsr $ffd2
        lda #<title
        ldy #>title
        jsr $cb1e
        rts
    
