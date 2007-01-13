#include "matrix.h"
#include "NoSuchElement.h"
#include <iostream>

using std::cerr;
using std::endl;

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	Matrix M(10, 10);
	try {
		float j = M.getElement(10, 10);
	} catch (const NoSuchElementException &/* e */) {
		cerr << "no such element." << endl;
		return 1;
	}
	return 0;
}