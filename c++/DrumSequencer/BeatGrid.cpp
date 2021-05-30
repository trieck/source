#include "StdAfx.h"
#include "BeatGrid.h"

constexpr auto COLOR_GRID  = RGB(0xc0, 0xc0, 0xc0);
constexpr auto COLOR_BKGND = RGB(0xEE, 0xEE, 0xFF);

const COLORREF INST_COLORS[Sequence::NINSTRUMENTS] = {
    RGB(192, 0, 0),
    RGB(255, 0, 0),
    RGB(255, 192, 0),
    RGB(255, 255, 0),
    RGB(146, 208, 80),
    RGB(0, 176, 80),
    RGB(0, 176, 240),
    RGB(0, 112, 192),
    RGB(0, 32, 96),
    RGB(112, 48, 160)
};

BeatGrid::BeatGrid(void)
{
    m_bkgBrush.CreateSolidBrush(COLOR_BKGND);
    m_thinPen.CreatePen(PS_SOLID, 0, COLOR_GRID);
    m_thickPen.CreatePen(PS_SOLID, 2, COLOR_GRID);

    CreateBitmap();
}

BeatGrid::~BeatGrid(void)
{
}

void BeatGrid::Draw(CDC* pDC)
{
    CRect rc;
    pDC->GetClipBox(rc);

    CBitmap* pOldBitmap = m_MemDC.SelectObject(&m_Bitmap);

    CRect aRect(rc);
    aRect.OffsetRect(-CX_OFFSET, -CY_OFFSET);

    pDC->BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &m_MemDC,
                aRect.left, aRect.top, SRCCOPY);

    m_MemDC.SelectObject(pOldBitmap);
}

void BeatGrid::CreateBitmap(void)
{
    CRect rcRegion;
    rcRegion.right = rcRegion.left + CX_GRID;
    rcRegion.bottom = rcRegion.top + CY_GRID;

    if (!m_Region.CreateRectRgnIndirect(&rcRegion))
        AfxThrowResourceException();

    CDC dc;
    dc.Attach(GetDC(nullptr));
    if (!m_MemDC.CreateCompatibleDC(&dc))
        AfxThrowResourceException();

    m_MemDC.SetMapMode(dc.GetMapMode());

    if (!m_Bitmap.CreateCompatibleBitmap(&dc, rcRegion.Width(),
                                         rcRegion.Height())) {
        AfxThrowResourceException();
    }

    PaintBitmap();
}

void BeatGrid::PaintBitmap(void)
{
    CRect rcBoard;
    m_Region.GetRgnBox(rcBoard);

    CBitmap* pOldBitmap = m_MemDC.SelectObject(&m_Bitmap);

    CBrush* pOldBrush = static_cast<CBrush*>(m_MemDC.SelectObject(&m_bkgBrush));
    CPen* pOldPen = static_cast<CPen*>(m_MemDC.SelectObject(&m_thinPen));

    m_MemDC.Rectangle(rcBoard);

    int cx = rcBoard.Width() / Sequence::NSUBS;
    int cy = rcBoard.Height() / Sequence::NINSTRUMENTS;

    CPoint ptStart(rcBoard.left + cx, rcBoard.top);
    m_MemDC.MoveTo(ptStart);

    // Draw vertical lines
    for (int i = 1; ptStart.x < rcBoard.right; i++) {
        if (i % Sequence::RESOLUTION == 0) {
            m_MemDC.SelectObject(&m_thickPen);
        } else {
            m_MemDC.SelectObject(&m_thinPen);
        }
        CPoint ptEnd = CPoint(ptStart.x, rcBoard.bottom - 1);
        m_MemDC.LineTo(ptEnd);
        m_MemDC.MoveTo(ptStart.x += cx, ptStart.y);
    }

    m_MemDC.SelectObject(&m_thinPen);

    // Draw horizontal lines
    ptStart = CPoint(rcBoard.left, rcBoard.top + cy);
    m_MemDC.MoveTo(ptStart);
    while (ptStart.y < rcBoard.bottom) {
        CPoint ptEnd = CPoint(rcBoard.right - 1, ptStart.y);
        m_MemDC.LineTo(ptEnd);
        m_MemDC.MoveTo(ptStart.x, ptStart.y += cy);
    }

    m_MemDC.SelectObject(pOldBrush);
    m_MemDC.SelectObject(pOldPen);
    m_MemDC.SelectObject(pOldBitmap);
}

void BeatGrid::GetDimensions(CRect& rc)
{
    rc.SetRectEmpty();
    rc.right = CX_GRID;
    rc.bottom = CY_GRID;
}

void BeatGrid::GetBoundingRect(CRect& rc)
{
    GetDimensions(rc);
    rc.right += 2 * CX_OFFSET;
    rc.bottom += 2 * CY_OFFSET;
}

BOOL BeatGrid::PointOnGrid(const CPoint& pt)
{
    CRect rc;
    GetDimensions(rc);
    rc.OffsetRect(CX_OFFSET, CY_OFFSET);
    return rc.PtInRect(pt);
}

CPoint BeatGrid::GetSubdivision(const CPoint& pt)
{
    CPoint sub;

    CPoint aPoint(pt);
    aPoint.x -= CX_OFFSET;
    aPoint.y -= CY_OFFSET;

    sub.x = min(max(0, (aPoint.x / CX_SUB)), Sequence::NSUBS-1);
    sub.y = min(max(0, (aPoint.y / CY_SUB)), Sequence::NINSTRUMENTS-1);

    return sub;
}

void BeatGrid::GetBeatRect(int x, int y, CRect& rc)
{
    x = x % Sequence::NSUBS;
    y = y % Sequence::NINSTRUMENTS;

    rc.SetRectEmpty();
    rc.left = CX_OFFSET + x * CX_SUB;
    rc.top = CY_OFFSET + y * CY_SUB;
    rc.right = rc.left + CX_SUB;
    rc.bottom = rc.top + CY_SUB;
}

COLORREF BeatGrid::GetInstColor(int i)
{
    return INST_COLORS[i % Sequence::NINSTRUMENTS];
}
