// StackView.cpp : implementation file
//

#include "stdafx.h"
#include "emu6502.h"
#include "StackView.h"
#include "Memory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StackView

IMPLEMENT_DYNCREATE(StackView, MultirowView)

StackView::StackView()
{
    SetNumLines(256);
}

StackView::~StackView()
{
}

BEGIN_MESSAGE_MAP(StackView, MultirowView)
    //{{AFX_MSG_MAP(StackView)
    //}}AFX_MSG_MAP
    ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StackView drawing

void StackView::OnDraw(CDC* pDC)
{
    CFont *pOldFont = pDC->SelectObject(&m_Font);
    MultirowView::OnDraw(pDC);
    DrawStack(pDC);
    pDC->SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
void StackView::DrawStack(CDC *pDC)
{
    CRect rc;
    pDC->GetClipBox(&rc);

    int begin = rc.top / m_szChar.cy;
    int end = min(m_nLines, (rc.bottom + m_szChar.cy - 1) / m_szChar.cy);

    for (int i = begin; i < end; i++) {
        int cy = m_szChar.cy * i;
        pDC->TextOut(0, cy, GetLine(i));
    }
}

/////////////////////////////////////////////////////////////////////////////
CString StackView::GetLine(USHORT i)
{
    static const TCHAR line[] = _T("$1%.2hX:  %.2hX");
    TCHAR buf[10];

    Memory* mem = Memory::instance();

    _stprintf(buf, line, 0xff - i, mem->Get(0x1ff - i));

    return buf;
}

/////////////////////////////////////////////////////////////////////////////
// StackView diagnostics

#ifdef _DEBUG
void StackView::AssertValid() const
{
    MultirowView::AssertValid();
}

void StackView::Dump(CDumpContext& dc) const
{
    MultirowView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// StackView message handlers

int StackView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
    m_nDocWidth = m_szChar.cx * _tcslen(_T("$$$$:  $$"));

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
