
// DrumSequencerView.cpp : implementation of the CDrumSequencerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DrumSequencer.h"
#endif

#include "DrumSequencerDoc.h"
#include "DrumSequencerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrumSequencerView

IMPLEMENT_DYNCREATE(CDrumSequencerView, CView)

BEGIN_MESSAGE_MAP(CDrumSequencerView, CView)
	// Standard printing commands
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
END_MESSAGE_MAP()

#define BKGND_COLOR	RGB(0xEE, 0xEE, 0xEE)

// CDrumSequencerView construction/destruction

const LPCTSTR Instruments[] = {
	_T("Closed Hi-Hat"),
	_T("Pedal Hi-Hat"),
	_T("Open Hi-Hat"),
	_T("Crash Cymbal"),
	_T("Ride Cymbal"),
	_T("Snare Drum"),
	_T("High Tom"),
	_T("Mid Tom"),
	_T("Low Tom"),
	_T("Bass Drum")
};

CDrumSequencerView::CDrumSequencerView()
{
}

CDrumSequencerView::~CDrumSequencerView()
{
}

BOOL CDrumSequencerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CDrumSequencerView drawing

void CDrumSequencerView::OnDraw(CDC* pDC)
{
	CDrumSequencerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawInstruments(pDC);
	m_grid.Draw(pDC);
	DrawBeats(pDC, pDoc->GetSequence());
}

// CDrumSequencerView printing

BOOL CDrumSequencerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrumSequencerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrumSequencerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

// CDrumSequencerView diagnostics

#ifdef _DEBUG
void CDrumSequencerView::AssertValid() const
{
	CView::AssertValid();
}

void CDrumSequencerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrumSequencerDoc* CDrumSequencerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrumSequencerDoc)));
	return (CDrumSequencerDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrumSequencerView message handlers

void CDrumSequencerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDrumSequencerDoc *pDoc = GetDocument();

	if (m_grid.PointOnGrid(point)) {
		CPoint sub = m_grid.GetSubdivision(point);
		pDoc->ToggleSub(sub);
	}

	CView::OnLButtonDown(nFlags, point);
}


BOOL CDrumSequencerView::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	pDC->SetBkMode(TRANSPARENT);
	pDC->GetClipBox(&rc);
	pDC->FillRect(&rc, &m_bkgndBrush);
	return TRUE;
}


int CDrumSequencerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_bkgndBrush.CreateSolidBrush(BKGND_COLOR))
		return -1;

	CClientDC dc(this);

	// Create the font
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	_tcscpy(lf.lfFaceName, _T("Verdana"));
	lf.lfWeight = FW_NORMAL;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight = -MulDiv(7, dc.GetDeviceCaps(LOGPIXELSY), 72);

	if (!m_font.CreateFontIndirect(&lf))
		return -1;

	return 0;
}

void CDrumSequencerView::DrawInstruments(CDC* pDC)
{
	CRect rc;
	pDC->GetClipBox(rc);

	CFont *pOldFont = pDC->SelectObject(&m_font);

	CSize sz;
	int x, y = BeatGrid::CY_OFFSET+2;
	for (int i = 0; i < sizeof(Instruments) / sizeof(LPCTSTR); i++) {
		sz = pDC->GetTextExtent(Instruments[i]);
		x = BeatGrid::CX_OFFSET - sz.cx - 2;
		pDC->TextOut(x, y, Instruments[i]);
		y += BeatGrid::CY_SUB;
	}

	pDC->SelectObject(pOldFont);
}

void CDrumSequencerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (pHint != NULL) {
		Sequence *pSeq = static_cast<Sequence*>(pHint);
		ASSERT_VALID(pSeq);
		int x = LOWORD(lHint);
		int y = HIWORD(lHint);
		CRect rc;
		m_grid.GetBeatRect(x, y, rc);
		InvalidateRect(rc);
	} else {
		CView::OnUpdate(pSender, lHint, pHint);
	}
}

void CDrumSequencerView::DrawBeats(CDC *pDC, Sequence *pSeq)
{
	CRect rc;
	COLORREF color;

	for (int i = 0; i < Sequence::NINSTRUMENTS; i++) {
		color = BeatGrid::GetInstColor(i);
		for (int j = 0; j < Sequence::NSUBS; j++) {
			if (pSeq->GetBeat(j, i)) {
				m_grid.GetBeatRect(j, i, rc);
				rc.DeflateRect(1,1,0,0);

				if (j % Sequence::RESOLUTION == Sequence::RESOLUTION-1) {
					rc.right -= 1;	// thick pen
				}
				if (i == Sequence::NINSTRUMENTS-1) {
					rc.bottom -= 1;
				}
				pDC->FillSolidRect(rc, color);
			}
		}
	}
}
