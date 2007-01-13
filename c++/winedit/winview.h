// winview.h : interface of the WinEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINVIEW_H__7AAF9E7B_A9FA_11D3_8900_000000000000__INCLUDED_)
#define AFX_WINVIEW_H__7AAF9E7B_A9FA_11D3_8900_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class WinEditView : public CEditView
{
protected: // create from serialization only
	WinEditView();
	DECLARE_DYNCREATE(WinEditView)

// Attributes
public:
	WinEditDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WinEditView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~WinEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(WinEditView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont m_font;
};

#ifndef _DEBUG  // debug version in winview.cpp
inline WinEditDoc* WinEditView::GetDocument()
   { return (WinEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINVIEW_H__7AAF9E7B_A9FA_11D3_8900_000000000000__INCLUDED_)

