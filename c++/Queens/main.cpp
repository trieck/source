#include "common.h"
#include "Queens.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 2) {
		cerr << "usage: queens boardsize" << endl;
		return 1;
	}

	uint32_t size = _ttoi(argv[1]);

	Queens queens(size);
	queens.solve(cout);

	return 0;
}
