#include "common.h"
#include "Queens.h"

static const int MIN_SIZE = 4;
static const int MAX_SIZE = 8;

int _tmain(int argc, _TCHAR* argv[])
{	
	uint32_t size = 0;

	string line;
	while (cin) {
		cout << "Enter board size (4-8):";
		getline(cin, line);
		if (line.length() == 0)
			break;

		size = atoi(line.c_str());
		if (size >= MIN_SIZE && size <= MAX_SIZE)
			break;
	}

	if (size >= MIN_SIZE && size <= MAX_SIZE) {
		Queens queens(size);
		queens.solve(cout);
		return 0;
	}
		
	return 1;
}

