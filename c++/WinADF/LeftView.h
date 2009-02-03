// LeftView.h : interface of the LeftView class
//


#pragma once

class WinADFDoc;

class LeftView : public CTreeView
{
protected: // create from serialization only
	LeftView();
	DECLARE_DYNCREATE(LeftView)

// Attributes
public:
	WinADFDoc* GetDocument();

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~LeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline WinADFDoc* LeftView::GetDocument()
   { return reinterpret_cast<WinADFDoc*>(m_pDocument); }
#endif

