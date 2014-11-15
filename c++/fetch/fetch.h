// fetch.h : main header file for the FETCH application
//

#if !defined(AFX_FETCH_H__DBEB1C73_117D_11D4_899E_00E098787497__INCLUDED_)
#define AFX_FETCH_H__DBEB1C73_117D_11D4_899E_00E098787497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// FetchApp:
// See fetch.cpp for the implementation of this class
//

class FetchApp : public CWinApp {
public:
    FetchApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(FetchApp)
public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

public:
    //{{AFX_MSG(FetchApp)
    afx_msg void OnAppAbout();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FETCH_H__DBEB1C73_117D_11D4_899E_00E098787497__INCLUDED_)

