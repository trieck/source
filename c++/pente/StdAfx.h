// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#if !defined(AFX_STDAFX_H__84460ED8_8E6D_11D4_9013_00010275679A__INCLUDED_)
#define AFX_STDAFX_H__84460ED8_8E6D_11D4_9013_00010275679A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable : 4996)	// deprecated POXIS names

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include "targetver.h"

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxpriv.h>

#if _MSC_VER >= 1500
#include <..\atlmfc\src\mfc\afximpl.h>
#else
#include <..\src\afximpl.h>
#endif

#include <stdint.h>

typedef const unsigned char* LPCBYTE;

struct StringPtrLess {
	bool operator()(LPCSTR left, LPCSTR right) {
		return strcmp(left, right) < 0;
	}
};

#include <vector>
#include <memory>
#include "globals.h"
#include <afxdlgs.h>

#define WM_APPSETTING_CHANGE	(WM_APP + 1)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_STDAFX_H__84460ED8_8E6D_11D4_9013_00010275679A__INCLUDED_)
