/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.H : simple stack based machine
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MACHINE_H__
#define __MACHINE_H__

#include "Stack.h"

// forward references
class Code;
class Machine;

typedef auto_ptr<Machine> MachinePtr;

typedef void (Machine::*Instruction)(void);

/////////////////////////////////////////////////////////////////////////////
class Machine
{
// Construction / destruction
private:
	Machine();
public:
	~Machine();

// Interface
	static Machine *getInstance();
	
	void initialize();
	void execute();
	Instruction lookup(uint32_t opcode) const;

// Implementation
private:
	
	// instructions
	void plus();
	void minus();
	void mult();
	void div();
	void hibyte();
	void lobyte();
	void sympush();
	void constpush();
	void fixup();

	void checkSym(LPSYMBOL s);

	typedef map<uint32_t, Machine::Instruction> InstrMap;

	static MachinePtr instance;	// singleton instance
	InstrMap m_instr;			// instruction map
	Stack m_stack;				// machine stack
	const Instruction *m_pc;	// program counter
	Code *m_code;				// code pointer
	friend class Code;
};

#endif // __MACHINE_H__