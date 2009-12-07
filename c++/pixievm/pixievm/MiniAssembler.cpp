/////////////////////////////////////////////////////////////////////////////
//
// MINIASSEMBLER.CPP : Mini Assembler
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Memory.h"
#include "Opcodes.h"
#include "Modes.h"
#include "Instructions.h"
#include "SymbolTable.h"
#include "MiniAssembler.h"
#include "Exception.h"
#include "Parser.hpp"
#include "CPU.h"

extern int yyparse(void);
extern void yyrestart(FILE *);
extern FILE *yyin;

/* address of assembly */
word address = 0x0000;

/////////////////////////////////////////////////////////////////////////////
MiniAssembler::MiniAssembler() : init(false)
{
	table = SymbolTable::getInstance();
}

/////////////////////////////////////////////////////////////////////////////
void MiniAssembler::prompt()
{
	fprintf(stdout, "$%.4hx: ", address);
}

/////////////////////////////////////////////////////////////////////////////
void MiniAssembler::assemble(word *start)
{
	if (start) {		/* start address supplied */
		address = *start;
	} else if (!init) {	/* not entered */
		address = CPU::getInstance()->getIP();
		init = true;
	}

	for (;;) {
		prompt();
		try {
			if (parse()) break;
		} catch (const Exception &e) {
			yyrestart(yyin);
			cerr << e.getDescription() << endl;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
int MiniAssembler::parse()
{
	int nret = yyparse();
	table->flushtmp();
	return nret;
}