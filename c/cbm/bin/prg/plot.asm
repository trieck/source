        *= $033c

; plot character in .A to 
; to row in .X, column in .Y
; uses current foreground color
; in $286
cplot
        pha

        lda $d3         ; store current row, col
        sta $fb
        lda $d6
        sta $fb

        clc             ; set row, col
        jsr $fff0       ; call plot

        pla
        sta ($d1), y    ; .A @ row, col

        jsr $eab2       ; determine color map address
        lda $286        ; current foreground color
        sta ($f3), y

        ldx $fb         ; restore x,y
        ldy $fc
        clc             ; set row, col
        jsr $fff0       ; call plot

        rts