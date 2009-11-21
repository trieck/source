// MemoryView.cpp : implementation file
//

#include "stdafx.h"
#include "emu6502.h"
#include "MemoryView.h"
#include "Memory.h"

#define MEMCHAR(b) (isprint(b) ? b : '.')

// MemoryView

IMPLEMENT_DYNCREATE(MemoryView, MultirowView)

MemoryView::MemoryView()
{
	SetNumLines(4096);
}

MemoryView::~MemoryView()
{
}

BEGIN_MESSAGE_MAP(MemoryView, MultirowView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// MemoryView drawing

void MemoryView::OnInitialUpdate()
{
	MultirowView::OnInitialUpdate();
}

void MemoryView::OnDraw(CDC* pDC)
{
	CFont *pOldFont = pDC->SelectObject(&m_Font);
	MultirowView::OnDraw(pDC);
	DrawMemory(pDC);
	pDC->SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
void MemoryView::DrawMemory(CDC *pDC)
{
	CRect rc;
	pDC->GetClipBox(&rc);

	int begin = rc.top / m_szChar.cy;
	int end = min(m_nLines, (rc.bottom + m_szChar.cy - 1) / m_szChar.cy);

	for (int i = begin; i < end; i++) {
		int cy = m_szChar.cy * i;
		pDC->TextOut(0, cy, GetLine(i*16));
	}
}

/////////////////////////////////////////////////////////////////////////////
CString MemoryView::GetLine(USHORT base)
{
	CString output;
	static const TCHAR line[] =
	    _T("$%.4hX:  %.2hX %.2hX %.2hX %.2hX %.2hX %.2hX %.2hX %.2hX ")
	    _T("%.2X %.2hX %.2hX %.2hX %.2hX %.2hX %.2hX %.2hX")
	    _T("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c");

	Memory* mem = Memory::instance();

	output.Format(line, base,
	              mem->Get(base),
	              mem->Get(base+1),
	              mem->Get(base+2),
	              mem->Get(base+3),
	              mem->Get(base+4),
	              mem->Get(base+5),
	              mem->Get(base+6),
	              mem->Get(base+7),
	              mem->Get(base+8),
	              mem->Get(base+9),
	              mem->Get(base+10),
	              mem->Get(base+11),
	              mem->Get(base+12),
	              mem->Get(base+13),
	              mem->Get(base+14),
	              mem->Get(base+15),

	              MEMCHAR(mem->Get(base)),
	              MEMCHAR(mem->Get(base+1)),
	              MEMCHAR(mem->Get(base+2)),
	              MEMCHAR(mem->Get(base+3)),
	              MEMCHAR(mem->Get(base+4)),
	              MEMCHAR(mem->Get(base+5)),
	              MEMCHAR(mem->Get(base+6)),
	              MEMCHAR(mem->Get(base+7)),
	              MEMCHAR(mem->Get(base+8)),
	              MEMCHAR(mem->Get(base+9)),
	              MEMCHAR(mem->Get(base+10)),
	              MEMCHAR(mem->Get(base+11)),
	              MEMCHAR(mem->Get(base+12)),
	              MEMCHAR(mem->Get(base+13)),
	              MEMCHAR(mem->Get(base+14)),
	              MEMCHAR(mem->Get(base+15))
	             );

	return output;
}

// MemoryView diagnostics

#ifdef _DEBUG
void MemoryView::AssertValid() const
{
	MultirowView::AssertValid();
}

void MemoryView::Dump(CDumpContext& dc) const
{
	MultirowView::Dump(dc);
}
#endif //_DEBUG


// MemoryView message handlers

int MemoryView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (MultirowView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font.CreatePointFont(110, _T("Courier New"));

	CClientDC dc(this);
	CFont *pOldFont = dc.SelectObject(&m_Font);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	m_szChar.cx = tm.tmAveCharWidth;
	m_szChar.cy = tm.tmHeight + tm.tmExternalLeading;
	dc.SelectObject(pOldFont);

	m_nDocHeight = m_szChar.cy * m_nLines;
	m_nDocWidth = m_szChar.cx * _tcslen(
	                  _T("$$$$$:  $$ $$ $$ $$ $$ $$ $$ $$ $$ $$ $$ $$ $$ $$ $$ $$")
	                  _T("   $$$$$$$$$$$$$$$$")
	              );

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

	return 0;
}

