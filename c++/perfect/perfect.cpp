#include "stdafx.h"
#include <iostream>

using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
{
	int sum;

	for (int i = 1; i <= 1000000; i++) {
		sum = 0;

		for (int j = 1; j < i; j++) {
			for (int k = j; k <= i; k++) {
				if (j * k == i) {
					if (j == 1)
						sum += 1;
					else {
						sum += j;
						sum += k;
					}
				}				
			}
		}

		if (sum == i) {
			cout << i << endl;
		}
	}

	return 0;
}

