// pentevw.h : interface of the PenteView class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_PENTEVW_H__84460EDE_8E6D_11D4_9013_00010275679A__INCLUDED_)
#define AFX_PENTEVW_H__84460EDE_8E6D_11D4_9013_00010275679A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PenteView : public CView
{
protected: // create from serialization only
	PenteView();
	DECLARE_DYNCREATE(PenteView)
// Attributes
public:
	PenteDoc* GetDocument();
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PenteView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~PenteView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(PenteView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBrush bkgBrush;
	COLORREF bkgColor;
};

#ifndef _DEBUG  // debug version in pentevw.cpp
inline PenteDoc* PenteView::GetDocument()
   { return (PenteDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_PENTEVW_H__84460EDE_8E6D_11D4_9013_00010275679A__INCLUDED_)
