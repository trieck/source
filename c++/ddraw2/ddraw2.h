// ddraw2.h : main header file for the DDRAW2 application
//

#if !defined(AFX_DDRAW2_H__A76F4DA4_E597_11D4_AE70_0008C7E97A92__INCLUDED_)
#define AFX_DDRAW2_H__A76F4DA4_E597_11D4_AE70_0008C7E97A92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// DDrawApp:
// See ddraw2.cpp for the implementation of this class
//

class DDrawApp : public CWinApp
{
public:
	DDrawApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DDrawApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	LPDIRECTDRAW GetDirectDraw() const { return pddraw; }

// Implementation
	//{{AFX_MSG(DDrawApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL CreateDirectDraw(void);
	LPDIRECTDRAW pddraw;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDRAW2_H__A76F4DA4_E597_11D4_AE70_0008C7E97A92__INCLUDED_)
