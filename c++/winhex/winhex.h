// winhex.h : main header file for the WINHEX application
//

#if !defined(AFX_WINHEX_H__B1B4E5F6_8F9B_11D3_88CE_000000000000__INCLUDED_)
#define AFX_WINHEX_H__B1B4E5F6_8F9B_11D3_88CE_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// HexApp:
// See winhex.cpp for the implementation of this class
//

class HexApp : public CWinApp
{
public:
    HexApp();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(HexApp)
    BOOL InitInstance() override;
    int ExitInstance() override;
    //}}AFX_VIRTUAL

    // Implementation
    //{{AFX_MSG(HexApp)
    afx_msg void OnAppAbout();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINHEX_H__B1B4E5F6_8F9B_11D3_88CE_000000000000__INCLUDED_)
