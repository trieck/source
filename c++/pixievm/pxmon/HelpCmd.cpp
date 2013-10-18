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
	cout << "l   load file" << endl;
	cout << "m   dump memory [range]" << endl;
	cout << "q   quit" << endl;
	cout << "r   print registers" << endl;
	cout << "s   save range file" << endl;
	cout << "t   step [address]" << endl;
	cout << "u   step until return [address]" << endl;
}
