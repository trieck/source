#include "StdAfx.h"
#include "HexView.h"

#define LINESIZE				16
#define LBUFFSIZE				81
#define DATAOFFSET				13
#define CHAROFFSET				5
#define COLOR_SILVER			PALETTERGB (0xc0, 0xc0, 0xc0)

BEGIN_MESSAGE_MAP(HexView, BigScrollView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(HexView, BigScrollView)

HexView::HexView(void)
		: m_pBuffer(0), m_pLine(0), m_nBufferLen(0)
{
}

HexView::~HexView(void)
{
	if (m_pBuffer != NULL)
		delete []m_pBuffer;

	if (m_pLine != NULL)
		delete []m_pLine;
}

void HexView::OnDraw(CDC* pDC)
{
	if (m_pBuffer != NULL && m_nBufferLen > 0) {
		CFont * pOldFont = pDC->SelectObject(&m_Font);
		Render(pDC);
		pDC->SelectObject(pOldFont);
	}
}

void HexView::Render(CDC* pDC)
{
	CRect rc;
	pDC->GetClipBox(rc);

	uint32_t nstart = rc.top / m_szChar.cy;
	uint32_t nend = min(m_nLinesTotal - 1,
	                    (rc.bottom + m_szChar.cy - 1) / m_szChar.cy);

	for (uint32_t n = nstart; n <= nend; n++) {
		DrawGridLine(pDC, n, rc.right);
		DrawText(pDC, n);
	}
}

void HexView::DrawGridLine(CDC *pDC, uint32_t line, uint32_t cx)
{
	ASSERT_VALID(pDC);

	CPen * pOldPen = pDC->SelectObject(&m_GridPen);

	uint32_t y = (line + 1) * m_szChar.cy - 1;

	pDC->MoveTo(m_ScrollPos.x, y);
	pDC->LineTo(m_ScrollPos.x + cx, y);

	pDC->SelectObject(pOldPen);
}

void HexView::DrawText(CDC *pDC, uint32_t line)
{
	uint32_t nlength = min(LINESIZE, m_nBufferLen - (line * LINESIZE));
	uint32_t nline = FormatLine(line, m_pBuffer + (line * LINESIZE), nlength);

	// TODO: BUGBUG
	pDC->TextOut(0, line * m_szChar.cy, m_pLine, nline);
}

uint32_t HexView::FormatLine(uint32_t line, uint8_t *pdata, uint32_t size)
{
	LPSTR pline = m_pLine;
	sprintf(pline, "%0.8x     ", line * LINESIZE);

	pline += DATAOFFSET;

	for (uint32_t j = 0; j < size; j++) {
		if (j > 0)
			pline++[0] = ' ';

		sprintf(pline, "%0.2x", pdata[j]);
		pline += 2;
	}

	uint32_t diff = LINESIZE - size;
	while (diff) {
		pline[0] = ' ';
		pline[1] = ' ';
		pline[2] = ' ';
		pline += 3;
		diff--;
	}

	strcpy(pline, "     ");
	pline += CHAROFFSET;

	for (uint32_t n = 0; n < size; n++) {
		if (isprint(pdata[n]))
			pline[n] = pdata[n];
		else pline[n] = '.';
	}

	pline[size] = '\0';

	return (pline + size) - m_pLine;
}

int HexView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (BigScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if ((m_pLine = new char[LBUFFSIZE + 1]) == NULL)
		return -1;

	m_GridPen.CreatePen(PS_SOLID, 1, COLOR_SILVER);

	return 0;
}

void HexView::SetSizes()
{
	CClientDC dc(this);

	CFont *pOldFont = dc.SelectObject(&m_Font);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	::GetCharWidth32(dc, '0', '0', (LPINT)&m_szChar.cx);
	m_szChar.cy = tm.tmHeight + tm.tmExternalLeading;

	if (m_pBuffer != NULL) {
		m_nLinesTotal = (m_nBufferLen + LINESIZE - 1) / LINESIZE;
		m_nDocWidth = m_nBufferLen ? LBUFFSIZE * m_szChar.cx : 0;
		m_nDocHeight = m_nLinesTotal * m_szChar.cy;
	} else {
		m_nLinesTotal = m_nDocHeight = m_nDocWidth = 0;
	}

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
