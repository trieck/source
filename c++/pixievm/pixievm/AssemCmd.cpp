/////////////////////////////////////////////////////////////////////////////
//
// ASSEMCMD.CPP : Monitor assembler command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "AssemCmd.h"

/////////////////////////////////////////////////////////////////////////////
AssemCmd::AssemCmd(Monitor *mon) : Command(mon)
{
}

/////////////////////////////////////////////////////////////////////////////
AssemCmd::~AssemCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
void AssemCmd::exec(const stringvec &v)
{
	word address;
	if (v.size()) {
		int n = sscanf(v[0].c_str(), "%hx", &address);
		if (n != 1) {
			cerr << "? a [address]" << endl;
			return;
		}
		assembler.assemble(&address);
	} else {
		assembler.assemble(NULL);
	}
}
