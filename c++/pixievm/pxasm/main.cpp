/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Application entry point
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Assembler.h"
#include "Exception.h"

ANON_BEGIN
void usage()
{
	cerr << "usage: pxasm file" << endl;
	exit(EXIT_FAILURE);
}
ANON_END

int main(int argc, char *argv[])
{
	if (argc < 2) 
		usage();

	Assembler assembler;

	int nret;

	try {
		nret = assembler.assemble(argv[1]);
	} catch (const Exception &e) {
		cerr << e.getDescription() << endl;
		exit(EXIT_FAILURE);
	}
	
	return nret;
}

