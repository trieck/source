// DDrawView.h : interface of the DDrawView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDRAWVIEW_H__A76F4DAC_E597_11D4_AE70_0008C7E97A92__INCLUDED_)
#define AFX_DDRAWVIEW_H__A76F4DAC_E597_11D4_AE70_0008C7E97A92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class DDrawView : public CView {
protected: // create from serialization only
	DDrawView();
	DECLARE_DYNCREATE(DDrawView)

// Attributes
public:
	DDrawDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DDrawView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~DDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(DDrawView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LPDIRECTDRAWSURFACE pdds;
};

#ifndef _DEBUG  // debug version in DDrawView.cpp
inline DDrawDoc* DDrawView::GetDocument()
{
	return (DDrawDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDRAWVIEW_H__A76F4DAC_E597_11D4_AE70_0008C7E97A92__INCLUDED_)
