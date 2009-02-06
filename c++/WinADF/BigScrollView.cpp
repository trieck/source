#include "stdafx.h"
#include "BigScrollView.h"

IMPLEMENT_DYNAMIC(BigScrollView, CScrollView)

BEGIN_MESSAGE_MAP(BigScrollView, CScrollView)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
BigScrollView::BigScrollView()
{
}

/////////////////////////////////////////////////////////////////////////////
BigScrollView::~BigScrollView()
{
}

/////////////////////////////////////////////////////////////////////////////
void BigScrollView::OnInitialUpdate()
{
	SetScrollSizes(MM_TEXT, 
		CSize(m_nDocWidth, m_nDocHeight),
		CSize(m_nXPageSize, m_nYPageSize),
		m_szChar);

	CScrollView::OnInitialUpdate();
}

// BigScrollView diagnostics

#ifdef _DEBUG
void BigScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

void BigScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

// BigScrollView message handlers

/////////////////////////////////////////////////////////////////////////////
BOOL BigScrollView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_VSCROLL | WS_HSCROLL;
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
void BigScrollView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	pDC->SetViewportOrg(-m_ScrollPos.x, -m_ScrollPos.y);
	pDC->SetBkMode(TRANSPARENT);
	CScrollView::OnPrepareDC(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
void BigScrollView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = m_ScrollPos.x;
	int orig = pos;
	int nMaxPos = m_nDocWidth - m_nXPageSize;

	SCROLLINFO info;
	
	switch (nSBCode) {
	case SB_TOP:
		pos = 0;
		break;
	case SB_BOTTOM:
		pos = nMaxPos;
		break;
	case SB_LINEUP:
		if (pos <= 0)
			return;
		pos -= min(m_szChar.cx, m_ScrollPos.x);
		break;
	case SB_PAGEUP:
		if (pos <= 0)
			return;
		pos -= min(m_nXPageSize, m_ScrollPos.x);
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		// Adjust for 32bit scroll coordinates
		info.cbSize = sizeof(SCROLLINFO);
		info.fMask = SIF_TRACKPOS;
		GetScrollInfo(SB_HORZ, &info);
       	pos = (int)info.nTrackPos;
		break;
	case SB_PAGEDOWN:
		if (pos >= nMaxPos)
			return;
		pos += min(m_nXPageSize, nMaxPos - m_ScrollPos.x);
		break;
	case SB_LINEDOWN:
		if (pos >= nMaxPos)
			return;
		pos += min(m_szChar.cx, nMaxPos - m_ScrollPos.x);
		break;
	}

	int delta = pos - orig;
	if (delta == 0)
		return;	// no change

	ScrollWindow(-delta, 0);
	SetScrollPos(SB_HORZ, m_ScrollPos.x = pos);

	UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
void BigScrollView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = m_ScrollPos.y;
	int orig = pos;
	int nMaxPos = m_nDocHeight - m_nYPageSize;

	SCROLLINFO info;
	
	switch (nSBCode) {
	case SB_TOP:
		pos = 0;
		break;
	case SB_BOTTOM:
		pos = nMaxPos;
		break;
	case SB_LINEUP:
		if (pos <= 0)
			return;
		pos -= min(m_szChar.cy, m_ScrollPos.y);
		break;
	case SB_PAGEUP:
		if (pos <= 0)
			return;
		pos -= min(m_nYPageSize, m_ScrollPos.y);
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		// Adjust for 32bit scroll coordinates
		info.cbSize = sizeof(SCROLLINFO);
		info.fMask = SIF_TRACKPOS;
		GetScrollInfo(SB_VERT, &info);
       	pos = (int)info.nTrackPos;
		break;
	case SB_PAGEDOWN:
		if (pos >= nMaxPos)
			return;
		pos += min(m_nYPageSize, nMaxPos - m_ScrollPos.y);
		break;
	case SB_LINEDOWN:
		if (pos >= nMaxPos)
			return;
		pos += min(m_szChar.cy, nMaxPos - m_ScrollPos.y);
		break;
	}

	int delta = pos - orig;
	if (delta == 0)
		return;	// no change

	ScrollWindow(0, -delta);
	SetScrollPos(SB_VERT, m_ScrollPos.y = pos);

	UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
void BigScrollView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
	
	int nScrollMax;
	if (cy < m_nDocHeight) {
		nScrollMax = m_nDocHeight;
		m_nYPageSize = cy;
		m_ScrollPos.y = min(m_ScrollPos.y, m_nDocHeight - m_nYPageSize);
	} else nScrollMax = m_ScrollPos.y = m_nYPageSize = 0;

	SCROLLINFO si;
	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nScrollMax;
	si.nPos = m_ScrollPos.y;
	si.nPage = m_nYPageSize;

	SetScrollInfo(SB_VERT, &si, TRUE);

	if (cx < m_nDocWidth) {
		nScrollMax = m_nDocWidth;
		m_nXPageSize = cx;
		m_ScrollPos.x = min(m_ScrollPos.x, m_nDocWidth - m_nXPageSize);
	} else nScrollMax = m_ScrollPos.x = m_nXPageSize = 0;

	si.nMax = nScrollMax;
	si.nPos = m_ScrollPos.x;
	si.nPage = m_nXPageSize;

	SetScrollInfo(SB_HORZ, &si, TRUE);
}

