;
; emulate a loop:
;
;   n = 10; 
;   while (n > 0) {
;       n = n - 1;
;   }
;

    *= 1000

.begin      lda #0a     ; load .A with 10
            sta 033c    ; store .A at 033c
.loop       lda 033c    ; load .A from 033c
            beq .end    ; branch if 0
            inc 033c    ; increment value in 033c
            jmp .loop   ; jump to beginning of loop
.end        rts         ; return
