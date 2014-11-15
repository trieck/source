// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4293)
#pragma warning(disable:4018)

#define WINVER 0x0501
#define WIN32_LEAN_AND_MEAN

#include <afx.h>
#include <afxwin.h>

#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxpriv.h>

#if _MSC_VER >= 1500
#include <..\atlmfc\src\mfc\afximpl.h>
#else
#include <..\src\afximpl.h>
#endif

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <algorithm>
#include <sstream>

using std::vector;
using std::map;
using std::cerr;
using std::cout;
using std::wcout;
using std::wcerr;
using std::endl;
using std::ostream;

typedef std::basic_string<TCHAR> tstring;
typedef vector<tstring> tstringvec;

