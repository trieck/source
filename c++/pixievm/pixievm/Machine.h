/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.H : Pixie Virtual Machine
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MACHINE_H__
#define __MACHINE_H__

#include "CPU.h"
#include "Memory.h"
#include "Monitor.h"

/////////////////////////////////////////////////////////////////////////////
class Machine {
// Construction / Destruction
public:
	Machine();
	~Machine();

// Interface
	void init();
	void run();

// Implementation
private:
	void loadROM(const char *filename, word base, word size);

	Memory* memory;				// pointer to memory
	CPU *cpu;					// pointer to CPU
	Monitor monitor;			// monitor instance
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MACHINE_H__


