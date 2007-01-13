// backends.h : main header file for the BACKENDS application
//

#if !defined(AFX_BACKENDS_H__70E80534_9543_42EA_90D5_63164D409081__INCLUDED_)
#define AFX_BACKENDS_H__70E80534_9543_42EA_90D5_63164D409081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// BackendsApp:
// See backends.cpp for the implementation of this class
//

class BackendsApp : public CWinApp
{
public:
	BackendsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BackendsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(BackendsApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CFont* getFont() const;
private:
	CFont font;
};


/////////////////////////////////////////////////////////////////////////////

inline CFont * BackendsApp::getFont() const {
	return (CFont*)&font;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKENDS_H__70E80534_9543_42EA_90D5_63164D409081__INCLUDED_)
