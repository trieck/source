/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.H : simple runtime machine
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MACHINE_H__
#define __MACHINE_H__

#include "Program.h"

// forward references
class Code;
class Machine;

typedef auto_ptr<Machine> MachinePtr;

/////////////////////////////////////////////////////////////////////////////
class Machine {
// Construction / destruction
private:
	Machine();
public:
	~Machine();

// Interface
	static Machine *getInstance();

	void exec(const Program &program);
	static Instruction lookup(uint32_t opcode);

// Implementation
private:
	Datum eval();
	Datum evalsym(LPSYMBOL s);

	// instructions
	Datum plus();
	Datum minus();
	Datum mult();
	Datum div();
	Datum hibyte();
	Datum lobyte();
	Datum fixup();
	Datum memstore();

	typedef map<uint32_t, Machine::Instruction> InstrMap;

	static MachinePtr instance;	// singleton instance
	InstrMap m_instr;			// instruction map
	const Datum *m_pc;			// program counter
	Code *m_code;				// code pointer
	friend class Code;
};

#endif // __MACHINE_H__
