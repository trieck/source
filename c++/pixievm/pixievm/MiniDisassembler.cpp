/////////////////////////////////////////////////////////////////////////////
//
// MINIDISASSEMBLER.CPP : Mini Disassembler
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Memory.h"
#include "MiniDisassembler.h"
#include "CPU.h"

/////////////////////////////////////////////////////////////////////////////
MiniDisassembler::MiniDisassembler() : init(false)
{
	mem = Memory::getInstance();
}

/////////////////////////////////////////////////////////////////////////////
byte MiniDisassembler::fetch()
{
	return mem->fetch(ip++);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::disassemble(word *start, word *end)
{
	word lastip = 0;
	if (start) {		/* start address supplied */
		ip = *start;
		init = true;
	} else if (!init) { /* not entered */
		ip = CPU::getInstance()->getIP();
		init = true;
	}

	for (int i = 0; ip >= lastip && (end ? ip <= *end : i < NLINES); i++) {
		printip();
		lastip = ip;
		byte b = fetch();
		PxDisassembler::disassemble(b);
	}
}

