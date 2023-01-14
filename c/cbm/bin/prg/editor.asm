            *= $0400

length      = $40           ; length of filename
pntr        = $d3
status      = $90
prtstr      = $cb1e
tbuffer     = $033c
kmsgshow    = $f1e6
clrch       = $ffcc
membuff     = $a000
prtfix      = $ddcd

cmdch       = $0f           ; command channel
filenum     = $05           ; open file number
secaddr     = $05           ; secondary address

            jmp start

fname       .ztext 'filename:'
seqsuff     .ztext ',s,r'

drive       .byte $08       ; current drive#
fsize       .word $0000     ; total file size
pmembuf     .word $0000     ; current pointer to memory buffer
pendbuf     .word $0000     ; end of buffer

;---------------------------------------
; code
;---------------------------------------
start
            lda #<fname
            ldy #>fname
            jsr prtstr

            lda #<tbuffer   ; get filename
            ldx #>tbuffer
            jsr getstr
            
            lda length      ; no file specified, ok
            beq edit

            jsr loadf
            bcs end         ; error loading

edit
            jsr editor
end
            rts

;---------------------------------------
; Screen editor
;---------------------------------------
editor
            lda #$93        ; clear screen
            jsr chrout

            lda #<membuff   ; initialize memory pointer
            sta pmembuf

            ldx #>membuff
            stx pmembuf+1
            
            clc              ; set end of buffer pointer
            lda #<membuff
            adc fsize
            sta pendbuf
            lda #>membuff
            adc fsize+1
            sta pendbuf+1

            lda pmembuf
            ldx pmembuf+1
            jsr cpyscr

egetkey
            jsr getkey
            cmp #$03        ; stop
            beq edone
            cmp #$11        ; cursor down
            beq k1
            cmp #$91        ; cursor up
            beq k2
            cmp #$1d        ; cursor right
            beq k3
            cmp #$9d        ; cursor left
            beq k4
            cmp #$13        ; home
            beq k5
            cmp #$93        ; clear
            beq k6
            bne egetkey
k1          jmp crsrdwn
k2          jmp crsrup
k3          jmp crsrrt
k4          jmp crsrlt
k5          jmp home
k6          jmp top

edone
            rts

;---------------------------------------
; Cursor down
;---------------------------------------
crsrdwn     
            ldy $d3         ; column
            ldx $d6         ; row
            inx             ; next row

            cpx #$16        ; max row
            bcc crd1
            beq crd1

            jsr scrldown    ; scroll down

            ldy $d3         ; column
            ldx #$16        ; set max row
crd1            
            clc             ; set cursor
            jsr plot
            jmp egetkey

;---------------------------------------
; Cursor up
;---------------------------------------
crsrup     
            ldy $d3         ; column
            ldx $d6         ; row
            dex             ; previous row

            cpx #$00        ; min row
            bpl cru1
            
            jsr scrlup      ; scroll up
            
            ldy $d3         ; column
            ldx #$00        ; set min row
cru1            
            clc             ; set cursor
            jsr plot
            jmp egetkey

;---------------------------------------
; Cursor right
;---------------------------------------
crsrrt
            ldy $d3         ; column
            ldx $d6         ; row
            iny             ; next column

            jsr endofline
crr1            
            clc             ; set cursor
            jsr plot
            jmp egetkey

;---------------------------------------
; Cursor left
;---------------------------------------
crsrlt
            ldy $d3         ; column
            ldx $d6         ; row
            dey             ; prev column

            cpy #$00        ; min column
            bpl crl1

            cpx #$00        ; min row
            bne crl2

            jsr scrlup      ; scroll up
            ldx #$01        ; min row before decrement
crl2
            ldy #$15        ; max column
            dex             ; previous row

crl1
            clc             ; set cursor
            jsr plot
            jmp egetkey

;---------------------------------------
; Handle end of line condition
; By scrolling if necessary
;
; .X contains row# $00-$16
; .Y contains col# $00-$15
; .Y contains >= $16, if end of line
;
; On return, 
; .X contains the row#
; .Y contains the col#
;---------------------------------------
endofline
            cpy #$15        ; max column
            bcc eoldone
            beq eoldone

            ldy #$00        ; set min column

            inx             ; next row
            cpx #$16        ; max row
            bcc eoldone
            beq eoldone

            jsr scrldown    ; scroll down

            ldy #$00        ; set min column
            ldx $d6         ; row
eoldone
            rts

;---------------------------------------
; Home cursor
;---------------------------------------
home
            ldx #$00        ; min row
            ldy #$00        ; min column

            clc             ; set cursor
            jsr plot
            jmp egetkey

;---------------------------------------
; Top of document
;---------------------------------------
top
            lda #<membuff   ; initialize memory pointer
            sta pmembuf

            ldx #>membuff
            stx pmembuf+1

            lda pmembuf
            ldx pmembuf+1
            jsr cpyscr

            jmp home

;---------------------------------------
; Scroll Down
;---------------------------------------
scrldown
            lda pmembuf     ; low byte of first number
            ldy pmembuf+1   ; high byte of first number

            ldx pendbuf     ; low byte of second number
            stx $14
            ldx pendbuf+1   ; high byte of second number
            stx $15
            ldx #$14

            jsr compare16
            bcs scddone     ; can't scroll, greater or equal

            lda pmembuf
            adc #$16        ; next line
            sta pmembuf
            bcc scdok2
            inc pmembuf+1   ; increment page
scdok2            
            lda pmembuf
            ldx pmembuf+1
            jsr cpyscr      ; copy new screen
scddone
            rts

;---------------------------------------
; Scroll Up
;---------------------------------------
scrlup      
            lda pmembuf     ; low byte of first number
            ldy pmembuf+1   ; high byte of first number

            ldx #<membuff   ; low byte of second number
            stx $14
            ldx #>membuff   ; high byte of second number
            stx $15
            ldx #$14

            jsr compare16
            bcc scudone     ; can't scroll, less than
            beq scudone     ; can't scroll, equal

            lda pmembuf
            sbc #$16        ; previous line
            sta pmembuf
            bcs scuok2
            dec pmembuf+1   ; decrement page
scuok2            
            lda pmembuf
            ldx pmembuf+1
            jsr cpyscr      ; copy new screen
scudone
            rts

;---------------------------------------
; Compare 2 16-bit numbers
;
; .A, .Y holds the first number
; .X is the low byte of two adjacent 
; bytes on zero page.
;
;---------------------------------------
compare16
        sta $16
        
        tya             ; compare high bytes
        cmp $01, x
        bne cmpdone

        lda $16
        cmp $00, x      ; compare low bytes
cmpdone

        rts

;---------------------------------------
; Load sequential file
;
; file should be stored in screen format
; filename is stored in tbuffer
; length of filename in length
; file contents are copied to
; an off-screen memory buffer
; membuff
;---------------------------------------
loadf
            lda #$00        ; initialize file size
            sta fsize
            sta fsize+1

            jsr cmdopen     ; open cmd. ch.
            bcc lf1

            jmp lio         ; i/o error

lf1         
            ldx #$00
lfs                         ; append file type, mode
            lda seqsuff, x
            beq lf4

            ldy length
            sta tbuffer, y
            inc length

            inx
            bne lfs
lf4
            lda length      ; length of file
            ldx #<tbuffer   ; filename
            ldy #>tbuffer
            jsr fopen       ; open file
            bcc lf2

            jmp lio         ; i/o error
lf2
            ldx #filenum    ; file number
            jsr chkin       ; open channel

            ldx status      ; check status
            beq lf3
            jmp lerr

lf3
            lda #<membuff
            sta $fb
            lda #>membuff
            sta $fc

            ldy #$00
lf5
            jsr chrin
            sta ($fb), y

            inc fsize
            bne lf6

            inc fsize+1
lf6
            lda status
            bne eof

            inc $fb
            bne lf5

            inc $fc
            bne lf5
eof
            cmp #$40        ; end of file?
            beq lfgood
lerr
            jsr diskerr     ; print disk error
            jmp lfbad
lio
            jsr ioerr       ; print i/o error
lfbad
            lda #$00        ; no size
            sta fsize       
            sta fsize+2

            lda #$ff        ; error indicator
            sta $fb
            jmp lfclean
lfgood      
            inc $fb         ; add terminator
            bne lfgood2

            inc $fc
lfgood2
            lda #$00
            tay
            sta ($fb), y

            lda #$00        ; no error
            sta $fb
lfclean
            jsr fclose      ; close file
            jsr cmdclose    ; close cmd. ch.

            lda $fb
            beq lfg2
            sec             ; error indicator
            bne lfend
lfg2        
            clc             ; all good
lfend
            rts

;---------------------------------------
; is character in .a printable
;---------------------------------------
isprnt
            cmp #$20        ; < 32
            bcc ip1

            cmp #$80        ; < 128
            bcc ip3

            cmp #$a0        ; < 160
            bcc ip1
ip3
            clc             ; printable
            jmp ip2
ip1
            sec             ; non-printable
ip2
            rts

;---------------------------------------
; get string input
; pointer to store string in .a,.x
;---------------------------------------
getstr
            sta $fb         ; set up buffer
            stx $fc         ; pointer

            lda pntr        ; minimum column
            sta $fd

            ldy #$00        ; initialize index
            sty length
gs1
            jsr getkey
            cmp #$0d        ; return
            beq gs4

            cmp #$14        ; backspace
            bne gs2

            ldx pntr        ; current column
            cpx $fd         ; min column
            beq gs1

            ldy length
            dey
            sty length
            jsr chrout
            jmp gs1
gs2
            jsr isprnt      ; is character
            bcs gs1         ; printable?

            ldx pntr        ; current column
            cpx #$27        ; max column
            bcs gs1
gs3
            ldy length
            sta ($fb),y     ; store character
            iny
            sty length
            jsr chrout
            jmp gs1
gs4
            lda #$00        ; store terminator
            ldy length
            sta ($fb),y

            lda $fb         ; restore regs
            ldx $fc

            rts

;---------------------------------------
; Copy screen data pointed to 
; by .A,.X to screen
; until '\0' is encounter of the end of 
; screen is reached.  Remainder of screen
; is filled with spaces if entire screen
; area is not copied.
;---------------------------------------
cpyscr
            sta $c1         ; set up source pointer
            stx $c2

            jsr setptrs     ; set up pointers to screen/color RAM
                            ; screen RAM at ($fc, $fd)
                            ; color RAM at ($fe, $ff)
                            ; end of screen at ($57, $58)
            ldy #$00
            sty $41         ; initialize EOF indicator
l1
            lda $41         ; check EOF
            bne l24

            lda ($c1),y     ; pointer to text
            bne l6

            lda #$ff
            sta $41
l24
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
            lda $fc         ; check end of screen
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

;---------------------------------------
; Compare 2 16-bit numbers
;---------------------------------------
cmp16
            rts
            
getkey      
            lda #$0
            sta $cc         ; turn on cursor
gk1
            lda $c6         ; number of characters in the keyboard buffer
            beq gk1         ; no keys

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

;---------------------------------------
; open command channel
;---------------------------------------
cmdopen
            lda #$00        ; len. of file
            jsr setnam      ; set filename
            lda #cmdch      ; command channel
            ldx drive       ; device number
            tay             ; secondary addr.
            jsr setlfs      ; set file params
            jsr open        ; open
            rts

;---------------------------------------
; open file with secondary address
; length of filename in .a
; lsb of filename in .x
; msb of filename in .y
;---------------------------------------
fopen
            jsr setnam      ; set filename
            lda #filenum    ; file number
            ldx drive       ; device number
            ldy #$0         ; secondary addr.
            jsr setlfs      ; set file params
            jsr open        ; open file
            rts

;---------------------------------------
; close file
;---------------------------------------
fclose
            lda #filenum
            jsr close       ; close file
            rts

;---------------------------------------
; close command channel
;---------------------------------------
cmdclose
            lda #cmdch      ; close command
            jsr close       ; channel
            jsr clrch       ; close channels
            rts

;---------------------------------------
; i/o error
;---------------------------------------
ioerr
            ldy #$00
            pha
            jsr kmsgshow    ; print i/o err.#
            pla
            ora #$30        ; make err. ascii
            jsr chrout      ; print it
            rts

;---------------------------------------
; disk error
;---------------------------------------
diskerr
            lda #$0d
            jsr chrout

            ldx #cmdch      ; open channel
            jsr chkin       ; for input
de1
            jsr chrin
            ldx status
            bne de2
            jsr chrout
            jmp de1
de2
            rts
