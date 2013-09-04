
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "DrumSequencerToolbar.h"
#include "DrumSequencerMenubar.h"
#include "SettingsPane.h"

class CMainFrame : public CFrameWndEx {

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	DrumSequencerMenubar	m_wndMenuBar;
	DrumSequencerToolbar	m_wndToolBar;
	SettingsPane			m_wndSettingsPane;
	CMFCStatusBar			m_wndStatusBar;
	CMFCToolBarImages		m_UserImages;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
public:
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	void ResizeFrame(void);
	virtual void AdjustClientArea();
	virtual void AdjustDockingLayout(HDWP hdwp = NULL);
};


