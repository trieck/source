            *= $0400
            
            jmp cpyscr      ; @ $0400 copy screen data to screen
            jmp getkey      ; @ $0403 blink cursor and get key
            jmp p2sc        ; @ $0406 PETSCII to screen code
            jmp advcrsr     ; @ $0409 advance cursor

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
; stored in ($57, $58)
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

getkey      
            lda #$0
            sta $cc         ; turn on cursor
            lda $c6         ; number of characters in the keyboard buffer
            beq getkey      ; no keys

            lda #$1         ; turn off the cursor
            sta $cc

            lda $cf         ; check blink status
            beq getchar     ; get if non-reversed

            lda #$0         ; set blink status to non-reversed
            sta $cf

            ldy $d3         ; cursor position within logical line
            lda $ce         ; character under cursor
            sta ($d1), y    ; store .A to current screen line

            lda $287        ; color of character under cursor
            sta ($f3), y    ; store .A to current physical line color map

getchar
            jsr getin        ; get character

            ldx #$ff         ; reset stop key
            stx $91

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

; Advance the cursor
; .C is set if cannot advance cursor
advcrsr
            lda #$15        ; last column
            cmp $d3         ; compare with cursor column
            beq nextln

            clc
            inc $d3         ; increment cursor column
            bne acdone

nextln
            lda #$00        ; column 0
            sta $d3

            lda #$16        ; last row, cannot advance cursor
            cmp $d6         ; without scrolling in contents
            bne acgood

            sec
            beq acdone
acgood
            inc $d6         ; next row
            jsr $e587       ; set screen pointers
            clc             ; all good
acdone
            rts
