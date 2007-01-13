VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsDisassembler"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Enum Modes
    Invalid = -1
    Immediate
    Absolute
    ZPage
    Accum
    Implied
    IndX
    IndY
    ZPageX
    AbsX
    AbsY
    Ind
    ZPageY
End Enum

Private Type Instruction
    Mnemonic As String * 3
    Mode As Modes
End Type

Private Instr(255) As Instruction
Private pc As Integer

' 6502 Mnemonics
Private Const ADC As String * 3 = "ADC"
Private Const AND_ As String * 3 = "AND"
Private Const ASL As String * 3 = "ASL"
Private Const BIT As String * 3 = "BIT"
Private Const BMI As String * 3 = "BMI"
Private Const BPL As String * 3 = "BPL"
Private Const BRK As String * 3 = "BRK"
Private Const BVC As String * 3 = "BVC"
Private Const BVS As String * 3 = "BVS"
Private Const CLC As String * 3 = "CLC"
Private Const CLI As String * 3 = "CLI"
Private Const EOR As String * 3 = "EOR"
Private Const JMP As String * 3 = "JMP"
Private Const JSR As String * 3 = "JSR"
Private Const LSR As String * 3 = "LSR"
Private Const ORA As String * 3 = "ORA"
Private Const PHA As String * 3 = "PHA"
Private Const PHP As String * 3 = "PHP"
Private Const PLA As String * 3 = "PLA"
Private Const PLP As String * 3 = "PLP"
Private Const ROL As String * 3 = "ROL"
Private Const ROR As String * 3 = "ROR"
Private Const RTI As String * 3 = "RTI"
Private Const RTS As String * 3 = "RTS"
Private Const SEC As String * 3 = "SEC"
Private Const SEI As String * 3 = "SEI"
Private Const STA As String * 3 = "STA"
Private Const STY As String * 3 = "STY"




Private Sub InitInstructions()
    Instr(&H0) = MakeInstr(BRK, Implied)
    Instr(&H1) = MakeInstr(ORA, IndX)
    Instr(&H2) = MakeNullInstr()
    Instr(&H3) = MakeNullInstr()
    Instr(&H4) = MakeNullInstr()
    Instr(&H5) = MakeInstr(ORA, ZPage)
    Instr(&H6) = MakeInstr(ASL, ZPage)
    Instr(&H7) = MakeNullInstr()
    Instr(&H8) = MakeInstr(PHP, Implied)
    Instr(&H9) = MakeInstr(ORA, Immediate)
    Instr(&HA) = MakeInstr(ASL, Accum)
    Instr(&HB) = MakeNullInstr()
    Instr(&HC) = MakeNullInstr()
    Instr(&HD) = MakeInstr(ORA, Absolute)
    Instr(&HE) = MakeInstr(ASL, Absolute)
    Instr(&HF) = MakeNullInstr()
    Instr(&H10) = MakeInstr(BPL, Implied)
    Instr(&H11) = MakeInstr(ORA, IndY)
    Instr(&H12) = MakeNullInstr()
    Instr(&H13) = MakeNullInstr()
    Instr(&H14) = MakeNullInstr()
    Instr(&H15) = MakeInstr(ORA, ZPageX)
    Instr(&H16) = MakeInstr(ASL, ZPageX)
    Instr(&H17) = MakeNullInstr()
    Instr(&H18) = MakeInstr(CLC, Implied)
    Instr(&H19) = MakeInstr(ORA, AbsY)
    Instr(&H1A) = MakeNullInstr()
    Instr(&H1B) = MakeNullInstr()
    Instr(&H1C) = MakeNullInstr()
    Instr(&H1D) = MakeInstr(ORA, AbsX)
    Instr(&H1E) = MakeInstr(ASL, AbsX)
    Instr(&H1F) = MakeNullInstr()
    Instr(&H20) = MakeInstr(JSR, Implied)
    Instr(&H21) = MakeInstr(AND_, IndX)
    Instr(&H22) = MakeNullInstr()
    Instr(&H23) = MakeNullInstr()
    Instr(&H24) = MakeInstr(BIT, ZPageX)
    Instr(&H25) = MakeInstr(AND_, ZPage)
    Instr(&H26) = MakeInstr(ROL, ZPage)
    Instr(&H27) = MakeNullInstr()
    Instr(&H28) = MakeInstr(PLP, Implied)
    Instr(&H29) = MakeInstr(AND_, Immediate)
    Instr(&H2A) = MakeInstr(ROL, Accum)
    Instr(&H2B) = MakeNullInstr()
    Instr(&H2C) = MakeInstr(BIT, Absolute)
    Instr(&H2D) = MakeInstr(AND_, Absolute)
    Instr(&H2E) = MakeInstr(ROL, Absolute)
    Instr(&H2F) = MakeNullInstr()
    Instr(&H30) = MakeInstr(BMI, Implied)
    Instr(&H31) = MakeInstr(AND_, IndY)
    Instr(&H32) = MakeNullInstr()
    Instr(&H33) = MakeNullInstr()
    Instr(&H34) = MakeNullInstr()
    Instr(&H35) = MakeInstr(AND_, ZPageX)
    Instr(&H36) = MakeInstr(ROL, ZPageX)
    Instr(&H37) = MakeNullInstr()
    Instr(&H38) = MakeInstr(SEC, Implied)
    Instr(&H39) = MakeInstr(AND_, AbsY)
    Instr(&H3A) = MakeNullInstr()
    Instr(&H3B) = MakeNullInstr()
    Instr(&H3C) = MakeNullInstr()
    Instr(&H3D) = MakeInstr(AND_, AbsX)
    Instr(&H3E) = MakeInstr(ROL, AbsX)
    Instr(&H3F) = MakeNullInstr()
    Instr(&H40) = MakeInstr(RTI, Implied)
    Instr(&H41) = MakeInstr(EOR, IndX)
    Instr(&H42) = MakeNullInstr()
    Instr(&H43) = MakeNullInstr()
    Instr(&H44) = MakeNullInstr()
    Instr(&H45) = MakeInstr(EOR, ZPage)
    Instr(&H46) = MakeInstr(LSR, ZPage)
    Instr(&H47) = MakeNullInstr()
    Instr(&H48) = MakeInstr(PHA, Implied)
    Instr(&H49) = MakeInstr(EOR, Immediate)
    Instr(&H4A) = MakeInstr(LSR, Accum)
    Instr(&H4B) = MakeNullInstr()
    Instr(&H4C) = MakeInstr(JMP, Absolute)
    Instr(&H4D) = MakeInstr(EOR, Absolute)
    Instr(&H4E) = MakeInstr(LSR, Absolute)
    Instr(&H4F) = MakeNullInstr()
    Instr(&H50) = MakeInstr(BVC, Implied)
    Instr(&H51) = MakeInstr(EOR, IndY)
    Instr(&H52) = MakeNullInstr()
    Instr(&H53) = MakeNullInstr()
    Instr(&H54) = MakeNullInstr()
    Instr(&H55) = MakeInstr(EOR, ZPageX)
    Instr(&H56) = MakeInstr(LSR, ZPageX)
    Instr(&H57) = MakeNullInstr()
    Instr(&H58) = MakeInstr(CLI, Implied)
    Instr(&H59) = MakeInstr(EOR, AbsY)
    Instr(&H5A) = MakeNullInstr()
    Instr(&H5B) = MakeNullInstr()
    Instr(&H5C) = MakeNullInstr()
    Instr(&H5D) = MakeInstr(EOR, AbsX)
    Instr(&H5E) = MakeInstr(LSR, AbsX)
    Instr(&H5F) = MakeNullInstr()
    Instr(&H60) = MakeInstr(RTS, Implied)
    Instr(&H61) = MakeInstr(ADC, IndX)
    Instr(&H62) = MakeNullInstr()
    Instr(&H63) = MakeNullInstr()
    Instr(&H64) = MakeNullInstr()
    Instr(&H65) = MakeInstr(ADC, ZPage)
    Instr(&H66) = MakeInstr(ROR, ZPage)
    Instr(&H67) = MakeNullInstr()
    Instr(&H68) = MakeInstr(PLA, Implied)
    Instr(&H69) = MakeInstr(ADC, Immediate)
    Instr(&H6A) = MakeInstr(ROR, Accum)
    Instr(&H6B) = MakeNullInstr()
    Instr(&H6C) = MakeInstr(JMP, Ind)
    Instr(&H6D) = MakeInstr(ADC, Absolute)
    Instr(&H6E) = MakeInstr(ROR, Absolute)
    Instr(&H6F) = MakeNullInstr()
    Instr(&H70) = MakeInstr(BVS, Implied)
    Instr(&H71) = MakeInstr(ADC, IndY)
    Instr(&H72) = MakeNullInstr()
    Instr(&H73) = MakeNullInstr()
    Instr(&H74) = MakeNullInstr()
    Instr(&H75) = MakeInstr(ADC, ZPageX)
    Instr(&H76) = MakeInstr(ROR, ZPageX)
    Instr(&H77) = MakeNullInstr()
    Instr(&H78) = MakeInstr(SEI, Implied)
    Instr(&H79) = MakeInstr(ADC, AbsY)
    Instr(&H7A) = MakeNullInstr()
    Instr(&H7B) = MakeNullInstr()
    Instr(&H7C) = MakeNullInstr()
    Instr(&H7D) = MakeInstr(ADC, AbsX)
    Instr(&H7E) = MakeInstr(ROR, AbsX)
    Instr(&H7F) = MakeNullInstr()
    Instr(&H80) = MakeNullInstr()
    Instr(&H81) = MakeInstr(STA, IndX)
    Instr(&H82) = MakeNullInstr()
    Instr(&H83) = MakeNullInstr()
    Instr(&H84) = MakeInstr(STY, ZPage)
    Instr(&H85) = MakeInstr(STA, ZPage)
    
 
'    &staIdx,    /* 0x81 */
'    NULL,       /* 0x82 */
'    NULL,       /* 0x83 */
'    &styZp,     /* 0x84 */
'    &staZp,     /* 0x85 */
'    &stxZp,     /* 0x86 */
'    NULL,       /* 0x87 */
'    &dey,       /* 0x88 */
'    NULL,       /* 0x89 */
'    &txa,       /* 0x8A */
'    NULL,       /* 0x8B */
'    &styAbsl,   /* 0x8C */
'    &staAbsl,   /* 0x8D */
'    &stxAbsl,   /* 0x8E */
'    NULL,       /* 0x8F */
'    &bcc,       /* 0x90 */
'    &staIdy,    /* 0x91 */
'    NULL,       /* 0x92 */
'    NULL,       /* 0x93 */
'    &styZpx,    /* 0x94 */
'    &staZpx,    /* 0x95 */
'    &stxZpy,    /* 0x96 */
'    NULL,       /* 0x97 */
'    &tya,       /* 0x98 */
'    &staAby,    /* 0x99 */
'    &txs,       /* 0x9A */
'    NULL,       /* 0x9B */
'    NULL,       /* 0x9C */
'    &staAbx,    /* 0x9D */
'    NULL,       /* 0x9E */
'    NULL,       /* 0x9F */
'    &ldyImm,    /* 0xA0 */
'    &ldaIdx,    /* 0xA1 */
'    &ldxImm,    /* 0xA2 */
'    NULL,       /* 0xA3 */
'    &ldyZp,     /* 0xA4 */
'    &ldaZp,     /* 0xA5 */
'    &ldxZp,     /* 0xA6 */
'    NULL,       /* 0xA7 */
'    &tay,       /* 0xA8 */
'    &ldaImm,    /* 0xA9 */
'    &tax,       /* 0xAA */
'    NULL,       /* 0xAB */
'    &ldyAbsl,   /* 0xAC */
'    &ldaAbsl,   /* 0xAD */
'    &ldxAbsl,   /* 0xAE */
'    NULL,       /* 0xAF */
'    &bcs,       /* 0xB0 */
'    &ldaIdy,    /* 0xB1 */
'    NULL,       /* 0xB2 */
'    NULL,       /* 0xB3 */
'    &ldyZpx,    /* 0xB4 */
'    &ldaZpx,    /* 0xB5 */
'    &ldxZpy,    /* 0xB6 */
'    NULL,       /* 0xB7 */
'    &clv,       /* 0xB8 */
'    &ldaAby,    /* 0xB9 */
'    &tsx,       /* 0xBA */
'    NULL,       /* 0xBB */
'    &ldyAbx,    /* 0xBC */
'    &ldaAbx,    /* 0xBD */
'    &ldxAby,    /* 0xBE */
'    NULL,       /* 0xBF */
'    &cpyImm,    /* 0xC0 */
'    &cmpIdx,    /* 0xC1 */
'    NULL,       /* 0xC2 */
'    NULL,       /* 0xC3 */
'    &cpyZp,     /* 0xC4 */
'    &cmpZp,     /* 0xC5 */
'    &decZp,     /* 0xC6 */
'    NULL,       /* 0xC7 */
'    &iny,       /* 0xC8 */
'    &cmpImm,    /* 0xC9 */
'    &dex,       /* 0xCA */
'    NULL,       /* 0xCB */
'    &cpyAbsl,   /* 0xCC */
'    &cmpAbsl,   /* 0xCD */
'    &decAbsl,   /* 0xCE */
'    NULL,       /* 0xCF */
'    &bne,       /* 0xD0 */
'    &cmpIdy,    /* 0xD1 */
'    NULL,       /* 0xD2 */
'    NULL,       /* 0xD3 */
'    NULL,       /* 0xD4 */
'    &cmpZpx,    /* 0xD5 */
'    &decZpx,    /* 0xD6 */
'    NULL,       /* 0xD7 */
'    &cld,       /* 0xD8 */
'    &cmpAby,    /* 0xD9 */
'    NULL,       /* 0xDA */
'    NULL,       /* 0xDB */
'    NULL,       /* 0xDC */
'    &cmpAbx,    /* 0xDD */
'    &decAbx,    /* 0xDE */
'    NULL,       /* 0xDF */
'    &cpxImm,    /* 0xE0 */
'    &sbcIdx,    /* 0xE1 */
'    NULL,       /* 0xE2 */
'    NULL,       /* 0xE3 */
'    &cpxZp,     /* 0xE4 */
'    &sbcZp,     /* 0xE5 */
'    &incZp,     /* 0xE6 */
'    NULL,       /* 0xE7 */
'    &inx,       /* 0xE8 */
'    &sbcImm,    /* 0xE9 */
'    &nop,       /* 0xEA */
'    NULL,       /* 0xEB */
'    &cpxAbsl,   /* 0xEC */
'    &sbcAbsl,   /* 0xED */
'    &incAbsl,   /* 0xEE */
'    NULL,       /* 0xEF */
'    &beq,       /* 0xF0 */
'    &sbcIdy,    /* 0xF1 */
'    NULL,       /* 0xF2 */
'    NULL,       /* 0xF3 */
'    NULL,       /* 0xF4 */
'    &sbcZpx,    /* 0xF5 */
'    &incZpx,    /* 0xF6 */
'    NULL,       /* 0xF7 */
'    &sed,       /* 0xF8 */
'    &sbcAby,    /* 0xF9 */
'    NULL,       /* 0xFA */
'    NULL,       /* 0xFB */
'    NULL,       /* 0xFC */
'    &sbcAbx,    /* 0xFD */
'    &incAbx,    /* 0xFE */
'    NULL        /* 0xFF */
    
End Sub

Private Function MakeInstr(ByVal m As String, Mode As Modes) As Instruction
    MakeInstr.Mnemonic = m
    MakeInstr.Mode = Mode
End Function

Private Function MakeNullInstr() As Instruction
    MakeNullInstr.Mnemonic = vbNullString
    MakeNullInstr.Mode = Invalid
End Function


Public Property Get NextStatement() As String
    
    NextStatement = vbNullString
    
End Property

Private Sub Class_Initialize()
    Call InitInstructions
    pc = 0
End Sub


