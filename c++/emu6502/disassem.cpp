/////////////////////////////////////////////////////////////////////////////
//
//	DISASSEM.CPP : 6502 CPU Disassembler
//
//	Copyright(c) 2003, Thomas A. Rieck
//

#include "stdafx.h"
#include "disassem.h"
#include "memory.h"

namespace  	// anonymous
{

CONST TCHAR ADC[] = _T("ADC");
CONST TCHAR AND[] = _T("AND");
CONST TCHAR ASL[] = _T("ASL");
CONST TCHAR BCC[] = _T("BCC");
CONST TCHAR BCS[] = _T("BCS");
CONST TCHAR BEQ[] = _T("BEQ");
CONST TCHAR BIT[] = _T("BIT");
CONST TCHAR BMI[] = _T("BMI");
CONST TCHAR BNE[] = _T("BNE");
CONST TCHAR BPL[] = _T("BPL");
CONST TCHAR BRK[] = _T("BRK");
CONST TCHAR BVC[] = _T("BVC");
CONST TCHAR BVS[] = _T("BVS");
CONST TCHAR CLC[] = _T("CLC");
CONST TCHAR CLD[] = _T("CLD");
CONST TCHAR CLI[] = _T("CLI");
CONST TCHAR CLV[] = _T("CLV");
CONST TCHAR CMP[] = _T("CMP");
CONST TCHAR CPX[] = _T("CPX");
CONST TCHAR CPY[] = _T("CPY");
CONST TCHAR DEC[] = _T("DEC");
CONST TCHAR DEX[] = _T("DEX");
CONST TCHAR DEY[] = _T("DEY");
CONST TCHAR EOR[] = _T("EOR");
CONST TCHAR INC[] = _T("INC");
CONST TCHAR INX[] = _T("INX");
CONST TCHAR INY[] = _T("INY");
CONST TCHAR JMP[] = _T("JMP");
CONST TCHAR JSR[] = _T("JSR");
CONST TCHAR LDA[] = _T("LDA");
CONST TCHAR LDX[] = _T("LDX");
CONST TCHAR LDY[] = _T("LDY");
CONST TCHAR LSR[] = _T("LSR");
CONST TCHAR NOP[] = _T("NOP");
CONST TCHAR ORA[] = _T("ORA");
CONST TCHAR PHA[] = _T("PHA");
CONST TCHAR PHP[] = _T("PHP");
CONST TCHAR PLA[] = _T("PLA");
CONST TCHAR PLP[] = _T("PLP");
CONST TCHAR ROL[] = _T("ROL");
CONST TCHAR ROR[] = _T("ROR");
CONST TCHAR RTI[] = _T("RTI");
CONST TCHAR RTS[] = _T("RTS");
CONST TCHAR SBC[] = _T("SBC");
CONST TCHAR SEC[] = _T("SEC");
CONST TCHAR SED[] = _T("SED");
CONST TCHAR SEI[] = _T("SEI");
CONST TCHAR STA[] = _T("STA");
CONST TCHAR STX[] = _T("STX");
CONST TCHAR STY[] = _T("STY");
CONST TCHAR TAX[] = _T("TAX");
CONST TCHAR TAY[] = _T("TAY");
CONST TCHAR TSX[] = _T("TSX");
CONST TCHAR TXA[] = _T("TXA");
CONST TCHAR TXS[] = _T("TXS");
CONST TCHAR TYA[] = _T("TYA");

CONST Instruction ADCABS = { ADC, _ABSOLUTE };
CONST Instruction ADCABSX = { ADC, ABSX };
CONST Instruction ADCABSY = { ADC, ABSY };
CONST Instruction ADCINDX = { ADC, INDX };
CONST Instruction ADCINDY = { ADC, INDY };
CONST Instruction ADCIMM = { ADC, IMMEDIATE };
CONST Instruction ADCZPAGE = { ADC, ZPAGE };
CONST Instruction ADCZPAGEX = { ADC, ZPAGEX };
CONST Instruction ANDABS = { AND, _ABSOLUTE };
CONST Instruction ANDABSX = { AND, ABSX };
CONST Instruction ANDABSY = { AND, ABSY };
CONST Instruction ANDINDX = { AND, INDX };
CONST Instruction ANDINDY = { AND, INDY };
CONST Instruction ANDIMM = { AND, IMMEDIATE };
CONST Instruction ANDZPAGE = { AND, ZPAGE };
CONST Instruction ANDZPAGEX = { AND, ZPAGEX };
CONST Instruction ASLABS = { ASL, _ABSOLUTE };
CONST Instruction ASLABSX = { ASL, ABSX };
CONST Instruction ASLACCUM = { ASL, ACCUM };
CONST Instruction ASLZPAGE = { ASL, ZPAGE };
CONST Instruction ASLZPAGEX = { ASL, ZPAGEX };
CONST Instruction BCCREL = { BCC, _RELATIVE };
CONST Instruction BCSREL = { BCS, _RELATIVE };
CONST Instruction BEQREL = { BEQ, _RELATIVE };
CONST Instruction BITABS = { BIT, _ABSOLUTE };
CONST Instruction BITZPAGE = { BIT, ZPAGE };
CONST Instruction BMIREL = { BMI, _RELATIVE };
CONST Instruction BNEREL = { BNE, _RELATIVE };
CONST Instruction BPLREL = { BPL, _RELATIVE };
CONST Instruction BRKIMP = { BRK, IMPLIED };
CONST Instruction BVCREL = { BVC, _RELATIVE };
CONST Instruction BVSREL = { BVS, _RELATIVE };
CONST Instruction CLCIMP = { CLC, IMPLIED };
CONST Instruction CLDIMP = { CLD, IMPLIED };
CONST Instruction CLIIMP = { CLI, IMPLIED };
CONST Instruction CLVIMP = { CLV, IMPLIED };
CONST Instruction CMPABS = { CMP, _ABSOLUTE };
CONST Instruction CMPABSX = { CMP, ABSX };
CONST Instruction CMPABSY = { CMP, ABSY };
CONST Instruction CMPINDX = { CMP, INDX };
CONST Instruction CMPINDY = { CMP, INDY };
CONST Instruction CMPIMM = { CMP, IMMEDIATE };
CONST Instruction CMPZPAGE = { CMP, ZPAGE };
CONST Instruction CMPZPAGEX = { CMP, ZPAGEX };
CONST Instruction CPXABS = { CPX, _ABSOLUTE };
CONST Instruction CPXIMM = { CPX, IMMEDIATE };
CONST Instruction CPXZPAGE = { CPX, ZPAGE };
CONST Instruction CPYABS = { CPY, _ABSOLUTE };
CONST Instruction CPYIMM = { CPY, IMMEDIATE };
CONST Instruction CPYZPAGE = { CPY, ZPAGE };
CONST Instruction DECABS = { DEC, _ABSOLUTE };
CONST Instruction DECABSX = { DEC, ABSX };
CONST Instruction DECZPAGE = { DEC, ZPAGE };
CONST Instruction DECZPAGEX = { DEC, ZPAGEX };
CONST Instruction DEXIMP = { DEX, IMPLIED };
CONST Instruction DEYIMP = { DEY, IMPLIED };
CONST Instruction EORABS = { EOR, _ABSOLUTE };
CONST Instruction EORABSX = { EOR, ABSX };
CONST Instruction EORABSY = { EOR, ABSY };
CONST Instruction EORINDX = { EOR, INDX };
CONST Instruction EORINDY = { EOR, INDY };
CONST Instruction EORIMM = { EOR, IMMEDIATE };
CONST Instruction EORZPAGE = { EOR, ZPAGE };
CONST Instruction EORZPAGEX = { EOR, ZPAGEX };
CONST Instruction INCABS = { INC, _ABSOLUTE };
CONST Instruction INCABSX = { INC, ABSX };
CONST Instruction INCZPAGE = { INC, ZPAGE };
CONST Instruction INCZPAGEX = { INC, ZPAGEX };
CONST Instruction INXIMP = { INX, IMPLIED };
CONST Instruction INYIMP = { INY, IMPLIED };
CONST Instruction JMPABS = { JMP, _ABSOLUTE };
CONST Instruction JMPIND = { JMP, IND };
CONST Instruction JSRABS = { JSR, _ABSOLUTE };
CONST Instruction LDAABS = { LDA, _ABSOLUTE };
CONST Instruction LDAABSX = { LDA, ABSX };
CONST Instruction LDAABSY = { LDA, ABSY };
CONST Instruction LDAINDX = { LDA, INDX };
CONST Instruction LDAINDY = { LDA, INDY };
CONST Instruction LDAIMM = { LDA, IMMEDIATE };
CONST Instruction LDAZPAGE = { LDA, ZPAGE };
CONST Instruction LDAZPAGEX = { LDA, ZPAGEX };
CONST Instruction LDXABS = { LDX, _ABSOLUTE };
CONST Instruction LDXABSY = { LDX, ABSY };
CONST Instruction LDXIMM = { LDX, IMMEDIATE };
CONST Instruction LDXZPAGE = { LDX, ZPAGE };
CONST Instruction LDXZPAGEY = { LDX, ZPAGEY };
CONST Instruction LDYABS = { LDY, _ABSOLUTE };
CONST Instruction LDYABSX = { LDY, ABSX };
CONST Instruction LDYIMM = { LDY, IMMEDIATE };
CONST Instruction LDYZPAGE = { LDY, ZPAGE };
CONST Instruction LDYZPAGEX = { LDY, ZPAGEX };
CONST Instruction LSRABS = { LSR, _ABSOLUTE };
CONST Instruction LSRABSX = { LSR, ABSX };
CONST Instruction LSRACCUM = { LSR, ACCUM };
CONST Instruction LSRZPAGE = { LSR, ZPAGE };
CONST Instruction LSRZPAGEX = { LSR, ZPAGEX };
CONST Instruction NOPIMP = { NOP, IMPLIED };
CONST Instruction ORAABS = { ORA, _ABSOLUTE };
CONST Instruction ORAABSX = { ORA, ABSX };
CONST Instruction ORAABSY = { ORA, ABSY };
CONST Instruction ORAINDX = { ORA, INDX };
CONST Instruction ORAINDY = { ORA, INDY };
CONST Instruction ORAIMM = { ORA, IMMEDIATE };
CONST Instruction ORAZPAGE = { ORA, ZPAGE };
CONST Instruction ORAZPAGEX = { ORA, ZPAGEX };
CONST Instruction PHAIMP = { PHA, IMPLIED };
CONST Instruction PHPIMP = { PHP, IMPLIED };
CONST Instruction PLAIMP = { PLA, IMPLIED };
CONST Instruction PLPIMP = { PLP, IMPLIED };
CONST Instruction ROLABS = { ROL, _ABSOLUTE };
CONST Instruction ROLABSX = { ROL, ABSX };
CONST Instruction ROLACCUM = { ROL, ACCUM };
CONST Instruction ROLZPAGE = { ROL, ZPAGE };
CONST Instruction ROLZPAGEX = { ROL, ZPAGEX };
CONST Instruction RORABS = { ROR, _ABSOLUTE };
CONST Instruction RORABSX = { ROR, ABSX };
CONST Instruction RORACCUM = { ROR, ACCUM };
CONST Instruction RORZPAGE = { ROR, ZPAGE };
CONST Instruction RORZPAGEX = { ROR, ZPAGEX };
CONST Instruction RTIIMP = { RTI, IMPLIED };
CONST Instruction RTSIMP = { RTS, IMPLIED };
CONST Instruction SBCABS = { SBC, _ABSOLUTE };
CONST Instruction SBCABSX = { SBC, ABSX };
CONST Instruction SBCABSY = { SBC, ABSY };
CONST Instruction SBCINDX = { SBC, INDX };
CONST Instruction SBCINDY = { SBC, INDY };
CONST Instruction SBCIMM = { SBC, IMMEDIATE };
CONST Instruction SBCZPAGE = { SBC, ZPAGE };
CONST Instruction SBCZPAGEX = { SBC, ZPAGEX };
CONST Instruction SECIMP = { SEC, IMPLIED };
CONST Instruction SEDIMP = { SED, IMPLIED };
CONST Instruction SEIIMP = { SEI, IMPLIED };
CONST Instruction STAABS = { STA, _ABSOLUTE };
CONST Instruction STAABSX = { STA, ABSX };
CONST Instruction STAABSY = { STA, ABSY };
CONST Instruction STAINDX = { STA, INDX };
CONST Instruction STAINDY = { STA, INDY };
CONST Instruction STAZPAGE = { STA, ZPAGE };
CONST Instruction STAZPAGEX = { STA, ZPAGE };
CONST Instruction STXABS = { STX, _ABSOLUTE };
CONST Instruction STXZPAGE = { STX, ZPAGE };
CONST Instruction STXZPAGEY = { STX, ZPAGEY };
CONST Instruction STYABS = { STY, _ABSOLUTE };
CONST Instruction STYZPAGE = { STY, ZPAGE };
CONST Instruction STYZPAGEX = { STY, ZPAGE };
CONST Instruction TAXIMP = { TAX, IMPLIED };
CONST Instruction TAYIMP = { TAY, IMPLIED };
CONST Instruction TSXIMP = { TSX, IMPLIED };
CONST Instruction TXAIMP = { TXA, IMPLIED };
CONST Instruction TXSIMP = { TXS, IMPLIED };
CONST Instruction TYAIMP = { TYA, IMPLIED };

/* instructions */
CONST Instruction* instructions[] = {
    &BRKIMP,	/* 0X00 */
    &ORAINDX,	/* 0X01 */
    NULL,		/* 0X02 */
    NULL,		/* 0X03 */
    NULL,		/* 0X04 */
    &ORAZPAGE,	/* 0X05 */
    &ASLZPAGE,	/* 0X06 */
    NULL,		/* 0X07 */
    &PHPIMP,	/* 0X08 */
    &ORAIMM,	/* 0X09 */
    &ASLACCUM,	/* 0X0A */
    NULL,		/* 0X0B */
    NULL,		/* 0X0C */
    &ORAABS,	/* 0X0D */
    &ASLABS,	/* 0X0E */
    NULL,		/* 0X0F */
    &BPLREL,	/* 0X10 */
    &ORAINDY,   /* 0X11 */
    NULL,		/* 0X12 */
    NULL,		/* 0X13 */
    NULL,		/* 0X14 */
    &ORAZPAGEX, /* 0X15 */
    &ASLZPAGEX, /* 0X16 */
    NULL,		/* 0X17 */
    &CLCIMP,	/* 0X18 */
    &ORAABSY,   /* 0X19 */
    NULL,		/* 0X1A */
    NULL,		/* 0X1B */
    NULL,		/* 0X1C */
    &ORAABSX,   /* 0X1D */
    &ASLABSX,   /* 0X1E */
    NULL,		/* 0X1F */
    &JSRABS,	/* 0X20 */
    &ANDINDX,   /* 0X21 */
    NULL,		/* 0X22 */
    NULL,		/* 0X23 */
    &BITZPAGE,	/* 0X24 */
    &ANDZPAGE,	/* 0X25 */
    &ROLZPAGE,	/* 0X26 */
    NULL,		/* 0X27 */
    &PLPIMP,	/* 0X28 */
    &ANDIMM,	/* 0X29 */
    &ROLACCUM,  /* 0X2A */
    NULL,		/* 0X2B */
    &BITABS,	/* 0X2C */
    &ANDABS,	/* 0X2D */
    &ROLABS,	/* 0X2E */
    NULL,		/* 0X2F */
    &BMIREL,	/* 0X30 */
    &ANDINDY,   /* 0X31 */
    NULL,		/* 0X32 */
    NULL,		/* 0X33 */
    NULL,		/* 0X34 */
    &ANDZPAGEX, /* 0X35 */
    &ROLZPAGEX, /* 0X36 */
    NULL,		/* 0X37 */
    &SECIMP,	/* 0X38 */
    &ANDABSY,   /* 0X39 */
    NULL,		/* 0X3A */
    NULL,		/* 0X3B */
    NULL,		/* 0X3C */
    &ANDABSX,   /* 0X3D */
    &ROLABSX,   /* 0X3E */
    NULL,		/* 0X3F */
    &RTIIMP,	/* 0X40 */
    &EORINDX,   /* 0X41 */
    NULL,		/* 0X42 */
    NULL,		/* 0X43 */
    NULL,		/* 0X44 */
    &EORZPAGE,	/* 0X45 */
    &LSRZPAGE,	/* 0X46 */
    NULL,		/* 0X47 */
    &PHAIMP,	/* 0X48 */
    &EORIMM,	/* 0X49 */
    &LSRACCUM,  /* 0X4A */
    NULL,		/* 0X4B */
    &JMPABS,	/* 0X4C */
    &EORABS,	/* 0X4D */
    &LSRABS,	/* 0X4E */
    NULL,		/* 0X4F */
    &BVCREL,	/* 0X50 */
    &EORINDY,   /* 0X51 */
    NULL,		/* 0X52 */
    NULL,		/* 0X53 */
    NULL,		/* 0X54 */
    &EORZPAGEX, /* 0X55 */
    &LSRZPAGEX, /* 0X56 */
    NULL,		/* 0X57 */
    &CLIIMP,	/* 0X58 */
    &EORABSY,   /* 0X59 */
    NULL,		/* 0X5A */
    NULL,		/* 0X5B */
    NULL,		/* 0X5C */
    &EORABSX,   /* 0X5D */
    &LSRABSX,   /* 0X5E */
    NULL,		/* 0X5F */
    &RTSIMP,	/* 0X60 */
    &ADCINDX,   /* 0X61 */
    NULL,		/* 0X62 */
    NULL,		/* 0X63 */
    NULL,		/* 0X64 */
    &ADCZPAGE,	/* 0X65 */
    &RORZPAGE,	/* 0X66 */
    NULL,		/* 0X67 */
    &PLAIMP,	/* 0X68 */
    &ADCIMM,	/* 0X69 */
    &RORACCUM,  /* 0X6A */
    NULL,		/* 0X6B */
    &JMPIND,	/* 0X6C */
    &ADCABS,	/* 0X6D */
    &RORABS,	/* 0X6E */
    NULL,		/* 0X6F */
    &BVSREL,	/* 0X70 */
    &ADCINDY,   /* 0X71 */
    NULL,		/* 0X72 */
    NULL,		/* 0X73 */
    NULL,		/* 0X74 */
    &ADCZPAGEX, /* 0X75 */
    &RORZPAGEX, /* 0X76 */
    NULL,		/* 0X77 */
    &SEIIMP,	/* 0X78 */
    &ADCABSY,   /* 0X79 */
    NULL,		/* 0X7A */
    NULL,		/* 0X7B */
    NULL,		/* 0X7C */
    &ADCABSX,   /* 0X7D */
    &RORABSX,   /* 0X7E */
    NULL,		/* 0X7F */
    NULL,		/* 0X80 */
    &STAINDX,	/* 0X81 */
    NULL,		/* 0X82 */
    NULL,		/* 0X83 */
    &STYZPAGE,	/* 0X84 */
    &STAZPAGE,	/* 0X85 */
    &STXZPAGE,	/* 0X86 */
    NULL,		/* 0X87 */
    &DEYIMP,	/* 0X88 */
    NULL,		/* 0X89 */
    &TXAIMP,	/* 0X8A */
    NULL,		/* 0X8B */
    &STYABS,	/* 0X8C */
    &STAABS,	/* 0X8D */
    &STXABS,	/* 0X8E */
    NULL,		/* 0X8F */
    &BCCREL,	/* 0X90 */
    &STAINDY,	/* 0X91 */
    NULL,		/* 0X92 */
    NULL,		/* 0X93 */
    &STYZPAGEX,	/* 0X94 */
    &STAZPAGEX,	/* 0X95 */
    &STXZPAGEY,	/* 0X96 */
    NULL,		/* 0X97 */
    &TYAIMP,	/* 0X98 */
    &STAABSY,	/* 0X99 */
    &TXSIMP,	/* 0X9A */
    NULL,		/* 0X9B */
    NULL,		/* 0X9C */
    &STAABSX,	/* 0X9D */
    NULL,		/* 0X9E */
    NULL,		/* 0X9F */
    &LDYIMM,	/* 0XA0 */
    &LDAINDX,	/* 0XA1 */
    &LDXIMM,	/* 0XA2 */
    NULL,		/* 0XA3 */
    &LDYZPAGE,	/* 0XA4 */
    &LDAZPAGE,	/* 0XA5 */
    &LDXZPAGE,	/* 0XA6 */
    NULL,		/* 0XA7 */
    &TAYIMP,	/* 0XA8 */
    &LDAIMM,	/* 0XA9 */
    &TAXIMP,	/* 0XAA */
    NULL,		/* 0XAB */
    &LDYABS,	/* 0XAC */
    &LDAABS,	/* 0XAD */
    &LDXABS,	/* 0XAE */
    NULL,		/* 0XAF */
    &BCSREL,	/* 0XB0 */
    &LDAINDY,	/* 0XB1 */
    NULL,		/* 0XB2 */
    NULL,		/* 0XB3 */
    &LDYZPAGEX,	/* 0XB4 */
    &LDAZPAGEX,	/* 0XB5 */
    &LDXZPAGEY,	/* 0XB6 */
    NULL,		/* 0XB7 */
    &CLVIMP,	/* 0XB8 */
    &LDAABSY,	/* 0XB9 */
    &TSXIMP,	/* 0XBA */
    NULL,		/* 0XBB */
    &LDYABSX,	/* 0XBC */
    &LDAABSX,	/* 0XBD */
    &LDXABSY,	/* 0XBE */
    NULL,		/* 0XBF */
    &CPYIMM,	/* 0XC0 */
    &CMPINDX,	/* 0XC1 */
    NULL,		/* 0XC2 */
    NULL,		/* 0XC3 */
    &CPYZPAGE,	/* 0XC4 */
    &CMPZPAGE,	/* 0XC5 */
    &DECZPAGE,	/* 0XC6 */
    NULL,		/* 0XC7 */
    &INYIMP,	/* 0XC8 */
    &CMPIMM,	/* 0XC9 */
    &DEXIMP,	/* 0XCA */
    NULL,		/* 0XCB */
    &CPYABS,	/* 0XCC */
    &CMPABS,	/* 0XCD */
    &DECABS,	/* 0XCE */
    NULL,		/* 0XCF */
    &BNEREL,	/* 0XD0 */
    &CMPINDY,	/* 0XD1 */
    NULL,		/* 0XD2 */
    NULL,		/* 0XD3 */
    NULL,		/* 0XD4 */
    &CMPZPAGEX,	/* 0XD5 */
    &DECZPAGEX,	/* 0XD6 */
    NULL,		/* 0XD7 */
    &CLDIMP,	/* 0XD8 */
    &CMPABSY,	/* 0XD9 */
    NULL,		/* 0XDA */
    NULL,		/* 0XDB */
    NULL,		/* 0XDC */
    &CMPABSX,	/* 0XDD */
    &DECABSX,	/* 0XDE */
    NULL,		/* 0XDF */
    &CPXIMM,	/* 0XE0 */
    &SBCINDX,	/* 0XE1 */
    NULL,		/* 0XE2 */
    NULL,		/* 0XE3 */
    &CPXZPAGE,	/* 0XE4 */
    &SBCZPAGE,	/* 0XE5 */
    &INCZPAGE,	/* 0XE6 */
    NULL,		/* 0XE7 */
    &INXIMP,	/* 0XE8 */
    &SBCIMM,	/* 0XE9 */
    &NOPIMP,	/* 0XEA */
    NULL,		/* 0XEB */
    &CPXABS,	/* 0XEC */
    &SBCABS,	/* 0XED */
    &INCABS,	/* 0XEE */
    NULL,		/* 0XEF */
    &BEQREL,	/* 0XF0 */
    &SBCINDY,	/* 0XF1 */
    NULL,		/* 0XF2 */
    NULL,		/* 0XF3 */
    NULL,		/* 0XF4 */
    &SBCZPAGEX,	/* 0XF5 */
    &INCZPAGEX,	/* 0XF6 */
    NULL,		/* 0XF7 */
    &SEDIMP,	/* 0XF8 */
    &SBCABSY,	/* 0XF9 */
    NULL,		/* 0XFA */
    NULL,		/* 0XFB */
    NULL,		/* 0XFC */
    &SBCABSX,	/* 0XFD */
    &INCABSX,	/* 0XFE */
    NULL		/* 0XFF */
};

}	// anonymous

/////////////////////////////////////////////////////////////////////////////
Disassembler::Disassembler()
{
    init();
}

/////////////////////////////////////////////////////////////////////////////
Disassembler::~Disassembler()
{
}

/////////////////////////////////////////////////////////////////////////////
void Disassembler::init()
{
}

/////////////////////////////////////////////////////////////////////////////
CString Disassembler::Get(USHORT &address)
{
    Memory *mem = Memory::instance();
    BYTE b = mem->Get(address);

    const Instruction *pInstr = instructions[b];

    return FormatInstruction(pInstr, b, address);
}

/////////////////////////////////////////////////////////////////////////////
CString Disassembler::FormatInstruction(const Instruction *pInstr,
                                        BYTE b, USHORT &address)
{
    CString output;
    USHORT save = address;

    if (pInstr == NULL) {
        output.Format(_T("$%.4hX: %.2hX ???"), address++, b);
    } else {
        output.Format(_T("$%.4hX: %.2hX %s"), save, b,
                      FormatInstruction(pInstr, address));
    }

    return output;
}

/////////////////////////////////////////////////////////////////////////////
CString Disassembler::FormatInstruction(const Instruction *pInstr,
                                        USHORT &address)
{
    Memory *mem = Memory::instance();

    BYTE b1, b2;
    CString output;

    switch (pInstr->mode) {
    case IMMEDIATE:
        address++;
        b1 = mem->Get(address++);
        output.Format(_T("%.2hX      %s #$%.2hX"),
                      b1, pInstr->mnemonic, b1);
        break;
    case _ABSOLUTE:
        address++;
        b1 = mem->Get(address++);
        b2 = mem->Get(address++);
        output.Format(_T("%.2hX %.2hX   %s $%.4hX"),
                      b1, b2, pInstr->mnemonic, MAKEWORD(b1, b2));
        break;
    case ZPAGE:
        address++;
        b1 = mem->Get(address++);
        output.Format(_T("%.2hX      %s $%.2hX"),
                      b1, pInstr->mnemonic, b1);
        break;
    case ACCUM:
        address++;
        output.Format(_T("        %s"), pInstr->mnemonic);
        break;
    case IMPLIED:
        address++;
        output.Format(_T("        %s"), pInstr->mnemonic);
        break;
    case INDX:
        address++;
        b1 = mem->Get(address++);
        output.Format(_T("%.2hX      %s ($%.2hX, X)"),
                      b1, pInstr->mnemonic, b1);
        break;
    case INDY:
        address++;
        b1 = mem->Get(address++);
        output.Format(_T("%.2hX      %s ($%.2hX), Y"),
                      b1, pInstr->mnemonic, b1);
        break;
    case ZPAGEX:
        address++;
        b1 = mem->Get(address++);
        output.Format(_T("%.2hX      %s $%.2hX, X"),
                      b1, pInstr->mnemonic, b1);
        break;
    case ABSX:
        address++;
        b1 = mem->Get(address++);
        b2 = mem->Get(address++);
        output.Format(_T("%.2hX %.2hX   %s $%.4hX, X"),
                      b1, b2, pInstr->mnemonic, MAKEWORD(b1, b2));
        break;
    case ABSY:
        address++;
        b1 = mem->Get(address++);
        b2 = mem->Get(address++);
        output.Format(_T("%.2hX %.2hX   %s $%.4hX, Y"),
                      b1, b2, pInstr->mnemonic, MAKEWORD(b1, b2));
        break;
    case IND:
        address++;
        b1 = mem->Get(address++);
        b2 = mem->Get(address++);
        output.Format(_T("%.2hX %.2hX   %s ($%.4hX)"),
                      b1, b2, pInstr->mnemonic, MAKEWORD(b1, b2));
        break;
    case ZPAGEY:
        address++;
        b1 = mem->Get(address++);
        output.Format(_T("%.2hX      %s $%.2hX, Y"),
                      b1, pInstr->mnemonic, b1);
        break;
    case _RELATIVE:
        address++;
        b1 = mem->Get(address++);
        output.Format(_T("%.2hX      %s $%.2hX"),
                      b1, pInstr->mnemonic, b1);
        break;
    };

    return output;
}