
// shorty.c

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

static LPCTSTR usage = _T("usage: shorty longpath");

int _tmain(int argc, TCHAR *argv[])
{
	TCHAR buff[_MAX_PATH + _MAX_FNAME];
	DWORD len;
	if (argc < 2) {
		_ftprintf(stderr, _T("%s\n"), usage);
		return 1;
	}
	len = GetShortPathName(argv[1], buff, sizeof(buff));
	if (len == 0) 
		return 1;
	_tprintf(_T("%s\n"), buff);
	return 0;
}