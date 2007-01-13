// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__5E534C1C_0A97_4F51_9ECA_ADF17721A803__INCLUDED_)
#define AFX_STDAFX_H__5E534C1C_0A97_4F51_9ECA_ADF17721A803__INCLUDED_

#pragma warning(disable:4786)
#pragma warning(disable:4503)
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4293)
#pragma warning(disable:4018)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN

#include <afx.h>
#include <afxwin.h>

#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxpriv.h>
#include <afximpl.h>

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
using std::string;
using std::wstring;
using std::cerr;
using std::cout;
using std::wcout;
using std::wcerr;
using std::endl;
using std::ostream;
using std::ostringstream;

typedef vector<string> stringvec;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5E534C1C_0A97_4F51_9ECA_ADF17721A803__INCLUDED_)
