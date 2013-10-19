/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.H : Pixie Virtual Machine
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MACHINE_H__
#define __MACHINE_H__

#include "CPU.h"
#include "Memory.h"

/////////////////////////////////////////////////////////////////////////////
class Machine {
// Construction / Destruction
public:
	Machine();
	~Machine();

// Interface
	void init();
	int run(int argc, char** argv);

// Implementation
private:
	int test();
	int run();
	void loadROM(const char *filename, word base, word size);

	Memory* memory;				// pointer to memory
	CPU *cpu;					// pointer to CPU
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MACHINE_H__


