/////////////////////////////////////////////////////////////////////////////
//
//	UTILITY.CPP : Utility functions
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#include "PlutoLib.h"

/////////////////////////////////////////////////////////////////////////////
DWORD SwapByteOrder(DWORD bytes)
{
	DWORD temp = 0;

	temp |= bytes >> 24;
	temp |= ((bytes & 0x00FF0000) >> 8);
	temp |= ((bytes & 0x0000FF00) << 8);
	temp |= ((bytes & 0x000000FF) << 24);

	return temp;
}

/////////////////////////////////////////////////////////////////////////////
DWORD SectorSize()
{
	DWORD sectorsize;
	if (!GetDiskFreeSpace(NULL, NULL, &sectorsize, NULL, NULL))
		return 0;

	return sectorsize;
}

/////////////////////////////////////////////////////////////////////////////
DWORD SectorAlign(DWORD address)
{
	DWORD secsize = SectorSize();

	return (address + (secsize-1)) & ~(secsize-1);
}

/////////////////////////////////////////////////////////////////////////////
tstring LastError()
{
	tstring output;

	TCHAR *pmsg = NULL;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
	              NULL, GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	              (LPTSTR)&pmsg, 0, NULL);

	if (pmsg != NULL) {
		int N = _tcslen(pmsg);
		if (N > 1 && pmsg[N - 1] == _T('\n'))
			pmsg[N - 1] = _T('\0');

		if (N > 1 && pmsg[N - 2] == _T('\r'))
			pmsg[N - 2] = _T('\0');

		output = pmsg;

		LocalFree(pmsg);
	}

	return output;
}

/////////////////////////////////////////////////////////////////////////////
tstring Comma(UINT64 i)
{
	tstring output;

	TCHAR buff[MAX_PATH];
	_stprintf(buff,_T("%I64u"), i);

	int n = _tcslen(buff);

	for (int j = n - 1, k = 1; j >= 0; j--, k++) {
		output += buff[j];
		if (k % 3 == 0 && j > 0 && j < n - 1)
			output += ',';
	}

	std::reverse(output.begin(), output.end());

	return output;
}
