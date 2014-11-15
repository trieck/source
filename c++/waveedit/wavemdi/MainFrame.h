//////////////////////////////////////
// Module Name	:	MainFrame.h		//
// Author		:	Thomas A. Rieck //
// Purpose		:	Main Frame		//
//					Declarations	//
// Date			:	11/23/1997		//
//////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include "stdafx.h"

///////////////////////////////////////////////////////////////////
// The CMainFrame frame window class
class CMainFrame : public CMDIFrameWnd {
public:
    CMainFrame();
    virtual ~CMainFrame();

    static UINT m_nIndicators[];

protected: // create from serialization only

    virtual BOOL PreCreateWindow(CREATESTRUCT&);

    // message map entries
    afx_msg	INT		OnCreate(LPCREATESTRUCT);
    afx_msg VOID	OnSize(UINT, INT, INT);
    afx_msg VOID	OnExit ();
    afx_msg VOID	OnDeviceInformation();

    CToolBar	m_ToolBar;
    CStatusBar	m_wndStatus;

    DECLARE_DYNCREATE(CMainFrame)
    DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////

#endif	// __MAINFRAME_H__