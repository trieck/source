// ColorChooserWnd.cpp : implementation file
//

#include "stdafx.h"
#include "torrentexplorer.h"
#include "ColorChooserWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CX_CELL				(11)
#define CY_CELL				(11)
#define CELLS_PER_ROW		(12)
#define LAST_CELLS_PER_ROW	(8)
#define SYSPALSIZE			(20)
#define PALSIZE				(256)
#define LASTPALIDX			(246)
#define NROWS				\
	((PALSIZE - SYSPALSIZE - LAST_CELLS_PER_ROW)/CELLS_PER_ROW)

static POINT pts[] = {
    { 0, 0 },
    { CX_CELL * (SYSPALSIZE / 2), 0 },
    { CX_CELL * (SYSPALSIZE / 2), CY_CELL * 2 },
    { CX_CELL * CELLS_PER_ROW, CY_CELL * 2 },
    { CX_CELL * CELLS_PER_ROW, CY_CELL * (NROWS + 2) },
    { CX_CELL * LAST_CELLS_PER_ROW, CY_CELL * (NROWS + 2) },
    { CX_CELL * LAST_CELLS_PER_ROW, CY_CELL * (NROWS + 3) },
    { 0, CY_CELL * (NROWS + 3) },
};

/////////////////////////////////////////////////////////////////////////////
// ColorChooserWnd

ColorChooserWnd::ColorChooserWnd()
    : m_ptSelected(-1, -1)
{
}

ColorChooserWnd::~ColorChooserWnd()
{
}

BEGIN_MESSAGE_MAP(ColorChooserWnd, CWnd)
    //{{AFX_MSG_MAP(ColorChooserWnd)
    ON_WM_PAINT()
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
    ON_WM_SYSCOLORCHANGE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColorChooserWnd message handlers

BOOL ColorChooserWnd::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.cx = CX_CELL * CELLS_PER_ROW;
    cs.cy = CY_CELL * (NROWS + 3);
    cs.style |= WS_VISIBLE | WS_CHILD;
    return CWnd::PreCreateWindow(cs);
}

void ColorChooserWnd::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    CRect rc;
    dc.GetClipBox(rc);

    CBitmap *pOldBitmap = m_MemDC.SelectObject(&m_Bitmap);

    dc.BitBlt(rc.left, rc.top,
              rc.Width(), rc.Height(), &m_MemDC,
              rc.left, rc.top, SRCCOPY
             );

    m_MemDC.SelectObject(pOldBitmap);
}

int ColorChooserWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_Region.CreatePolygonRgn(pts, _countof(pts), ALTERNATE))
        return -1;

    CClientDC dc(this);
    if (!m_MemDC.CreateCompatibleDC(&dc))
        return -1;

    m_MemDC.SetMapMode(dc.GetMapMode());

    CRect rcRegion;
    if (!m_Region.GetRgnBox(rcRegion))
        return -1;

    if (!m_Bitmap.CreateCompatibleBitmap(&dc, rcRegion.Width(),
                                         rcRegion.Height()))
        return -1;

    m_Shadow = GetSysColor(COLOR_3DSHADOW);
    m_Hilight = GetSysColor(COLOR_3DHILIGHT);
    m_BtnFace = GetSysColor(COLOR_BTNFACE);

    PaintBitmap();

    return 0;
}

void ColorChooserWnd::PaintBitmap()
{
    TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
    RGBTRIPLE *pPalette = pApp->GetPalette();

    CRect rc;
    m_Region.GetRgnBox(rc);

    CBitmap *pOldBitmap = m_MemDC.SelectObject(&m_Bitmap);

    int i, j, cx = rc.left, cy = rc.top;
    for (i = 0; i < SYSPALSIZE / 2; i++, cx += CX_CELL) {
        m_MemDC.Draw3dRect(cx, cy, CX_CELL, CY_CELL, m_Shadow, m_Hilight);
        m_MemDC.FillSolidRect(
            cx + 1,
            cy + 1,
            CX_CELL - 2,
            CY_CELL - 2,
            RGB(pPalette[i].rgbtRed,
                pPalette[i].rgbtGreen,
                pPalette[i].rgbtBlue
               )
        );
    }

    cx = rc.left;
    cy += CY_CELL;
    for (i = 0; i < SYSPALSIZE / 2; i++, cx += CX_CELL) {
        m_MemDC.Draw3dRect(cx, cy, CX_CELL, CY_CELL, m_Shadow, m_Hilight);
        m_MemDC.FillSolidRect(
            cx + 1,
            cy + 1,
            CX_CELL - 2,
            CY_CELL - 2,
            RGB(pPalette[i+LASTPALIDX].rgbtRed,
                pPalette[i+LASTPALIDX].rgbtGreen,
                pPalette[i+LASTPALIDX].rgbtBlue
               )
        );
    }

    m_MemDC.FillSolidRect(CX_CELL * 10, 0, CX_CELL * 2, CY_CELL * 2,
                          m_BtnFace);

    pPalette = &pPalette[SYSPALSIZE/2];
    for (i = 0; i < NROWS; i++) {
        cx = rc.left;
        cy += CY_CELL;
        for (j = 0; j < CELLS_PER_ROW; j++, cx += CX_CELL, pPalette++) {
            m_MemDC.Draw3dRect(cx, cy, CX_CELL, CY_CELL, m_Shadow, m_Hilight);
            m_MemDC.FillSolidRect(
                cx + 1,
                cy + 1,
                CX_CELL - 2,
                CY_CELL - 2,
                RGB(pPalette->rgbtRed,
                    pPalette->rgbtGreen,
                    pPalette->rgbtBlue
                   )
            );
        }
    }

    cx = rc.left;
    cy += CY_CELL;
    for (i = 0; i < LAST_CELLS_PER_ROW; i++, cx += CX_CELL, pPalette++) {
        m_MemDC.Draw3dRect(cx, cy, CX_CELL, CY_CELL, m_Shadow, m_Hilight);
        m_MemDC.FillSolidRect(
            cx + 1,
            cy + 1,
            CX_CELL - 2,
            CY_CELL - 2,
            RGB(pPalette->rgbtRed,
                pPalette->rgbtGreen,
                pPalette->rgbtBlue
               )
        );
    }

    m_MemDC.FillSolidRect(CX_CELL * LAST_CELLS_PER_ROW,
                          cy, CX_CELL * (CELLS_PER_ROW - LAST_CELLS_PER_ROW), CY_CELL,
                          m_BtnFace);

    m_MemDC.SelectObject(pOldBitmap);
}

void ColorChooserWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (m_Region.PtInRegion(point)) {
        m_ptSelected.y = point.y / CY_CELL;
        m_ptSelected.x = point.x / CX_CELL;

        GetParent()->SendMessage(WM_COMMAND, IDOK);
    } else {
        GetParent()->SendMessage(WM_COMMAND, IDCANCEL);
    }
    CWnd::OnLButtonDown(nFlags, point);
}

void ColorChooserWnd::OnSysColorChange()
{
    CWnd::OnSysColorChange();

    m_Shadow = GetSysColor(COLOR_3DSHADOW);
    m_Hilight = GetSysColor(COLOR_3DHILIGHT);
    m_BtnFace = GetSysColor(COLOR_BTNFACE);

    PaintBitmap();
    Invalidate();
}

COLORREF ColorChooserWnd::GetSelectedColor() const
{
    if (m_ptSelected.x == -1 || m_ptSelected.y == -1)
        return -1;

    TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
    RGBTRIPLE *pPalette = pApp->GetPalette();

    int offset;
    if (m_ptSelected.y == 0) {			// first system palette
        offset = m_ptSelected.x;
    } else if (m_ptSelected.y == 1) {	// second system palette
        offset = m_ptSelected.x + LASTPALIDX;
    } else if (m_ptSelected.y == NROWS + 2) {	// last row
        offset = LASTPALIDX - LAST_CELLS_PER_ROW + m_ptSelected.x;
    } else {
        offset = (SYSPALSIZE / 2) + (m_ptSelected.y - 2) * CELLS_PER_ROW
                 + m_ptSelected.x;
    }

    return RGB(pPalette[offset].rgbtRed,
               pPalette[offset].rgbtGreen,
               pPalette[offset].rgbtBlue);
}
