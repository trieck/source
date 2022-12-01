;
; alpha.asm
;
; 6502 assembly program to print the alphabet
;
    *= $033c

.begin  lda #$41     ; load 'A' in accumulator
        sta $fb      ; store accumulator at .data
.loop   lda $fb      ; load accumulator from .data
        cmp #$5b     ; is it 'Z'
        beq end      ; if so goto the end
        jsr chrout   ; print it
        inc $fb      ; increment value in .data
        jmp loop     ; keep looping...
.end    rts          ; return
