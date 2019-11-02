//////////////////////////////////////
// Module Name	:	MainFrame.h		//
// Author		:	Thomas A. Rieck //
// Purpose		:	Simple Document //
//					 - View Test	//
// Date			:	4/11/97			//
//////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include "stdafx.h"
#include "DocViewView.h"

///////////////////////////////////////////////////////////////////
// The CMainFrame frame window class

class CMainFrame : public CFrameWnd
{
    friend CDocViewView;

protected: // create from serialization only
    CMainFrame();
    virtual BOOL PreCreateWindow(CREATESTRUCT&);
    virtual ~CMainFrame();

    // message map entries
    afx_msg	INT	OnCreate(LPCREATESTRUCT);
    afx_msg VOID OnSize(UINT, INT, INT);
    afx_msg VOID OnExit ();

protected:
    CStatusBar*	m_pWndStatus;

    DECLARE_DYNCREATE(CMainFrame)
    DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////

#endif	// __MAINFRAME_H__