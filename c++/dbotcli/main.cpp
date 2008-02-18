/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Application entry point
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "dbotcli.h"

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	DatabotClient client;

	try {
		;
	} catch (const Exception &e) {
		cerr << e.getDescription() << endl;
		exit(1);
	}

	return 0;
}