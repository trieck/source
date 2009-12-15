/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.CPP : simple stack based machine
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Machine.h"
#include "SymbolTable.h"
#include "Parser.hpp"
#include "Program.h"
#include "Code.h"
#include "Exception.h"

MachinePtr Machine::instance(Machine::getInstance());

extern Program program;

/////////////////////////////////////////////////////////////////////////////
Machine::Machine() : m_pc(NULL)
{
	m_code = Code::getInstance();

	m_instr[PLUS] = &Machine::plus;
	m_instr[MINUS] = &Machine::minus;
	m_instr[MULT] = &Machine::mult;
	m_instr[DIV] = &Machine::div;
	m_instr[LO_BYTE] = &Machine::lobyte;
	m_instr[HI_BYTE] = &Machine::hibyte;
}

/////////////////////////////////////////////////////////////////////////////
Machine::~Machine()
{
}

/////////////////////////////////////////////////////////////////////////////
Machine *Machine::getInstance()
{
	if (instance.get() == NULL) {
		instance = MachinePtr(new Machine);
	}
	return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
Instruction Machine::lookup(uint32_t opcode) const
{
	InstrMap::const_iterator it = m_instr.find(opcode);
	if (it == m_instr.end())
		return NULL;

	return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
void Machine::initialize()
{
	program.init();
	m_stack.reset();
}

/////////////////////////////////////////////////////////////////////////////
void Machine::execute()
{
	m_pc = program;
	
	while (*m_pc != NULL) {
		(this->*(*m_pc++))();
	}

}

/////////////////////////////////////////////////////////////////////////////
void Machine::plus()
{
}

/////////////////////////////////////////////////////////////////////////////
void Machine::minus()
{
}

/////////////////////////////////////////////////////////////////////////////
void Machine::mult()
{
}

/////////////////////////////////////////////////////////////////////////////
void Machine::div()
{
}

/////////////////////////////////////////////////////////////////////////////
void Machine::hibyte()
{
	Datum ctxt = m_stack.pop();
	Datum loc = m_stack.pop();
	Datum dsym = m_stack.pop();

	checkSym(dsym.sym);

	m_code->putByteAt(loc.value, HIBYTE(dsym.sym->val16));
}

/////////////////////////////////////////////////////////////////////////////
void Machine::lobyte()
{
	Datum ctxt = m_stack.pop();
	Datum loc = m_stack.pop();
	Datum dsym = m_stack.pop();

	checkSym(dsym.sym);

	m_code->putByteAt(loc.value, LOBYTE(dsym.sym->val16));	
}

/////////////////////////////////////////////////////////////////////////////
void Machine::fixup()
{
	Datum ctxt = m_stack.pop();
	Datum loc = m_stack.pop();
	Datum dsym = m_stack.pop();

	checkSym(dsym.sym);

	word symloc = dsym.sym->val16;
	word fixloc = loc.value;
	
	if (ctxt.value == IM8) {	// relative branch fix-up
		word diff = symloc - fixloc;
		if (diff > 0x7F) {
			throw Exception("branch out of range for label \"%s\".",
				dsym.sym->name.c_str());
		}		
		m_code->putByteAt(fixloc, (byte)diff);
	} else {	// forward reference
		m_code->putWordAt(fixloc, symloc);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Machine::sympush()
{
	LPSYMBOL sym = *(LPSYMBOL*)++m_pc;
	m_stack.push(sym);
}

/////////////////////////////////////////////////////////////////////////////
void Machine::constpush()
{
	word w = *(word*)++m_pc;
	m_stack.push(w);
}

/////////////////////////////////////////////////////////////////////////////
void Machine::checkSym(LPSYMBOL s)
{
	// ensure symbol value has been defined
	if (s->type == ST_UNDEF) {
		throw Exception("identifier \"%s\" was never defined.", 
			s->name.c_str());
	}
}
