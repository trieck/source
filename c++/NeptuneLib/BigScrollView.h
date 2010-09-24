#pragma once

/////////////////////////////////////////////////////////////////////////////
class BigScrollView : public CScrollView {
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
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

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


