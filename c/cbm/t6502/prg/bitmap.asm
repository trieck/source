;
;
; BITMAP.ASM
; C-64 Bitmap example program
;
; base = 2000h
;
		
;
; put bitmap at 2000h
		lda d018
		ora #8
		sta d018
;
; select bitmap mode
	 	lda d011	; set bit 5 in VIC-II control register
		ora #20
		sta d011
		
;
; clear bitmap screen
		lda #0		; starting number, 2000h		
		sta fb
		lda #20
		sta fc
		
		lda #40		; destination number, 3f40h
		sta fd
		lda #3f
		sta fe
		
.loop	sec		
		lda fb		; compare low order bytes
		sbc fd
		sta d7		; d7h is temp buffer
		
		lda fc		; compare high order bytes
		sbc fe		
		
		ora d7
		beq .fin	; first number = second number
		
		lda #0		; put zero at address
		ldy #0
		sta (fb), y
		
		inc fb		; increment low order byte
		beq .next 
		jmp .loop
		
.next	inc fc			; increment high order byte
		jmp .loop
.fin
;
; set color to cyan and black
;
		lda #0		; starting number, 400h		
		sta fb
		lda #4
		sta fc
		
		lda #e8		; destination number, 7e8h
		sta fd
		lda #7
		sta fe
		
.loop2	sec		
		lda fb		; compare low order bytes
		sbc fd
		sta d7		; d7h is temp buffer
		
		lda fc		; compare high order bytes
		sbc fe		
		
		ora d7
		beq .fin2	; first number = second number
		
		lda #3		; put 3 at address
		ldy #0
		sta (fb), y
		
		inc fb		; increment low order byte
		beq .next2
		jmp .loop2
		
.next2	inc fc		; increment high order byte
		jmp .loop2
.fin2
; clear bitmap mode
;
		lda d011	; clear bit 5 in VIC-II control register
		and #DF	
		sta d011
;		
; exit
		rts
		
