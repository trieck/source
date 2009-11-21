// TextView.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "TextView.h"


// TextView

IMPLEMENT_DYNCREATE(TextView, BigScrollView)

TextView::TextView() : m_nLineLen(0), m_nBlockedLen(0)
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
	uint32_t nlen = m_blockedText.GetLength();
	if (nlen > 0) {
		CFont * pOldFont = pDC->SelectObject(&m_Font);
		DrawLines(pDC);
		pDC->SelectObject(pOldFont);
	}
}

void TextView::DrawLines(CDC *pDC)
{
	CRect rc;
	pDC->GetClipBox(rc);

	uint32_t nstart = rc.top / m_szChar.cy;
	uint32_t nend = min(m_nLinesTotal - 1,
	                    (rc.bottom + m_szChar.cy - 1) / m_szChar.cy);

	for (uint32_t n = nstart; n <= nend; n++) {
		DrawLine(pDC, n);
	}
}

void TextView::DrawLine(CDC *pDC, uint32_t line)
{
	uint32_t offset = line * m_nLineLen;
	LPCSTR pbuff = (LPCSTR)m_blockedText;
	LPCSTR pline = &pbuff[offset];

	CRect rc;
	rc.left = 0;	// TODO: BUGBUG
	rc.top = line * m_szChar.cy;
	rc.right = rc.left + (m_nLineLen * m_szChar.cx);
	rc.bottom = rc.top + m_szChar.cy;

	pDC->DrawText(pline, m_nLineLen, rc, DT_EXPANDTABS|DT_EDITCONTROL);
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
	rc.SetRectEmpty();
	dc.DrawText(m_Text, -1, &rc, DT_EXPANDTABS|DT_CALCRECT|DT_EDITCONTROL);

	m_nDocWidth = rc.Width();
	m_nDocHeight = rc.Height();
	m_nLinesTotal = rc.Height() / m_szChar.cy;
	m_nLineLen = m_nDocWidth / m_szChar.cx;
	m_nBlockedLen = m_nLineLen * m_nLinesTotal;

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

void TextView::RecalcLayout(void)
{
	SetSizes();
	BlockText();
}

void TextView::BlockText()
{
	m_blockedText.Empty();

	m_Text.Replace("\r\n", "\n");
	m_Text.Replace("\r", "\n");

	LPCSTR ptext = m_Text;

	uint32_t n = 0;
	char c;
	for (;;) {
		switch (c = *ptext++) {
		case '\0':
			if (m_blockedText.GetLength() < (int)m_nBlockedLen) {
				if (n < m_nLineLen)
					m_blockedText += CString(' ', m_nLineLen-n);
			}
			return;
		case '\n':
			if (n < m_nLineLen)
				m_blockedText += CString(' ', m_nLineLen-n);
			n = 0;
			break;
		default:
			m_blockedText += c;
			n++;
			break;
		}
	}
}