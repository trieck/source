/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Application entry point
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Memory.h"
#include "Trap.h"
#include "Interrupt.h"
#include "CPU.h"
#include "Monitor.h"
#include "Machine.h"
#include "Exception.h"

////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	Machine machine;
	
	try {
		machine.init();
		machine.run();
	} catch(const Exception & e) {
		cerr << e.getDescription() << endl;
		return 1;
	}
	return 0;
}