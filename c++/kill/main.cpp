
#include "common.h"
#include "procenum.h"
#include "prockill.h"

namespace {
LPCTSTR usage = _T("usage: kill process");
}

/////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, TCHAR *argv[])
{
	if (argc < 2) {
		cerr << usage << endl;
		return 1;
	}

	argc--;
	argv++;

	try {
		ProcessEnumerator E;
		PidVector V = E.getMatchingPids(argv[0]);

		ProcessKiller killer;
		killer.kill(V, &cout);
	} catch (const Exception & e) {
		cerr << (LPCTSTR)e << endl;
		return 1;
	}

	return 0;
}

