/////////////////////////////////////////////////////////////////////////////
//
// PROGRAM.CPP : expression machine program
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Program.h"
#include "Machine.h"
#include "Exception.h"

/////////////////////////////////////////////////////////////////////////////
Program::Program() : m_pmem(m_memory)
{
	memset(m_memory, 0, sizeof(Instruction) * NPROG);
}

/////////////////////////////////////////////////////////////////////////////
Program::~Program()
{
}

/////////////////////////////////////////////////////////////////////////////
void Program::init()
{
	m_pmem = m_memory;
}

/////////////////////////////////////////////////////////////////////////////
void Program::opcode(uint32_t opcode)
{
	Machine *machine = Machine::getInstance();
	Instruction i;
	
	if ((i = machine->lookup(opcode)) == NULL) {
		throw Exception("unrecognized opcode %d.", opcode);
	}

	code(i);
}

/////////////////////////////////////////////////////////////////////////////
void Program::code(word location)
{
	Instruction i = *reinterpret_cast<Instruction*>(&location);
	put(i);
}

/////////////////////////////////////////////////////////////////////////////
void Program::code(Instruction i)
{
	put(i);	
}

/////////////////////////////////////////////////////////////////////////////
void Program::code(LPSYMBOL s)
{
	Instruction i = *reinterpret_cast<Instruction*>(&s);
	put(i);
}

/////////////////////////////////////////////////////////////////////////////
void Program::put(Instruction i)
{
	if (m_pmem >= &m_memory[NPROG])
		throw Exception("memory overflow.");

	*m_pmem++ = i;
}