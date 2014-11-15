// music.h : main header file for the MUSIC application

//



#if !defined(AFX_MUSIC_H__F7CFDC33_51AB_11D4_89F0_00E098787497__INCLUDED_)

#define AFX_MUSIC_H__F7CFDC33_51AB_11D4_89F0_00E098787497__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000



#ifndef __AFXWIN_H__

#error include 'stdafx.h' before including this file for PCH

#endif



#include "resource.h"       // main symbols



/////////////////////////////////////////////////////////////////////////////

// MusicApp:

// See music.cpp for the implementation of this class

//



class MusicApp : public CWinApp

{

public:

    MusicApp();

    ~MusicApp();



// Overrides

    // ClassWizard generated virtual function overrides

    //{{AFX_VIRTUAL(MusicApp)

public:

    virtual BOOL InitInstance();

    virtual int ExitInstance();

    //}}AFX_VIRTUAL



    CDaoDatabase* database();



// Implementation

    //{{AFX_MSG(MusicApp)

    afx_msg void OnAddRecord();

    afx_msg void OnDeleteRecord();

    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:

    CDaoDatabase *db;

    static LPCTSTR databasePath;

};



inline CDaoDatabase* MusicApp::database()
{

    return db;

}



/////////////////////////////////////////////////////////////////////////////



// global helper functions

CString LoadString(UINT resource);



BOOL setButtonImage(CWnd *pParent,					/* parent dialog */

                    UINT button,								/* button resource */

                    UINT image,									/* image resource */

                    UINT imageType,								/* image type */

                    UINT cx = LR_DEFAULTSIZE,					/* horizontal size */

                    UINT cy = LR_DEFAULTSIZE,					/* vertical size */

                    UINT flags = LR_DEFAULTCOLOR | LR_SHARED);	/* load flags */



//{{AFX_INSERT_LOCATION}}

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



#endif // !defined(AFX_MUSIC_H__F7CFDC33_51AB_11D4_89F0_00E098787497__INCLUDED_)

