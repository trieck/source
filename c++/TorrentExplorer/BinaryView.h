#if !defined(AFX_BINARYVIEW_H__0B13B227_1783_468B_81C6_601F9F184A8A__INCLUDED_)
#define AFX_BINARYVIEW_H__0B13B227_1783_468B_81C6_601F9F184A8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BinaryView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BinaryView view

class BinaryView : public CView
{
protected:
	BinaryView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(BinaryView)

// Attributes
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BinaryView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnEraseBkgnd(CDC *pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~BinaryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(BinaryView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSettingChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Render(CDC *pDC);

	int FormatLine(UINT line, LPCBYTE pdata, UINT size);
	void DrawHighlight(CDC *pDC, int line, int cx);
	void DrawGridLine(CDC *pDC, int line, int cx);
	void DrawText(CDC *pDC, int line);
	void InvalidateHighlightRect(BOOL clear = FALSE);

	void SetSizes();
	CFont m_Font;
	CPen m_GridPen, m_HilightPen;
	CBrush m_HilightBrush;
	LPSTRING m_pString;

	int m_cyChar;
	int m_cxChar;
	int m_nLinesTotal;
	int m_nXPageSize;
	int m_nYPageSize;
	int m_nDocHeight;
	int m_nDocWidth;
	int m_Highlight;

	CPoint m_ScrollPos;
	LPSTR m_pBuffer;

	COLORREF m_BkgndColor, m_TextColor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINARYVIEW_H__0B13B227_1783_468B_81C6_601F9F184A8A__INCLUDED_)
