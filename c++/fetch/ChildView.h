// ChildView.h : interface of the ChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__DBEB1C79_117D_11D4_899E_00E098787497__INCLUDED_)
#define AFX_CHILDVIEW_H__DBEB1C79_117D_11D4_899E_00E098787497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "netenum.h"

/////////////////////////////////////////////////////////////////////////////
// ChildView window

class ChildView : public CListView
{
// Construction
public:
    ChildView();

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ChildView)
public:
    virtual void OnInitialUpdate();
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ChildView();

    // Generated message map functions
protected:
    void InsertHeaders();
    BOOL IsSearching() const;
    static UINT PerformSearch(LPVOID);

    //{{AFX_MSG(ChildView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSearch();
    afx_msg void OnUpdateSearch(CCmdUI* pCmdUI);
    afx_msg void OnStop();
    afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
    afx_msg LRESULT OnSearchComplete(WPARAM, LPARAM);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    CImageList m_ImageList;
    CWinThread *m_pThread;
    CEvent m_event;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__DBEB1C79_117D_11D4_899E_00E098787497__INCLUDED_)

