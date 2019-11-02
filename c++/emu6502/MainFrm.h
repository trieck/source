// MainFrm.h : interface of the MainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__7674561C_0466_4A49_8D45_3828E4215212__INCLUDED_)
#define AFX_MAINFRM_H__7674561C_0466_4A49_8D45_3828E4215212__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gripbar.h"

class MainFrame : public CFrameWnd
{

protected: // create from serialization only
    MainFrame();
    DECLARE_DYNCREATE(MainFrame)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(MainFrame)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~MainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
    CStatusBar m_wndStatusBar;
    GripperBar m_wndToolBar;

// Generated message map functions
protected:
    //{{AFX_MSG(MainFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnRegisters();
    afx_msg void OnMemory();
    afx_msg void OnSysColorChange();
    afx_msg void OnToolbarDropDown(NMHDR *pnmh, LRESULT* plRes);
    afx_msg void OnStack();
    afx_msg void OnUpdateRegisters(CCmdUI* pCmdUI);
    afx_msg void OnUpdateStack(CCmdUI* pCmdUI);
    afx_msg void OnUpdateMemory(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnUpdateDisassembly(CCmdUI *pCmdUI);
    afx_msg void OnDisassembly();
private:
    void ToggleFrameWnd(CRuntimeClass *pClass, int id);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7674561C_0466_4A49_8D45_3828E4215212__INCLUDED_)
