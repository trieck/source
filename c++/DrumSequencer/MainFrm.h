// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "DrumSequencerToolbar.h"
#include "DrumSequencerMenubar.h"
#include "SettingsPane.h"

class CMainFrame : public CFrameWndEx
{
protected: // create from serialization only
    CMainFrame() = default;
DECLARE_DYNCREATE(CMainFrame)

    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
    BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
                   CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL) override;

    // Implementation
    virtual ~CMainFrame() = default;
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
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
DECLARE_MESSAGE_MAP()
public:
    void RecalcLayout(BOOL bNotify = TRUE) override;
    void ResizeFrame();
    void AdjustClientArea() override;
    void AdjustDockingLayout(HDWP hdwp = NULL) override;
};
