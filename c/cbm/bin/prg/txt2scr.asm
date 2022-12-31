            *= $0400

; Copy text pointed to 
; by .A,.X to screen
; until '\0' is encountered
; or the end of the screen is reached
txt2scr
            sta $c1         ; set up source pointer
            stx $c2
            jsr setptrs     ; set up pointers to screen/color RAM
                            ; screen RAM at ($fc, $fd)
                            ; color RAM at ($fe, $ff)
                            ; end of screen at ($57, $58)

            clv             ; clear NL mode
            ldx #$00        ; column
            ldy #$00
l1
            lda ($c1),y     ; pointer to text
            beq done

            cmp #$0d        ; new line
            bne l7

            lda #$7f        ; NL mode
            adc #$01        ; set .V
            bne l6
l7
            bvs l2          ; NL mode

            jsr p2sc        ; PETSCII to screen code
            sta ($fc),y

            lda $286        ; current color
            sta ($fe),y
l6            
            inc $c1         ; increment text ptr
            bne l2
            inc $c2
l2
            inc $fc         ; increment screen ptr
            bne l3
            inc $fd
l3
            inc $fe         ; increment color ptr
            bne l4
            inc $ff
l4
            lda $fc         ; check done
            cmp $57
            bne l5
            lda $fd
            cmp $58
            beq done
l5
            inx
            cpx #$16
            bne l1

            ldx #$00        ; reset column counter
            clv             ; clear NL mode
            beq l1
done
            rts

; Set up pointers to top line of 
; screen and color memory
; in ($fc, $fd) and ($fe, $ff)
; end of screen pointers
; stored in ($57, $58
setptrs
            lda #$00        ; always on a page boundary
            sta $fc
            lda $288        ; screen RAM page
            sta $fd

            lda $9002       ; determine color map location
            and #$80
            bne st1
            lda #$94
            sta $ff
            jmp st2
    st1                 
            lda #$96
            sta $ff
    st2
            lda #$00
            sta $fe

            clc             ; end of screen pointers in $57, $58
            lda $fc
            adc #$fa
            sta $57
            lda $fd
            adc #$01
            sta $58
            rts

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

    dd2     and #$5f        ; 96 <= .A <= 127, strip bits 5 and 7
            bne ddend

    dd3     ora #$40        ; 128 <= .A <= 159, set bit 6
            bne ddend

    dd4     eor #$c0        ; 160 <= .A <= 191, flip bits 6 and 7
            bne ddend

    dd1     and #$3f        ; 32 <= .A  <= 95, strip bits 6 and 7
            bpl ddend

    ddrev   eor #$80        ; flip bit 7

    ddend
            rts
