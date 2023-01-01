            *= $0400

; Copy screen data pointed to 
; by .A,.X to screen
; until '\0' is encountered
; or the end of the screen is reached
cpyscr
            sta $c1         ; set up source pointer
            stx $c2
            jsr setptrs     ; set up pointers to screen/color RAM
                            ; screen RAM at ($fc, $fd)
                            ; color RAM at ($fe, $ff)
                            ; end of screen at ($57, $58)

                            ; Set up pointers to top line of 

            ldy #$00
l1
            lda ($c1),y     ; pointer to text
            bne l6

            lda #$20        ; fill rest of screen with spaces
            
l6
            sta ($fc),y     ; copy to screen

            lda $286        ; current color
            sta ($fe),y

            inc $c1         ; increment source ptr
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
            jmp l1

done
            rts

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