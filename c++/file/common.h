/////////////////////////////////////////////////////////////////////////////
//
// COMMON.H : common include file
//

#ifndef __COMMON_H__
#define __COMMON_H__

#pragma warning(disable:4786) // disable truncation warning

#include <windows.h>
#include <tchar.h>
#include <crtdbg.h>

#include <string>
#include <iostream>
#include <memory>
#include <map>

using namespace std;
typedef basic_string<TCHAR> tstring;

// global helper functions
bool loadString(UINT id, tstring & str);
HINSTANCE getInstance();
int debugReport (LPCTSTR file, int line, LPCTSTR module, LPCTSTR format);

#ifdef _DEBUG
#undef ASSERT
#define ASSERT(expr)	\
	do { if (!(expr) && \
		(1 == debugReport(__FILE__, __LINE__, NULL, #expr))) \
			_CrtDbgBreak(); } while (0)
#endif // _DEBUG

#include "app.h"	// application class

#endif // __COMMON_H__