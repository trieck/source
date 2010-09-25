
// getstring.cpp

#include <windows.h>
#include <tchar.h>
#include <string>
#include "resource.h"

typedef std::basic_string<TCHAR> tstring;

tstring getstring(HINSTANCE, unsigned id);

#define STRINGBLOCKID(x)	( x / 16 ) + 1

/////////////////////////////////////////////////////////////////////////////
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR cmdLine,
                     int show)
{
	tstring x = getstring(hInst, IDS_NEXTSTUFF);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
tstring getstring(HINSTANCE hInst, unsigned id)
{
	HRSRC hRes = FindResource(hInst,
	                          MAKEINTRESOURCE(STRINGBLOCKID(id)),
	                          MAKEINTRESOURCE(RT_STRING));
	if (hRes == NULL)
		return _T("");

	HGLOBAL hGlobal = LoadResource(hInst, hRes);

	WORD *pdata = (WORD*)LockResource(hGlobal) + 2 + 18;

	WORD len = *pdata++;

	wchar_t *pstr = (wchar_t*)pdata;

	char buffer[1024];

	int n = WideCharToMultiByte(CP_ACP,
	                            0,
	                            pstr,
	                            len,
	                            buffer,
	                            sizeof(buffer),
	                            NULL,
	                            NULL);

	buffer[n] = _T('\0');

	UnlockResource(pdata);

	return buffer;
}