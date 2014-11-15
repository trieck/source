// hexview.cpp : implementation of the HexView class
//

#include "stdafx.h"
#include "winhex.h"
#include "hexdoc.h"
#include "hexview.h"
#include "global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LINESIZE 16
#define MAXCOL LINESIZE - 1
#define BUFFSIZE 81
#define DATAOFFSET 13
#define DATALEN 47
#define CHAROFFSET 5
#define INVALID_CELL (UINT)-1
#define COLOR_SILVER PALETTERGB(0xc0, 0xc0, 0xc0)

/////////////////////////////////////////////////////////////////////////////
// HexView

IMPLEMENT_DYNCREATE(HexView, CView)

BEGIN_MESSAGE_MAP(HexView, CView)
    //{{AFX_MSG_MAP(HexView)
    ON_WM_CREATE()
    ON_COMMAND(IDM_VIEWGRID, OnViewGrid)
    ON_UPDATE_COMMAND_UI(IDM_VIEWGRID, OnUpdateViewGrid)
    ON_WM_VSCROLL()
    ON_WM_SIZE()
    ON_COMMAND(IDM_FONT, OnFont)
    ON_WM_HSCROLL()
    ON_WM_LBUTTONDOWN()
    ON_WM_ERASEBKGND()
    ON_COMMAND(IDM_BGCOLOR, OnBackgroundColor)
    ON_WM_KEYDOWN()
    ON_WM_SETFOCUS()
    ON_WM_DESTROY()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HexView construction/destruction

HexView::HexView()
{
    m_cyChar = 0;
    m_cxChar = 0;
    m_nLinesTotal = 0;
    m_nXPageSize = 0;
    m_nYPageSize = 0;
    m_nDocHeight = 0;
    m_nDocWidth = 0;
    m_grid = TRUE;
    m_color = GetProfileInt("colors", "TextColor");
    m_bgBrush.CreateSolidBrush(GetProfileInt("colors", "BackgroundColor"));
    m_gridpen.CreatePen(PS_SOLID, 1, COLOR_SILVER);
    m_ActiveCell = INVALID_CELL;
    m_ScrollPos = CPoint(0, 0);
}

HexView::~HexView()
{
}

BOOL HexView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= WS_VSCROLL | WS_HSCROLL;

    return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// HexView drawing

void HexView::OnDraw(CDC* pDC)
{
    HexDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    LPCBYTE pdata = pDoc->GetData();
    if (pdata != NULL) {
        CFont * pOldFont = pDC->SelectObject(&m_font);
        Render(pDC, pdata, pDoc->GetDataSize());
        pDC->SelectObject(pOldFont);
    }
}

void HexView::Render(CDC *pDC, LPCBYTE pdata, UINT size)
{
    ASSERT_VALID(pDC);
    ASSERT(pdata != NULL);

    CRect rc;
    pDC->GetClipBox(rc);

    int nstart = rc.top / m_cyChar;
    int nend = min(m_nLinesTotal - 1,
                   (rc.bottom + m_cyChar - 1) / m_cyChar);

    static char buffer[BUFFSIZE + 1];
    for (int n = nstart; n <= nend; n++) {
        int nlength = min(LINESIZE, size - (n * LINESIZE));
        int j = FormatLine(n, buffer, pdata + (n * LINESIZE), nlength);
        pDC->TextOut(0, n * m_cyChar, buffer, j);

        if (m_grid)
            DrawGridLine(pDC, (n + 1) * m_cyChar - 1, rc.right);
    }
}

void HexView::DrawGridLine(CDC *pDC, int vpos, int xextent)
{
    ASSERT_VALID(pDC);

    CPen * pOldPen = pDC->SelectObject(&m_gridpen);

    pDC->MoveTo(0, vpos);
    pDC->LineTo(xextent, vpos);

    pDC->SelectObject(pOldPen);
}
/////////////////////////////////////////////////////////////////////////////
// HexView diagnostics

#ifdef _DEBUG
void HexView::AssertValid() const
{
    CView::AssertValid();
}

void HexView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

HexDoc* HexView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(HexDoc)));
    return (HexDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// HexView message handlers

void HexView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    if (pHint != NULL && m_ActiveCell != INVALID_CELL)
        InvalidateCell();
    else Invalidate();
}

void HexView::OnInitialUpdate()
{
    UINT nsize = GetDocument()->GetDataSize();
    m_nLinesTotal = (nsize + LINESIZE - 1) / LINESIZE;

    if (nsize == 0) {
        m_ActiveCell = INVALID_CELL;
        m_edit.SetWindowPos(NULL, 0, 0, 0, 0, SW_HIDE);
        SetFocus();
        SetSizes();
    } else {
        SetSizes();
        SetCellPos(0, 0);
    }

    CView::OnInitialUpdate();
}

int HexView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    CClientDC dc(this);

    // Create the font
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));
    strcpy(lf.lfFaceName, GetProfileString("font", "FaceName"));
    lf.lfItalic = GetProfileInt("font", "Italic");
    lf.lfWeight = GetProfileInt("font", "Bold") == 1 ? FW_BOLD : FW_NORMAL;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfHeight = -MulDiv(GetProfileInt("font", "PointSize"),
                          dc.GetDeviceCaps(LOGPIXELSY), 72);

    if (!m_font.CreateFontIndirect(&lf))
        return -1;

    // Create the edit control
    if (!m_edit.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0),
                       this, ID_EDITCTRL))
        return -1;

    m_edit.SetFont(&m_font);

    LOGBRUSH lb;
    m_bgBrush.GetLogBrush(&lb);

    m_edit.SetBkColor(lb.lbColor);
    m_edit.SetTextColor(m_color);

    SetSizes();

    return 0;
}

int HexView::FormatLine(UINT line, LPSTR buffer, LPCBYTE pdata, UINT size) const
{
    LPSTR pbuffer = buffer;
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

    return (pbuffer + size) - buffer;
}

void HexView::OnViewGrid()
{
    m_grid = !m_grid;
    Invalidate();
}

void HexView::OnUpdateViewGrid(CCmdUI* pCmdUI)
{
    ASSERT(pCmdUI);
    pCmdUI->SetCheck(m_grid);
}

void HexView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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

void HexView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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

void HexView::OnSize(UINT nType, int cx, int cy)
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

    if (m_ActiveCell != INVALID_CELL) {
        RepositionCell();
    }
}

void HexView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    pDC->SetViewportOrg(-m_ScrollPos.x, -m_ScrollPos.y);
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(m_color);

    CView::OnPrepareDC(pDC, pInfo);
}

void HexView::OnFont()
{
    ASSERT(m_font.m_hObject != NULL);

    LOGFONT lf;
    m_font.GetLogFont(&lf);

    CHOOSEFONT cf;
    memset(&cf, 0, sizeof(CHOOSEFONT));

    cf.lStructSize = sizeof(CHOOSEFONT);
    cf.Flags = CF_INITTOLOGFONTSTRUCT |
               CF_SCREENFONTS | CF_EFFECTS | CF_FIXEDPITCHONLY;
    cf.lpLogFont = &lf;
    cf.hwndOwner = *this;
    cf.rgbColors = m_color;

    if (!ChooseFont(&cf))
        return;

    m_color = cf.rgbColors;

    m_font.DeleteObject();
    m_font.CreateFontIndirect(&lf);

    m_edit.SetFont(&m_font);
    m_edit.SetTextColor(m_color);

    SetSizes();

    if (m_ActiveCell != INVALID_CELL)
        RepositionCell();

    Invalidate();
}

void HexView::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (GetDocument()->GetDataSize() == 0) {
        Default();
        return;
    }

    int row, col;
    if (!GetCellByPoint(point, row, col)) {
        Default();
        return;
    }

    SetCellPos(row, col);
}

BOOL HexView::GetCellByPoint(CPoint pt, int & row, int & col) const
{
    UINT nsize = GetDocument()->GetDataSize();

    row = -1;
    col = -1;

    pt.x += m_ScrollPos.x;
    pt.y += m_ScrollPos.y;

    CRect rcClient, rc;
    GetClientRect(rcClient);

    rc.left = m_cxChar * DATAOFFSET;
    rc.top = m_ScrollPos.y;
    rc.right = rc.left + m_cxChar * DATALEN;
    rc.bottom = rc.top + rcClient.Height();

    if (!PtInRect(rc, pt))
        return FALSE;

    row = pt.y / m_cyChar;

    int i, j;
    for (i = rc.left, j = 0; i < rc.right; i += 3 * m_cxChar, j++)
        if (pt.x >= i && pt.x <= i + 3 * m_cxChar) {
            col = j;
            break;
        }

    UINT offset = row * LINESIZE + col;
    if (offset >= nsize)
        return FALSE;

    return TRUE;
}

void HexView::UpdateCell()
{
    ASSERT(m_ActiveCell != INVALID_CELL);

    CString str;
    m_edit.GetWindowText(str);

    WORD data;
    if (sscanf(str, "%hx", &data) == -1)
        InvalidateCell(FALSE);
    else GetDocument()->SetData(m_ActiveCell, (BYTE)data);
    m_edit.SetModify(FALSE);
}

void HexView::SetSizes()
{
    CClientDC dc(this);

    CFont *pOldFont = dc.SelectObject(&m_font);

    TEXTMETRIC tm;
    dc.GetTextMetrics(&tm);

    ::GetCharWidth32(dc, '0', '0', &m_cxChar);
    m_cyChar = tm.tmHeight + tm.tmExternalLeading;

    m_nDocHeight = m_nLinesTotal * m_cyChar;
    m_nDocWidth = GetDocument()->GetDataSize() ? BUFFSIZE * m_cxChar : 0;

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

BOOL HexView::OnEraseBkgnd(CDC* pDC)
{
    ASSERT_VALID(pDC);

    CRect rc;
    pDC->GetClipBox(rc);

    CBrush *pOldBrush = pDC->SelectObject(&m_bgBrush);

    pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);

    pDC->SelectObject(pOldBrush);

    return TRUE;
}

void HexView::OnBackgroundColor()
{
    CHOOSECOLOR cc;
    memset(&cc, 0, sizeof(CHOOSECOLOR));

    LOGBRUSH lb;
    m_bgBrush.GetLogBrush(&lb);

    static COLORREF custom[16];

    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.hwndOwner = *this;
    cc.Flags = CC_RGBINIT | CC_SOLIDCOLOR;
    cc.rgbResult = lb.lbColor;
    cc.lpCustColors = custom;

    if (ChooseColor(&cc)) {
        m_edit.SetBkColor(cc.rgbResult);
        m_bgBrush.DeleteObject();
        m_bgBrush.CreateSolidBrush(cc.rgbResult);
        Invalidate();
    }
}

void HexView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar) {
    case VK_TAB:
    case VK_RIGHT:
    case VK_LEFT:
    case VK_DOWN:
    case VK_UP:
        NavigateCell(nChar);
        break;
    case VK_HOME:
        SendMessage(WM_VSCROLL, SB_TOP, 0L);
        break;
    case VK_END:
        SendMessage(WM_VSCROLL, SB_BOTTOM, 0L);
        break;
    case VK_PRIOR:
        SendMessage(WM_VSCROLL, SB_PAGEUP, 0L);
        break;
    case VK_NEXT:
        SendMessage(WM_VSCROLL, SB_PAGEDOWN, 0L);
        break;
    default:
        break;
    }

    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL HexView::PrevCell()
{
    ASSERT(m_ActiveCell != INVALID_CELL);

    if (m_ActiveCell == 0)
        return FALSE;	// first cell

    int row, col;

    GetCellPos(row, col);
    if (col == 0) {
        col = MAXCOL;
        row--;
    } else col--;

    SetCellPos(row, col);

    return TRUE;
}

BOOL HexView::NextCell()
{
    ASSERT(m_ActiveCell != INVALID_CELL);

    UINT nsize = GetDocument()->GetDataSize();
    if (m_ActiveCell == nsize - 1)
        return FALSE;	// last cell

    int row, col;

    GetCellPos(row, col);
    if (col == MAXCOL) {
        col = 0;
        row++;
    } else col++;

    SetCellPos(row, col);

    return TRUE;
}

BOOL HexView::PrevRow()
{
    ASSERT(m_ActiveCell != INVALID_CELL);

    int row, col;
    GetCellPos(row, col);

    if (row == 0)
        return FALSE;	// first row

    SetCellPos(--row, col);

    return TRUE;
}

BOOL HexView::NextRow()
{
    ASSERT(m_ActiveCell != INVALID_CELL);

    UINT nsize = GetDocument()->GetDataSize();

    int row, col;
    GetCellPos(row, col);

    UINT cell = ++row * LINESIZE + col;
    if (cell >= nsize)
        return FALSE;	// invalid cell

    SetCellPos(row, col);

    return TRUE;
}

void HexView::InvalidateCell(BOOL eraseChar)
{
    if (m_ActiveCell == INVALID_CELL)
        return;	// nothing to repaint

    CRect rc;
    GetCellRect(rc);
    rc.bottom++; // correction for gridline

    InvalidateRect(rc);

    if (eraseChar) {	// erase corresponding character
        int col = (rc.left + m_ScrollPos.x - (DATAOFFSET * m_cxChar)) /
                  rc.Width();
        int cx = (DATAOFFSET + DATALEN + CHAROFFSET) * m_cxChar +
                 (m_cxChar * col) - m_ScrollPos.x;

        CRect rcChar;
        rcChar.left = cx;
        rcChar.top = rc.top;
        rcChar.right = rcChar.left + m_cxChar;
        rcChar.bottom = rcChar.top + m_cyChar;

        InvalidateRect(rcChar);
    }
}

void HexView::RepositionCell()
{
    ASSERT(m_ActiveCell != INVALID_CELL);

    int row, col;

    GetCellPos(row, col);
    SetCellPos(row, col);
}

void HexView::GetCellPos(int & row, int & col) const
{
    ASSERT(m_ActiveCell != INVALID_CELL);

    row = m_ActiveCell / LINESIZE;
    col = m_ActiveCell - (row * LINESIZE);
}

void HexView::GetCellRect(CRect & rc) const
{
    m_edit.GetWindowRect(rc);
    ScreenToClient(rc);
}

void HexView::SetCellPos(int row, int col)
{
    ASSERT(row < (m_nDocHeight / m_cyChar));
    ASSERT(col < LINESIZE);

    UINT nsize = GetDocument()->GetDataSize();
    UINT cell = row * LINESIZE + col;

    ASSERT(cell < nsize);

    CRect rc;
    GetCellByPos(row, col, rc);

    if (m_edit.GetModify()) {
        UpdateCell();
    } else InvalidateCell(FALSE);

    m_edit.SetWindowPos(NULL, rc.left, rc.top,
                        rc.Width(), rc.Height(), SWP_SHOWWINDOW);

    LPCBYTE pdata = GetDocument()->GetData();
    ASSERT(pdata != NULL);

    CString text;
    text.Format("%0.2x", pdata[m_ActiveCell = cell]);
    m_edit.SetWindowText(text);

    m_edit.SetFocus();
    m_edit.SetSel(0, -1);
}

void HexView::OnSetFocus(CWnd* pOldWnd)
{
    if (m_ActiveCell != INVALID_CELL) {
        m_edit.SetFocus();
        return;
    }
    CView::OnSetFocus(pOldWnd);
}

void HexView::Update()
{
    if (m_ActiveCell != INVALID_CELL && m_edit.GetModify())
        UpdateCell();
}

void HexView::OnDestroy()
{
    CView::OnDestroy();

    if (m_bgBrush.m_hObject) {
        LOGBRUSH lb;
        m_bgBrush.GetLogBrush(&lb);
        SetProfileInt("colors", "TextColor", m_color);
        SetProfileInt("colors", "BackgroundColor", lb.lbColor);
    }

    if (m_font.m_hObject) {
        CClientDC dc(this);
        LOGFONT lf;

        m_font.GetLogFont(&lf);
        SetProfileString("font", "FaceName", lf.lfFaceName);
        SetProfileInt("font", "PointSize",
                      abs(MulDiv(lf.lfHeight, 72, dc.GetDeviceCaps(LOGPIXELSY))));
        SetProfileInt("font", "Bold", lf.lfWeight >= FW_BOLD ? 1 : 0);
        SetProfileInt("font", "Italic", lf.lfItalic);
    }
}

void HexView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (m_ActiveCell != INVALID_CELL) {
        UpdateCell();
    }
    CView::OnChar(nChar, nRepCnt, nFlags);
}

void HexView::GetCellByPos(int row, int col, CRect & rc) const
{
    ASSERT(row < (m_nDocHeight / m_cyChar));
    ASSERT(col < LINESIZE);

    rc.SetRectEmpty();

    rc.left = (DATAOFFSET * m_cxChar) + (m_cxChar * 3 * col) - m_ScrollPos.x;
    rc.top = m_cyChar * row - m_ScrollPos.y;
    rc.right = rc.left + (m_cxChar * 3);
    rc.bottom = rc.top + m_cyChar - 1;	// gridline
}

BOOL HexView::NavigateCell(UINT nChar)
{
    BOOL retcode = FALSE;

    if (m_ActiveCell == INVALID_CELL)
        return retcode;

    switch (nChar) {
    case VK_TAB:
    case VK_RIGHT:
        retcode = NextCell();
        break;
    case VK_LEFT:
        retcode = PrevCell();
        break;
    case VK_DOWN:
        retcode = NextRow();
        break;
    case VK_UP:
        retcode = PrevRow();
        break;
    }

    if (retcode)
        ScrollToCell();

    return retcode;
}

void HexView::ScrollToCell()
{
    ASSERT(m_ActiveCell != INVALID_CELL);

    CClientDC dc(this);
    OnPrepareDC(&dc);

    CRect rc, rcCell;

    dc.GetClipBox(rc);
    GetCellRect(rcCell);
    rcCell.OffsetRect(m_ScrollPos);

    // the RectVisible function will return true
    // if any portion of the rectangle is visible.
    // We need to determine if the entire rectangle
    // is visible.  UnionRect can be used to determine
    // if scrolling is necessary

    CRect dummy;
    dummy.UnionRect(rc, rcCell);

    if (dummy == rc)
        return;	// no need to scroll

    // for horizontal scrolling we must calculate a scroll position
    // the default line size is only size of character width
    int cx = m_ScrollPos.x;

    if (dummy.bottom > rc.bottom) {
        SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), NULL);
        return;
    } else if (dummy.top < rc.top) {
        SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), NULL);
        return;
    } else if (dummy.left < rc.left) {
        cx -= m_cxChar * 3;
    } else if (dummy.right > rc.right) {
        cx += m_cxChar * 3;
    }

    ScrollWindow(-(cx - m_ScrollPos.x), 0);
    SetScrollPos(SB_HORZ, m_ScrollPos.x=cx);
    UpdateWindow();
}