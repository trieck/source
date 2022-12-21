;---------------------------------------
; print basic variables and values
;---------------------------------------

;---------------------------------------
; definitions
;---------------------------------------

chrout   = $ffd2
strout   = $ab1e
givayf   = $b391
movfm    = $bba2
fout     = $bddd

; zero page locations
vartyp   = $07
vartab   = $2d
arytab   = $2f
fac1     = $61
ptr1     = $ac
ptr2     = $ae

;---------------------------------------
; code @ $033c : not to exceed $03fc
;---------------------------------------

         *= $033c

         lda vartab   ; set up pointer
         sta ptr1
         ldy vartab+1
         sty ptr1+1
l0
         lda ptr1
         ldy ptr1+1
         cpy arytab+1 ; compare
         bne l1
         cmp arytab
l1
         bcs l4
l2
         ldy #$00
         lda (ptr1),y ; first char
         tax
         jsr prvchar  ; print it
         txa
         and #$80
         sta vartyp
         iny
         lda (ptr1),y ; second char
         tax
         jsr prvchar  ; print it
         txa
         lsr a
         ora vartyp
         lsr a
         lsr a
         lsr a
         lsr a
         lsr a
         lsr a
         sta vartyp   ; store type

         tax
         lda vttab,x
         jsr chrout

         jsr varval
         lda #$0d
         jsr chrout

         clc
         lda ptr1
         adc #$07
         sta ptr1
         bcc l0
         inc ptr1+1
         bne l0
l4
         rts

;---------------------------------------
; print variable character
;---------------------------------------
prvchar
         and #$7f
         bpl prvf1

;---------------------------------------
; print variable value
;---------------------------------------
varval
         lda #"="
         jsr chrout

         lda vartyp   ; form index into
         asl a
         tax

         lda vftab+1,x
         pha
         lda vftab,x
         pha

         ldy #$02     ; offset to val
         lda (ptr1),y

         rts          ; call function

;---------------------------------------
; print float value
;---------------------------------------
prvflt
         ldy ptr1+1   ; high byte

         clc
         lda ptr1     ; low byte
         adc #$02     ; variable value
         bcc pvf1
         iny
pvf1
         jsr movfm    ; move float from
                      ; memory to fac#1
         jsr fout     ; convert fac#1
                      ; to string
         jmp strout   ; print it

;---------------------------------------
; print string value
;---------------------------------------
prvstr
         tax          ; length
         jsr prquot   ; print quote
         txa
         beq pvs2

         iny
         lda (ptr1),y ; pointer low
         sta ptr2
         iny
         lda (ptr1),y ; pointer high
         sta ptr2+1

         ldy #$00
pvs1
         lda (ptr2),y
         jsr chrout
         iny
         dex
         bne pvs1
pvs2
         jmp prquot   ; print quote

;---------------------------------------
; print function value
;---------------------------------------
prvfnc
         lda #"!"
prvf1    jmp chrout


;---------------------------------------
; print quote
;---------------------------------------
prquot
         lda #$22
         bne prvf1

;---------------------------------------
; print int value
;---------------------------------------
prvint
         tax          ; low byte
         iny
         lda (ptr1),y ; high byte
         tay
         txa
         jsr givayf   ; convert to float
         jsr fout     ; convert fac#1
                      ; to string
         jmp strout   ; print it

;---------------------------------------
; data declarations
;---------------------------------------
vttab    .byte $00    ; float
         .byte "$"    ; string
         .byte $00    ; function
         .byte "%"    ; int

vftab    .word prvflt-1
         .word prvstr-1
         .word prvfnc-1
         .word prvint-1

