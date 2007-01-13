/////////////////////////////////////////////////////////////////////////////
//
//	PROGID.CPP : returns COM Object information for Prog Id
//

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <atlbase.h>

using namespace std;

#ifndef _UNICODE
ostream & terr = cerr;
ostream & tout = cout;
istream & tin = cin;
#else
wostream & terr = wcerr;
wostream & tout = wcout;
wistream & tin = wcin;
#endif // _UNICODE

/////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, TCHAR *argv[])
{
	if (argc < 2) {
		terr << _T("usage: progid name") << endl;
		return 1;
	}

	return 0;
}
