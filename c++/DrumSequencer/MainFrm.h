// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "DrumSequencerToolbar.h"
#include "DrumSequencerMenubar.h"
#include "SettingsPane.h"

class CMainFrame : public CFrameWndEx
{
protected: // create from serialization only
    CMainFrame();
DECLARE_DYNCREATE(CMainFrame)

    // Attributes
public:

    // Operations
public:

    // Overrides
public:
    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
    BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
                   CWnd* pParentWnd = nullptr, CCreateContext* pContext = nullptr) override;

    // Implementation
public:
    virtual ~CMainFrame();
#ifdef _DEBUG
    void AssertValid() const override;
    void Dump(CDumpContext& dc) const override;
#endif

protected: // control bar embedded members
    DrumSequencerMenubar m_wndMenuBar;
    DrumSequencerToolbar m_wndToolBar;
    SettingsPane m_wndSettingsPane;
    CMFCStatusBar m_wndStatusBar;
    CMFCToolBarImages m_UserImages;

    // Generated message map functions
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
DECLARE_MESSAGE_MAP()
public:
    void RecalcLayout(BOOL bNotify = TRUE) override;
    void ResizeFrame(void);
    void AdjustClientArea() override;
    void AdjustDockingLayout(HDWP hdwp = nullptr) override;
//    virtual BOOL OnCmdMsg(UINT nID, int nCode, void *pExtra,
//                          AFX_CMDHANDLERINFO *pHandlerInfo);
};
