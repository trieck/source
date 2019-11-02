// MainFrm.h : interface of the MainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_MAINFRM_H__84460EDA_8E6D_11D4_9013_00010275679A__INCLUDED_)
#define AFX_MAINFRM_H__84460EDA_8E6D_11D4_9013_00010275679A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GripBar.h"
#include "penteBar.h"

class MainFrame : public CFrameWnd
{

protected: // create from serialization only
    MainFrame();
    DECLARE_DYNCREATE(MainFrame)
// Attributes
public:
// Operations
public:
    PenteBar & getPenteBar();
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(MainFrame)
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void RecalcLayout(BOOL bNotify = TRUE);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~MainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
    //{{AFX_MSG(MainFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
    afx_msg void onUpdateCaptures(CCmdUI *pCmdUI);
    afx_msg LRESULT OnAppSettingChange(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    PenteBar statusBar;
    GripperBar toolBar;
    void adjustFrameByBoard();
};
/////////////////////////////////////////////////////////////////////////////

inline PenteBar & MainFrame::getPenteBar()
{
    return statusBar;
}
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_MAINFRM_H__84460EDA_8E6D_11D4_9013_00010275679A__INCLUDED_)
