/*---------------------------------------
	Module Name	:	MainFrame.h
	Author		:	Thomas A. Rieck
	Purpose		:	Main Frame Window
					declarations
	Date		:	08/21/1997
---------------------------------------*/

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

///////////////////////////////////////////////////////////////////
// The CMainFrame frame window class

class CMainFrame : public CFrameWnd {
protected: // create from serialization only
	CMainFrame();
	virtual BOOL PreCreateWindow(CREATESTRUCT&);
	virtual ~CMainFrame();

	VOID SetStatusIndicators(int nWidth);

	// message map entries
	afx_msg	INT	 OnCreate(LPCREATESTRUCT);
	afx_msg VOID OnSize(UINT, INT, INT);
	afx_msg VOID OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg VOID OnExitMenuLoop(BOOL bIsTrackPopupMenu);
public:
	inline CStatusBar*	GetStatusBar() {
		return &m_StatusBar;
	}
	inline CToolBar*	GetToolBar() {
		return &m_ToolBar;
	}
protected:
	CStatusBar	m_StatusBar;
	CToolBar	m_ToolBar;

	DECLARE_DYNCREATE(CMainFrame)
	DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////

#endif	// __MAINFRAME_H__