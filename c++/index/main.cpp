// main.cpp

#include "stdafx.h"
#include "index.h"
#include "HiresTimer.h"

/////////////////////////////////////////////////////////////////////////////
void usage()
{
	cerr << "usage: index txtfile" << endl;
	exit(1);
}

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	if (argc < 2) usage();

	HiresTimer timer;

	try {
		Index index;
		index.index(argv[1]);
		index.writeStats(cout);
	} catch (RCEXCEPTION e) {
		cerr << e.getDescription() << endl;
		exit(1);
	}

	cout << "   elapsed time " << timer << endl;

	return 0;
}

