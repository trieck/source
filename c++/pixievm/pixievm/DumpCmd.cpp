/////////////////////////////////////////////////////////////////////////////
//
// DUMPCMD.CPP : Monitor dump command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "DumpCmd.h"
#include "Memory.h"
#include "CPU.h"

/////////////////////////////////////////////////////////////////////////////
DumpCmd::DumpCmd(Monitor *mon) : Command(mon)
{
}

/////////////////////////////////////////////////////////////////////////////
DumpCmd::~DumpCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
void DumpCmd::exec(const stringvec &v) 
{
	word start, end;
	if (v.size() == 0) {
		start = CPU::getInstance()->getIP();
		end = start + NBYTES;
	} else if (v.size() == 1) {
		int n = sscanf(v[0].c_str(), "%hx", &start);
		if (n != 1) {
			cerr << "? u [range]" << endl;
			return;
		}
		end = start + NBYTES;
	} else if (v.size() > 1) {
		int n = sscanf(v[0].c_str(), "%hx", &start);
		if (n != 1) {
			cerr << "? u [range]" << endl;
			return;
		}
		n = sscanf(v[1].c_str(), "%hx", &end);
		if (n != 1) {
			cerr << "? u [range]" << endl;
			return;
		}
	}

	Memory *mem = Memory::getInstance();
	/// $$$ /// $$$
};