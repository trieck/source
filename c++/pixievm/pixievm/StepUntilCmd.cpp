/////////////////////////////////////////////////////////////////////////////
//
// STEPUNTILCMD.CPP : Step until return command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "StepUntilCmd.h"
#include "CPU.h"
#include "Memory.h"
#include "Interrupt.h"
#include "Opcodes.h"

/////////////////////////////////////////////////////////////////////////////
StepUntilCmd::StepUntilCmd(Monitor *mon) : Command(mon)
{
}

/////////////////////////////////////////////////////////////////////////////
StepUntilCmd::~StepUntilCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
void StepUntilCmd::exec(const stringvec &v)
{
	CPU *cpu = CPU::getInstance();
	Memory *mem = Memory::getInstance();

	// set the stack pointer to a sane value if zero
	word sp;
	if ((sp = cpu->getSP()) == 0) {
		cpu->setSP(0x1FF);
	}

	// push the current value of IP onto the stack
	word ip = cpu->getIP();
	cpu->push16(ip);

	if (v.size() > 0) {
		int n = sscanf(v[0].c_str(), "%hx", &ip);
		if (n != 1) {
			cerr << "? u [address]" << endl;
			return;
		}

		// set instruction pointer
		cpu->setIP(ip);	
	}
	
	Monitor *mon = getMonitor();
	mon->disassemble(ip);

	g_interrupt.setTrap(this, reinterpret_cast<void*>(ip));
	mon->setExit(true);	
}

/////////////////////////////////////////////////////////////////////////////
void StepUntilCmd::trap(void *data)
{
	Monitor *mon = getMonitor();
	Memory *mem = Memory::getInstance();
	CPU *cpu = CPU::getInstance();

	word ip = reinterpret_cast<word>(data);

	// check whether the last instruction executed was RET
	// if so, break back into the monitor. Otherwise, keep stepping.
	
	byte instruction = mem->fetch(ip);
	if (instruction == RET || mon->isRunning()) {
		g_interrupt.setMonitorBreak(mon);
	} else {		
		ip = cpu->getIP();
		mon->disassemble(ip);
		g_interrupt.setTrap(this, reinterpret_cast<void*>(ip));
	}
}

