         *= $0800

;---------------------------------------
; lissajous curve
;---------------------------------------

;---------------------------------------
; definitions
;---------------------------------------
storeflt = $bbd4 ; store fac#1 to mem.
loadflt  = $bba2 ; load fac#1 from mem.
conupk   = $ba8c ; load fac#2 from mem.
fltadd   = $b86a ; float pt. add
fltmult  = $ba2b ; float pt. mult.
fltand   = $afe9 ; float pt. and
fltor    = $afe6 ; float pt. or
fltnot   = $aed4 ; float pt. not
fltxfer  = $bc0c ; copy fac#1 fac#2
byte2flt = $bc3c ; byte to float
uwrd2flt = $bc49 ; unsig. word to float
givayf   = $b391 ; 16-bit int to float
qint     = $bc9b ; float to unsigned int
fout     = $bddd ; float to string
strout   = $ab1e ; print string
sin      = $e26b ; sin(x)
chrout   = $ffd2 ; print char
linprt   = $bdcd ; print int
pi2      = $e2e0 ; constant pi / 2
fac1exp  = $61   ; fac#1 exponent
fac1mant = $62   ; fac#1 mantissa
vmcsb    = $d018 ; vic memory control
scroly   = $d011 ; vic scroll reg.
bbitmap  = $2000 ; bitmap begin
ebitmap  = $3f3f ; bitmap end
bcolor   = $0400 ; color begin
ecolor   = $07e7 ; color end

;---------------------------------------
; basic program
;---------------------------------------
         .byte $00    ; begin basic prg
         .byte <nextl ; next link
         .byte >nextl
         .byte $00    ; line #
         .byte $00
         .byte $9e    ; sys token
         .text "2061" ; $80d
         .byte $00    ; end of line
nextl    .byte $00    ; end of program
         .byte $00
;---------------------------------------
         jmp start    ; must be @ $80d
;---------------------------------------

;---------------------------------------
; storage
;---------------------------------------
alpha    .byte $09
beta     .byte $08
tau      .byte $00,$00,$00,$00,$00
tmp      .byte $00,$00,$00,$00,$00
ival     .byte $79,$00,$00,$00,$00
xval     .word $00
yval     .word $00
by       .word $00
xfac     .byte $a0
yfac     .byte $64

;---------------------------------------
; code
;---------------------------------------
start
         lda vmcsb    ; put bitmap
         ora #$08     ; at $2000
         sta vmcsb

         lda scroly   ; enable bitmap
         ora #$20     ; mode
         sta scroly

         jsr clearbm  ; clear bitmap
         jsr colorbm  ; color bitmap

         lda #$00     ; tau = 0
         jsr byte2flt ; store to fac#1
         ldx #<tau    ; store fac#1 to
         ldy #>tau    ; tau
         jsr storeflt

l4
         lda #$80     ; check stop key
         bit $91
         beq l5

         jsr calcx    ; calculate x
         jsr calcy    ; calculate y
         jsr calcby   ; calculate byte
         jsr plot     ; plot x, y
         jsr next     ; tau=tau+ival
         jmp l4
l5
         lda scroly   ; disable bitmap
         and #$df     ; mode
         sta scroly

         lda vmcsb    ; character dot
         and #$f7     ; data at $1000
         sta vmcsb

         lda #$93     ; clear screen
         jsr chrout

         rts

;---------------------------------------
; clear bitmap area
;---------------------------------------
clearbm
         lda #<bbitmap
         sta $fb
         lda #>bbitmap
         sta $fc

         lda #<ebitmap
         sta $fd
         lda #>ebitmap
         sta $fe

         ldx #$00
         jsr fillblock

         rts

;---------------------------------------
; color bitmap
;---------------------------------------
colorbm
         lda #<bcolor
         sta $fb
         lda #>bcolor
         sta $fc

         lda #<ecolor
         sta $fd
         lda #>ecolor
         sta $fe

         ldx #$6f
         jsr fillblock

         rts

;---------------------------------------
; fill a memory block with a byte
;
; start address in $fb,$fc
; end address in $fd, $fe
; byte in .x
; $02 used for comparison
;---------------------------------------
fillblock
         ldy #$00

l1       txa
         sta ($fb),y

         clc           ; compare
         lda $fb
         sta $02
         tya
         adc $02

         sec
         sbc $fd
         sta $02

         lda $fc
         sbc $fe
         ora $02
         beq l3

         iny
         clc
         lda $fb
         sta $02
         tya
         adc $02
         beq l2
         bne l1

l2       lda #$00     ; next page
         sta $fb
         inc $fc
         jmp l1

l3       rts

;---------------------------------------
; calculate x value
;---------------------------------------
calcx
         lda #<tau    ; load tau to
         ldy #>tau    ; fac#1
         jsr loadflt

         jsr fnx      ; call x(t)
         jsr fltxfer  ; xfer to fac#2

         lda xfac     ; mult. by x
         jsr ubyt2flt ; x factor
         jsr multf

         jsr fltxfer  ; xfer to fac#2

         lda xfac     ; add x factor
         jsr ubyt2flt
         jsr addf

         jsr flt2int  ; convert to
                      ; unsigned
                      ; integer

         stx xval
         sta xval+1

         rts

;---------------------------------------
; calculate y value
;---------------------------------------
calcy
         lda #<tau    ; load tau to
         ldy #>tau    ; fac#1
         jsr loadflt

         jsr fny      ; call y(t)
         jsr fltxfer  ; xfer to fac#2

         lda yfac     ; mult. by
         jsr ubyt2flt ; yfactor
         jsr multf

         jsr fltxfer  ; xfer to fac#2

         lda yfac     ; add y factor
         jsr ubyt2flt

         jsr addf

         jsr flt2int  ; convert to
                      ; unsigned
                      ; integer
         stx yval
         sta yval+1

         rts

;---------------------------------------
; calculate byte based on x, y
;
; by = base+40*(y and 248)+(y and 7)
;      +(x and 504)
;---------------------------------------
calcby
         lda xval+1    ; store hi byte
         sta fac1mant  ; to fac#1
                       ; mantissa
         lda xval      ; store lo byte
         sta fac1mant+1
         jsr uword2flt ; convert to
                       ; float

         jsr fltxfer   ; xfer to fac#2

         lda #$01      ; 504
         ldy #$f8
         jsr givayf    ; convert to
                       ; float

         jsr fltand    ; and them

         ldx #<tmp     ; store to tmp
         ldy #>tmp
         jsr storeflt

         lda yval+1    ; store hi byte
         sta fac1mant  ; to fac#1
                       ; mantissa
         lda yval      ; store lo byte
         sta fac1mant+1
         jsr uword2flt ; convert to
                       ; float

         jsr fltxfer   ; xfer to fac#2

         lda #$07      ; 7
         jsr byte2flt  ; convert to
                       ; float
         jsr fltand    ; and them

         lda #<tmp     ; load fac#2 from
         ldy #>tmp     ; tmp
         jsr conupk

         jsr addf      ; add the results

         ldx #<tmp     ; store to tmp
         ldy #>tmp
         jsr storeflt

         lda yval+1    ; store hi byte
         sta fac1mant  ; to fac#1
                       ; mantissa
         lda yval      ; store lo byte
         sta fac1mant+1
         jsr uword2flt ; convert to
                       ; float

         jsr fltxfer   ; xfer to fac#2

         lda #$f8      ; 248
         jsr ubyt2flt  ; convert to
                       ; float

         jsr fltand    ; and them

         jsr fltxfer   ; xfer to fac#2

         lda #$28      ; 40
         jsr byte2flt  ; convert to
                       ; float

         jsr multf     ; multiply them

         lda #<tmp     ; load fac#2 from
         ldy #>tmp     ; tmp
         jsr conupk

         jsr addf      ; add them

         jsr fltxfer   ; xfer to fac#2

         lda #>bbitmap ; convert base
         ldy #<bbitmap ; address to
         jsr givayf    ; float

         jsr addf      ; add them

         jsr flt2int   ; unsigned
                       ; integer
         stx by
         sta by+1

         rts

;---------------------------------------
; plot point in x, y on hi-res screen
;---------------------------------------
plot
         lda xval+1    ; store hi byte
         sta fac1mant  ; to fac#1
                       ; mantissa
         lda xval      ; store lo byte
         sta fac1mant+1
         jsr uword2flt ; convert to
                       ; float

         jsr fltnot    ; not(x)
         jsr fltxfer   ; xfer to fac#2

         lda #$07      ; 7
         jsr byte2flt  ; convert to
                       ; float
         jsr fltand    ; and them

         jsr flt2int   ; convert to
                       ; unsigned
                       ; integer

         lda #$01      ; power of 2
         cpx #$00      ; lsb in .x
         beq l7
l6
         asl a
         dex
         bne l6
l7
         jsr ubyt2flt  ; convert to
                       ; float
         jsr fltxfer   ; xfer to fac#2

         lda by
         sta $fb
         lda by+1
         sta $fc

         ldy #$00
         lda ($fb),y

         jsr ubyt2flt  ; convert to
                       ; float

         jsr fltor     ; or them
         jsr flt2int   ; convert to
                       ; unsigned
                       ; integer
                       ; lo byte in .x
         lda by
         sta $fb
         lda by+1
         sta $fc

         ldy #$00
         txa
         sta ($fb),y

         rts

;---------------------------------------
; tau = tau + ival
; ival is defined to be 2^(-8)
; or approximately 0.00390625
;---------------------------------------
next
         lda #<tau    ; load tau to
         ldy #>tau    ; fac#1
         jsr loadflt
         jsr fltxfer  ; xfer fac#1 to
                      ; fac#2

         lda #<ival   ; load ival to
         ldy #>ival   ; fac#1
         jsr loadflt

         jsr addf     ; add them

         ldx #<tau    ; store fac#1 to
         ldy #>tau    ; tau
         jsr storeflt

         rts

;---------------------------------------
; convert fac#1 to unsigned 16-bit
; integer.  unsigned integer returned
; in .a, .x
;---------------------------------------
flt2int
         jsr qint       ; convert to
                        ; integer
         lda fac1mant+2 ; msb mantissa
         ldx fac1mant+3 ; lsb mantissa
         rts

;---------------------------------------
; convert unsigned word to float
; msb of word in fac#1 mantissa
; lsb of word in fac#1 mantissa+1
;---------------------------------------
uword2flt
         ldx #$90     ; setting the
                      ; exponent to
                      ; $90 places the
                      ; binary point to
                      ; the right of
                      ; the least
                      ; significant bit
                      ; of this integer
                      ; making it a
                      ; whole number
         sec          ; treat int as
                      ; unsigned
         jsr uwrd2flt ; store in fac#1
         rts

;---------------------------------------
; convert unsigned byte in a. to float
;---------------------------------------
ubyt2flt
         sta fac1mant+1 ; store lo byte
         lda #$00       ; store hi byte
         sta fac1mant
         jsr uword2flt
         rts

;---------------------------------------
; print fac#1
;---------------------------------------
fltprnt
         jsr fout     ; convert fac#1
                      ; to a string
                      ; in .a, .y
         jsr strout   ; print it

         lda #$0d     ; print newline
         jsr chrout

         rts

;---------------------------------------
; print int in .a, .x
;---------------------------------------
intprnt
         jsr linprt
         lda #$0d
         jsr chrout

         rts

;---------------------------------------
; x(t) = sin(a*t+d)
; t is in fac#1
;---------------------------------------
fnx
         jsr fltxfer  ; xfer to fac#2

         lda alpha    ; load alpha to
         jsr byte2flt ; fac#1

         jsr multf    ; multiply them
         jsr fltxfer  ; xfer to fac#2

         lda #<pi2    ; load delta to
         ldy #>pi2    ; fac#1
         jsr loadflt

         jsr addf     ; add them

         jsr sin      ; call sin(x)

         rts

;---------------------------------------
; y(t) = sin(b*t)
; t is in fac#1
;---------------------------------------
fny
         jsr fltxfer  ; xfer to fac#2

         lda beta     ; load beta to
         jsr byte2flt ; fac#1

         jsr multf    ; multiply them

         jsr sin      ; call sin(x)

         rts

;---------------------------------------
; mult fac#1 by fac#2
;---------------------------------------
multf
         jsr sgncmp
         lda fac1exp
         jsr fltmult
         rts

;---------------------------------------
; add fac#1 to fac#2
;---------------------------------------
addf
         jsr sgncmp
         lda fac1exp
         jsr fltadd
         rts

;---------------------------------------
; setup sign compare
;---------------------------------------
sgncmp
         lda $66      ; setup sign
         eor $6e      ; compare
         sta $6f
         rts

