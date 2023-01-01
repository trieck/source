        *= $033c

; PETSCII to screen code
; PETSCII code in .A
; result in .A
p2sc
        cmp #$20        ; < 32
        bcc ddrev

        cmp #$60        ; < 96
        bcc dd1

        cmp #$80        ; < 128
        bcc dd2

        cmp #$a0        ; < 160
        bcc dd3

        cmp #$c0        ; < 192
        bcc dd4

        cmp #$ff        ; < 255
        bcc ddrev

        lda #$5e        ; .A=255 -> .A=96
        bne ddend

dd2     
        and #$5f        ; 96 <= .A <= 127, strip bits 5 and 7
        bne ddend

dd3     
        ora #$40        ; 128 <= .A <= 159, set bit 6
        bne ddend

dd4     
        eor #$c0        ; 160 <= .A <= 191, flip bits 6 and 7
        bne ddend

dd1     
        and #$3f        ; 32 <= .A  <= 95, strip bits 6 and 7
        bpl ddend

ddrev   
        eor #$80        ; flip bit 7

ddend
        rts

