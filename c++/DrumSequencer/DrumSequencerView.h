#pragma once

#include "BeatGrid.h"

class CDrumSequencerView : public CView
{
protected: // create from serialization only
    CDrumSequencerView() = default;
    virtual ~CDrumSequencerView() = default;

DECLARE_DYNCREATE(CDrumSequencerView)

    CDrumSequencerDoc* GetDocument() const;

    void OnDraw(CDC* pDC) override; // overridden to draw this view
    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
protected:
    BOOL OnPreparePrinting(CPrintInfo* pInfo) override;

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
    void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/) override;
    void DrawBeats(CDC* pDC, Sequence* pSeq);
};

#ifndef _DEBUG  // debug version in DrumSequencerView.cpp
inline CDrumSequencerDoc* CDrumSequencerView::GetDocument() const
{
    return reinterpret_cast<CDrumSequencerDoc*>(m_pDocument);
}
#endif
