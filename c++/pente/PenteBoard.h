/////////////////////////////////////////////////////////////////////////////
//
//	PENTEBOARD.H	: pente board
//

#ifndef __PENTEBOARD_H__
#define __PENTEBOARD_H__

#include "libpente.h"
#include "PieceBitmap.h"

/////////////////////////////////////////////////////////////////////////////
class PenteBoard : public CObject {
// Construction / Destruction
public:
	DECLARE_SERIAL(PenteBoard);
	PenteBoard();
	~PenteBoard();

// Interface
	void clear();
	void render(CDC *pDC, const CRect & rc);
	bool ptOnBoard(const CPoint & pt) const;
	CPoint getSquare(const CPoint & pt) const;
	void getSquareRect(int x, int y, CRect & rc) const;
	COLORREF getBackgroundColor() const;
	void setBackgroundColor(COLORREF rgb);
	COLORREF getGridColor() const;
	void setGridColor(COLORREF rgb);
	uint32_t getPiece(int x, int y) const;
	void Serialize(CArchive& ar);

	void setPlayerOneColor(COLORREF rgb);
	COLORREF getPlayerOneColor() const;

	void setPlayerTwoColor(COLORREF rgb);
	COLORREF getPlayerTwoColor() const;

	bool addPiece(int x, int y, uint32_t currentTurn);

	const Vector *winner(uint32_t &nplayer) const;
	void getCaptures(const CPoint &pt, CaptureVec &captures);

	bool isEmpty() const;

	static CPoint getBorderSizes();
	static int getSquareSize();
	static CPoint getBoardSize();
	static void getDimensions(CRect & rc);
	static void getBoundingRect(CRect & rc);

	enum { DEFAULT_TABLE_COLOR		= 0x00003250 };
	enum { DEFAULT_BOARD_COLOR		= 0x00D4F0FF };
	enum { DEFAULT_GRID_COLOR		= 0xC0C0C0 };
	enum { DEFAULT_PLAYER_ONE_COLOR = 0x00008000 };
	enum { DEFAULT_PLAYER_TWO_COLOR = 0x00000080 };

// Implementation
private:
	void renderTable(CDC *pDC, const CRect & rc);
	void renderBoard(CDC *pDC, const CRect & rc);
	void CreateBitmap();
	void PaintBitmap();

	static CPoint mapIndexToPoint(const CPoint &);

	enum { cxPiece = 18 };
	enum { cyPiece = 18 };
	enum { cxBorder = 20 };
	enum { cyBorder = 20 };
	enum { cxSquares = BOARD_SIZE-1 };
	enum { cySquares = BOARD_SIZE-1 };
	enum { squareSize = 21 };
	enum { cxOffset = 2 };
	enum { cyOffset = 2 };

	PieceBitmap bmPlayerOne, bmPlayerTwo;

	CBrush bkgBrush;
	CPen pen;
	COLORREF bkgColor, gridColor;
	Board *board;

	CRgn m_Region;
	CDC m_MemDC;
	CBitmap m_Bitmap;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
inline CPoint PenteBoard::getBorderSizes()
{
	return CPoint(cxBorder, cyBorder);
}

/////////////////////////////////////////////////////////////////////////////
inline int PenteBoard::getSquareSize()
{
	return squareSize;
}

/////////////////////////////////////////////////////////////////////////////
inline CPoint PenteBoard::getBoardSize()
{
	return CPoint(cxSquares, cySquares);
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::getDimensions(CRect & rc)
{
	rc.SetRectEmpty();
	rc.right = squareSize * cxSquares;
	rc.bottom = squareSize * cySquares;
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::getBoundingRect(CRect & rc)
{
	getDimensions(rc);
	rc.right += cxBorder * 2;
	rc.bottom += cyBorder * 2;
}

/////////////////////////////////////////////////////////////////////////////
inline COLORREF PenteBoard::getBackgroundColor() const
{
	return bkgColor;
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::setBackgroundColor(COLORREF rgb)
{
	bkgColor = rgb;
	bkgBrush.DeleteObject();
	bkgBrush.CreateSolidBrush(bkgColor);
	PaintBitmap();
}

/////////////////////////////////////////////////////////////////////////////
inline COLORREF PenteBoard::getGridColor() const
{
	return gridColor;
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::setGridColor(COLORREF rgb)
{
	gridColor = rgb;
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 0, gridColor);
	PaintBitmap();
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::setPlayerOneColor(COLORREF rgb)
{
	bmPlayerOne.setColor(rgb);
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::setPlayerTwoColor(COLORREF rgb)
{
	bmPlayerTwo.setColor(rgb);
}

/////////////////////////////////////////////////////////////////////////////
inline COLORREF PenteBoard::getPlayerOneColor() const
{
	return bmPlayerOne.getColor();
}

/////////////////////////////////////////////////////////////////////////////
inline COLORREF PenteBoard::getPlayerTwoColor() const
{
	return bmPlayerTwo.getColor();
}

#endif // __PENTEBOARD_H__