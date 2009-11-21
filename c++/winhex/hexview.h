// hexview.h : interface of the HexView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXVIEW_H__B1B4E5FE_8F9B_11D3_88CE_000000000000__INCLUDED_)
#define AFX_HEXVIEW_H__B1B4E5FE_8F9B_11D3_88CE_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HexEdit.h"

class HexView : public CView {
protected: // create from serialization only
	HexView();
	DECLARE_DYNCREATE(HexView)

// Attributes
public:
	HexDoc* GetDocument() const;

// Operations
public:
	void Update();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HexView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~HexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void Render(CDC *pDC, LPCBYTE pdata, UINT size);
	int FormatLine(UINT line, LPSTR buffer, LPCBYTE pdata, UINT size) const;
	void DrawGridLine(CDC *pDC, int vpos, int xextent);
	BOOL GetCellByPoint(CPoint pt, int & row, int & col) const;
	BOOL NavigateCell(UINT nChar);
	void UpdateCell();
	BOOL PrevCell();
	BOOL NextCell();
	BOOL PrevRow();
	BOOL NextRow();
	void InvalidateCell(BOOL eraseChar = TRUE);
	void RepositionCell();
	void SetSizes();
	void GetCellPos(int & row, int & col) const;
	void SetCellPos(int row, int col);
	void GetCellRect(CRect & rc) const;
	void GetCellByPos(int row, int col, CRect & rc) const;
	void ScrollToCell();

// Generated message map functions
protected:
	//{{AFX_MSG(HexView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFont();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBackgroundColor();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont m_font;
	CPen m_gridpen;
	CBrush m_bgBrush;
	int m_cyChar;
	int m_cxChar;
	int m_nLinesTotal;
	int m_nXPageSize;
	int m_nYPageSize;
	int m_nDocHeight;
	int m_nDocWidth;
	BOOL m_grid;
	COLORREF m_color;	// text color
	HexEdit m_edit;
	UINT m_ActiveCell;
	CPoint m_ScrollPos;

	friend class HexEdit;
};

/////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in hexview.cpp
inline HexDoc* HexView::GetDocument() const
{
	return (HexDoc*)m_pDocument;
}
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXVIEW_H__B1B4E5FE_8F9B_11D3_88CE_000000000000__INCLUDED_)
