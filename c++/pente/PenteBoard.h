/////////////////////////////////////////////////////////////////////////////
//
//	PENTEBOARD.H	: pente board
//

#ifndef __PENTEBOARD_H__
#define __PENTEBOARD_H__

#include "libpente.h"
#include "PieceIcon.h"

/////////////////////////////////////////////////////////////////////////////
class PenteBoard : public CObject
{
// Construction / Destruction
public:
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

	void setPlayerOneColor(COLORREF rgb);
	COLORREF getPlayerOneColor() const;

	void setPlayerTwoColor(COLORREF rgb);
	COLORREF getPlayerTwoColor() const;

	bool addPiece(int x, int y, uint32_t currentTurn);

	static CPoint getBorderSizes();
	static int getSquareSize();
	static CPoint getBoardSize();
	static void getDimensions(CRect & rc);
	static void getBoundingRect(CRect & rc);
	
	enum { DEFAULT_PLAYER_ONE_COLOR = 0x8000 };
	enum { DEFAULT_PLAYER_TWO_COLOR = 0x800000 };

// Implementation
private:
	void renderTable(CDC *pDC, const CRect & rc);
	void renderBoard(CDC *pDC);
	static CPoint mapIndexToPoint(const CPoint &);

	enum { cxIcon = 16 };
	enum { cyIcon = 16 };
	enum { cxBorder = BOARD_SIZE+1 };
	enum { cyBorder = BOARD_SIZE+1 };
	enum { cxSquares = BOARD_SIZE };
	enum { cySquares = BOARD_SIZE };
	enum { squareSize = BOARD_SIZE+2 };
	enum { cxOffset = 3 };
	enum { cyOffset = 3 };
	
	PieceIcon playerOneIcon, playerTwoIcon;

	CBrush bkgBrush;
	CPen pen;
	COLORREF bkgColor, gridColor;
	Board *board;
	CPalette palette;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
inline CPoint PenteBoard::getBorderSizes() {
	return CPoint(cxBorder, cyBorder);
}

/////////////////////////////////////////////////////////////////////////////
inline int PenteBoard::getSquareSize() {
	return squareSize;
}

/////////////////////////////////////////////////////////////////////////////
inline CPoint PenteBoard::getBoardSize() {
	return CPoint(cxSquares, cySquares);
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::getDimensions(CRect & rc) {
	rc.SetRectEmpty();
	rc.right = squareSize * cxSquares;
	rc.bottom = squareSize * cySquares;
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::getBoundingRect(CRect & rc) {
	getDimensions(rc);
	rc.right += cxBorder * 2;
	rc.bottom += cyBorder * 2;
}

/////////////////////////////////////////////////////////////////////////////
inline COLORREF PenteBoard::getBackgroundColor() const {
	return bkgColor;
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::setBackgroundColor(COLORREF rgb) {
	bkgColor = rgb;
	bkgBrush.DeleteObject();
	bkgBrush.CreateSolidBrush(bkgColor);
}

/////////////////////////////////////////////////////////////////////////////
inline COLORREF PenteBoard::getGridColor() const {
	return gridColor;
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::setGridColor(COLORREF rgb) {
	gridColor = rgb;
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 0, gridColor);
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::setPlayerOneColor(COLORREF rgb) {
	playerOneIcon.setColor(rgb);
}

/////////////////////////////////////////////////////////////////////////////
inline void PenteBoard::setPlayerTwoColor(COLORREF rgb) {
	playerTwoIcon.setColor(rgb);
}

/////////////////////////////////////////////////////////////////////////////
inline COLORREF PenteBoard::getPlayerOneColor() const {
	return playerOneIcon.getColor();
}

/////////////////////////////////////////////////////////////////////////////
inline COLORREF PenteBoard::getPlayerTwoColor() const {
	return playerTwoIcon.getColor();
}

#endif // __PENTEBOARD_H__