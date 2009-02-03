// WinADFView.h : interface of the WinADFView class
//


#pragma once


class WinADFView : public CListView
{
protected: // create from serialization only
	WinADFView();
	DECLARE_DYNCREATE(WinADFView)

// Attributes
public:
	WinADFDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~WinADFView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WinADFView.cpp
inline WinADFDoc* WinADFView::GetDocument() const
   { return reinterpret_cast<WinADFDoc*>(m_pDocument); }
#endif

