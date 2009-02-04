#pragma once


// WinADFView view

class WinADFView : public CListView
{
	DECLARE_DYNCREATE(WinADFView)

protected:
	WinADFView();           // protected constructor used by dynamic creation
	virtual ~WinADFView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	WinADFDoc* GetDocument() const;

protected:
	void AddImages();
	void InsertHeaders();
	CImageList m_ImageList;

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  //debug version in WinADFView.cpp
inline WinADFDoc* WinADFView::GetDocument() const { 
	return reinterpret_cast<WinADFDoc*>(m_pDocument); 
}
#endif
