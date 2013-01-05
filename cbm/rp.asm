         *= $0800
;---------------------------------------
; basic program declaration
;---------------------------------------
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

         jmp start    ; must be @ $08d
;---------------------------------------
; data declarations
;---------------------------------------
m1       .text "command: f(iler)"
         .text ",m(emory),x:"
         .byte $00
m2       .text "filer: d,i,l,r,v,x,?:"
         .byte $00
m3       .text "drive:"
         .byte $00
m4       .text "press space"
         .byte $00
m5       .text "memory: d,m,x:"
         .byte $00
m6       .text "start:"
         .byte $00
m7       .text "end  :"
         .byte $00
m8       .text "filename:"
         .byte $00
m9       .text "validating..."
         .byte $00
m10      .text "initializing..."
         .byte $00
m11      .text "track,sector:"
         .byte $00
sfhelp   .text "d - directory"
         .byte $0d
         .text "i - initialize drive"
         .byte $0d
         .text "l - list a basic prg"
         .byte $0d
         .text "r - read a block"
         .byte $0d
         .text "v - validate disk"
         .byte $0d
         .text "x - exit"
         .byte $0d
         .text "? - help"
         .byte $00

dirname  .text "$0"
dirlen   = *-dirname

initnm   .text "i0"
initlen  = *-initnm

valname  .text "v0"
vallen   = *-valname

daname   .text "#"
dalen    = *-daname

readcmd  .text "u1"
         .text " "
rchannel .text "00"
         .text " "
         .text "00"
         .text " "
rtrack   .text "00"
         .text " "
rsector  .text "00"
rcmdlen  = *-readcmd

chkin    = $ffc6
chkout   = $ffc9
chrin    = $ffcf
chrout   = $ffd2
close    = $ffc3
clrch    = $ffcc
getin    = $ffe4
hab47    = $ab47
init     = $e3bf
open     = $ffc0
printint = $bdcd
readst   = $ffb7
reslst   = $a09e
setlfs   = $ffba
setnam   = $ffbd
strout   = $ab1e
tbuffer  = $033c

count    = $46
format   = $40
forpnt   = $49
garbfl   = $0f
length   = $41
lmnem    = $42
ndx      = $c6
pch      = $45
pcl      = $44
pntr     = $d3
rmnem    = $43
rvs      = $c7
status   = $90

drive    .byte $08
cols     .byte $00
rows     .byte $00
filenum  .byte $01

saddr    .word $00    ; start addr.
daddr    .word $00    ; dest. addr.

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

;---------------------------------------
; code
;---------------------------------------
start
         lda #$0c     ; init screen
         sta $d020    ; gray 2 border
         lda #$0f
         sta $d021    ; gray 3 bkgnd
         lda #$02
         sta $0286    ; red char
         lda #$17
         sta $d018    ; lowercase
         lda #$80
         sta $0291    ; dis. shft/cmdr
         jsr $e505    ; # of rows/cols
         stx cols
         sty rows

main
         lda #$93     ; clear screen
         jsr chrout
         lda #<m1
         ldy #>m1
         jsr strout   ; print m1

i1       jsr getchar  ; get char
         cmp #$46     ; is it "f"?
         beq i1f      ; file menu
         cmp #$4d     ; it it "m"?
         beq i1m      ; memory menu
         cmp #$58     ; is it "x"?
         beq end      ; exit
         jmp i1
i1f
         jmp fmenu    ; file menu
i1m
         jmp mmenu    ; memory menu

end
         jsr init     ; init. basic
         jmp $fe66    ; warm start

;---------------------------------------
; file menu
;---------------------------------------
fmenu                 ; file menu
         lda #$93     ; clear screen
         jsr chrout
         lda #<m2
         ldy #>m2
         jsr strout   ; print m2

f1       jsr getchar  ; get char
         cmp #$44     ; is it "d"?
         beq f2       ; directory
         cmp #$49     ; is it "i"?
         beq f3       ; initialize
         cmp #$4c     ; is it "l"?
         beq f4       ; listing
         cmp #$52     ; is it "r"?
         beq f5       ; read block
         cmp #$56     ; is it "v"?
         beq f6       ; validate
         cmp #$58     ; is it "x"?
         beq f7       ; main menu
         cmp #$3f     ; is it "?"
         beq f8       ; help
         jmp f1
f2       jmp dir      ; directory
f3       jmp initd    ; initialize
f4       jmp list     ; listing
f5       jmp rblock   ; read block
f6       jmp valid    ; validate
f7       jmp main     ; main menu
f8       jmp fhelp    ; help

;---------------------------------------
; list a program
;---------------------------------------
list                  ; list a program
         jsr getdrive ; get drive
         jsr chrout   ; print return

         lda #<m8
         ldy #>m8
         jsr strout   ; print m8

         lda #<tbuffer; get filename
         ldx #>tbuffer
         jsr getstr

         lda #$00
         sty garbfl   ; init quote mode

         jsr loline   ; lower line sep.

         jsr cmdopen  ; open cmd. ch.
         bcc l7
         jmp lio      ; i/o error
l7
         lda length   ; len. of file
         ldx #<tbuffer; filename
         ldy #>tbuffer
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
         jsr printint ; print line #

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

         jsr upline   ; upper line sep.

         jsr waitsp   ; wait for space
         jmp fmenu    ; file menu

;---------------------------------------
; read a block
;---------------------------------------
rblock
         jsr getdrive ; get drive
         jsr chrout   ; print return

         lda #<m11
         ldy #>m11
         jsr strout   ; print m11

         lda #<tbuffer
         ldx #>tbuffer

         jsr getstr   ; get t/s

         ldy #$2c     ; find index of ,
         jsr instr
         bcs rbdone   ; not found

         jsr loline   ; lower line sep.

         lda #$00     ; initialize
         sta rvs      ; reverse flag

         jsr cmdopen  ; open cmd. ch
         bcs rbio     ; i/o error

         lda #dalen   ; len of filename
         ldx #<daname ; direct access
         ldy #>daname ; filename
         jsr fopen    ; open file
         bcs rbio

         ldx #$0f     ; command channel
         jsr chkout   ; set channel out

         ldx #$00
         ldy rcmdlen
rb1
         lda readcmd,x; loop until last
         jsr chrout   ; character sent
         inx
         dey
         bne rb1

         jsr clrch    ; restore channel
         ldx filenum
         jsr chkin    ; set channel in

rb2
         jsr chrin
         ldx status
         bne rbclean

         jsr hexbyte

         lda #$01
         eor rvs
         sta rvs

         jmp rb2
rbio
         jsr ioerr    ; drive i/o error
rbclean
         jsr fclose   ; close file
         jsr cmdclose ; close cmd. ch.
         jsr upline   ; upper line sep.

         jsr waitsp   ; wait for space

rbdone
         jmp fmenu    ; file menu

         rts

;---------------------------------------
; validate a disk
;---------------------------------------
valid
         jsr getdrive ; get drive

         jsr loline   ; lower line sep.

         lda #<m9
         ldy #>m9
         jsr strout   ; print m9

         lda #vallen  ; len. of filename
         ldx #<valname; filename
         ldy #>valname
         jsr cmdopen2 ; open cmd. ch.
         bcc valclean
valio
         jsr ioerr    ; drive i/o error

valclean
         jsr cmdclose ; close cmd. ch.

         jsr upline   ; upper line sep.

         jsr waitsp   ; wait for space
         jmp fmenu    ; file menu

;---------------------------------------
; initialize a drive
;---------------------------------------
initd
         jsr getdrive ; get drive

         jsr loline   ; lower line sep.

         lda #<m10
         ldy #>m10
         jsr strout   ; print m9

         lda #initlen ; len. of filename
         ldx #<initnm ; filename
         ldy #>initnm
         jsr cmdopen2 ; open cmd. ch.
         bcc initclean
initio
         jsr ioerr    ; drive i/o error

initclean
         jsr cmdclose ; close cmd. ch.

         jsr upline   ; upper line sep.

         jsr waitsp   ; wait for space
         jmp fmenu    ; file menu

;---------------------------------------
; directory
;---------------------------------------
dir                   ; directory
         jsr getdrive ; get drive

         jsr loline   ; lower line sep.

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
         jsr printint ; output int in
                      ; .a, .x
         lda #$20     ; print space
         jsr chrout   ; after blocks
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
         lda #$0d
         jsr chrout   ; print return
         jmp dir6
direrr
         jsr diskerr  ; print disk error
         jmp dirclean

dirio
         jsr ioerr    ; drive i/o error
dirclean
         jsr fclose   ; close file
         jsr cmdclose ; close cmd. ch.

         jsr upline   ; upper line sep.

         jsr waitsp   ; wait for space
         jmp fmenu    ; file menu

;---------------------------------------
; filer menu help
;---------------------------------------
fhelp
         jsr loline   ; lower line sep.

         lda #<sfhelp
         ldy #>sfhelp
         jsr strout   ; print help

         jsr upline   ; upper linn sep.

         jsr waitsp   ; wait for space
         jmp fmenu    ; file menu
         rts

;---------------------------------------
; memory menu
;---------------------------------------
mmenu                 ; memory menu
         lda #$93     ; clear screen
         jsr chrout
         lda #<m5
         ldy #>m5
         jsr strout   ; print m5

i3       jsr getchar  ; get char
         cmp #$44     ; is it "d"?
         beq i3d      ; disassemble
         cmp #$4d     ; is it "m"?
         beq i3m      ; memory dump
         cmp #$58     ; is it "x"?
         beq i3e      ; main menu
         jmp i3
i3d
         jmp disass   ; disassemble
i3m
         jmp dump     ; memory dump
i3e
         jmp main     ; main menu

;---------------------------------------
; Disassembler
;
; Adapted from "A 6502 CPU Disassembler"
; By Steve Wozniak and Allen Baum
; Dr. Dobbs Journal, Sept. 1976
;---------------------------------------
disass
         jsr getstart ; get start addr.
         jsr getdest  ; get dest. addr.
         jsr loline   ; lower line sep.

         lda saddr    ; set up pointers
         sta pcl
         lda saddr+1
         sta pch
         lda daddr
         sta $05
         lda daddr+1
         sta $06
dis1
         lda $028d    ; check for shift
         bne dis1
         lda $91      ; check for stop
         cmp #$7f
         beq dis2

         jsr instdsp
         jsr pcadj
         sta pcl
         sty pch
         jsr prnret

         lda pch      ; compare high
         cmp $06      ; bytes
         bcc dis1     ; pch < ($06)
         bne dis2     ; pch > ($06)

         lda pcl      ; compare low
         cmp $05      ; bytes
         bcc dis1     ; pcl < ($05)
         beq dis1     ; pcl = ($05)
dis2
         jsr upline   ; upper line sep.

         jsr waitsp   ; wait for space
         jmp mmenu    ; memory menu

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
         ldx pcl      ; print pcl,h
         ldy pch
         jsr pryx2
         jsr prblnk   ; followed by a
                      ; blank
         lda (pcl,x)  ; get opcode
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
         .byte $ff,$ff,$ff

instdsp
         jsr insds1   ; get format, len
                      ; bytes
         pha          ; save mnemonic
                      ; table index
prntop
         lda (pcl),y
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
         lda (pcl),y  ; special (print
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
         ldy pch
         tax          ; test displacment
                      ; sign
         bpl pcadj4   ; for rel branch
         dey          ; extend neg by
                      ; decr pch
pcadj4
         adc pcl      ;
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
; memory dump
;---------------------------------------
dump                  ; memory dump
         jsr getstart ; get start addr.
         jsr getdest  ; get dest. addr.

         jsr loline   ; lower line sep.

du1
         lda saddr    ; set up pointers
         sta $03
         lda saddr+1
         sta $04
         lda daddr
         sta $05
         lda daddr+1
         sta $06

         ldy #$00     ; init. index
         sty $07      ; new line counter
du2
         lda $028d    ; check for shift
         bne du2
         lda $91      ; check for stop
         cmp #$7f
         bne du8
         jmp du4      ; stop
du8
         lda $07      ; check nl counter
         bne du3

         lda $03      ; print line
         sta $02
         tya
         ora $02
         tax

         lda $04
         jsr hexint

         lda #$20     ; print space
         jsr chrout

         lda #$3a     ; print :
         jsr chrout
du3
         lda #$20     ; print space
         jsr chrout

         lda ($03),y  ; print byte
         jsr hexbyte

         lda #$01
         sta rvs      ; enable reverse

         lda pntr     ; save current
         sta $08      ; column

         clc
         lda $07      ; nl counter
         adc #$1f     ; plus col 31
         sta pntr

         sec
         lda $08      ; provisions for
         sbc #$27     ; logical line
         bcc du6      ; col. >= 39

         clc          ; add 40 to column
         lda pntr     ; because logical
         adc #$28     ; line is extended
         sta pntr
du6
         lda ($03),y
         jsr isprnt   ; is printable?
         bcc du9      ; okay

         lda #$2e     ; non-printable
                      ; use a period

du9
         jsr chrout   ; print it

         lda #$00     ; disable reverse
         sta rvs

         lda $08      ; restore column
         sta pntr

         clc          ; compare
         lda $03
         sta $02
         tya
         adc $02

         sec
         sbc $05
         sta $02

         lda $04
         sbc $06
         ora $02
         beq du4      ; done

         iny          ; next byte
         inc $07      ; increment
         lda $07      ; new line counter
         cmp #$08     ; 8 bytes per
         bne du5      ; line

         lda #$0d     ; print new line
         jsr chrout

         lda #$00     ; reset new line
         sta $07      ; counter
         sta pntr
du5
         clc
         lda $03
         sta $02
         tya
         adc $02
         beq du7
         jmp du2
du7

         lda #$00     ; next page
         sta $03
         inc $04
         jmp du2
du4
         jsr upline   ; upper line sep.

         jsr waitsp   ; wait for space
         jmp mmenu    ; memory menu

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
         jsr open     ; open
         rts

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
         jsr open     ; open
         rts

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
         jsr open     ; open file
         rts

;---------------------------------------
; close file
;---------------------------------------
fclose
         lda filenum
         jsr close    ; close file
         rts

;---------------------------------------
; close command channel
;---------------------------------------
cmdclose
         lda #$0f     ; close command
         jsr close    ; channel
         jsr clrch    ; close channels
         rts

;---------------------------------------
; get starting address
;---------------------------------------
getstart              ; get start addr.
         lda #$0d
         jsr chrout   ; print return
         lda #<m6
         ldy #>m6
         jsr strout   ; print m6

         lda #$00     ; reinitialize
         sta saddr
         sta saddr+1

         lda #<saddr  ; set up pointer
         ldx #>saddr
         jsr getaddr

         rts

;---------------------------------------
; get destination address
;---------------------------------------
getdest               ; get dest. addr.
         lda #$0d
         jsr chrout   ; print return
         lda #<m7
         ldy #>m7
         jsr strout   ; print m7

         lda #$00     ; reinitialize
         sta daddr
         sta daddr+1

         lda #<daddr  ; set up pointer
         ldx #>daddr
         jsr getaddr

         rts

;---------------------------------------
; get address
; address to store is in .a, .x
;---------------------------------------
getaddr               ; get address

         sta $fb      ; store pointer
         stx $fc

         lda #$30     ; initialize to
         jsr chrout   ; zeros
         jsr chrout
         jsr chrout
         jsr chrout
         jmp gabk

ga1
         jsr getchar
         cmp #$0d
         beq gadone
         jsr ishex
         bcs ga1
         jsr chrout   ; print it

         tya          ; index of char
         asl a        ; multiply by 16
         asl a        ; for hi-nybble
         asl a
         asl a

         ldy #$01     ; hi-byte
         sta ($fb),y  ; store hi-nybble
ga2
         jsr getchar
         cmp #$0d     ; is it return
         beq gadone
         jsr ishex
         bcs ga2
         jsr chrout   ; print it

         tya          ; index of char
         ldy #$01     ; hi-byte
         ora ($fb),y  ; store lo-nybble
         sta ($fb),y  ; of hi-byte
ga3
         jsr getchar
         cmp #$0d     ; is it return
         beq gadone
         jsr ishex
         bcs ga3
         jsr chrout   ; print it

         tya          ; index of char
         asl a        ; multiply by 16
         asl a        ; for hi-nybble
         asl a
         asl a
         ldy #$00     ; lo-byte
         sta ($fb),y

ga4
         jsr getchar
         cmp #$0d     ; is it return
         beq gadone
         jsr ishex
         bcs ga4
         jsr chrout   ; print it

         tya          ; index of char
         ldy #$00     ; lo-byte
         ora ($fb),y  ; store lo-nybble
         sta ($fb),y  ; of lo-byte
gabk
         lda #$9d     ; bkspace
         jsr chrout
         jsr chrout
         jsr chrout
         jsr chrout
         jmp ga1

gadone
         lda $fb      ; restore pointer
         ldx $fc
         rts

;---------------------------------------
; get character from keyboard
; and blink the cursor
;---------------------------------------
getchar               ; get character
         lda #$00
         sta ndx      ; clear buffer
         sta $cc      ; blink cursor
gc1      jsr getin    ; get char
         beq gc1      ; empty buffer
         pha          ; push .a
         jsr crsroff  ; cursor off
         pla          ; pull .a
         rts

;---------------------------------------
; turn the cursor off
;---------------------------------------
crsroff
         inc $cc      ; cursor off
         ldx $0287    ; orig color
         lda $ce      ; orig char
         and #$7f     ; turn off rvs
         jsr $ea1c    ; store to scn
         rts

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
; wait for space
;---------------------------------------
waitsp                ; wait for space
         lda #$01
         sta rvs      ; enable rev.
         lda #<m4
         ldy #>m4
         jsr strout
         lda #$00
         sta rvs      ; disable rev.

wsp1     jsr getin
         cmp #$20     ; space
         bne wsp1
         rts

;---------------------------------------
; get drive
;---------------------------------------
getdrive              ; get drive
         lda #$0d
         jsr chrout   ; print return
         lda #<m3
         ldy #>m3
         jsr strout   ; print m3
gd1
         lda drive
         cmp #$0a
         bcs gd2      ; drive >= 10
         lda #$00
         ldx #$00
         jsr printint ; output lead 0

gd2
         lda #$00     ; high byte
         ldx drive    ; lo byte
         jsr printint ; output integer
         lda #$9d
         jsr chrout   ; print bkspace
         jsr chrout

gd3      jsr getchar  ; get char
         cmp #$11     ; is it cr. dwn?
         beq gd4
         cmp #$0d     ; is it return?
         beq gd5
         jmp gd3
gd4
         inc drive    ; next drive
         lda drive
         cmp #$0c
         bcc gd1      ; drive < 12
         lda #$08
         sta drive    ; reset drive #
         jmp gd1

gd5
         rts

;---------------------------------------
; check for hex digit in .a
;---------------------------------------
ishex
         sta $02      ; store char

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
         lda $02      ; restore char
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
; lower line separator
;---------------------------------------
loline
         jsr prnret   ; print return

         lda #$b9     ; lower line sep.
         ldx cols     ; # of cols.

ll1
         jsr chrout   ; print sep.
         dex
         bne ll1

         rts

;---------------------------------------
; upper line separator
;---------------------------------------
upline
         jsr prnret   ; print return

         lda #$b8     ; upper line sep.
         ldx cols     ; # of cols.
ul1
         jsr chrout   ; print sep.
         dex
         bne ul1
         rts

;---------------------------------------
; print return conditionally
;---------------------------------------
prnret
         lda $d7      ; last character
                      ; printed

         cmp #$0d     ; is it return?
         beq pr1

         lda #$0d     ; print return
         jsr chrout
pr1
         rts

;---------------------------------------
; print integer in .a, x in hexadecimal
;---------------------------------------
hexint
         jsr hexbyte
         txa
         jsr hexbyte
         rts

;---------------------------------------
; print byte in .a in hexadecimal
;---------------------------------------
hexbyte
         sta $fb

         lsr a
         lsr a
         lsr a
         lsr a
         jsr prhexz
         lda $fb
prhex
         and #$0f
prhexz
         ora #$30
         cmp #$3a
         bcc cout
         adc #$06
cout
         jsr chrout

         lda $fb
         rts

;---------------------------------------
; get string input
; pointer to store string in .a,.x
;---------------------------------------
getstr
         sta $fb      ; set up buffer
         stx $fc      ; pointer

         lda pntr     ; minimum column
         sta $fd

         ldy #$00     ; initialize index
         sty length
gs1
         jsr getchar
         cmp #$0d     ; return
         beq gs4

         cmp #$14     ; backspace
         bne gs2

         ldx pntr     ; current column
         cpx $fd      ; min column
         beq gs1

         ldy length
         dey
         sty length
         jsr chrout
         jmp gs1
gs2
         jsr isprnt   ; is character
         bcs gs1      ; printable?

         ldx pntr     ; current column
         cpx #$27     ; max column
         bcs gs1
gs3
         ldy length
         sta ($fb),y  ; store character
         iny
         sty length
         jsr chrout
         jmp gs1
gs4
         lda #$00     ; store terminator
         ldy length
         sta ($fb),y

         lda $fb      ; restore regs
         ldx $fc

         rts

;---------------------------------------
; find index of character in a string
; string pointer in .a,.x
; character to find in .y
; index returned in .y
; .c set if not found
;---------------------------------------
instr
         sta $fb      ; set up pointer
         stx $fc

         sty $02      ; store char
         ldy #$00     ; init index

ins1
         lda ($fb),y
         beq ins3     ; terminator

         cmp $02
         beq ins4     ; found it

         iny
         bne ins1     ; keep looping
ins3
         sec          ; not found
         jmp ins2
ins4
         clc          ; found
ins2
         lda $fb      ; restore regs
         ldx $fc
         rts

