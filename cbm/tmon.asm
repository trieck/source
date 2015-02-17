;---------------------------------------
; TinyMonitor
; Copyright(c) 2012-2013
; Thomas A. Rieck
; All Rights Reserved
;---------------------------------------

;---------------------------------------
; definitions
;---------------------------------------

chkin    = $ffc6
chkout   = $ffc9
chrin    = $ffcf
chrout   = $ffd2
close    = $ffc3
clrch    = $ffcc
stop     = $ffe1
getin    = $ffe4
hab47    = $ab47
init     = $e3bf
open     = $ffc0
prntint  = $bdcd
readst   = $ffb7
reslst   = $a09e
setlfs   = $ffba
setnam   = $ffbd
strout   = $ab1e
tbuff    = $033c
cbinv    = $0316      ; brk int. vec.
ready    = $a002      ; warm start vec.
setmsg   = $ff90
crlf     = $aad7

; zero page locations
unused   = $02
garbfl   = $0f
scanc    = $3c
nemo     = $3d
wrap     = $3e
acmd     = $3f
format   = $40
length   = $41
lmnem    = $42
rmnem    = $43
count    = $44
rows     = $45
cols     = $46
forpnt   = $47
pch      = $48
pcl      = $49
flgs     = $4a
acc      = $4b
xr       = $4c
yr       = $4d
sp       = $4e
ptr1     = $4f
ptr2     = $51
ptr3     = $53

; reserved kernal zero page locations
status   = $90
ndx      = $c6
rvs      = $c7
crsw     = $d0
pntr     = $d3

;--------------------------------------
; basic program
;---------------------------------------

         *= $0800

         .byte $00    ; begin basic prg
         .byte <nextl ; next link
         .byte >nextl
         .byte $00    ; line #
         .byte $00
         .byte $9e    ; sys token
         .text "2061" ; $08d
         .byte $00    ; end of line
nextl    .byte $00    ; end of program
         .byte $00

;---------------------------------------
; code   must be @$08d
;---------------------------------------
         lda #<break  ; setup break
         sta cbinv    ; interrupt vector
         lda #>break
         sta cbinv+1
         lda #$80     ; set kernal
         jsr setmsg   ; messages only
         brk          ; break!

break                 ; break entry
         cld
         cli
         pla
         sta yr
         pla
         sta xr
         pla
         sta acc
         pla
         sta flgs
         pla
         tax
         pla
         tay
         sec
         txa
         sbc #$02
         sta pcl
         tya
         sbc #$00
         sta pch
         tsx
         stx sp

         jsr $e505    ; # of rows/cols
         stx cols
         sty rows

         lda #<notice ; print notice
         ldy #>notice
         jsr strout

         lda #$52     ; registers
         bne s2

;---------------------------------------
; increment pointer with wrap
;---------------------------------------
incp
         inc ptr1
         bne inp1
         inc ptr1+1
         bne inp1
         inc wrap
inp1
         rts

;---------------------------------------
; start
;---------------------------------------
start
         lda #$00     ; init. wrap
         sta wrap

         jsr crlf
s0
         lda #$2e
         jsr chrout
s1
         jsr chrin
         cmp #$20
         beq s1

         cmp #$0d
         beq start
s2
         ldx #keywl-1 ; # commands-1
s3
         cmp keyw,x   ; keyword
         bne s4

         txa          ; calc offset
         asl a        ; into address
         tax          ; table
         lda kaddr+1,x
         pha
         lda kaddr,x
         pha
         rts          ; jump to routine
s4
         dex
         bpl s3
         jmp error    ; not found

exit                  ; back to basic
         ldx sp
         txs
         jmp (ready)

altrit                ; write display
         tya          ; prompt
         pha
         jsr crlf
         pla
         jmp prtwo

;---------------------------------------
; display registers
;---------------------------------------
dispr
         lda #<regk
         ldy #>regk
         jsr strout

         lda pch      ; print pc
         ldx pcl
         jsr hexint
         jsr setr     ; display them
         jsr dm0
         beq a9

;---------------------------------------
; display memory
;---------------------------------------
dispm
         jsr pcpy     ; copy pointers
         jsr rdadd    ; read address 1
         bcs dsp0
         jsr pcpy     ; again
         jsr rdadd    ; read address 2
         bcs dsp0
         jsr pswap    ; swap pointers
         jmp dsp1
dsp0
         clc
         lda ptr2
         adc #$80
         sta ptr2

         lda ptr2+1
         adc #$00
         sta ptr2+1
dsp1
         lda ptr1     ; store ptr1 to
         sta ptr3     ; ptr3
         lda ptr1+1
         sta ptr3+1

         jsr stop     ; check for stop
         beq a9
         ldx wrap     ; break if wrap
         bne a9
         jsr diffp    ; are we done?
         bcc a9
         ldy #$3a     ; display prompt
         jsr altrit
         jsr pradd    ; print address
         jsr dm       ; display memory
         jsr dma      ; display ascii
         beq dsp1

dm                    ; memory display
         lda #$08
dm0
         tax
         ldy #$00
dm1
         jsr space
         lda (ptr1),y
         jsr hexbyte
         jsr incp
         dex
         bne dm1
         rts
dma                   ; ascii display
         jsr space

         lda #$01     ; enable reverse
         sta rvs

         ldx #$08
         ldy #$00
dma0
         lda (ptr3),y
         jsr isprnt   ; printable?
         bcc dma1

         lda #$2e     ; non-printable
dma1
         jsr chrout
         iny
         dex
         bne dma0

         rts
a9
         jmp start

setr
         lda #<flgs
         sta ptr1
         lda #>flgs
         sta ptr1+1
         lda #$05
         rts

;---------------------------------------
; go routine
;---------------------------------------
go
         jsr rdadd
         bcs error
         jsr putp
         ldx sp
         txs
         sei
         lda pch
         pha
         lda pcl
         pha
         lda flgs
         pha
         lda acc
         ldx xr
         ldy yr
         rti

;---------------------------------------
; set pc address
;---------------------------------------
putp
         lda ptr1
         sta pcl
         lda ptr1+1
         sta pch
         rts

error
         ldx sp       ; fix stack
         txs
         jsr crlf
         lda #$3f     ; ?
         jsr chrout
         jmp start

;---------------------------------------
; scan a character
;---------------------------------------
scnin
         jsr isscn     ; is scan?
         bcs sc0
         jsr chrin
         clc
         sta scanc     ; last scanned
sc0
         rts

;---------------------------------------
; scan a non-space
;---------------------------------------
scnchar
         jsr scnin
         bcs sch0
         cmp #$20
         beq scnchar
         clc
sch0
         rts

;---------------------------------------
; is input available from screen?
;---------------------------------------
isscn
         clc
         lda crsw
         bne iss0
         sec
iss0
         rts

;---------------------------------------
; Disassembler
;
; Adapted from "A 6502 CPU Disassembler"
; By Steve Wozniak and Allen Baum
; Dr. Dobbs Journal, Sept. 1976
;---------------------------------------
disasm
         jsr pcpy     ; copy pointers
         jsr rdadd    ; start address
         bcs dis1
         jsr pcpy     ; again
         jsr rdadd    ; end address
         bcs dis1     ; just start add

         jsr pswap    ; swap pointers
         jmp dis2
dis1
         clc
         lda ptr2
         adc #$16
         sta ptr2

         lda ptr2+1
         adc #$00
         sta ptr2+1

dis2
         jsr crlf
         jsr instdsp
         jsr pcadj

         sta ptr1
         sty ptr1+1

         jsr stop     ; check for stop
         beq dis3

         jsr diffp
         bcs dis2
dis3
         jmp start

scrn2
         bcc rtmskz   ; if even, use
                      ; lo half
         lsr a
         lsr a
         lsr a
         lsr a
rtmskz
         and #$0f     ; mask 4-bits
         rts
insds1
         ldx ptr1     ; print pc
         ldy ptr1+1
         jsr pryx2
         jsr prblnk   ; followed by a
                      ; blank
         lda (ptr1,x) ; get opcode
insds2
         tay
         lsr a        ; even/odd test
         bcc ieven
         ror a        ; bit 1 test
         bcs err      ; xxxxxx11 invalid
                      ; opcode
         and #$87     ; mask bits
                      ; 10000111 for
                      ; addr. mode
ieven
         lsr a        ; lsb into carry
                      ; for l/r test
         tax
         lda fmt1,x   ; get format index
                      ; byte
         jsr scrn2    ; r/l h-byte on
                      ; carry
         bne getfmt
err
         ldy #$80     ; substitute $80
                      ; for invalid ops
         lda #$00     ; set print format
                      ; index to 0
getfmt
         tax
         lda fmt2,x   ; index into print
                      ; format table
         sta format   ; save for adr
                      ; field formatting
         and #$03     ; mask for 2-bit
                      ; length
                      ; 0=1 byte, 1=2
                      ; byte, 2=3 byte
         sta length
         tya          ; opcode
         and #$8f     ; mask for
                      ; 1xxx1010 test
         tax          ; save it
         tya          ; opcode to .a
         ldy #$03
         cpx #$8a
         beq mnndx3
mnndx1
         lsr a
         bcc mnndx3   ; form index into
                      ; mnemonic table
         lsr a
mnndx2
         lsr a        ; 1) 1XXX1010 =>
         ora #$20     ;     00101XXX
         dey          ; 2) XXXYYY01 =>
         bne mnndx2   ;     00111XXX
         iny          ; 3) XXXYYY10 =>
                      ;     00110XXX
                      ; 4) XXXYY100 =>
                      ;     00100XXX
                      ; 5) XXXXX000 =>
                      ;     000XXXXX
mnndx3
         dey
         bne mnndx1
         rts

instdsp
         jsr insds1   ; get format, len
                      ; bytes
         pha          ; save mnemonic
                      ; table index
prntop
         lda (ptr1),y
         jsr hexbyte
         ldx #$01     ; print 2 blanks
prntbl
         jsr prbl2
         cpy length   ; print inst
                      ; (1-3 bytes)
         iny          ; in a 12 char.
                      ; field
         bcc prntop
         ldx #$03     ; char count for
         cpy #$04     ; mnemonic print
         bcc prntbl
         pla          ; recover mnemonic
                      ; index
         tay
         lda mneml,y
         sta lmnem    ; fetch 3-char
                      ; mnemonic
         lda mnemr,y  ; (packed in 2
                      ; bytes)
         sta rmnem
prmn1
         lda #$00
         ldy #$05
prmn2
         asl rmnem    ; shift 5 bits
         rol lmnem    ; of character
         rol a        ; into .a
                      ; (clears carry)
         dey
         bne prmn2
         adc #$3f     ; add "?" offset
         jsr chrout   ; output a char
                      ; of mnem.
         dex
         bne prmn1
         jsr prblnk   ; output blank
         ldy length
         ldx #$06     ; cnt for 6 format
                      ; bits
pradr1
         cpx #$03
         beq pradr5   ; if x=3 then addr
pradr2
         asl format
         bcc pradr3
         lda char1-1,x
         jsr chrout
         lda char2-1,x
         beq pradr3
         jsr chrout
pradr3
         dex
         bne pradr1
         rts
pradr4
         dey
         bmi pradr2
         jsr hexbyte
pradr5
         lda format
         cmp #$e8     ; handle rel adr
                      ; mode
         lda (ptr1),y ; special (print
                      ;  target not
         bcc pradr4   ;  offset)
reladr
         jsr pcadj3
         tax          ; pcl,pch+offset
                      ; +1 to a,y
         inx
         bne prntyx   ; +1 to y,x
         iny
prntyx
         tya
prntax
         jsr hexbyte  ; output target
                      ; adr of branch
                      ; and return
prntx
         txa
         jmp hexbyte
prblnk
         ldx #$01     ; blank count

prbl2
         lda #$20     ; load a space
prbl3
         jsr chrout
         dex
         bne prbl2    ; loop until
                      ; count=0
         rts
pcadj
         sec          ; 0=1-byte
pcadj2                ; 1=2-byte
         lda length   ; 2=3-byte
pcadj3
         ldy ptr1+1
         tax          ; test displacment
                      ; sign
         bpl pcadj4   ; for rel branch
         dey          ; extend neg by
                      ; decr pch
pcadj4
         adc ptr1
         bcc rts2     ; pcl+length
                      ; (or displ)+1
                      ; to a
         iny          ; carry into y
                      ; (pch)
rts2
         rts

pryx2
         jsr prntyx
         lda #$3a     ; print :
         jmp chrout

;---------------------------------------
; directory
;---------------------------------------
dir
         jsr crlf
         jsr cmdopen  ; open cmd. ch.
         bcc dir2
dir3
         jmp dirio    ; i/o error
dir2
         lda #dirlen  ; len. of file
         ldx #<dirname; filename
         ldy #>dirname
         jsr fopen
         bcc dir4
dir5
         jmp dirio    ; i/o error
dir4
         ldx filenum  ; file number
         jsr chkin    ; open channel

         jsr chrin    ; discard load
         jsr chrin    ; address
         lda status   ; check status
         bne direrr

dir6     jsr chrin    ; discard line
         jsr chrin    ; link
         jsr chrin    ; retrieve number
                      ; of blocks used
         sta $fc      ; store to zero
         jsr chrin    ; page in low,
                      ; high format
         sta $fb      ;
         lda status   ; read i/o status
         bne dirclean ; eof
         lda $fb      ; retrieve number
         ldx $fc      ; of blocks
         jsr prntint  ; output int in
                      ; .a, .x
         jsr space    ; print space
                      ; after blocks
         jsr chrin
dir7
         jsr chrout

dir8     ldx $028d    ; check for shift
         bne dir8
         ldx $91      ; check for stop
         cpx #$7f
         beq dirclean
         jsr chrin
         bne dir7
         jsr crlf
         jmp dir6
direrr
         jsr diskerr  ; print disk error
         jmp dirclean
dirio
         jsr ioerr    ; drive i/o error
dirclean
         jsr fclose   ; close file
         jsr cmdclose ; close cmd. ch.
         jmp cstart

;---------------------------------------
; initialize drive
;---------------------------------------
initd
         lda #initlen ; len. of filename
         ldx #<initnm ; filename
         ldy #>initnm
         jsr cmdopen2 ; open cmd. ch
         bcc initclean
         jsr ioerr    ; drive i/o error
initclean
         jsr cmdclose ; close cmd. ch.
         jmp start

;---------------------------------------
; validate a disk
;---------------------------------------
validd
         lda #vallen  ; len. of filename
         ldx #<valname; filename
         ldy #>valname
         jsr cmdopen2 ; open cmd. ch
         bcc valclean
         jsr ioerr    ; drive i/o error
valclean
         jsr cmdclose ; close cmd. ch.
         jmp start

;---------------------------------------
; read a block
;---------------------------------------
rblock
         jsr readts   ; read t/s
         bcc rb0
         jmp error
rb0
         lda #dalen   ; len of filename
         ldx #<daname ; direct access
         ldy #>daname ; filename
         jsr fopen2   ; open file
         bcs rbio

         lda #rcmdlen ; len. of filename
         ldx #<readcmd; filename
         ldy #>readcmd
         jsr cmdopen2 ; open cmd. ch.
         bcs rbio     ; i/o error

         ldx filenum
         jsr chkin    ; set channel in

         lda #$00     ; initialize count
         sta count

         jmp rb11
rb2
         lda status   ; eof
         bne rbclean

         jsr space
         jsr chrin    ; read char
         tax
         jsr hexbyte
         inc count

         lda #$01     ; enable reverse
         sta rvs

         lda pntr     ; save current
         sta $08      ; column

         clc
         lda $07      ; n/l counter
         adc #$1f     ; plus col 31
         sta pntr

         sec
         lda $08      ; provisions for
         sbc #$27     ; logical line
         bcc rb9      ; col. >= 39

         clc          ; add 40 to column
         lda pntr     ; because logical
         adc #$28     ; line is extended
         sta pntr
rb9
         txa          ; byte again
         jsr isprnt   ; is printable?
         bcc rb10     ; okay

         lda #$2e     ; non-printable
                      ; use a period
rb10
         jsr chrout   ; print it

         lda #$00     ; disable reverse
         sta rvs

         lda $08      ; restore column
         sta pntr

         inc $07      ; increment
         lda $07      ; new line counter
         cmp #$08     ; 8 bytes per
         bne rb2      ; line
rb11
         lda status   ; eof
         bne rbclean

         jsr crlf
         lda #":"
         jsr chrout
         lda count
         jsr hexbyte
         jsr space
         jsr space

         lda #$00     ; reset new line
         sta $07      ; counter

         jmp rb2
rbio
         jsr ioerr    ; drive i/o error
rbclean
         jsr fclose   ; close file
         jsr cmdclose ; close cmd. ch.
         jmp cstart

;---------------------------------------
; list a program
;---------------------------------------
list
         lda #<tbuff  ; get filename
         ldx #>tbuff
         jsr getfn
         bcc l0
         jmp error
l0
         jsr crlf
         lda #$00
         sty garbfl   ; init quote mode

         jsr cmdopen  ; open cmd. ch.
         bcc l7
         jmp lio      ; i/o error
l7
         lda length   ; len. of file
         ldx #<tbuff  ; filename
         ldy #>tbuff
         jsr fopen    ; open file
         bcc l9
l8
         jmp lio      ; i/o error
l9
         ldx filenum  ; file number
         jsr chkin    ; open channel
         jsr chrin    ; discard load
         jsr chrin    ; address
         lda status   ; check status
         beq l10
         jmp lerr
l10
         ldx $028d    ; check for shift
         bne l10
         ldx $91      ; check for stop
         cpx #$7f
         bne l23
         jmp lclean
l23
         jsr chrin    ; line link
         sta $fb
         jsr chrin
         ora $fb
         bne l22
         jmp lclean   ; no more lines
l22
         jsr chrin    ; line #
         tax
         jsr chrin
         jsr prntint  ; print line #

         lda #$20     ; print space
         jsr chrout
l12
         lda status
         bne lclean   ; eof

         jsr chrin    ; read token or
                      ; character

         beq l15      ; end of line
         bpl l14      ; character

         bit garbfl   ; quote mode
         bmi l14

         cmp #$ff
         beq l14

         sec          ; keyword
         sbc #$7f     ; table offset+1
         tax
         ldy #$ff
l16
         dex          ; traverse table
         beq l18      ; print keyword
l17
         iny          ; read keyword
         lda reslst,y
         bpl l17
         bmi l16
l18                   ; print keyword
         iny
         lda reslst,y
         bmi l19
         jsr hab47
         bne l18
l19
         and #$7f     ; strip high bit
l14
         jmp lprint   ; print character
l15
         lda #$00     ; end of line
         sta garbfl   ; turn off quote

         lda #$0d     ; print new line
         jsr chrout
         jmp l10
lprint
         cmp #$a2     ; shifted-quote
         beq l21

         jsr isprnt   ; only print
         bcc l21      ; non-printable
         ldx garbfl   ; chars in quote
         bpl l12      ; mode
l21
         jsr hab47    ; print it

         and #$7f
         cmp #$22     ; is it quote?
         bne l12
l20
         lda garbfl   ; toggle quote
         eor #$ff     ; mode
         sta garbfl
         jmp l12
lerr
         jsr diskerr  ; print disk error
         jmp lclean
lio
         jsr ioerr    ; drive i/o error
lclean
         jsr fclose   ; close file
         jsr cmdclose ; close cmd. ch.
         jmp cstart

;---------------------------------------
; help
;---------------------------------------
help
         lda #<helpmsg
         ldy #>helpmsg
         jsr strout
         jmp start

;---------------------------------------
; open command channel
;---------------------------------------
cmdopen
         lda #$00     ; len. of file
         jsr setnam   ; set filename
         lda #$0f     ; command channel
         ldx drive    ; device number
         tay          ; secondary addr.
         jsr setlfs   ; set file params
         jmp open     ; open

;---------------------------------------
; open command channel
; .a,.x,.y set for filename
;---------------------------------------
cmdopen2
         jsr setnam   ; set filename
         lda #$0f     ; command channel
         ldx drive    ; device number
         tay          ; secondary addr.
         jsr setlfs   ; set file params.
         jmp open     ; open

;---------------------------------------
; open file
; length of filename in .a
; lsb of filename in .x
; msb of filename in .y
;---------------------------------------
fopen
         jsr setnam   ; set filename
         lda filenum  ; file number
         ldx drive    ; device number
         ldy #$00     ; secondary addr.
         jsr setlfs   ; set file params
         jmp open     ; open file

;---------------------------------------
; open file w/secondary address
; length of filename in .a
; lsb of filename in .x
; msb of filename in .y
;---------------------------------------

fopen2
         jsr setnam   ; set filename
         lda filenum  ; file number
         ldx drive    ; device number
         ldy secaddr  ; secondary addr.
         jsr setlfs   ; set file params
         jmp open     ; open file

;---------------------------------------
; close file
;---------------------------------------
fclose
         lda filenum
         jmp close    ; close file

;---------------------------------------
; close command channel
;---------------------------------------
cmdclose
         lda #$0f     ; close command
         jsr close    ; channel
         jmp clrch    ; close channels

;---------------------------------------
; disk error
;---------------------------------------
diskerr
         ldx #$0f     ; open channel
         jsr chkin    ; for input
de1
         jsr chrin
         ldx status
         bne de2
         jsr chrout
         jmp de1
de2
         rts

;---------------------------------------
; i/o error
;---------------------------------------
ioerr
         ldy #$01     ; move past cr.
         pha
         jsr $f12f    ; print i/o err.#
         pla
         ora #$30     ; make err. ascii
         jsr chrout   ; print it
         rts

;---------------------------------------
; check for decimal digit in .a
; index stored to .y
;---------------------------------------
isdec
         pha          ; save char

         cmp #$30     ; < 48
         bcc id2

         cmp #$3a     ; < 58
         bcc id1
id2
         sec          ; non-decimal
         jmp id3
id1
         sec          ; store idx to .y
         sbc #$30
         tay
         clc          ; decimal
id3
         pla          ; restore char
         rts

;---------------------------------------
; check for hex digit in .a
; index stored to .y
;---------------------------------------
ishex
         pha          ; save char

         cmp #$30     ; < 48
         bcc ih2

         cmp #$3a     ; < 58
         bcc ih1

         cmp #$41     ; < 65
         bcc ih2

         cmp #$47     ; < 71
         bcs ih2

ih1
         sec          ; hex digit
         sbc #$30     ; store idx to .y
         cmp #$11
         bcc ih4
         sbc #$07
ih4
         tay
         clc
         jmp ih3
ih2
         sec          ; non-hex
ih3
         pla          ; restore char
         rts

;---------------------------------------
; is character in .a printable
;---------------------------------------
isprnt
         cmp #$20     ; < 32
         bcc ip1

         cmp #$80     ; < 128
         bcc ip3

         cmp #$a0     ; < 160
         bcc ip1
ip3
         clc          ; printable
         jmp ip2
ip1
         sec          ; non-printable
ip2
         rts

;---------------------------------------
; print integer in .a,.x in hexadecimal
;---------------------------------------
hexint
         jsr hexbyte
         txa
         jmp hexbyte

;---------------------------------------
; print byte in .a in hexadecimal
;---------------------------------------
hexbyte
         sta unused

         lsr a
         lsr a
         lsr a
         lsr a
         jsr prhexz
         lda unused
prhex
         and #$0f
prhexz
         ora #$30
         cmp #$3a
         bcc cout
         adc #$06
cout
         jsr chrout

         lda unused
         rts

;---------------------------------------
; print space
;---------------------------------------
space
         lda #$20
         jmp chrout

;---------------------------------------
; print address
;---------------------------------------
pradd
         lda ptr1+1
         ldx ptr1
         jmp hexint

;---------------------------------------
; print two chars
;---------------------------------------
prtwo
         pha
         txa
         jsr chrout
         pla
         jmp chrout

;---------------------------------------
; swap ptr1, ptr2
;---------------------------------------
pswap
         ldx #$02
ps1
         lda ptr1-1,x
         pha
         lda ptr2-1,x
         sta ptr1-1,x
         pla
         sta ptr2-1,x
         dex
         bne ps1
         rts

;---------------------------------------
; copy ptr1 to ptr2
;---------------------------------------
pcpy
         lda ptr1
         sta ptr2
         lda ptr1+1
         sta ptr2+1
         rts

;---------------------------------------
; calc ptr2-ptr1
;---------------------------------------
diffp
         lda ptr2
         ldy ptr2+1
deck
         sec
         sbc ptr1
         sta nemo
         tya
         sbc ptr1+1
         tay
         ora nemo
         rts

;---------------------------------------
; read hex address
;---------------------------------------
rdadd
         ldx #$00     ; init length of
                      ; address read

         jsr rdnyb    ; read nybble
         bcs ra4
         bcc ra1
ra0
         jsr scnin    ; scan a character
         bcs ra2

         cmp #$20     ; check for space
         beq ra2
         cmp #$0d     ; check for cr
         beq ra2

         jsr rdn0     ; read nybble
         bcs ra4
ra1
         sta tbuff,x  ; store nybble
         inx
         cpx #$04
         bne ra0
ra2
         lda #$00     ; init. pointer
         sta ptr1
         sta ptr1+1

         dex          ; form pointer
         bmi ra3      ; from input buff

         lda tbuff,x
         sta ptr1

         dex
         bmi ra3

         lda tbuff,x
         asl a
         asl a
         asl a
         asl a
         ora ptr1
         sta ptr1

         dex
         bmi ra3

         lda tbuff,x
         sta ptr1+1

         dex
         bmi ra3

         lda tbuff,x
         asl a
         asl a
         asl a
         asl a
         ora ptr1+1
         sta ptr1+1
ra3
         clc
ra4
         rts

;---------------------------------------
; scan for hex byte
;---------------------------------------
rdbyt
         jsr rdnyb    ; read hi/lo
         bcs rdb3     ; nybble

         sta acmd

         jsr scnin    ; scan character
         bcs rdb0

         cmp #$20     ; one char byte
         beq rdb0
         cmp #$0d
         bne rdb1
rdb0
         lda acmd
         bpl rdb2
rdb1
         jsr rdn0
         bcs rdb3
         tax

         lda acmd     ; hi-nybble
         asl a
         asl a
         asl a
         asl a
         sta acmd
         txa
         ora acmd
rdb2
         clc
rdb3
         rts

;---------------------------------------
; read hex nybble
;---------------------------------------
rdnyb
         jsr scnchar  ; scan non-space
         bcs rdb3
rdn0
         jsr ishex    ; is it hex?
         bcs rdb3
         tya
         rts

;---------------------------------------
; read decimal digit
;---------------------------------------
rddec
         jsr scnchar  ; scan non-space
         bcs rdb3
         jmp isdec    ; is it decimal?

;---------------------------------------
; read 1 or 2 decimal digits
;---------------------------------------
rddec2
         jsr rddec
         bcs rdd4

         sty acmd

         jsr scnin    ; scan 2nd digit
         bcs rdd1

         jsr isdec
         bcc rdd2
rdd1
         lda acmd
         bpl rdd3
rdd2
         lda acmd
         jsr mult10
         sta acmd
         tya
         adc acmd
rdd3
         clc
rdd4
         rts

;---------------------------------------
; scan a character and match
; character to match in .a
;---------------------------------------
scnmatch
         sta unused
         lda scanc    ; last scanned
         cmp unused
         beq scm1

scm0
         jsr scnchar  ; scan non-space
         bcs scm3

         cmp unused
         bne scm2
scm1
         clc
         beq scm3
scm2
         sec
scm3
         rts

;---------------------------------------
; fast multiply .a by 10
;---------------------------------------
mult10
         asl a        ; mult. by 2
         sta unused
         asl a
         asl a        ; mult. by 8
         clc
         adc unused   ; a = x*8 + x*2
         rts

;---------------------------------------
; divide .a by 10
; result in .a, remainder in .x
;---------------------------------------
div10
         ldy #$00
         sec
dv0
         sbc #$0a

         bcc dv1
         iny
         bcs dv0
dv1
         adc #$0a     ; remainder
         tax
         tya          ; result
         rts

;---------------------------------------
; read track and sector
;---------------------------------------
readts
         jsr rddec2   ; read track
         bcs rts0
         jsr div10
         clc
         adc #$30     ; ascii
         sta rtrack
         txa
         adc #$30
         sta rtrack+1

         lda #","     ; comma
         jsr scnmatch
         bcs rts0

         jsr rddec2   ; read sector
         bcs rts0
         jsr div10
         clc
         adc #$30
         sta rsector
         txa
         adc #$30
         sta rsector+1

rts0
         rts

;---------------------------------------
; get filename
;---------------------------------------
getfn
         sta $fb      ; set up buffer
         stx $fc      ; pointer

         lda #$22     ; quote
         sta unused
         jsr scm0
         bcs gfn3

         ldy #$00     ; initialize index
         sty length
gfn0
         jsr scnin    ; scan character
         bcs gfn2

         cmp #$22     ; quote
         beq gfn1

         cmp #$0d     ; return
         beq gfn2

         sta ($fb),y
         iny
         bne gfn0
gfn1
         clc
         sty length   ; store length
         lda #$00     ; store terminator
         sta ($fb),y
         beq gfn3
gfn2
         sec
gfn3
         rts

cstart
         lda $d7      ; last ch. printed
         cmp #$0d     ; return
         beq cs0
         jmp start
cs0
         jmp s0       ; no return

;---------------------------------------
; data declarations
;---------------------------------------
notice
         .byte $0d
         .text "tiny monitor"
         .byte $0d
         .text "copyright(c) 2013 "
         .text "thomas a. rieck "
         .byte $0d
         .byte $00

regk     .byte $0d
         .text "  pc sr"
         .text " ac xr yr sp"
         .byte $0d
         .byte $00

fmt1
; fmt1 bytes: xxxxxxy0 instrs
; if y=0 then right half byte
; if y=1 then left half byte
; x=index

         .byte $04,$20,$54,$30,$0d
         .byte $80,$04,$90,$03,$22
         .byte $54,$33,$0d,$80,$04
         .byte $90,$04,$20,$54,$33
         .byte $0d,$80,$04,$90,$04
         .byte $20,$54,$3b,$0d,$80
         .byte $04,$90,$00,$22,$44
         .byte $33,$0d,$c8,$44,$00
         .byte $11,$22,$44,$33,$0d
         .byte $c8,$44,$a9,$01,$22
         .byte $44,$33,$0d,$80,$04
         .byte $90,$01,$22,$44,$33
         .byte $0d,$80,$04,$90
; zzxxxy01 instrs
         .byte $26,$31,$87,$9a

fmt2
         .byte $00    ; err
         .byte $21    ; imm
         .byte $81    ; z-page
         .byte $82    ; abs
         .byte $00    ; implied
         .byte $00    ; accumulator
         .byte $59    ; (zpag,x)
         .byte $4d    ; (zpag),y
         .byte $91    ; zpag,x
         .byte $92    ; abs,x
         .byte $86    ; abs,y
         .byte $4a    ; (abs)
         .byte $85    ; zpag,y
         .byte $9d    ; relative

char1
         .text ",),#($"
char2
         .text "y"
         .byte $00
         .text "x$$"
         .byte $00

; mneml is of form:
; (a) xxxxx000
; (b) xxxyy100
; (c) 1xxx1010
; (d) xxxyyy10
; (e) xxxyyy01
; (x=index)
mneml
         .byte $1c,$8a,$1c,$23,$5d,$8b
         .byte $1b,$a1,$9d,$8a,$1d,$23
         .byte $9d,$8b,$1d,$a1,$00,$29
         .byte $19,$ae,$69,$a8,$19,$23
         .byte $24,$53,$1b,$23,$24,$53
         .byte $19,$a1 ; (a) format
                       ;     above
         .byte $00,$1a,$5b,$5b,$a5,$69
         .byte $24,$24 ; (b) format
         .byte $ae,$ae,$a8,$ad,$29,$00
         .byte $7c,$00 ; (c) format
         .byte $15,$9c,$6d,$9c,$a5,$69
         .byte $29,$53 ; (d) format
         .byte $84,$13,$34,$11,$a5,$69
         .byte $23,$a0 ; (e) format

mnemr
         .byte $d8,$62,$5a,$48,$26,$62
         .byte $94,$88,$54,$44,$c8,$54
         .byte $68,$44,$e8,$94,$00,$b4
         .byte $08,$84,$74,$b4,$28,$6e
         .byte $74,$f4,$cc,$4a,$72,$f2
         .byte $a4,$8a ; (a) format
         .byte $00,$aa,$a2,$a2,$74,$74
         .byte $74,$72 ; (b) format
         .byte $44,$68,$b2,$32,$b2,$00
         .byte $22,$00 ; (c) format
         .byte $1a,$1a,$26,$26,$72,$72
         .byte $88,$c8 ; (d) format
         .byte $c4,$ca,$26,$48,$44,$44
         .byte $a2,$c8 ; (e) format
         .byte $ff,$ff,$ff

dirname  .text "$0"
dirlen   = *-dirname

filenum  .byte $01
secaddr  .byte $02
drive    .byte $08

daname   .text "#"
dalen    = *-daname

initnm   .text "i0"
initlen  = *-initnm

valname  .text "v0"
vallen   = *-valname

readcmd  .text "u1:2,0,"
rtrack   .text "00,"
rsector  .text "00"
rcmdlen  = *-readcmd

helpmsg  .byte $0d
         .text "d - disassemble"
         .byte $0d
         .text "e - read block"
         .byte $0d
         .text "g - go address"
         .byte $0d
         .text "i - initialize drive"
         .byte $0d
         .text "p - list program"
         .byte $0d
         .text "r - registers"
         .byte $0d
         .text "m - display memory"
         .byte $0d
         .text "v - validate disk"
         .byte $0d
         .text "* - directory"
         .byte $0d
         .text "? - help"
         .byte $0d
         .text "x - exit"
         .byte $00
keyw
         .text "degiprmv*?x"
keywl    = *-keyw
kaddr
         .word disasm-1
         .word rblock-1
         .word go-1
         .word initd-1
         .word list-1
         .word dispr-1
         .word dispm-1
         .word validd-1
         .word dir-1
         .word help-1
         .word exit-1

