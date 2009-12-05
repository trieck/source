         *= $0800
;---------------------------------------
; BASIC PROGRAM DECLARATION
;---------------------------------------
         .BYTE $00    ; BEGIN BASIC PRG
         .BYTE <NEXTL ; NEXT LINK
         .BYTE >NEXTL
         .BYTE $00    ; LINE #
         .BYTE $00
         .BYTE $9E    ; SYS TOKEN
         .TEXT "2061" ; $08D
         .BYTE $00    ; END OF LINE
NEXTL    .BYTE $00    ; END OF PROGRAM
         .BYTE $00

         JMP START    ; MUST BE @ $08D
;---------------------------------------
; DATA DECLARATIONS
;---------------------------------------
M1       .TEXT "COMMAND: F(ILE)"
         .TEXT ",M(EMORY),E(XIT):"
         .BYTE $00
M2       .TEXT "FILER: D,L,E:"
         .BYTE $00
M3       .TEXT "DRIVE:"
         .BYTE $00
M4       .TEXT "PRESS SPACE"
         .BYTE $00
M5       .TEXT "MEMORY: M,E:"
         .BYTE $00
M6       .TEXT "START:"
         .BYTE $00
M7       .TEXT "END:"
         .BYTE $00

HEXISH   .TEXT "0123456789ABCDEF"
         .BYTE $00

DIRNAME  .TEXT "$0"
DIRLEN   = *-DIRNAME

SETNAM   = $FFBD
SETLFS   = $FFBA
OPEN     = $FFC0
CHKIN    = $FFC6
CHRIN    = $FFCF
CLOSE    = $FFC3
CLRCH    = $FFCC
CHROUT   = $FFD2
READST   = $FFB7
PRINTSTR = $AB1E
GETIN    = $FFE4

DRIVE    .BYTE $08
COLS     .BYTE $00
ROWS     .BYTE $00
FILENUM  .BYTE $01

SADDR    .WORD $00
DADDR    .WORD $00

;---------------------------------------
; CODE
;---------------------------------------
START
         LDA #$02     ; INIT SCREEN
         STA $D020    ; RED BORDER
         STA $0286    ; RED CHAR
         LDA #$0A
         STA $D021    ; LT.RED BKGND
         LDA #$17
         STA $D018    ; LOWERCASE
         LDA #$80
         STA $0291    ; DIS. SHFT/CMDR
         JSR $E505    ; # OF ROWS/COLS
         STX COLS
         STY ROWS

MAIN
         LDA #$93     ; CLEAR SCREEN
         JSR CHROUT
         LDA #<M1
         LDY #>M1
         JSR PRINTSTR ; PRINT M1

I1       JSR GETCHAR  ; GET CHAR
         CMP #$46     ; IS IT "F"?
         BEQ I1F      ; FILE MENU
         CMP #$4D     ; IT IT "M"?
         BEQ I1M      ; MEMORY MENU
         CMP #$45     ; IS IT "E"?
         BEQ END      ; EXIT
         JMP I1
I1F
         JMP FMENU    ; FILE MENU
I1M
         JMP MMENU    ; MEMORY MENU

END
         LDA #$00
         STA $0291    ; ENAB. SHFT/CMDR
         RTS

;---------------------------------------
; FILE MENU
;---------------------------------------
FMENU                 ; FILE MENU
         LDA #$93     ; CLEAR SCREEN
         JSR CHROUT
         LDA #<M2
         LDY #>M2
         JSR PRINTSTR ; PRINT M2

I2       JSR GETCHAR  ; GET CHAR
         CMP #$44     ; IS IT "D"?
         BEQ DIR      ; DIRECTORY
         CMP #$4C     ; IS IT "L"?
         BEQ LIST     ; LISTING
         CMP #$45     ; IS IT "E"?
         BEQ MAIN     ; MAIN MENU
         JMP I2

;---------------------------------------
; LIST A PROGRAM
;---------------------------------------
LIST                  ; LIST A PROGRAM
         JSR GETDRIVE ; GET DRIVE
         JSR CHROUT   ; PRINT RETURN

         JSR WAITSP   ; WAIT FOR SPACE
         JMP FMENU    ; FILE MENU

;---------------------------------------
; DIRECTORY
;---------------------------------------
DIR                   ; DIRECTORY
         JSR GETDRIVE ; GET DRIVE

                      ; VIEW DIR
         JSR CHROUT   ; PRINT RETURN
         LDA #$B9     ; LOWER LINE SEP
         LDX COLS     ; # OF COLS
DIR1     JSR CHROUT   ; PRINT SEP
         DEX
         BNE DIR1

         LDA #$00     ; LEN. OF FILE
         JSR SETNAM   ; SET FILENAME
         LDA #$0F     ; COMMAND CHANNEL
         LDX DRIVE    ; DEVICE NUMBER
         TAY          ; SECONDARY ADDR.
         JSR SETLFS   ; SET FILE PARAMS
         JSR OPEN     ; OPEN
         BCC DIR2
DIR3
         JMP DIRIO    ; I/O ERROR
DIR2
         LDA #DIRLEN  ; LEN. OF FILE
         LDX #<DIRNAME; FILENAME
         LDY #>DIRNAME
         JSR SETNAM   ; SET FILENAME
         LDA FILENUM  ; FILE NUMBER
         LDX DRIVE    ; DEVICE NUMBER
         LDY #$00     ; SECONDARY ADDR.
         JSR SETLFS   ; SET FILE PARAMS
         JSR OPEN     ; OPEN FILE
         BCC DIR4
DIR5
         JMP DIRIO    ; I/O ERROR
DIR4
         LDX FILENUM  ; FILE NUMBER
         JSR CHKIN    ; OPEN CHANNEL

         JSR CHRIN    ; DISCARD LOAD
         JSR CHRIN    ; ADDRESS
         LDA $90
         BNE DIRERR

DIR6     JSR CHRIN    ; DISCARD LINE
         JSR CHRIN    ; LINK
         JSR CHRIN    ; RETRIEVE NUMBER
                      ; OF BLOCKS USED
         STA $FC      ; STORE TO ZERO
         JSR CHRIN    ; PAGE IN LOW,
                      ; HIGH FORMAT
         STA $FB      ;
         LDA $90      ; READ I/O STATUS
         BNE DIRCLEAN ; EOF
         LDA $FB      ; RETRIEVE NUMBER
         LDX $FC      ; OF BLOCKS
         JSR $BDCD    ; OUTPUT INT IN
                      ; .A, .X
         LDA #$20     ; PRINT SPACE
         JSR CHROUT   ; AFTER BLOCKS
         JSR CHRIN
DIR7
         JSR CHROUT

DIR8     LDX $028D    ; CHECK FOR SHIFT
         BNE DIR8
         LDX $91      ; CHECK FOR STOP
         CPX #$7F
         BEQ DIRCLEAN
         JSR CHRIN
         BNE DIR7
         LDA #$0D
         JSR CHROUT   ; PRINT RETURN
         JMP DIR6
DIRERR
         JSR DISKERR  ; PRINT DISK ERROR
         JMP DIRCLEAN

DIRIO
         JSR IOERR    ; DRIVE I/O ERROR
DIRCLEAN
         LDA FILENUM
         JSR CLOSE    ; CLOSE FILE
         LDA #$0F     ; CLOSE COMMAND
         JSR CLOSE    ; CHANNEL
         JSR CLRCH    ; CLOSE CHANNELS

         LDA #$0D
         JSR CHROUT   ; PRINT RETURN

         LDA #$B8     ; UPPER LINE SEP
         LDX COLS     ; # OF COLS
DIR9     JSR CHROUT   ; PRINT SEP
         DEX
         BNE DIR9
         JSR WAITSP   ; WAIT FOR SPACE
         JMP FMENU    ; FILE MENU

;---------------------------------------
; MEMORY MENU
;---------------------------------------
MMENU                 ; MEMORY MENU
         LDA #$93     ; CLEAR SCREEN
         JSR CHROUT
         LDA #<M5
         LDY #>M5
         JSR PRINTSTR ; PRINT M5

I3       JSR GETCHAR  ; GET CHAR
         CMP #$4D     ; IS IT "M"?
         BEQ I3M      ; MEMORY DUMP
         CMP #$45     ; IS IT "E"?
         BEQ I3E      ; MAIN MENU
         JMP I3
I3M
         JMP DUMP     ; MEMORY DUMP
I3E
         JMP MAIN     ; MAIN MENU

;---------------------------------------
; MEMORY DUMP
;---------------------------------------
DUMP                  ; MEMORY DUMP
         JSR GETSTART ; GET START ADDR.
         JSR GETDEST  ; GET DEST. ADDR.
         JMP MMENU    ; MEMORY MENU

;---------------------------------------
; SUBROUTINE SECTION
;---------------------------------------

;---------------------------------------
; GET STARTING ADDRESS
;---------------------------------------
GETSTART              ; GET START ADDR.
         LDA #$0D
         JSR CHROUT   ; PRINT RETURN
         LDA #<M6
         LDY #>M6
         JSR PRINTSTR ; PRINT M6

         LDA #$00     ; REINITIALIZE
         STA SADDR
         STA SADDR+1

         LDA #<SADDR  ; SET UP POINTER
         LDX #>SADDR
         JSR GETADDR

         RTS

;---------------------------------------
; GET DESTINATION ADDRESS
;---------------------------------------
GETDEST               ; GET DEST. ADDR.
         LDA #$0D
         JSR CHROUT   ; PRINT RETURN
         LDA #<M7
         LDY #>M7
         JSR PRINTSTR ; PRINT M7

         LDA #$00     ; REINITIALIZE
         STA DADDR
         STA DADDR+1

         LDA #<DADDR  ; SET UP POINTER
         LDX #>DADDR
         JSR GETADDR

         RTS

;---------------------------------------
; GET ADDRESS
; ADDRESS TO STORE IS IN .A, .X
;---------------------------------------
GETADDR               ; GET ADDRESS

         STA $FB      ; STORE POINTER
         STX $FC

         LDA #$30     ; INITIALIZE TO
         JSR CHROUT   ; ZEROS
         JSR CHROUT
         JSR CHROUT
         JSR CHROUT
         JMP GABK

GA1
         JSR GETCHAR
         CMP #$0D
         BEQ GADONE
         JSR ISHEX
         BCS GA1
         JSR CHROUT   ; PRINT IT

         TYA          ; INDEX OF CHAR
         ASL A        ; MULTIPLY BY 16
         ASL A        ; FOR HI-NIBBLE
         ASL A
         ASL A

         LDY #$01     ; HI-BYTE
         STA ($FB),Y  ; STORE HI-NIBBLE
GA2
         JSR GETCHAR
         CMP #$0D     ; IS IT RETURN
         BEQ GADONE
         JSR ISHEX
         BCS GA2
         JSR CHROUT   ; PRINT IT

         TYA          ; INDEX OF CHAR
         LDY #$01     ; HI-BYTE
         ORA ($FB),Y  ; STORE LO-NIBBLE
         STA ($FB),Y  ; OF HI-BYTE
GA3
         JSR GETCHAR
         CMP #$0D     ; IS IT RETURN
         BEQ GADONE
         JSR ISHEX
         BCS GA3
         JSR CHROUT   ; PRINT IT

         TYA          ; INDEX OF CHAR
         ASL A        ; MULTIPLY BY 16
         ASL A        ; FOR HI-NIBBLE
         ASL A
         ASL A
         LDY #$00     ; LO-BYTE
         STA ($FB),Y

GA4
         JSR GETCHAR
         CMP #$0D     ; IS IT RETURN
         BEQ GADONE
         JSR ISHEX
         BCS GA4
         JSR CHROUT   ; PRINT IT

         TYA          ; INDEX OF CHAR
         LDY #$00     ; LO-BYTE
         ORA ($FB),Y  ; STORE LO-NIBBLE
         STA ($FB),Y  ; OF LO-BYTE
GABK
         LDA #$9D     ; BKSPACE
         JSR CHROUT
         JSR CHROUT
         JSR CHROUT
         JSR CHROUT
         JMP GA1

GADONE
         LDA $FB      ; RESTORE POINTER
         LDX $FC
         RTS

;---------------------------------------
; GET CHARACTER FROM KEYBOARD
; AND BLINK THE CURSOR
;---------------------------------------
GETCHAR               ; GET CHARACTER
         LDA #$00
         STA $CC      ; BLINK CURSOR
GC1      JSR GETIN    ; GET CHAR
         BEQ GC1      ; EMPTY BUFFER
         PHA          ; PUSH .A
         JSR CRSROFF  ; CURSOR OFF
         PLA          ; PULL .A
         RTS

;---------------------------------------
; TURN THE CURSOR OFF
;---------------------------------------
CRSROFF
         INC $CC      ; CURSOR OFF
         LDX $0287    ; ORIG COLOR
         LDA $CE      ; ORIG CHAR
         AND #$7F     ; TURN OFF RVS
         JSR $EA1C    ; STORE TO SCN
         RTS

;---------------------------------------
; DISK ERROR
;---------------------------------------
DISKERR
         LDX #$0F     ; OPEN CHANNEL
         JSR CHKIN    ; FOR INPUT
DE1
         JSR CHRIN
         LDX $90
         BNE DE2
         JSR CHROUT
         JMP DE1
DE2
         RTS

;---------------------------------------
; I/O ERROR
;---------------------------------------
IOERR
         LDY #$01     ; MOVE PAST CR.
         PHA
         JSR $F12F    ; PRINT I/O ERR.#
         PLA
         ORA #$30     ; MAKE ERR. ASCII
         JSR CHROUT   ; PRINT IT
         RTS

;---------------------------------------
; WAIT FOR SPACE
;---------------------------------------
WAITSP                ; WAIT FOR SPACE
         LDA #$01
         STA $C7      ; ENABLE REV.
         LDA #<M4
         LDY #>M4
         JSR PRINTSTR
         LDA #$00
         STA $C7      ; DISABLE REV.

WSP1     JSR GETIN
         CMP #$20     ; SPACE
         BNE WSP1
         RTS

;---------------------------------------
; GET DRIVE
;---------------------------------------
GETDRIVE              ; GET DRIVE
         LDA #$0D
         JSR CHROUT   ; PRINT RETURN
         LDA #<M3
         LDY #>M3
         JSR PRINTSTR ; PRINT M3
GD1
         LDA DRIVE
         CMP #$0A
         BCS GD2      ; DRIVE >= 10
         LDA #$00
         LDX #$00
         JSR $BDCD    ; OUTPUT LEAD 0

GD2
         LDA #$00     ; HIGH BYTE
         LDX DRIVE    ; LO BYTE
         JSR $BDCD    ; OUTPUT INTEGER
         LDA #$9D
         JSR CHROUT   ; PRINT BKSPACE
         JSR CHROUT

GD3      JSR GETCHAR  ; GET CHAR
         CMP #$11     ; IS IT CR. DWN?
         BEQ GD4
         CMP #$0D     ; IS IT RETURN?
         BEQ GD5
         JMP GD3
GD4
         INC DRIVE    ; NEXT DRIVE
         LDA DRIVE
         CMP #$0C
         BCC GD1      ; DRIVE < 12
         LDA #$08
         STA DRIVE    ; RESET DRIVE #
         JMP GD1

GD5
         RTS

;---------------------------------------
; CHECK FOR HEX DIGIT IN .A
;---------------------------------------
ISHEX
         STA $02      ; STORE ORIG. CHAR

         LDA #<HEXISH ; MAKE ZERO-PAGE
         STA $FD      ; POINTER
         LDA #>HEXISH ; FROM HEX STRING
         STA $FE
         LDY #$00     ; INITIALIZE INDEX
IHLOOP
         LDA ($FD),Y  ; COMPARE NEXT
         BEQ IHBAD    ; ZERO TERMINATOR
         CMP $02      ; COMPARE AGAINST
         BEQ IHGOOD   ; ORIGINAL CHAR
         INY          ; NEXT CHAR
         JMP IHLOOP
IHBAD
         SEC          ; NO MATCH
         JMP IHEND
IHGOOD
         CLC          ; MATCH
IHEND
         LDA $02      ; RESTORE CHAR
         RTS

