/////////////////////////////////////////////////////////////////////////////
//
//	PENTEBOARD.CPP : pente board
//
#include "stdafx.h"
#include "Game.h"
#include "PenteBoard.h"
#include "resource.h"

IMPLEMENT_SERIAL(PenteBoard, CObject, VERSIONABLE_SCHEMA | 1)

/////////////////////////////////////////////////////////////////////////////
PenteBoard::PenteBoard() : winnerVec(NULL)
{
    CWinApp *pApp = AfxGetApp();
    ASSERT_VALID(pApp);

    bkgColor = pApp->GetProfileInt(_T("Settings"), _T("BoardColor"),
                                   DEFAULT_BOARD_COLOR);
    gridColor = pApp->GetProfileInt(_T("Settings"), _T("GridColor"),
                                    DEFAULT_GRID_COLOR);
    bkgBrush.CreateSolidBrush(bkgColor);
    pen.CreatePen(PS_SOLID, 0, gridColor);

    COLORREF playerOneColor = pApp->GetProfileInt(_T("Settings"),
                              _T("playerOneColor"), DEFAULT_PLAYER_ONE_COLOR);
    COLORREF playerTwoColor = pApp->GetProfileInt(_T("Settings"),
                              _T("playerTwoColor"), DEFAULT_PLAYER_TWO_COLOR);

    bmPlayerOne.setColor(playerOneColor);
    bmPlayerTwo.setColor(playerTwoColor);
    bmWinner.setColor(DEFAULT_WINNER_COLOR);

    board = Board::instance();

    CreateBitmap();
}

/////////////////////////////////////////////////////////////////////////////
PenteBoard::~PenteBoard()
{
}

/////////////////////////////////////////////////////////////////////////////
void PenteBoard::render(CDC *pDC, const CRect & rc)
{
    ASSERT_VALID(pDC);
    renderTable(pDC, rc);
    renderBoard(pDC, rc);
}

/////////////////////////////////////////////////////////////////////////////
void PenteBoard::renderTable(CDC *pDC, const CRect & rc)
{
    CBitmap *pOldBitmap = m_MemDC.SelectObject(&m_Bitmap);

    CRect aRect(rc);
    aRect.OffsetRect(-cxBorder, -cyBorder);

    pDC->BitBlt(rc.left, rc.top,
                rc.Width(), rc.Height(), &m_MemDC,
                aRect.left, aRect.top, SRCCOPY
               );

    m_MemDC.SelectObject(pOldBitmap);
}

/////////////////////////////////////////////////////////////////////////////
void PenteBoard::renderBoard(CDC *pDC, const CRect & rc)
{
    CPoint pt, ePoint;
    CRect rcPiece;

    UInt32EntryMapEnum e = board->enumEntries();
    while (e.hasNext()) {
        const Entry & entry = e.next().second;
        ePoint = entry.where();
        pt = mapIndexToPoint(ePoint);
        rcPiece.left = pt.x;
        rcPiece.top = pt.y;
        rcPiece.right = rcPiece.left + cxPiece;
        rcPiece.bottom = rcPiece.top + cyPiece;

        if (!pDC->RectVisible(rcPiece))
            continue;

        PieceBitmap &piece = isWinner(ePoint) ?
                             bmWinner : (
                                 entry.getType() == ET_PLAYER_ONE ?
                                 bmPlayerOne : bmPlayerTwo);

        piece.Draw(pDC, pt.x, pt.y);
    }
}

/////////////////////////////////////////////////////////////////////////////
bool PenteBoard::isWinner(const CPoint &aPoint) const
{
    if (winnerVec == NULL)
        return false;

    POINT pt;
    for (uint32_t i = 0; i < VSIZE; i++) {
        pt = winnerVec->entry(i);

        if (aPoint == pt)
            return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////
CPoint PenteBoard::mapIndexToPoint(const CPoint & pt)
{
    CPoint aPoint;
    aPoint.x = min(max(0, pt.x), cxSquares);
    aPoint.y = min(max(0, pt.y), cySquares);

    CPoint ptDest;
    ptDest.x = (cxBorder - (cxPiece / 2)) + (aPoint.x * squareSize);
    ptDest.y = (cyBorder - (cyPiece / 2)) + (aPoint.y * squareSize);

    return ptDest;
}

/////////////////////////////////////////////////////////////////////////////
bool PenteBoard::ptOnBoard(const CPoint & pt) const
{
    CRect rc;
    getDimensions(rc);
    rc.InflateRect(cxPiece / 2, cyPiece / 2);
    rc.OffsetRect(cxBorder, cyBorder);
    if (rc.PtInRect(pt))
        return true;
    return false;
}

/////////////////////////////////////////////////////////////////////////////
CPoint PenteBoard::getSquare(const CPoint & pt) const
{
    CPoint square;

    CPoint aPoint(pt);
    aPoint.x -= (cxBorder - (cxPiece / 2));
    aPoint.y -= (cyBorder - (cyPiece / 2));

    square.x = min(max(0, (aPoint.x / squareSize)), cxSquares);
    square.y = min(max(0, (aPoint.y / squareSize)), cySquares);

    return square;
}

/////////////////////////////////////////////////////////////////////////////
void PenteBoard::getSquareRect(int x, int y, CRect & rc) const
{
    x = min(max(0, x), cxSquares);
    y = min(max(0, y), cySquares);

    rc.SetRectEmpty();
    rc.left = (cxBorder - (cxPiece / 2)) + (x * squareSize);
    rc.top = (cyBorder - (cyPiece / 2)) + (y * squareSize);
    rc.right = rc.left + squareSize;
    rc.bottom = rc.top + squareSize;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t PenteBoard::getPiece(int x, int y) const
{
    return board->getEntry(x, y);
}

/////////////////////////////////////////////////////////////////////////////
bool PenteBoard::addPiece(int x, int y, uint32_t currentTurn)
{
    if (getPiece(x, y) != ET_EMPTY)
        return false;

    board->setEntry(x, y, currentTurn);

    return true;
}

/////////////////////////////////////////////////////////////////////////////
void PenteBoard::clear()
{
    board->clear();
    winnerVec = NULL;
}

/////////////////////////////////////////////////////////////////////////////
const Vector *PenteBoard::winner(uint32_t &nplayer)
{
    const Vector *vector;
    if ((vector = board->winner(nplayer)) != NULL) {
        winnerVec = vector;
    }

    return vector;
}

/////////////////////////////////////////////////////////////////////////////
void PenteBoard::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        ar << board->size();
        UInt32EntryMapEnum e = board->enumEntries();
        while (e.hasNext()) {
            const Entry & entry = e.next().second;
            ar << entry.where();
            ar << entry.getType();
        }
    } else {
        board->clear();

        POINT pt;
        uint32_t size, type;

        ar >> size;
        for (uint32_t i = 0; i < size; i++) {
            ar >> pt;
            ar >> type;
            board->setEntry(pt.x, pt.y, type);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
void PenteBoard::CreateBitmap()
{
    CRect rcRegion;
    getDimensions(rcRegion);
    if (!m_Region.CreateRectRgnIndirect(&rcRegion))
        AfxThrowResourceException();

    CDC dc;
    dc.Attach(::GetDC(NULL));
    if (!m_MemDC.CreateCompatibleDC(&dc))
        AfxThrowResourceException();

    m_MemDC.SetMapMode(dc.GetMapMode());

    if (!m_Bitmap.CreateCompatibleBitmap(&dc, rcRegion.Width(),
                                         rcRegion.Height()))
        AfxThrowResourceException();

    PaintBitmap();
}

/////////////////////////////////////////////////////////////////////////////
void PenteBoard::PaintBitmap()
{
    CRect rcBoard;
    m_Region.GetRgnBox(rcBoard);

    CBitmap *pOldBitmap = m_MemDC.SelectObject(&m_Bitmap);

    CBrush *pOldBrush = (CBrush *)m_MemDC.SelectObject(&bkgBrush);
    CPen *pOldPen = (CPen *)m_MemDC.SelectObject(&pen);

    m_MemDC.Rectangle(rcBoard);

    int cx = rcBoard.Width() / cxSquares;
    int cy = rcBoard.Height() / cySquares;

    CPoint ptStart(rcBoard.left + cx, rcBoard.top);
    m_MemDC.MoveTo(ptStart);

    // Draw vertical lines
    while (ptStart.x < rcBoard.right) {
        CPoint ptEnd = CPoint(ptStart.x, rcBoard.bottom - 1);
        m_MemDC.LineTo(ptEnd);
        m_MemDC.MoveTo(ptStart.x += cx, ptStart.y);
    }

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

/////////////////////////////////////////////////////////////////////////////
void PenteBoard::getCaptures(const CPoint &pt, CaptureVec &captures)
{
    board->getCaptures(pt.x, pt.y, captures);
}

/////////////////////////////////////////////////////////////////////////////
bool PenteBoard::isEmpty() const
{
    return board->size() == 0;
}
