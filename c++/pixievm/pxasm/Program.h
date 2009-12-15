/////////////////////////////////////////////////////////////////////////////
//
// PROGRAM.H : expression machine program
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "Machine.h"
#include "SymbolTable.h"

/////////////////////////////////////////////////////////////////////////////
class Program
{
public:
	Program();
	~Program();

	void init();
	void opcode(uint32_t opcode);
	void code(word location);
	void code(Instruction i);
	void code(LPSYMBOL s);

	operator const Instruction*() const;
private:
	void put(Instruction i);

	enum { NPROG = 4096 };

	Instruction m_memory[NPROG];
	Instruction *m_pmem;
};

/////////////////////////////////////////////////////////////////////////////
inline Program::operator const Instruction*() const {
	return m_memory;
}

#endif // __PROGRAM_H__