
; PixieVM bubble sort
;
; the starting address of the list is in .d
; the length of the list is in .cl
; .ch is used to hold an exchange flag.

.org $8800

sort8:
		xor ch, ch		; turn exchange flag off
        xor x, x		; initialize index register
nxtel:   
		mov al, [d+x]	; fetch element
        inx
        cmp al, [d+x]	; is it larger than the next element ?
        jcc chkend
		jz chkend
		mov ah, [d+x]	; yes exchange elements
		mov [d+x], al
		dex
		mov [d+x], ah
		inx
		mov ch, $ff		; turn on exchange flag
chkend:
		dec cl			; end of list ?
		jnz nxtel		; no, fetch next element
		bit ch, ch		; exchange flag still off ?
		bmi sort8		; no, go through list again
		ret				; yes, list is now ordered
