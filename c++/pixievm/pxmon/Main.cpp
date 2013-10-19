/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Application entry point
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Machine.h"
#include "Exception.h"

////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	int result = 0;

	Machine machine;

	try {
		machine.init();
		result = machine.run(argc, argv);
	} catch (const Exception & e) {
		cerr << e.getDescription() << endl;
		return 1;
	}
	return result;
}