// TextView.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "TextView.h"


// TextView

IMPLEMENT_DYNCREATE(TextView, CView)

TextView::TextView()
{
	m_cxChar = 0;
	m_cyChar = 0;
	m_nLinesTotal = 0;
	m_nXPageSize = 0;
	m_nYPageSize = 0;
	m_nDocHeight = 0;
	m_nDocWidth = 0;
	m_ScrollPos = CPoint(0, 0);
}

TextView::~TextView()
{
}

BEGIN_MESSAGE_MAP(TextView, CView)
	ON_WM_CREATE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// TextView drawing

void TextView::OnDraw(CDC* pDC)
{
	CBitmap *pOldBitmap = m_MemDC.SelectObject(&m_Bitmap);	

	CRect rc;
	pDC->GetClipBox(rc);
	pDC->BitBlt(rc.left, rc.top, 
		rc.Width(), rc.Height(), &m_MemDC, 
		rc.left, rc.top, SRCCOPY
	);

	m_MemDC.SelectObject(pOldBitmap);

}


// TextView diagnostics

#ifdef _DEBUG
void TextView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void TextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// TextView message handlers

BOOL TextView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_VSCROLL | WS_HSCROLL;
	return CView::PreCreateWindow(cs);
}

void TextView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	pDC->SetViewportOrg(-m_ScrollPos.x, -m_ScrollPos.y);

	CView::OnPrepareDC(pDC, pInfo);
}

void TextView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
}

void TextView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}

int TextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	RecalcLayout();

	return 0;
}

void TextView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
		pos -= min(m_cyChar, m_ScrollPos.y);
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
		pos += min(m_cyChar, nMaxPos - m_ScrollPos.y);
		break;
	}

	int delta = pos - orig;
	if (delta == 0)
		return;	// no change

	ScrollWindow(0, -delta);
	SetScrollPos(SB_VERT, m_ScrollPos.y = pos);

	UpdateWindow();
}

void TextView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
		pos -= min(m_cxChar, m_ScrollPos.x);
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
		pos += min(m_cxChar, nMaxPos - m_ScrollPos.x);
		break;
	}

	int delta = pos - orig;
	if (delta == 0)
		return;	// no change

	ScrollWindow(-delta, 0);
	SetScrollPos(SB_HORZ, m_ScrollPos.x = pos);

	UpdateWindow();
}

void TextView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	
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

void TextView::CalcSizes(void)
{
	CClientDC dc(this);

	CFont *pOldFont = dc.SelectObject(&m_Font);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	::GetCharWidth32(dc, '0', '0', &m_cxChar);
	m_cyChar = tm.tmHeight + tm.tmExternalLeading;

	CRect rc;
	dc.DrawText(m_Text, -1, &rc, DT_CALCRECT | DT_EDITCONTROL);

	m_nDocWidth = rc.Width();
	m_nDocHeight = rc.Height();

	m_nLinesTotal = rc.Height() / m_cyChar;

	m_ScrollPos = CPoint(0, 0);

	SCROLLINFO si;
	memset(&si, 0, sizeof(SCROLLINFO));
	si.fMask = SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = m_nDocHeight;
	si.nPos = 0;

	SetScrollInfo(SB_VERT, &si, TRUE);

	si.nMax = m_nDocWidth;
	SetScrollInfo(SB_HORZ, &si, TRUE);

	dc.SelectObject(pOldFont);
}

int TextView::RecalcLayout(void)
{
	CalcSizes();
	
	CClientDC dc(this);

	m_MemDC.DeleteDC();
    if (!m_MemDC.CreateCompatibleDC(&dc))
		return -1;

	m_MemDC.SetBkMode(TRANSPARENT);
    m_MemDC.SetMapMode(dc.GetMapMode());

	m_Bitmap.DeleteObject();
	if (!m_Bitmap.CreateCompatibleBitmap(&dc, m_nDocWidth, m_nDocHeight))
		return -1;	

	CRect rc(0, 0, m_nDocWidth, m_nDocHeight);

	CBrush *pBrush = dc.GetCurrentBrush();
	
	CBrush *pOldBrush = m_MemDC.SelectObject(pBrush);
	CFont *pOldFont = m_MemDC.SelectObject(&m_Font);
	CBitmap *pOldBitmap = m_MemDC.SelectObject(&m_Bitmap);	

	m_MemDC.PatBlt(0, 0, rc.Width(), rc.Height(), PATCOPY);
	m_MemDC.DrawText(m_Text, -1, &rc, DT_EDITCONTROL);

	m_MemDC.SelectObject(pOldBitmap);	
	m_MemDC.SelectObject(pOldFont);
	m_MemDC.SelectObject(pOldBrush);

	return 0;
}
