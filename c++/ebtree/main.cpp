/////////////////////////////////////////////////////////////////////////////
//
//	MAIN.CPP : application entry point
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "stdint.h"
#include "item.h"
#include "RandStream.h"
#include "blockio.h"
#include "blockmgr.h"
#include "wthread.h"
#include "lazyio.h"
#include "BTree.h"
#include "btreeimpl.h"
#include "HiresTimer.h"

#define MAXLEN (5000000)

/////////////////////////////////////////////////////////////////////////////
UINT randomInt(UINT lo, UINT hi) 
{
	double r = double(rand()) / RAND_MAX;
	return lo + UINT(r * (hi - lo));
}

/////////////////////////////////////////////////////////////////////////////
char randomChar()
{
	return (char)randomInt(32, 126);
}

/////////////////////////////////////////////////////////////////////////////
char randomAlpha()
{
	return (char)randomInt(65, 91);
}

/////////////////////////////////////////////////////////////////////////////
string randomKey()
{
	string output;
	
	int nlen = randomInt(256, 256);
	output.resize(nlen);

	for (int i = 0; i < nlen; i++) {
		output[i] = randomChar();
	}

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string randomVal(int min, int max)
{
	string output;
	
	UINT nlen = randomInt(min, max);
	nlen = min(nlen, MAXLEN);
	output.resize(nlen);

	for (UINT i = 0; i < nlen; i++) {
		output[i] = randomAlpha();
	}

	return output;
}

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	if (argc < 5) {
		cerr << "usage: ebtree filename minval maxval iterations" << endl;
		exit(1);
	}

	HiresTimer timer;
	srand(GetTickCount());

	BTreeImpl tree;
	tree.open(argv[1], OM_CREATE);

	string key, val;

	int i;
	int minval = atoi(argv[2]);
	int maxval = atoi(argv[3]);
	int n = atoi(argv[4]);
	for (i = 0; i < n; i++) {
		string key = randomKey();
		string val = randomVal(minval, maxval);
		tree.insert(key, val);
	}

	tree.writeStats(cout);
	tree.close();		  	

	cout << "   elapsed time " << timer << endl;

	return 0;
}