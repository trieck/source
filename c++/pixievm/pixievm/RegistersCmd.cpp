/////////////////////////////////////////////////////////////////////////////
//
// REGISTERSCMD.CPP : Monitor registers command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "RegistersCmd.h"
#include "CPU.h"

/////////////////////////////////////////////////////////////////////////////
RegistersCmd::RegistersCmd(Monitor *mon) : Command(mon)
{
}

/////////////////////////////////////////////////////////////////////////////
RegistersCmd::~RegistersCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
void RegistersCmd::exec(const stringvec &v)
{
	CPU *cpu = CPU::getInstance();

	char sr[9];
	word flags = cpu->getFL();
	sr[0] = flags & NEG_FLAG ? '1' : '0';
	sr[1] = flags & OVERFLOW_FLAG ? '1' : '0';
	sr[2] = '0'; /* unused */
	sr[3] = '0'; /* unused */
	sr[4] = flags & BRK_FLAG ? '1' : '0';
	sr[5] = flags & INT_DISABLE_FLAG ? '1' : '0';
	sr[6] = flags & ZERO_FLAG ? '1' : '0';
	sr[7] = flags & CARRY_FLAG ? '1' : '0';
	sr[8] = '\0';

	printf(" A: $%.4hX"
	       "  B: $%.4hX"
	       "  C: $%.4hX"
	       "  D: $%.4hX\n"
	       " X: $%.4hX"
	       " SP: $%.4hX"
	       " IP: $%.4hX"
	       " FL: %s (NV--BIZC)\n",
	       cpu->getA(), cpu->getB(), cpu->getC(), cpu->getD(),
	       cpu->getX(), cpu->getSP(), cpu->getIP(), sr);
}
