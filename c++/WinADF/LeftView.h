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
	BOOL SelectFolder(const CString &name);

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	
// Implementation
public:
	virtual ~LeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void AddImages();

	CImageList m_ImageList;

// Generated message map functions
protected:
	void InsertDir(HTREEITEM hParent, const EntryList &entries);

	//{{AFX_MSG(LeftView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline WinADFDoc* LeftView::GetDocument()
   { return reinterpret_cast<WinADFDoc*>(m_pDocument); }
#endif

