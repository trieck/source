// TextView.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "TextView.h"


// TextView

IMPLEMENT_DYNCREATE(TextView, BigScrollView)

TextView::TextView()
{
}

TextView::~TextView()
{
}

BEGIN_MESSAGE_MAP(TextView, BigScrollView)
	ON_WM_CREATE()
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
	BigScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void TextView::Dump(CDumpContext& dc) const
{
	BigScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// TextView message handlers

void TextView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
}

void TextView::OnInitialUpdate()
{
	BigScrollView::OnInitialUpdate();
}

int TextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (BigScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	RecalcLayout();

	return 0;
}

void TextView::SetSizes(void)
{
	CClientDC dc(this);

	CFont *pOldFont = dc.SelectObject(&m_Font);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	::GetCharWidth32(dc, '0', '0', (LPINT)&m_szChar.cx);
	m_szChar.cy = tm.tmHeight + tm.tmExternalLeading;

	CRect rc;
	dc.DrawText(m_Text, -1, &rc, DT_CALCRECT | DT_EDITCONTROL);

	m_nDocWidth = rc.Width();
	m_nDocHeight = rc.Height();

	m_nLinesTotal = rc.Height() / m_szChar.cy;

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
	SetSizes();
	
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
