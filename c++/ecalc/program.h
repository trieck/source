/////////////////////////////////////////////////////////////////////////////
//
//	PROGRAM.H	compiled machine program
//
//	Copyright (c) 1999 Thomas A. Rieck
//

#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#define NPROG 2048
#define STOP (Instr)NULL

/////////////////////////////////////////////////////////////////////////////
class Program {
public:
// Construction / Destruction
    Program();
    Program (const Program &);
    ~Program();

// Interface
    void init();
    Program & operator = (const Program &);
    const Instr * code (Instr instruction);
    const Instr * code (const Symbol * data);
    const Instr * set(const Instr * offset, Instr instr);
    const Instr * setjumpat (const Instr * offset);
    void define(const char *, SymbolType type);

    operator const Instr* () const;
    const Instr * operator++(int);	// postfix
private:
// Implementation

    Instr memory[NPROG];
    Instr * pmem;
    Instr * pbase;
};

/////////////////////////////////////////////////////////////////////////////

inline Program::operator const Instr * () const
{
    return pbase;
}

inline const Instr * Program::operator++(int)
{
    return pmem++;
}

#endif // __PROGRAM_H__

