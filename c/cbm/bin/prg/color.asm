;
; TEST2.ASM
;
; Test C64 Program
;
;
; initialization routine
;
.init   lda #a          ; background and border, light red
        sta d020
        sta d021
        lda #2          ; text color, dark red
        sta 0286
        lda #93         ; clear screen
        jsr chrout
        lda #e          ; switch to lowercase
        jsr chrout      
        rts
            
            
