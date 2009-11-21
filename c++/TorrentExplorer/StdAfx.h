// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__55AEFC10_A8A8_4B58_A394_DB5C9869A45E__INCLUDED_)
#define AFX_STDAFX_H__55AEFC10_A8A8_4B58_A394_DB5C9869A45E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WINVER 0x0501

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxtempl.h>
#include <afxpriv.h>

#if _MSC_VER >= 1500
#include <..\atlmfc\src\mfc\afximpl.h>
#else
#include <..\src\afximpl.h>
#endif

#define WM_SETTING_CHANGE	(WM_APP + 1)

#include <vector>

typedef std::vector<LPCSTR> KeyVec;
typedef std::vector<CString> CStringVec;
typedef const unsigned char* LPCBYTE;

struct StringPtrLess {
	bool operator()(LPCSTR left, LPCSTR right) {
		return strcmp(left, right) < 0;
	}
};

/////////////////////////////////////////////////////////////////////////////
// Callable interface
DECLARE_INTERFACE(ICallable)
{
public:
	virtual void Call(DWORD param) PURE;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__55AEFC10_A8A8_4B58_A394_DB5C9869A45E__INCLUDED_)
