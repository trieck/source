#pragma once

/////////////////////////////////////////////////////////////////////////////
class BigScrollView : public CView
{
	DECLARE_DYNAMIC(BigScrollView)

protected:
	BigScrollView();
	virtual ~BigScrollView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
protected:
	CSize m_szChar;					// font width / height
	int m_nLinesTotal;
	int m_nXPageSize;
	int m_nYPageSize;
	int m_nDocHeight;
	int m_nDocWidth;
	CPoint m_ScrollPos;
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


