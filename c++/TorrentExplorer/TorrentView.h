// TorrentView.h : interface of the TorrentView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TORRENTVIEW_H__0C0C4FB4_39C3_4632_A33A_588B4883F6D1__INCLUDED_)
#define AFX_TORRENTVIEW_H__0C0C4FB4_39C3_4632_A33A_588B4883F6D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class TorrentView : public CTreeView {
protected: // create from serialization only
	TorrentView();
	DECLARE_DYNCREATE(TorrentView)

// Attributes
public:
	TorrentDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TorrentView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~TorrentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(TorrentView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateBinaryView(CCmdUI* pCmdUI);
	afx_msg void OnBinaryView();
	afx_msg void OnUpdateDateView(CCmdUI* pCmdUI);
	afx_msg void OnDateView();
	afx_msg LRESULT OnSettingChange(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void AutoSwap(LPTORRENTOBJECT o);
	void OnExpanding(LPTVITEM item);
	void InsertItem(HTREEITEM hParent, LPTORRENTOBJECT Object);
	void InsertDict(HTREEITEM hParent, LPDICTIONARY d);
	void InsertList(HTREEITEM hParent, LPLIST l);
	void InsertListItem(HTREEITEM hParent, LPTORRENTOBJECT Object);
	void InsertInt(HTREEITEM hParent, LPINTEGER i);
	void InsertString(HTREEITEM hParent, LPSTRING s);

	void AddImages();
	void Reselect();

	CImageList m_ImageList;
	BOOL m_BinaryView, m_DateView;
};

#ifndef _DEBUG  // debug version in TorrentView.cpp
inline TorrentDoc* TorrentView::GetDocument()
{
	return (TorrentDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TORRENTVIEW_H__0C0C4FB4_39C3_4632_A33A_588B4883F6D1__INCLUDED_)
