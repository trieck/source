/////////////////////////////////////////////////////////////////////////////
//
//	PROGRAM.CPP		compiled machine program
//
//	Copyright (c) 1999 Thomas A. Rieck
//

#include "common.h"
#include "program.h"
#include "symbol.h"
#include <iostream>

extern SymbolTable symbols;

static void fatalerror(const char* error);

//
// Constructor
//
Program::Program()
{ 
	memory[0] = STOP;
	pbase = pmem = memory;
}

//
// Destructor
//
Program::~Program()
{
}

//
// Copy constructor
//
Program::Program (const Program & prog)
{
	memcpy(memory, prog.memory, NPROG * sizeof(Instr));
	pmem = memory + (prog.pmem - prog.memory);
	pbase = memory + (prog.pbase - prog.memory);
}

//
// operator = 
//
Program & Program::operator = (const Program & prog)
{
	if (this != &prog) {
		memcpy(memory, prog.memory, NPROG * sizeof(Instr));
		pmem = memory + (prog.pmem - prog.memory);
		pbase = memory + (prog.pbase - prog.memory);
	}

	return *this;
}

//
// init
//
void Program::init()
{
	pmem = pbase;
}

//
// code
//
const Instr * Program::code(Instr instruction)
{
	if (pmem >= &memory[NPROG])
		fatalerror ("memory overflow.");

	*pmem = instruction;

	return pmem++;
}

//
// code
//
const Instr * Program::code(const Symbol * data)
{
	Instr instruction = * reinterpret_cast<Instr*>(&data);

	return code(instruction);
}

//
// set
//
const Instr * Program::set(const Instr * offset, Instr instruction)
{
	const Instr * pmem = memory;

	return &(memory[offset - pmem] = instruction);
}

//
// setjumpat 
//
const Instr * Program::setjumpat (const Instr * offset)
{
	Instr i = * reinterpret_cast<Instr*>(&pmem);

	const Instr * pmem = memory;

	return &(memory[offset - pmem] = i);
}

//
// define
// define procedure / function
//
void Program::define(const char *name, SymbolType type)
{
	symbols.install(name, type, pbase);
	pbase = pmem;
}

// Helper functions

//
// fatalerror
//
void fatalerror(const char *error)
{
	cerr << error << endl;
	exit (-1);
}
