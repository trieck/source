// winedit.h : main header file for the WINEDIT application
//

#if !defined(AFX_WINEDIT_H__7AAF9E73_A9FA_11D3_8900_000000000000__INCLUDED_)
#define AFX_WINEDIT_H__7AAF9E73_A9FA_11D3_8900_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// WinEditApp:
// See winedit.cpp for the implementation of this class
//

class WinEditApp : public CWinApp
{
public:
	WinEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WinEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(WinEditApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINEDIT_H__7AAF9E73_A9FA_11D3_8900_000000000000__INCLUDED_)

