;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; UTIL.ASM
;
; CBM 6502 utility routines
;
; Copyright (c)2001 Thomas A. Rieck
;
; external declarations
;
.extern _initcolor, _drawbitmap		; defined in a separate module
; declare this module as the global
; entry point for the image
;
; .global _hexword					; only one of these per image
.hextable
		.byte '0123456789abcdef'
; output word in a,x in hexadecimal
;
.outhex	
		pha				; remember hi byte
		txa		
		pha				; remember lo byte
		
		lda #24			; print '$' character
		jsr ffd2
		
		tsx				; output hi nybble of hi byte
		lda 101, x
		jsr .outhi
		
		tsx				; output lo nybble of hi byte
		lda 101, x
		jsr .outlo
		
		tsx				; output hi nybble of lo byte
		lda 102, x
		jsr .outhi
		
		tsx				; output lo nybble of lo byte
		lda 102, x
		jsr .outlo
		
		pla				; restore x register
		tax
		pla				; restore a register
		
		rts
	
.outlo	and #0f
		jmp .out
		
.outhi	and #f0
		lsr
		lsr
		lsr
		lsr
		
.out	tax
		lda .hextable, x
		jsr ffd2
		
		rts
		