/////////////////////////////////////////////////////////////////////////////
//
// MINIASSEMBLER.H : Mini Assembler
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MINIASSEMBLER_H__
#define __MINIASSEMBLER_H__

#include "SymbolTable.h"

/////////////////////////////////////////////////////////////////////////////
class MiniAssembler {
// Construction / Destruction
public:
	MiniAssembler();

// Interface
	void assemble(word *start);
	bool assemble(word *start, const char *str);

// Implementation
private:
	void initialize(word *start);
	bool tryParse();
	int parse();
	void prompt();

	bool init;			// have we been entered ?
	SymbolTable *table;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MINIASSEMBLER_H__
