/////////////////////////////////////////////////////////////////////////////
// 
//	NeptuneTest.cpp : test Neptune COM component
//

#import "..\neptune\bin\neptune.dll" no_namespace

#include <iostream>
using namespace std;

struct _coinit {
	_coinit() { CoInitialize(NULL); }
	~_coinit() { CoUninitialize(); }
} coinit;

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	IPlanetPtr planet;

	try {
		planet.CreateInstance(__uuidof(Neptune));


	} catch (_com_error & E) {
		cerr << E.ErrorMessage() << endl;
		return 1;
	}

	return 0;
}