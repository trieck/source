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
length      = $41

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
        cmp #$49        ; is it "i"?
        beq me2         ; initialize
        cmp #$4c        ; is it "l"?
        beq me3          ; listing
        cmp #$4d        ; is it "m"?
        beq me4         ; memory dump
        cmp #$56        ; is it "v"?
        beq me5         ; validate
        cmp #$2a        ; is it "*"?
        beq me6         ; directory
        cmp #$58        ; is it "x"?
        beq end
        jmp me1
me2     jmp initd       ; initialize
me3     jmp list        ; listing
me4     jmp dump        ; memory dump
me5     jmp valid       ; validate disk
me6     jmp dir         ; directory
        jmp prmenu      ; menu
end
        jmp warmbas     ; basic warm start

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
