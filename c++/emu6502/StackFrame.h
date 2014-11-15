#if !defined(AFX_STACKFRAME_H__74DD967C_BD66_45FD_B913_4F1AE2B60783__INCLUDED_)
#define AFX_STACKFRAME_H__74DD967C_BD66_45FD_B913_4F1AE2B60783__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StackFrame.h : header file
//

#include "StackView.h"

/////////////////////////////////////////////////////////////////////////////
// StackFrame frame

class StackFrame : public CMiniFrameWnd {
    DECLARE_DYNCREATE(StackFrame)
protected:
    StackFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(StackFrame)
protected:
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~StackFrame();

    // Generated message map functions
    //{{AFX_MSG(StackFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    CStatusBar m_wndStatusBar;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STACKFRAME_H__74DD967C_BD66_45FD_B913_4F1AE2B60783__INCLUDED_)
