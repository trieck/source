#pragma once


// TextView view

class TextView : public CView
{
	DECLARE_DYNCREATE(TextView)

protected:
	TextView();           // protected constructor used by dynamic creation
	virtual ~TextView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	CFont m_Font;
	int m_cyChar;
	int m_cxChar;
	int m_nLinesTotal;
	int m_nXPageSize;
	int m_nYPageSize;
	int m_nDocHeight;
	int m_nDocWidth;
	CPoint m_ScrollPos;

	CString m_Text;
	CDC m_MemDC;
	CBitmap m_Bitmap;

	void CalcSizes(void);
	int RecalcLayout(void);
};



