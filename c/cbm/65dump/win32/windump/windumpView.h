// windumpView.h : interface of the WindumpView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDUMPVIEW_H__644DB00C_42F9_46C4_8F67_2243318BBBC7__INCLUDED_)
#define AFX_WINDUMPVIEW_H__644DB00C_42F9_46C4_8F67_2243318BBBC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class WindumpView : public CListView
{
protected: // create from serialization only
    WindumpView();
    DECLARE_DYNCREATE(WindumpView)

// Attributes
public:
    WindumpDoc* GetDocument();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(WindumpView)
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void OnInitialUpdate(); // called first time after construct
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~WindumpView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(WindumpView)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    //}}AFX_MSG
    afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in windumpView.cpp
inline WindumpDoc* WindumpView::GetDocument()
{
    return (WindumpDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDUMPVIEW_H__644DB00C_42F9_46C4_8F67_2243318BBBC7__INCLUDED_)
