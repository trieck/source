// DisassemView.cpp : implementation file
//

#include "stdafx.h"
#include "emu6502.h"
#include "DisassemView.h"

// DisassemView

IMPLEMENT_DYNCREATE(DisassemView, MultirowView)

DisassemView::DisassemView()
{
	SetNumLines(65536);
}

DisassemView::~DisassemView()
{
}

BEGIN_MESSAGE_MAP(DisassemView, MultirowView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// DisassemView drawing

void DisassemView::OnDraw(CDC* pDC)
{
	CFont *pOldFont = pDC->SelectObject(&m_Font);
	MultirowView::OnDraw(pDC);
	DrawDisassem(pDC);
	pDC->SelectObject(pOldFont);
}

void DisassemView::DrawDisassem(CDC *pDC)
{
	CRect rc;
	pDC->GetClipBox(&rc);

	int begin = rc.top / m_szChar.cy;
	int end = min(m_nLines, (rc.bottom + m_szChar.cy - 1) / m_szChar.cy);

	USHORT addr = 0;
	for (int i = begin; i < end; i++) {
		int cy = m_szChar.cy * i;
		pDC->TextOut(0, cy, GetLine(addr));
	}
}

CString DisassemView::GetLine(USHORT &addr)
{
	return disassembler.Get(addr);
}

// DisassemView diagnostics

#ifdef _DEBUG
void DisassemView::AssertValid() const
{
	MultirowView::AssertValid();
}

void DisassemView::Dump(CDumpContext& dc) const
{
	MultirowView::Dump(dc);
}
#endif //_DEBUG


// DisassemView message handlers

int DisassemView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_nDocWidth = 0;
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
