/////////////////////////////////////////////////////////////////////////////
//
// COMMON.CPP : global helper functions
//

#include "common.h"

// default implementations
static int NeptuneMain(int argc, TCHAR *argv[]);
static int NeptuneWinMain(HINSTANCE hInstance,
                          HINSTANCE hPrevInstance, TCHAR *commandLine, int show);

/////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, TCHAR *argv[])
{
	return NeptuneMain(argc, argv);
}

/////////////////////////////////////////////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                       TCHAR *commandLine, int show)
{
	return NeptuneWinMain(hInstance, hPrevInstance, commandLine, show);
}
/////////////////////////////////////////////////////////////////////////////
bool loadString(UINT id, tstring & str)
{
	HMODULE module = getInstance();
	if (0 == module)
		return false;

	HRSRC resource = FindResource(module,
	                              MAKEINTRESOURCE((id >> 4) + 1), RT_STRING);
	if (0 == resource) {
		ASSERT(0);	// resource not found
		return false;
	}

	// TODO: use efficient heap allocation to retrieve whole string
	TCHAR buffer[4096];
	int rtn = LoadString(module, id, buffer, 4095);
	buffer[rtn] = _T('\0');

	str = buffer;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
int debugReport(LPCTSTR file, int line, LPCTSTR module, LPCTSTR format)
{
	return _CrtDbgReport(_CRT_ASSERT, file, line, module, format);
}

/////////////////////////////////////////////////////////////////////////////
HINSTANCE getInstance()
{
	Application *pApp = getApp();
	ASSERT(pApp != NULL);
	return pApp->getInstance();
}

/////////////////////////////////////////////////////////////////////////////
int NeptuneMain(int argc, TCHAR *argv[])
{
	Application *pApp = getApp();
	ASSERT(pApp != NULL);

	if (!pApp->initInstance())
		return pApp->exitInstance();

	return pApp->run() ? 0 : 1;
}

/////////////////////////////////////////////////////////////////////////////
int NeptuneWinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance, TCHAR *commandLine, int show)
{
	Application *pApp = getApp();
	ASSERT(pApp != NULL);

	if (!pApp->initInstance())
		return pApp->exitInstance();

	return pApp->run() ? 0 : 1;
}


