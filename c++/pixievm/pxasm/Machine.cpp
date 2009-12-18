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
		throw Exception("identifier \"%s\" was undefined near line %d.",
		                s->name.c_str(), s->lineno);
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
	Datum d1 = eval();
	Datum d2 = eval();

	Datum result;
	result.type = DT_CONST;
	result.value = d1.value - d2.value;

	return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::mult()
{
	Datum d1 = eval();
	Datum d2 = eval();

	Datum result;
	result.type = DT_CONST;
	result.value = d1.value * d2.value;

	return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::div()
{
	Datum d1 = eval();
	Datum d2 = eval();

	Datum result;
	result.type = DT_CONST;
	result.value = d1.value / d2.value;

	return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::hibyte()
{
	Datum arg = eval();

	Datum result;
	result.type = DT_CONST;
	result.value = HIBYTE(arg.value);

	return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::lobyte()
{
	Datum arg = eval();

	Datum result;
	result.type = DT_CONST;
	result.value = LOBYTE(arg.value);

	return result;
}

/////////////////////////////////////////////////////////////////////////////
Datum Machine::fixup()
{
	Datum ctxt = eval();
	Datum loc = eval();
	Datum target = eval();

	if (ctxt.value == IM8) {	// relative branch fix-up
		int16_t diff = target.value - (loc.value+1);
		
		if (diff < (int8_t)0x80) {	// backward branch
			throw Exception("backward branch out of range.");
		} else if (diff > 0x7F) {	// forward branch
			throw Exception("forward branch out of range.");
		}
		m_code->putByteAt(loc.value, (byte)diff);
	} else {	// forward reference
		m_code->putWordAt(loc.value, target.value);
	}

	return target;
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

