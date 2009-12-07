/////////////////////////////////////////////////////////////////////////////
//
// STEPCMD.CPP : Monitor step command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "StepCmd.h"
#include "CPU.h"
#include "Interrupt.h"

/////////////////////////////////////////////////////////////////////////////
StepCmd::StepCmd(Monitor *mon) : Command(mon)
{
}

/////////////////////////////////////////////////////////////////////////////
StepCmd::~StepCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
void StepCmd::exec(const stringvec &v) 
{
	CPU *cpu = CPU::getInstance();

	word ip = cpu->getIP();
	if (v.size() > 0) {
		int n = sscanf(v[0].c_str(), "%hx", &ip);
		if (n != 1) {
			cerr << "? z [address]" << endl;
			return;
		}
		
		// set instruction pointer
		cpu->setIP(ip);
	}

	Monitor *mon = getMonitor();
	mon->disassemble(ip);

	g_interrupt.setPending(IK_TRAP);
	mon->setExit(true);
}
