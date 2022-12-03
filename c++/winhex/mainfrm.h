// mainfrm.h : interface of the MainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B1B4E5FA_8F9B_11D3_88CE_000000000000__INCLUDED_)
#define AFX_MAINFRM_H__B1B4E5FA_8F9B_11D3_88CE_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MainFrame : public CFrameWnd
{
protected: // create from serialization only
    MainFrame();
    DECLARE_DYNCREATE(MainFrame)

    // Attributes
    // Operations
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(MainFrame)
    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
    //}}AFX_VIRTUAL

    // Implementation
    ~MainFrame() override;
#ifdef _DEBUG
    void AssertValid() const override;
    void Dump(CDumpContext& dc) const override;
#endif

protected: // control bar embedded members
    CStatusBar m_wndStatusBar;
    CToolBar m_wndToolBar;

    // Generated message map functions
    //{{AFX_MSG(MainFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    //    afx_msg void OnDropFiles(HDROP hDropInfo);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B1B4E5FA_8F9B_11D3_88CE_000000000000__INCLUDED_)
