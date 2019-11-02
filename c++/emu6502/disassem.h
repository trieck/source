/////////////////////////////////////////////////////////////////////////////
//
//	DISASSEM.H : 6502 CPU Disassembler
//
//	Copyright(c) 2003, Thomas A. Rieck
//

#ifndef __DISASSEM_H__
#define __DISASSEM_H__

enum Modes {
    IMMEDIATE = 0,
    _ABSOLUTE,	/* conflicts with wingdi.h */
    ZPAGE,
    ACCUM,
    IMPLIED,
    INDX,
    INDY,
    ZPAGEX,
    ABSX,
    ABSY,
    IND,
    ZPAGEY,
    _RELATIVE	/* conflicts with wingdi.h */
};

typedef struct tagInstruction {
    LPCTSTR mnemonic;
    Modes mode;
} Instruction;

/////////////////////////////////////////////////////////////////////////////
class Disassembler
{

// Construction / Destruction
public:
    Disassembler();
    ~Disassembler();

// Interface
    CString Get(USHORT &address);

// Implementation
private:
    void init();
    CString FormatInstruction(const Instruction *pInstr, BYTE b,
                              USHORT &address);
    CString FormatInstruction(const Instruction *pInstr, USHORT &address);
};

#endif // __DISASSEM_H__