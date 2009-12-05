         *= $0800;---------------------------------------; LISSAJOUS CURVE;---------------------------------------;---------------------------------------; DEFINITIONS;---------------------------------------STOREFLT = $BBD4 ; STORE FAC#1 TO MEM.LOADFLT  = $BBA2 ; LOAD FAC#1 FROM MEM.CONUPK   = $BA8C ; LOAD FAC#2 FROM MEM.FLTADD   = $B86A ; FLOAT PT. ADDFLTMULT  = $BA2B ; FLOAT PT. MULT.FLTAND   = $AFE9 ; FLOAT PT. ANDFLTOR    = $AFE6 ; FLOAT PT. ORFLTNOT   = $AED4 ; FLOAT PT. NOTFLTXFER  = $BC0C ; COPY FAC#1 FAC#2BYTE2FLT = $BC3C ; BYTE TO FLOATUWRD2FLT = $BC49 ; UNSIG. WORD TO FLOATGIVAYF   = $B391 ; 16-BIT INT TO FLOATQINT     = $BC9B ; FLOAT TO UNSIGNED INTFOUT     = $BDDD ; FLOAT TO STRINGSTROUT   = $AB1E ; PRINT STRINGSIN      = $E26B ; SIN(X)CHROUT   = $FFD2 ; PRINT CHARLINPRT   = $BDCD ; PRINT INTPI2      = $E2E0 ; CONSTANT PI / 2FAC1EXP  = $61   ; FAC#1 EXPONENTFAC1MANT = $62   ; FAC#1 MANTISSAVMCSB    = $D018 ; VIC MEMORY CONTROLSCROLY   = $D011 ; VIC SCROLL REG.BBITMAP  = $2000 ; BITMAP BEGINEBITMAP  = $3F3F ; BITMAP ENDBCOLOR   = $0400 ; COLOR BEGINECOLOR   = $07E7 ; COLOR END;---------------------------------------; BASIC PROGRAM;---------------------------------------         .BYTE $00    ; BEGIN BASIC PRG         .BYTE <NEXTL ; NEXT LINK         .BYTE >NEXTL         .BYTE $00    ; LINE #         .BYTE $00         .BYTE $9E    ; SYS TOKEN         .TEXT "2061" ; $80D         .BYTE $00    ; END OF LINENEXTL    .BYTE $00    ; END OF PROGRAM         .BYTE $00;---------------------------------------         JMP START    ; MUST BE @ $80D;---------------------------------------;---------------------------------------; STORAGE;---------------------------------------ALPHA    .BYTE $09BETA     .BYTE $08TAU      .BYTE $00,$00,$00,$00,$00TMP      .BYTE $00,$00,$00,$00,$00IVAL     .BYTE $79,$00,$00,$00,$00XVAL     .WORD $00YVAL     .WORD $00BY       .WORD $00XFAC     .BYTE $A0YFAC     .BYTE $64;---------------------------------------; CODE;---------------------------------------START         LDA VMCSB    ; PUT BITMAP         ORA #$08     ; AT $2000         STA VMCSB         LDA SCROLY   ; ENABLE BITMAP         ORA #$20     ; MODE         STA SCROLY         JSR CLEARBM  ; CLEAR BITMAP         JSR COLORBM  ; COLOR BITMAP         LDA #$00     ; TAU = 0         JSR BYTE2FLT ; STORE TO FAC#1         LDX #<TAU    ; STORE FAC#1 TO         LDY #>TAU    ; TAU         JSR STOREFLTL4         LDA #$80     ; CHECK STOP KEY         BIT $91         BEQ L5         JSR CALCX    ; CALCULATE X         JSR CALCY    ; CALCULATE Y         JSR CALCBY   ; CALCULATE BYTE         JSR PLOT     ; PLOT X, Y         JSR NEXT     ; TAU=TAU+IVAL         JMP L4L5         LDA SCROLY   ; DISABLE BITMAP         AND #$DF     ; MODE         STA SCROLY         LDA VMCSB    ; CHARACTER DOT         AND #$F7     ; DATA AT $1000         STA VMCSB         LDA #$93     ; CLEAR SCREEN         JSR CHROUT         RTS;---------------------------------------; CLEAR BITMAP AREA;---------------------------------------CLEARBM         LDA #<BBITMAP         STA $FB         LDA #>BBITMAP         STA $FC         LDA #<EBITMAP         STA $FD         LDA #>EBITMAP         STA $FE         LDX #$00         JSR FILLBLOCK         RTS;---------------------------------------; COLOR BITMAP;---------------------------------------COLORBM         LDA #<BCOLOR         STA $FB         LDA #>BCOLOR         STA $FC         LDA #<ECOLOR         STA $FD         LDA #>ECOLOR         STA $FE         LDX #$6F         JSR FILLBLOCK         RTS;---------------------------------------; FILL A MEMORY BLOCK WITH A BYTE;; START ADDRESS IN $FB,$FC; END ADDRESS IN $FD, $FE; BYTE IN .X; $02 USED FOR COMPARISON;---------------------------------------FILLBLOCK         LDY #$00L1       TXA         STA ($FB),Y         CLC           ; COMPARE         LDA $FB         STA $02         TYA         ADC $02         SEC         SBC $FD         STA $02         LDA $FC         SBC $FE         ORA $02         BEQ L3         INY         CLC         LDA $FB         STA $02         TYA         ADC $02         BEQ L2         BNE L1L2       LDA #$00     ; NEXT PAGE         STA $FB         INC $FC         JMP L1L3       RTS;---------------------------------------; CALCULATE X VALUE;---------------------------------------CALCX         LDA #<TAU    ; LOAD TAU TO         LDY #>TAU    ; FAC#1         JSR LOADFLT         JSR FNX      ; CALL X(T)         JSR FLTXFER  ; XFER TO FAC#2         LDA XFAC     ; MULT. BY X         JSR UBYT2FLT ; X FACTOR         JSR MULTF         JSR FLTXFER  ; XFER TO FAC#2         LDA XFAC     ; ADD X FACTOR         JSR UBYT2FLT         JSR ADDF         JSR FLT2INT  ; CONVERT TO                      ; UNSIGNED                      ; INTEGER         STX XVAL         STA XVAL+1         RTS;---------------------------------------; CALCULATE Y VALUE;---------------------------------------CALCY         LDA #<TAU    ; LOAD TAU TO         LDY #>TAU    ; FAC#1         JSR LOADFLT         JSR FNY      ; CALL Y(T)         JSR FLTXFER  ; XFER TO FAC#2         LDA YFAC     ; MULT. BY         JSR UBYT2FLT ; YFACTOR         JSR MULTF         JSR FLTXFER  ; XFER TO FAC#2         LDA YFAC     ; ADD Y FACTOR         JSR UBYT2FLT         JSR ADDF         JSR FLT2INT  ; CONVERT TO                      ; UNSIGNED                      ; INTEGER         STX YVAL         STA YVAL+1         RTS;---------------------------------------; CALCULATE BYTE BASED ON X, Y;; BY = BASE+40*(Y AND 248)+(Y AND 7);      +(X AND 504);---------------------------------------CALCBY         LDA XVAL+1    ; STORE HI BYTE         STA FAC1MANT  ; TO FAC#1                       ; MANTISSA         LDA XVAL      ; STORE LO BYTE         STA FAC1MANT+1         JSR UWORD2FLT ; CONVERT TO                       ; FLOAT         JSR FLTXFER   ; XFER TO FAC#2         LDA #$01      ; 504         LDY #$F8         JSR GIVAYF    ; CONVERT TO                       ; FLOAT         JSR FLTAND    ; AND THEM         LDX #<TMP     ; STORE TO TMP         LDY #>TMP         JSR STOREFLT         LDA YVAL+1    ; STORE HI BYTE         STA FAC1MANT  ; TO FAC#1                       ; MANTISSA         LDA YVAL      ; STORE LO BYTE         STA FAC1MANT+1         JSR UWORD2FLT ; CONVERT TO                       ; FLOAT         JSR FLTXFER   ; XFER TO FAC#2         LDA #$07      ; 7         JSR BYTE2FLT  ; CONVERT TO                       ; FLOAT         JSR FLTAND    ; AND THEM         LDA #<TMP     ; LOAD FAC#2 FROM         LDY #>TMP     ; TMP         JSR CONUPK         JSR ADDF      ; ADD THE RESULTS         LDX #<TMP     ; STORE TO TMP         LDY #>TMP         JSR STOREFLT         LDA YVAL+1    ; STORE HI BYTE         STA FAC1MANT  ; TO FAC#1                       ; MANTISSA         LDA YVAL      ; STORE LO BYTE         STA FAC1MANT+1         JSR UWORD2FLT ; CONVERT TO                       ; FLOAT         JSR FLTXFER   ; XFER TO FAC#2         LDA #$F8      ; 248         JSR UBYT2FLT  ; CONVERT TO                       ; FLOAT         JSR FLTAND    ; AND THEM         JSR FLTXFER   ; XFER TO FAC#2         LDA #$28      ; 40         JSR BYTE2FLT  ; CONVERT TO                       ; FLOAT         JSR MULTF     ; MULTIPLY THEM         LDA #<TMP     ; LOAD FAC#2 FROM         LDY #>TMP     ; TMP         JSR CONUPK         JSR ADDF      ; ADD THEM         JSR FLTXFER   ; XFER TO FAC#2         LDA #>BBITMAP ; CONVERT BASE         LDY #<BBITMAP ; ADDRESS TO         JSR GIVAYF    ; FLOAT         JSR ADDF      ; ADD THEM         JSR FLT2INT   ; UNSIGNED                       ; INTEGER         STX BY         STA BY+1         RTS;---------------------------------------; PLOT POINT IN X, Y ON HI-RES SCREEN;---------------------------------------PLOT         LDA XVAL+1    ; STORE HI BYTE         STA FAC1MANT  ; TO FAC#1                       ; MANTISSA         LDA XVAL      ; STORE LO BYTE         STA FAC1MANT+1         JSR UWORD2FLT ; CONVERT TO                       ; FLOAT         JSR FLTNOT    ; NOT(X)         JSR FLTXFER   ; XFER TO FAC#2         LDA #$07      ; 7         JSR BYTE2FLT  ; CONVERT TO                       ; FLOAT         JSR FLTAND    ; AND THEM         JSR FLT2INT   ; CONVERT TO                       ; UNSIGNED                       ; INTEGER         LDA #$01      ; POWER OF 2         CPX #$00      ; LSB IN .X         BEQ L7L6         ASL A         DEX         BNE L6L7         JSR UBYT2FLT  ; CONVERT TO                       ; FLOAT         JSR FLTXFER   ; XFER TO FAC#2         LDA BY         STA $FB         LDA BY+1         STA $FC         LDY #$00         LDA ($FB),Y         JSR UBYT2FLT  ; CONVERT TO                       ; FLOAT         JSR FLTOR     ; OR THEM         JSR FLT2INT   ; CONVERT TO                       ; UNSIGNED                       ; INTEGER                       ; LO BYTE IN .X         LDA BY         STA $FB         LDA BY+1         STA $FC         LDY #$00         TXA         STA ($FB),Y         RTS;---------------------------------------; TAU = TAU + IVAL; IVAL IS DEFINED TO BE 2^(-8); OR APPROXIMATELY 0.00390625;---------------------------------------NEXT         LDA #<TAU    ; LOAD TAU TO         LDY #>TAU    ; FAC#1         JSR LOADFLT         JSR FLTXFER  ; XFER FAC#1 TO                      ; FAC#2         LDA #<IVAL   ; LOAD IVAL TO         LDY #>IVAL   ; FAC#1         JSR LOADFLT         JSR ADDF     ; ADD THEM         LDX #<TAU    ; STORE FAC#1 TO         LDY #>TAU    ; TAU         JSR STOREFLT         RTS;---------------------------------------; CONVERT FAC#1 TO UNSIGNED 16-BIT; INTEGER.  UNSIGNED INTEGER RETURNED; IN .A, .X;---------------------------------------FLT2INT         JSR QINT       ; CONVERT TO                        ; INTEGER         LDA FAC1MANT+2 ; MSB MANTISSA         LDX FAC1MANT+3 ; LSB MANTISSA         RTS;---------------------------------------; CONVERT UNSIGNED WORD TO FLOAT; MSB OF WORD IN FAC#1 MANTISSA; LSB OF WORD IN FAC#1 MANTISSA+1;---------------------------------------UWORD2FLT         LDX #$90     ; SETTING THE                      ; EXPONENT TO                      ; $90 PLACES THE                      ; BINARY POINT TO                      ; THE RIGHT OF                      ; THE LEAST                      ; SIGNIFICANT BIT                      ; OF THIS INTEGER                      ; MAKING IT A                      ; WHOLE NUMBER         SEC          ; TREAT INT AS                      ; UNSIGNED         JSR UWRD2FLT ; STORE IN FAC#1         RTS;---------------------------------------; CONVERT UNSIGNED BYTE IN A. TO FLOAT;---------------------------------------UBYT2FLT         STA FAC1MANT+1 ; STORE LO BYTE         LDA #$00       ; STORE HI BYTE         STA FAC1MANT         JSR UWORD2FLT         RTS;---------------------------------------; PRINT FAC#1;---------------------------------------FLTPRNT         JSR FOUT     ; CONVERT FAC#1                      ; TO A STRING                      ; IN .A, .Y         JSR STROUT   ; PRINT IT         LDA #$0D     ; PRINT NEWLINE         JSR CHROUT         RTS;---------------------------------------; PRINT INT IN .A, .X;---------------------------------------INTPRNT         JSR LINPRT         LDA #$0D         JSR CHROUT         RTS;---------------------------------------; X(T) = SIN(A*T+D); T IS IN FAC#1;---------------------------------------FNX         JSR FLTXFER  ; XFER TO FAC#2         LDA ALPHA    ; LOAD ALPHA TO         JSR BYTE2FLT ; FAC#1         JSR MULTF    ; MULTIPLY THEM         JSR FLTXFER  ; XFER TO FAC#2         LDA #<PI2    ; LOAD DELTA TO         LDY #>PI2    ; FAC#1         JSR LOADFLT         JSR ADDF     ; ADD THEM         JSR SIN      ; CALL SIN(X)         RTS;---------------------------------------; Y(T) = SIN(B*T); T IS IN FAC#1;---------------------------------------FNY         JSR FLTXFER  ; XFER TO FAC#2         LDA BETA     ; LOAD BETA TO         JSR BYTE2FLT ; FAC#1         JSR MULTF    ; MULTIPLY THEM         JSR SIN      ; CALL SIN(X)         RTS;---------------------------------------; MULT FAC#1 BY FAC#2;---------------------------------------MULTF         JSR SGNCMP         LDA FAC1EXP         JSR FLTMULT         RTS;---------------------------------------; ADD FAC#1 TO FAC#2;---------------------------------------ADDF         JSR SGNCMP         LDA FAC1EXP         JSR FLTADD         RTS;---------------------------------------; SETUP SIGN COMPARE;---------------------------------------SGNCMP         LDA $66      ; SETUP SIGN         EOR $6E      ; COMPARE         STA $6F         RTS