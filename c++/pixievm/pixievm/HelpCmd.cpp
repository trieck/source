/////////////////////////////////////////////////////////////////////////////
//
// HELPCMD.CPP : Monitor help command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "HelpCmd.h"

/////////////////////////////////////////////////////////////////////////////
HelpCmd::HelpCmd(Monitor *mon) : Command(mon)
{
}

/////////////////////////////////////////////////////////////////////////////
HelpCmd::~HelpCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
void HelpCmd::exec(const stringvec &v) 
{
	cout << "?   print help screen" << endl;
	cout << "a   assemble [address]" << endl;
	cout << "d   disassemble [range]" << endl;
	cout << "l   load address file" << endl;
	cout << "q   quit" << endl;
	cout << "r   print registers" << endl;
	cout << "s   save range file" << endl;
	cout << "u   dump [range]" << endl;
	cout << "z   step [address]" << endl;
}
