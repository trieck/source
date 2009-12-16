/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.CPP : simple runtime machine
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
Instruction Machine::lookup(uint32_t opcode)
{
	Machine *machine = Machine::getInstance();

	InstrMap::const_iterator it = machine->m_instr.find(opcode);
	if (it == machine->m_instr.end())
		return NULL;

	return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
void Machine::exec(const Program &program)
{
	m_pc = program;
	
	while (m_pc->type != DT_UNDEF)
		eval();
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::eval()
{
	Datum d;
	switch (m_pc->type) {
	case DT_UNDEF:
		return d;
	case DT_SYM:
		return evalsym(m_pc++->sym);
	case DT_INSTR:
		return (this->*m_pc++->instr)();
	default:
		return *m_pc++; 
	};
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::evalsym(LPSYMBOL s)
{
	Datum d;
	Instruction i;

	switch (s->type) {
	case ST_UNDEF:
		throw Exception("identifier \"%s\" was undefined.", 
			s->name.c_str());
	case ST_OP:
		if ((i = lookup(s->opcode)) == NULL) {
			throw Exception("unrecognized opcode %d.", s->opcode);
		}
		return (this->*i)();
	default:
		d.type = DT_CONST;
		d.value = s->val16;
		return d;
	};
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::plus()
{
	Datum d1 = eval();
	Datum d2 = eval();

	Datum result;
	result.type = DT_CONST;
	result.value = d1.value + d2.value;

	return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::minus()
{
	Datum d;
	return d;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::mult()
{
	Datum d;
	return d;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::div()
{
	Datum d;
	return d;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::hibyte()
{
	Datum arg = eval();

	Datum result;
	
	return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::lobyte()
{
	Datum arg = eval();

	Datum result;
	
	return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::fixup()
{
	Datum result;

	return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::memstore()
{
	Datum ctxt = eval();
	Datum loc = eval();
	Datum value = eval();

	if (ctxt.value == IM16) {
		m_code->putWordAt(loc.value, value.value);
	} else {
		m_code->putByteAt(loc.value, (byte)value.value);
	}

	return value;
}

