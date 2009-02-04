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
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
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
	void AddImages();
	void InsertHeaders();

	CImageList m_ImageList;

// Generated message map functions
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
};

#ifndef _DEBUG  // debug version in WinADFView.cpp
inline WinADFDoc* WinADFView::GetDocument() const
   { return reinterpret_cast<WinADFDoc*>(m_pDocument); }
#endif

