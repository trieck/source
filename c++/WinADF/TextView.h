#pragma once

#include "BigScrollView.h"

// TextView view

class TextView : public BigScrollView
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
public:
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	CFont m_Font;
	CString m_Text;
	CString m_blockedText;
	uint32_t m_nLineLen;
	uint32_t m_nBlockedLen;

	void SetSizes(void);
	void RecalcLayout(void);
	void BlockText();
	void DrawLines(CDC *pDC);
	void DrawLine(CDC *pDC, uint32_t line);
};



