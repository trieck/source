/////////////////////////////////////////////////////////////////////////////
//
// MINIASSEMBLER.H : Mini Assembler
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
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

// Implementation
private:
	int parse();
	void prompt();

	bool init;		/* have we been entered ? */
	SymbolTable *table;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MINIASSEMBLER_H__
