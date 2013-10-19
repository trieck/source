/////////////////////////////////////////////////////////////////////////////
//
// MINIASSEMBLER.CPP : Mini Assembler
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
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

struct yy_buffer_state;
typedef yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char *str);
extern void yy_switch_to_buffer(YY_BUFFER_STATE buffer);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

// address of assembly
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
	initialize(start);

	for (;;) {
		prompt();
		if (!tryParse())
			break;
	}
}

/////////////////////////////////////////////////////////////////////////////
bool MiniAssembler::assemble(word *start, const char *str)
{
	initialize(start);
	
	YY_BUFFER_STATE buffer = yy_scan_string(str);
	yy_switch_to_buffer(buffer);

	bool result = tryParse();

	yy_delete_buffer(buffer);

	yyrestart(yyin);

	return result;
}

/////////////////////////////////////////////////////////////////////////////
void MiniAssembler::initialize(word *start)
{
	if (start) {				// start addres
		address = *start;
		init = true;
	} else if (!init) {	// not entered
		address = CPU::getInstance()->getIP();
		init = true;
	}
}

/////////////////////////////////////////////////////////////////////////////
bool MiniAssembler::tryParse() 
{
	try {
		if (parse() == 0)
			return true;
	} catch (const Exception &e) {
		yyrestart(yyin);
		cerr << e.getDescription() << endl;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
int MiniAssembler::parse()
{
	int nret = yyparse();
	table->flushtmp();
	return nret;
}