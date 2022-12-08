;
; vicpencil.asm
;
; The "VIC Pencil" for the expanded VIC-20
;
        *= $1200

status      = $90
rvs         = $c7
pntr        = $d3
garbfl      = $0f

format      = $40
length      = $41
lmnem       = $42
rmnem       = $43
pcl         = $44
pch         = $45

prtstr      = $cb1e
prtfix      = $ddcd
warmbas     = $e467
cclrch      = $ffcc
kmsgshow    = $f1e6
reslst      = $c09e
tbuffer     = $033c

;---------------------------------------
; basic program declaration
;---------------------------------------
        .byte $00       ; begin basic prg
        .byte <nextl    ; next link
        .byte >nextl
        .byte $00       ; line #
        .byte $00
        .byte $9e       ; sys token
        .text '4621'    ; $120d
        .byte $00       ; end of line

nextl  
        .byte $00       ; end of program
        .byte $00 

        jmp start       ; must be @ $120d

;---------------------------------------
; data declarations
;---------------------------------------
title
        .text 'vic pencil'
        .byte $0d
        .byte $0d
        .byte $0
menu   
        .text 'a - assembler'
        .byte $0d
        .text 'd - disassemble mem'
        .byte $0d
        .text 'f - disassemble file'
        .byte $0d
        .text 'i - initialize drive'
        .byte $0d
        .text 'l - list program'
        .byte $0d
        .text 'm - view/edit memory'
        .byte $0d
        .text 'r - read disk block'
        .byte $0d
        .text 'v - validate disk'
        .byte $0d
        .text '* - directory'
        .byte $0d
        .ztext 'x - exit'

m1      .ztext 'initializing...'
m2      .ztext 'validating...'
m6      .ztext 'start:'
m7      .ztext 'end  :'
m8      .ztext 'filename:'

dprmpt  .ztext 'drive:'
prspc   .ztext 'press space'

dirname  .text '$0'
dirlen   = *-dirname

initnm   .text 'i0'
initlen  = *-initnm

valname  .text 'v0'
vallen   = *-valname

drive   .byte $08       ; current drive#
cols    .byte $0        ; number of columns
rows    .byte $0        ; number of rows
filenum .byte $01       ; open file number

saddr   .word $0000     ; start addr.
daddr   .word $0000     ; dest. addr.

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
        .text ',),#($'
char2
        .ztext 'y'
        .ztext 'x$$'

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
        lda #$02        ; red character
        sta $0286
        lda #$19        ; white border, rvs, white background
        sta $900f
        lda #$e
        jsr $e742       ; lowercase
        lda #$8
        jsr $e742       ; dis. shft/cmdr

        jsr $e505       ; # of rows/cols
        stx cols
        sty rows

prmenu                  ; print the menu
        lda #$93        ; clear screen
        jsr chrout
        lda #<title
        ldy #>title
        jsr prtstr      ; output title

        jsr loline      ; lower line sep.

        lda #<menu
        ldy #>menu
        jsr prtstr      ; print menu

        jsr upline      ; upper line sep.

me1
        jsr getchar     ; get character
        cmp #$44        ; is it "d"?
        beq me2         ; disassemble
        cmp #$49        ; is it "i"?
        beq me3         ; initialize
        cmp #$4c        ; is it "l"?
        beq me4          ; listing
        cmp #$4d        ; is it "m"?
        beq me5         ; memory dump
        cmp #$56        ; is it "v"?
        beq me6         ; validate
        cmp #$2a        ; is it "*"?
        beq me7         ; directory
        cmp #$58        ; is it "x"?
        beq end
        jmp me1
me2     jmp disass      ; disassemble
me3     jmp initd       ; initialize
me4     jmp list        ; listing
me5     jmp dump        ; memory dump
me6     jmp valid       ; validate disk
me7     jmp dir         ; directory
        jmp prmenu      ; menu
end
        jmp warmbas     ; basic warm start

;---------------------------------------
; Disassembler
;
; Adapted from "A 6502 CPU Disassembler"
; By Steve Wozniak and Allen Baum
; Dr. Dobbs Journal, Sept. 1976
;---------------------------------------
disass
        jsr getstart    ; get start addr.
        jsr getdest     ; get dest. addr.

        lda #$93        ; clear screen
        jsr chrout

        jsr loline      ; lower line sep.
        
        lda saddr       ; set up pointers
        sta pcl
        lda saddr+1
        sta pch
        lda daddr
        sta $05
        lda daddr+1
        sta $06
dis1
        lda $028d       ; check for shift
        bne dis1
        lda $91         ; check for stop
        cmp #$fe
        beq dis2

        jsr instdsp
        jsr pcadj
        sta pcl
        sty pch
        jsr prnret

        lda pch         ; compare high
        cmp $06         ; bytes
        bcc dis1        ; pch < ($06)
        bne dis2        ; pch > ($06)

        lda pcl         ; compare low
        cmp $05         ; bytes
        bcc dis1        ; pcl < ($05)
        beq dis1        ; pcl = ($05)
dis2
        jsr upline      ; upper line sep.

        jsr waitsp      ; wait for space
        jmp prmenu      ; memory menu

scrn2
        bcc rtmskz      ; if even, use
                        ; lo half
        lsr
        lsr
        lsr
        lsr
rtmskz
        and #$0f        ; mask 4-bits
        rts
insds1
        ldx pcl         ; print pcl,h
        ldy pch
        jsr pryx2

        lda #$00
        sta rvs
        
        ldx #$0
        lda (pcl,x)     ; get opcode
insds2
        tay
        lsr             ; even/odd test
        bcc ieven
        ror             ; bit 1 test
        bcs err         ; xxxxxx11 invalid
                        ; opcode
        and #$87        ; mask bits
                        ; 10000111 for
                        ; addr. mode
ieven
        lsr             ; lsb into carry
                        ; for l/r test
        tax
        lda fmt1,x      ; get format index
                        ; byte
        jsr scrn2       ; r/l h-byte on
                        ; carry
        bne getfmt
err
        ldy #$80        ; substitute $80
                        ; for invalid ops
        lda #$00        ; set print format
                        ; index to 0
getfmt
        tax
        lda fmt2,x      ; index into print
                        ; format table
        sta format      ; save for adr
                        ; field formatting
        and #$03        ; mask for 2-bit
                        ; length
                        ; 0=1 byte, 1=2
                        ; byte, 2=3 byte
        sta length
        tya             ; opcode
        and #$8f        ; mask for
                        ; 1xxx1010 test
        tax             ; save it
        tya             ; opcode to .a
        ldy #$03
        cpx #$8a
        beq mnndx3
mnndx1
        lsr
        bcc mnndx3      ; form index into
                        ; mnemonic table
        lsr
mnndx2
        lsr             ; 1) 1XXX1010 =>
        ora #$20        ;     00101XXX
        dey             ; 2) XXXYYY01 =>
        bne mnndx2      ;     00111XXX
        iny             ; 3) XXXYYY10 =>
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
        jsr insds1      ; get format, len
                        ; bytes
        pha             ; save mnemonic
                        ; table index        
prntop
        lda rvs         ; toggle reverse
        eor #$1
        sta rvs

        lda (pcl),y

        jsr hexbyte
        cpy length      ; print inst
                        ; (1-3 bytes)
        iny             ; in a 12 char.
                        ; field
        bcc prntop

        lda #$0
        sta rvs
prntbl2
        iny             ; char count for
        cpy #$04        ; mnemonic print
        bcs prntbl3

        ldx# $02
        jsr prbl2
        bcc prntbl2

prntbl3
        ldx #$03
        pla             ; recover mnemonic
                        ; index
        tay
        lda mneml,y
        sta lmnem       ; fetch 3-char
                        ; mnemonic
        lda mnemr,y     ; (packed in 2
                        ; bytes)
        sta rmnem

prmn1
        lda #$00
        ldy #$05
prmn2
        asl rmnem       ; shift 5 bits
        rol lmnem       ; of character
        rol             ; into .a
                        ; (clears carry)
        dey
        bne prmn2
        adc #$3f        ; add "?" offset


        jsr chrout      ; output a char
                        ; of mnem.
        dex
        bne prmn1

        ldy length
        ldx #$06        ; cnt for 6 format
                        ; bits
pradr1
        cpx #$03
        beq pradr5      ; if x=3 then addr
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
        cmp #$e8        ; handle rel adr
                        ; mode
        lda (pcl),y     ; special (print
                        ;  target not
        bcc pradr4      ;  offset)
reladr
        jsr pcadj3
        tax             ; pcl,pch+offset
                        ; +1 to a,y
        inx
        bne prntyx      ; +1 to y,x
        iny
prntyx
        tya
prntax
        jsr hexbyte     ; output target
                        ; adr of branch
                        ; and return
prntx
        txa
        jmp hexbyte
prblnk
        ldx #$01        ; blank count
prbl2
        lda #$20        ; load a space
prbl3
        jsr chrout
        dex
        bne prbl2       ; loop until
                        ; count=0
        rts
pcadj
        sec             ; 0=1-byte
pcadj2                  ; 1=2-byte
        lda length      ; 2=3-byte
pcadj3
        ldy pch
        tax             ; test displacment
                        ; sign
        bpl pcadj4      ; for rel branch
        dey             ; extend neg by
                        ; decr pch
pcadj4
        adc pcl      
        bcc rts2        ; pcl+length
                        ; (or displ)+1
                        ; to a
        iny             ; carry into y
                        ; (pch)
rts2
        rts

pryx2
        jsr prntyx
        lda #$3a        ; print :
        jmp chrout

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

        lsr
        lsr
        lsr
        lsr
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
; lower line separator
;---------------------------------------
loline
        jsr prnret      ; print return

        lda #$b9        ; lower line sep.
        ldx cols        ; # of cols.

ll1
         jsr chrout     ; print sep.
         dex
         bne ll1

         rts

;---------------------------------------
; upper line separator
;---------------------------------------
upline
         jsr prnret     ; print return

         lda #$b8       ; upper line sep.
         ldx cols       ; # of cols.
ul1
         jsr chrout     ; print sep.
         dex
         bne ul1
         rts

;---------------------------------------
; print return conditionally
;---------------------------------------
prnret
        lda $d7         ; last character printed

        cmp #$0d        ; is it return?
        beq pr1

        lda #$0d        ; print return
        jsr chrout
pr1
        rts

;---------------------------------------
; check for hex digit in .a
; index stored to .y
;---------------------------------------
ishex
        pha             ; save char

        cmp #$30        ; < 48
        bcc ih2

        cmp #$3a        ; < 58
        bcc ih1

        cmp #$41        ; < 65
        bcc ih2

        cmp #$47        ; < 71
        bcs ih2

ih1
        sec             ; hex digit
        sbc #$30        ; store idx to .y
        cmp #$11
        bcc ih4
        sbc #$07
ih4
        tay
        clc
        jmp ih3
ih2
        sec             ; non-hex
ih3
        pla             ; restore char
        rts

;---------------------------------------
; get starting address
;---------------------------------------
getstart                ; get start addr.
        lda #$0d
        jsr chrout      ; print return
        lda #<m6
        ldy #>m6
        jsr prtstr      ; print m6

        lda #$00        ; reinitialize
        sta saddr
        sta saddr+1

        lda #<saddr     ; set up pointer
        ldx #>saddr
        jsr getaddr

        rts

;---------------------------------------
; get destination address
;---------------------------------------
getdest                 ; get dest. addr.
        lda #$0d
        jsr chrout      ; print return
        lda #<m7
        ldy #>m7
        jsr prtstr      ; print m7

        lda #$00        ; reinitialize
        sta daddr
        sta daddr+1

        lda #<daddr     ; set up pointer
        ldx #>daddr
        jsr getaddr

        rts

;---------------------------------------
; get address
; address to store is in .a, .x
;---------------------------------------
getaddr                 ; get address

        sta $fb         ; store pointer
        stx $fc

        lda #$30        ; initialize to
        jsr chrout      ; zeros
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
        jsr chrout      ; print it

        tya             ; index of char
        asl             ; multiply by 16
        asl             ; for hi-nybble
        asl
        asl

        ldy #$01        ; hi-byte
        sta ($fb),y     ; store hi-nybble
ga2
        jsr getchar
        cmp #$0d        ; is it return
        beq gadone
        jsr ishex
        bcs ga2
        jsr chrout      ; print it

        tya             ; index of char
        ldy #$01        ; hi-byte
        ora ($fb),y     ; store lo-nybble
        sta ($fb),y     ; of hi-byte
ga3
        jsr getchar
        cmp #$0d        ; is it return
        beq gadone
        jsr ishex
        bcs ga3
        jsr chrout      ; print it

        tya             ; index of char
        asl             ; multiply by 16
        asl             ; for hi-nybble
        asl
        asl
        ldy #$00        ; lo-byte
        sta ($fb),y

ga4
        jsr getchar
        cmp #$0d        ; is it return
        beq gadone
        jsr ishex
        bcs ga4
        jsr chrout      ; print it

        tya             ; index of char
        ldy #$00        ; lo-byte
        ora ($fb),y     ; store lo-nybble
        sta ($fb),y     ; of lo-byte
gabk
        lda #$9d        ; bkspace
        jsr chrout
        jsr chrout
        jsr chrout
        jsr chrout
        jmp ga1

gadone
        lda $fb         ; restore pointer
        ldx $fc
        rts

;---------------------------------------
; get character from keyboard
; and blink the cursor
;---------------------------------------
getchar
        lda #$0
        sta $cc         ; turn on cursor
        lda $c6         ; number of characters in the keyboard buffer
        beq getchar

        lda #$1         ; turn off the cursor
        sta $cc

        lda $cf         ; check blink status
        beq gc1         ; get if non-reversed

        lda #$0         ; set blink status to non-reversed
        sta $cf

        ldy $d3         ; cursor position within logical line
        lda $ce         ; character under cursor
        sta ($d1), y    ; store .A to current screen line

        lda $287        ; color of character under cursor
        sta ($f3), y    ; store .A to current physical line color map

gc1
        jsr getin       ; get character
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
        jsr getchar
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
; validate a disk
;---------------------------------------
valid
         jsr getdrive   ; get drive

         jsr loline     ; lower line sep.

         lda #<m2
         ldy #>m2
         jsr prtstr     ; print m2

         lda #<vallen   ; len. of filename
         ldx #<valname  ; filename
         ldy #>valname
         jsr cmdopen2   ; open cmd. ch.
         bcc valclean
valio
         jsr ioerr      ; drive i/o error

valclean
         jsr cmdclose   ; close cmd. ch.

         jsr upline     ; upper line sep.

         jsr waitsp     ; wait for space
         jmp prmenu     ; file menu

;---------------------------------------
; initialize a drive
;---------------------------------------
initd
         jsr getdrive   ; get drive

         jsr loline     ; lower line sep.

         lda #<m1
         ldy #>m1
         jsr prtstr     ; print m1

         lda #<initlen  ; len. of filename
         ldx #<initnm   ; filename
         ldy #>initnm
         jsr cmdopen2   ; open cmd. ch.
         bcc initclean
initio
         jsr ioerr      ; drive i/o error

initclean
         jsr cmdclose   ; close cmd. ch.

         jsr upline     ; upper line sep.

         jsr waitsp     ; wait for space
         jmp prmenu     ; menu

;---------------------------------------
; directory
;---------------------------------------
dir                     ; directory
        jsr getdrive    ; get drive
        lda #$93        ; clear screen
        jsr chrout
        jsr loline      ; lower line sep.

        jsr cmdopen     ; open cmd. ch.
        bcc dir2
dir3
        jmp dirio       ; i/o error
dir2
        lda #<dirlen    ; len. of file
        ldx #<dirname   ; filename
        ldy #>dirname
        jsr fopen
        bcc dir4
        jmp dirio       ; i/o error
dir4
        ldx filenum     ; file number
        jsr chkin       ; open channel

        jsr chrin       ; discard load
        jsr chrin       ; address
        lda status      ; check status
        bne direrr
dir6
        jsr chrin       ; discard line
        jsr chrin       ; link
        jsr chrin       ; retrieve number
                        ; of blocks used
        sta $fc         ; store to zero
        jsr chrin       ; page in low,
                        ; high format
        sta $fb        
        lda status      ; read i/o status
        bne dirclean    ; eof
        lda $fb         ; retrieve number
        ldx $fc         ; of blocks
        jsr prtfix      ; output int in
                        ; .a, .x
        lda #$20        ; print space
        jsr chrout      ; after blocks

        jsr chrin
dir7
        jsr chrout

dir8    lda $028d       ; check for shift
        bne dir8
        jsr stop        ; check for stop
        beq dirclean
        jsr chrin
        bne dir7
        lda #$0d
        jsr chrout     ; print return
        jmp dir6
direrr
        jsr diskerr    ; print disk error
        jmp dirclean

dirio
        jsr ioerr     ; drive i/o error
dirclean
        jsr fclose    ; close file
        jsr cmdclose  ; close cmd. ch.

        jsr upline    ; upper line sep.

        jsr waitsp    ; wait for space
        jmp prmenu    ; menu

;---------------------------------------
; memory dump
;---------------------------------------
dump                    ; memory dump
        jsr getstart    ; get start addr.
        jsr getdest     ; get dest. addr.

        lda #$93        ; clear screen
        jsr chrout

        jsr loline      ; lower line sep.

du1
        lda saddr       ; set up pointers
        sta $03
        lda saddr+1
        sta $04
        lda daddr
        sta $05
        lda daddr+1
        sta $06

        ldy #$00        ; init. index
        sty $07         ; new line counter
du2
        lda $028d       ; check for shift
        bne du2
        jsr stop        ; check for stop
        beq du4

        lda $07         ; check nl counter
        bne du3

        lda $03         ; print line
        sta $02
        tya
        ora $02
        tax

        lda $04
        jsr hexint

        lda #$3a        ; print :
        jsr chrout

        lda #$20        ; print space
        jsr chrout

        lda #$00
        sta rvs         ; init reverse
du3
        lda ($03),y     ; print byte
        jsr hexbyte

        lda rvs         ; toggle reverse
        eor #$1
        sta rvs

        clc             ; compare
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
        beq du4         ; done

        iny             ; next byte
        inc $07         ; increment
        lda $07         ; new line counter
        cmp #$08        ; 8 bytes per
        bne du5         ; line

        lda #$00        ; reset new line
        sta $07         ; counter
du5
        clc
        lda $03
        sta $02
        tya
        adc $02
        beq du7
        jmp du2
du7

        lda #$00        ; next page
        sta $03
        inc $04
        jmp du2
du4
        jsr upline      ; upper line sep.

        jsr waitsp      ; wait for space
        jmp prmenu      ; memory menu

;---------------------------------------
; list a program
;---------------------------------------
list                    ; list a program
        jsr getdrive    ; get drive
        jsr chrout      ; print return

        lda #<m8
        ldy #>m8
        jsr prtstr      ; print m8

        lda #<tbuffer   ; get filename
        ldx #>tbuffer
        jsr getstr

        lda #$93        ; clear screen
        jsr chrout

        lda #$00
        sty garbfl      ; init quote mode

        jsr loline      ; lower line sep.

        jsr cmdopen     ; open cmd. ch.
        bcc l7
        jmp lio         ; i/o error
l7
        lda length      ; len. of file
        ldx #<tbuffer   ; filename
        ldy #>tbuffer
        jsr fopen       ; open file
        bcc l9
l8
        jmp lio         ; i/o error
l9
        ldx filenum     ; file number
        jsr chkin       ; open channel
        jsr chrin       ; discard load
        jsr chrin       ; address
        lda status      ; check status
        beq l10
        jmp lerr
l10
        ldx $028d       ; check for shift
        bne l10
        ldx $91         ; check for stop
        cpx #$fe
        bne l23
        jmp lclean
l23
        jsr chrin       ; line link
        sta $fb
        jsr chrin
        ora $fb
        bne l22
        jmp lclean      ; no more lines
l22
        jsr chrin       ; line #
        tax
        jsr chrin
        jsr prtfix      ; print line #

        lda #$20        ; print space
        jsr chrout
l12
        lda status
        bne lclean      ; eof

        jsr chrin       ; read token or
                        ; character

        beq l15         ; end of line
        bpl l14         ; character

        bit garbfl      ; quote mode
        bmi l14

        cmp #$ff
        beq l14

        sec             ; keyword
        sbc #$7f        ; table offset+1
        tax
        ldy #$ff
l16
        dex             ; traverse table
        beq l18         ; print keyword
l17
        iny             ; read keyword
        lda reslst,y
        bpl l17
        bmi l16
l18                     ; print keyword
        iny
        lda reslst,y
        bmi l19
        jsr chrout
        bne l18
l19
        and #$7f        ; strip high bit
l14
        jmp lprint      ; print character
l15
        lda #$00        ; end of line
        sta garbfl      ; turn off quote

        lda #$0d        ; print new line
        jsr chrout
        jmp l10
lprint
        cmp #$a2        ; shifted-quote
        beq l21

        jsr isprnt      ; only print
        bcc l21         ; non-printable
        ldx garbfl      ; chars in quote
        bpl l12         ; mode
l21
        jsr chrout      ; print it

        and #$7f
        cmp #$22        ; is it quote?
        bne l12
l20
        lda garbfl      ; toggle quote
        eor #$ff        ; mode
        sta garbfl
        jmp l12
lerr
        jsr diskerr     ; print disk error
        jmp lclean
lio
        jsr ioerr       ; drive i/o error
lclean
        jsr fclose      ; close file
        jsr cmdclose    ; close cmd. ch.

        jsr upline      ; upper line sep.

        jsr waitsp      ; wait for space
        jmp prmenu      ; menu

;---------------------------------------
; get drive
;---------------------------------------
getdrive                ; get drive
        lda #$0d
        jsr chrout      ; print return

        lda #<dprmpt    ; drive prompt
        ldy #>dprmpt
        jsr prtstr
gd1
        lda drive
        cmp #$0a
        bcs gd2         ; drive >= 10
        lda #$00
        ldx #$00
        jsr prtfix      ; output lead 0

gd2
        lda #$00        ; high byte
        ldx drive       ; lo byte
        jsr prtfix      ; output integer
        lda #$9d
        jsr chrout      ; backup twice
        jsr chrout
gd3
        jsr getchar     ; get char
        cmp #$11        ; is it cr. down?
        beq gd4
        cmp #$0d        ; is it return?
        beq gd5
        jmp gd3
gd4
        inc drive       ; next drive
        lda drive
        cmp #$0c
        bcc gd1         ; drive < 12
        lda #$08
        sta drive       ; reset drive #
        jmp gd1
gd5
        rts

;---------------------------------------
; wait for space
;---------------------------------------
waitsp                  ; wait for space
        lda #$01
        sta $c7         ; enable rev.
        lda #<prspc
        ldy #>prspc
        jsr prtstr
        lda #$00
        sta $c7         ; disable rev.

wsp1     
        jsr getin
        cmp #$20        ; space
        bne wsp1
        rts

;---------------------------------------
; disk error
;---------------------------------------
diskerr
        ldx #$0f        ; open channel
        jsr chkin       ; for input
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
        ldy #$01        ; move past cr.
        pha
        jsr kmsgshow    ; print i/o err.#
        pla
        ora #$30        ; make err. ascii
        jsr chrout      ; print it
        rts

;---------------------------------------
; open command channel
;---------------------------------------
cmdopen
        lda #$00        ; len. of file
        jsr setnam      ; set filename
        lda #$0f        ; command channel
        ldx drive       ; device number
        tay             ; secondary addr.
        jsr setlfs      ; set file params
        jsr open        ; open
        rts

;---------------------------------------
; open command channel
; .a,.x,.y set for filename
;---------------------------------------
cmdopen2
        jsr setnam      ; set filename
        lda #$0f        ; command channel
        ldx drive       ; device number
        tay             ; secondary addr.
        jsr setlfs      ; set file params.
        jsr open        ; open
        rts

;---------------------------------------
; open file
; length of filename in .a
; lsb of filename in .x
; msb of filename in .y
;---------------------------------------
fopen
        jsr setnam      ; set filename
        lda filenum     ; file number
        ldx drive       ; device number
        ldy #$00        ; secondary addr.
        jsr setlfs      ; set file params
        jsr open        ; open file
        rts

;---------------------------------------
; close file
;---------------------------------------
fclose
        lda filenum
        jsr close       ; close file
        rts

;---------------------------------------
; close command channel
;---------------------------------------
cmdclose
        lda #$0f        ; close command
        jsr close       ; channel
        jsr cclrch      ; close channels
        rts
