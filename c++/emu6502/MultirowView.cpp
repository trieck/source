// MultirowView.cpp : implementation file
//

#include "stdafx.h"
#include "emu6502.h"
#include "MultirowView.h"

// MultirowView

IMPLEMENT_DYNCREATE(MultirowView, BigScrollView)

MultirowView::MultirowView()
{
	m_Highlight = 0;
	m_nLines = 0;
}

MultirowView::~MultirowView()
{
}

BEGIN_MESSAGE_MAP(MultirowView, BigScrollView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// MultirowView drawing

void MultirowView::OnDraw(CDC* pDC)
{
	CRect rc;
	pDC->GetClipBox(&rc);

	CPen *pOldPen = pDC->SelectObject(&m_GridPen);

	int begin = rc.top / m_szChar.cy;
	int end = min(m_nLines, (rc.bottom + m_szChar.cy - 1) / m_szChar.cy);

	for (int i = begin; i < end; i++) {
		int cy = m_szChar.cy * i;
		if (i == m_Highlight) {
			pDC->FillSolidRect(0, cy, rc.right, m_szChar.cy,
			                   RGB(0xFF, 0xC0, 0xC0));

			CPen *pOldPen2 = pDC->SelectObject(&m_HighlightPen);
			pDC->MoveTo(0, cy);
			pDC->LineTo(rc.right, cy);
			pDC->LineTo(rc.right, cy + m_szChar.cy - 1);
			pDC->LineTo(0, cy + m_szChar.cy - 1);
			pDC->LineTo(0, cy);
			pDC->SelectObject(pOldPen2);
		} else if (i != m_Highlight + 1) {
			pDC->MoveTo(0, cy);
			pDC->LineTo(rc.right, cy);
		}
	}
	pDC->SelectObject(pOldPen);
}

// MultirowView diagnostics

#ifdef _DEBUG
void MultirowView::AssertValid() const
{
	BigScrollView::AssertValid();
}

void MultirowView::Dump(CDumpContext& dc) const
{
	BigScrollView::Dump(dc);
}
#endif //_DEBUG


// MultirowView message handlers

int MultirowView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (BigScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_GridPen.CreatePen(PS_SOLID, 1, RGB(0xC0, 0xC0, 0xC0));
	m_HighlightPen.CreatePen(PS_SOLID, 1, RGB(0x80, 0x00, 0x00));

	return 0;
}

void MultirowView::OnLButtonDown(UINT nFlags, CPoint point)
{
	point.x += m_ScrollPos.x;
	point.y += m_ScrollPos.y;

	InvalidateHighlightRect(TRUE);	// erase old region

	m_Highlight = point.y / m_szChar.cy;

	InvalidateHighlightRect();	// erase new region

	BigScrollView::OnLButtonDown(nFlags, point);
}

void MultirowView::InvalidateHighlightRect(BOOL clear)
{
	if (m_Highlight != -1) {
		CRect rcClient, rcInvalid;
		GetClientRect(&rcClient);

		rcInvalid.left = 0;
		rcInvalid.top = m_szChar.cy * m_Highlight - m_ScrollPos.y;
		rcInvalid.right = rcInvalid.left + rcClient.Width();
		rcInvalid.bottom = rcInvalid.top + m_szChar.cy + 1;

		if (clear) m_Highlight = -1;	// erase

		InvalidateRect(&rcInvalid);
		UpdateWindow();
	}
}
