// BinaryView.cpp : implementation file
//

#include "stdafx.h"
#include "torrentexplorer.h"
#include "TorrentObject.h"
#include "String.h"
#include "BinaryView.h"
#include "String.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LINESIZE				16
#define BUFFSIZE				81
#define DATAOFFSET				13
#define CHAROFFSET				5
#define COLOR_SILVER			PALETTERGB (0xc0, 0xc0, 0xc0)
#define COLOR_HILIGHT			PALETTERGB (0xFF, 0xC0, 0xC0)
#define COLOR_HILIGHT_BORDER	PALETTERGB(0x80, 0x00, 0x00)

/////////////////////////////////////////////////////////////////////////////
// BinaryView

IMPLEMENT_DYNCREATE(BinaryView, CView)

BinaryView::BinaryView()
    : m_pString(NULL), m_pBuffer(NULL)
{
    m_cyChar = 0;
    m_cxChar = 0;
    m_nLinesTotal = 0;
    m_nXPageSize = 0;
    m_nYPageSize = 0;
    m_nDocHeight = 0;
    m_nDocWidth = 0;
    m_Highlight = -1;
    m_ScrollPos = CPoint(0, 0);
}

BinaryView::~BinaryView()
{
    if (m_pBuffer != NULL)
        delete m_pBuffer;
}

BEGIN_MESSAGE_MAP(BinaryView, CView)
    //{{AFX_MSG_MAP(BinaryView)
    ON_WM_CREATE()
    ON_WM_VSCROLL()
    ON_WM_HSCROLL()
    ON_WM_SIZE()
    ON_MESSAGE(WM_SETTING_CHANGE, OnSettingChange)
    ON_WM_LBUTTONDOWN()
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BinaryView drawing

void BinaryView::OnInitialUpdate()
{
    CView::OnInitialUpdate();
}

void BinaryView::OnDraw(CDC* pDC)
{
    if (m_pString != NULL) {
        CFont * pOldFont = pDC->SelectObject(&m_Font);
        Render(pDC);
        pDC->SelectObject(pOldFont);
    }
}

void BinaryView::Render(CDC *pDC)
{
    CRect rc;
    pDC->GetClipBox(rc);

    int nstart = rc.top / m_cyChar;
    int nend = min(m_nLinesTotal - 1,
                   (rc.bottom + m_cyChar - 1) / m_cyChar);

    for (int n = nstart; n <= nend; n++) {
        if (n == m_Highlight) {
            DrawHighlight(pDC, n, rc.right);
        } else if (n > 0 && n != m_Highlight + 1) {
            DrawGridLine(pDC, n, rc.right);
        } else {
            DrawGridLine(pDC, n, rc.right);
        }
        DrawText(pDC, n);
    }
}

void BinaryView::DrawHighlight(CDC *pDC, int line, int cx)
{
    int cy = line * m_cyChar;

    CBrush *pOldBrush = pDC->SelectObject(&m_HilightBrush);
    pDC->PatBlt(0, cy, cx, m_cyChar, PATCOPY);
    pDC->SelectObject(pOldBrush);

    CPen *pOldPen = pDC->SelectObject(&m_HilightPen);
    pDC->MoveTo(0, cy);
    pDC->LineTo(cx, cy);
    pDC->LineTo(cx, cy + m_cyChar - 1);
    pDC->LineTo(0, cy + m_cyChar - 1);
    pDC->LineTo(0, cy);
    pDC->SelectObject(pOldPen);
}

void BinaryView::DrawGridLine(CDC *pDC, int line, int cx)
{
    ASSERT_VALID(pDC);

    CPen * pOldPen = pDC->SelectObject(&m_GridPen);

    int y = (line + 1) * m_cyChar - 1;

    pDC->MoveTo(m_ScrollPos.x, y);
    pDC->LineTo(m_ScrollPos.x + cx, y);

    pDC->SelectObject(pOldPen);
}

void BinaryView::DrawText(CDC *pDC, int line)
{
    const CString &s = *m_pString;
    LPCBYTE pdata = (LPCBYTE)(LPCSTR)s;
    UINT size = s.GetLength();

    int nlength = min(LINESIZE, size - (line * LINESIZE));
    int j = FormatLine(line, pdata + (line * LINESIZE), nlength);
    pDC->TextOut(0, line * m_cyChar, m_pBuffer, j);
}

/////////////////////////////////////////////////////////////////////////////
// BinaryView diagnostics

#ifdef _DEBUG
void BinaryView::AssertValid() const
{
    CView::AssertValid();
}

void BinaryView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// BinaryView message handlers

void BinaryView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    LPTORRENTOBJECT o = (LPTORRENTOBJECT)pHint;
    m_pString = (o != NULL && o->GetElementType() == ET_STRING) ?
                (LPSTRING)o : NULL;

    SetSizes();
    Invalidate();
}

int BinaryView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    CClientDC dc(this);

    // Create the font
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    strcpy(lf.lfFaceName, "Courier New");
    lf.lfWeight = FW_NORMAL;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfHeight = -MulDiv(10, dc.GetDeviceCaps(LOGPIXELSY), 72);

    if (!m_Font.CreateFontIndirect(&lf))
        return -1;

    TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();

    COLORREF clrHilight = COLOR_HILIGHT;
    if (pApp->IsSetting("ui_hilight_color")) {
        clrHilight = pApp->GetIntSetting("ui_hilight_color");
    }
    if (!m_HilightBrush.CreateSolidBrush(clrHilight))
        return -1;

    COLORREF clrHilightBorder = COLOR_HILIGHT_BORDER;
    if (pApp->IsSetting("ui_hilight_border_color")) {
        clrHilightBorder = pApp->GetIntSetting("ui_hilight_border_color");
    }

    if (!m_HilightPen.CreatePen(PS_SOLID, 1, clrHilightBorder))
        return -1;

    m_pBuffer = new char[BUFFSIZE + 1];

    SetSizes();
    OnSettingChange(0, 0);

    return 0;
}

BOOL BinaryView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= WS_VSCROLL | WS_HSCROLL;
    return CView::PreCreateWindow(cs);
}

void BinaryView::SetSizes()
{
    CClientDC dc(this);

    CFont *pOldFont = dc.SelectObject(&m_Font);

    TEXTMETRIC tm;
    dc.GetTextMetrics(&tm);

    ::GetCharWidth32(dc, '0', '0', &m_cxChar);
    m_cyChar = tm.tmHeight + tm.tmExternalLeading;

    if (m_pString != NULL) {
        m_nLinesTotal = (m_pString->GetLength() + LINESIZE - 1) / LINESIZE;
        m_nDocWidth = m_pString->GetLength() ? BUFFSIZE * m_cxChar : 0;
        m_nDocHeight = m_nLinesTotal * m_cyChar;
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

void BinaryView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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

void BinaryView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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

void BinaryView::OnSize(UINT nType, int cx, int cy)
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

int BinaryView::FormatLine(UINT line, LPCBYTE pdata, UINT size)
{
    LPSTR pbuffer = m_pBuffer;
    sprintf(pbuffer, "%0.8x     ", line * LINESIZE);

    pbuffer += DATAOFFSET;

    for (unsigned j = 0; j < size; j++) {
        if (j > 0)
            pbuffer++[0] = ' ';

        sprintf(pbuffer, "%0.2x", pdata[j]);
        pbuffer += 2;
    }

    unsigned diff = LINESIZE - size;
    while (diff) {
        pbuffer[0] = ' ';
        pbuffer[1] = ' ';
        pbuffer[2] = ' ';
        pbuffer += 3;
        diff--;
    }

    strcpy(pbuffer, "     ");
    pbuffer += CHAROFFSET;

    for (unsigned n = 0; n < size; n++) {
        if (isprint(pdata[n]))
            pbuffer[n] = pdata[n];
        else pbuffer[n] = '.';
    }

    pbuffer[size] = '\0';

    return (pbuffer + size) - m_pBuffer;
}

void BinaryView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    pDC->SetViewportOrg(-m_ScrollPos.x, -m_ScrollPos.y);
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(m_TextColor);
    pDC->SetBkColor(m_BkgndColor);
    CView::OnPrepareDC(pDC, pInfo);
}

LRESULT BinaryView::OnSettingChange(WPARAM wParam, LPARAM lParam)
{
    TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();

    if (pApp->IsSetting("ui_bkgnd_color")) {
        m_BkgndColor = pApp->GetIntSetting("ui_bkgnd_color");
    } else {
        m_BkgndColor = GetSysColor(COLOR_WINDOW);
    }

    if (pApp->IsSetting("ui_text_color")) {
        m_TextColor = pApp->GetIntSetting("ui_text_color");
    } else {
        m_TextColor = GetSysColor(COLOR_WINDOWTEXT);
    }

    COLORREF GridColor = COLOR_SILVER;
    if (pApp->IsSetting("ui_grid_color")) {
        GridColor = pApp->GetIntSetting("ui_grid_color");
    }
    if (pApp->IsSetting("ui_hilight_color")) {
        COLORREF clrHilight = pApp->GetIntSetting("ui_hilight_color");
        m_HilightBrush.DeleteObject();
        m_HilightBrush.CreateSolidBrush(clrHilight);
    }
    if (pApp->IsSetting("ui_hilight_border_color")) {
        COLORREF clrHilightBorder =
            pApp->GetIntSetting("ui_hilight_border_color");
        m_HilightPen.DeleteObject();
        m_HilightPen.CreatePen(PS_SOLID, 1, clrHilightBorder);
    }

    m_GridPen.DeleteObject();
    m_GridPen.CreatePen(PS_SOLID, 1, GridColor);

    RedrawWindow();

    return 0;
}

void BinaryView::OnLButtonDown(UINT nFlags, CPoint point)
{
    point.x += m_ScrollPos.x;
    point.y += m_ScrollPos.y;

    InvalidateHighlightRect(TRUE);	// erase old region

    m_Highlight = point.y / m_cyChar;

    InvalidateHighlightRect();	// erase new region

    CView::OnLButtonDown(nFlags, point);
}

void BinaryView::InvalidateHighlightRect(BOOL clear)
{
    if (m_Highlight != -1) {
        CRect rcClient, rcInvalid;
        GetClientRect(&rcClient);

        rcInvalid.left = 0;
        rcInvalid.top = m_cyChar * m_Highlight - m_ScrollPos.y;
        rcInvalid.right = rcInvalid.left + rcClient.Width();
        rcInvalid.bottom = rcInvalid.top + m_cyChar;

        if (clear) m_Highlight = -1;	// erase

        InvalidateRect(&rcInvalid);
        UpdateWindow();
    }
}

BOOL BinaryView::OnEraseBkgnd(CDC* pDC)
{
    CRect rc;
    pDC->GetClipBox(rc);
    pDC->FillSolidRect(rc.left, rc.top, rc.Width(), rc.Height(),
                       m_BkgndColor);
    return TRUE;
}