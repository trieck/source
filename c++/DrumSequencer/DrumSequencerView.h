
// DrumSequencerView.h : interface of the CDrumSequencerView class
//

#pragma once

#include "BeatGrid.h"

class CDrumSequencerView : public CView {
protected: // create from serialization only
	CDrumSequencerView();
	DECLARE_DYNCREATE(CDrumSequencerView)

// Attributes
public:
	CDrumSequencerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDrumSequencerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	BeatGrid m_grid;
	CBrush m_bkgndBrush;
	CFont m_font;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void DrawInstruments(CDC* pDC);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	void DrawBeats(CDC * pDC, Sequence * pSeq);
};

#ifndef _DEBUG  // debug version in DrumSequencerView.cpp
inline CDrumSequencerDoc* CDrumSequencerView::GetDocument() const
{
	return reinterpret_cast<CDrumSequencerDoc*>(m_pDocument);
}
#endif

