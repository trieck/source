// main.cpp
//

#include "stdafx.h"
#include "stdint.h"
#include "item.h"
#include "RandStream.h"
#include "blockio.h"
#include "btree.h"
#include "walker.h"

/////////////////////////////////////////////////////////////////////////////
void usage()
{
	cerr << "usage: walk idxfile" << endl;
	exit(1);
}

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	if (argc < 2) usage();

	Walker walker;

	try {
		walker.walk(argv[1]);
	} catch (RCEXCEPTION e) {
		cerr << e.getDescription() << endl;
		return 1;
	}

	return 0;
}

