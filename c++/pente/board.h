/////////////////////////////////////////////////////////////////////////////
//
//	BOARD.H	: pente board
//

#ifndef __BOARD_H__
#define __BOARD_H__

/////////////////////////////////////////////////////////////////////////////
class Board : public CObject
{
// Construction / Destruction
public:
	Board();
	~Board();

// Interface
	void render(CDC *pDC, const CRect & rc);
	bool ptOnBoard(const CPoint & pt) const;
	CPoint getSquare(const CPoint & pt) const;
	void getSquareRect(int x, int y, CRect & rc) const;
	COLORREF getBackgroundColor() const;
	void setBackgroundColor(COLORREF rgb);
	COLORREF getGridColor() const;
	void setGridColor(COLORREF rgb);

	static CPoint getBorderSizes();
	static int getSquareSize();
	static CPoint getBoardSize();
	static void getDimensions(CRect & rc);
	static void getBoundingRect(CRect & rc);
	static CPoint mapIndexToPoint(const CPoint &);
	static bool isValidPiece(int x, int y);

// Implementation
protected:
private:
	enum { cxBorder = 20 };
	enum { cyBorder = 20 };
	enum { cxSquares = 19 };
	enum { cySquares = 19 };
	enum { squareSize = 21 };
	enum { cxOffset = 3 };
	enum { cyOffset = 3 };

	CBrush bkgBrush;
	CPen pen;
	COLORREF bkgColor, gridColor;
};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
inline CPoint Board::getBorderSizes() {
	return CPoint(cxBorder, cyBorder);
}

/////////////////////////////////////////////////////////////////////////////
inline int Board::getSquareSize() {
	return squareSize;
}

/////////////////////////////////////////////////////////////////////////////
inline CPoint Board::getBoardSize() {
	return CPoint(cxSquares, cySquares);
}

/////////////////////////////////////////////////////////////////////////////
inline void Board::getDimensions(CRect & rc) {
	rc.SetRectEmpty();
	rc.right = squareSize * cxSquares;
	rc.bottom = squareSize * cySquares;
}

/////////////////////////////////////////////////////////////////////////////
inline void Board::getBoundingRect(CRect & rc) {
	getDimensions(rc);
	rc.right += cxBorder * 2;
	rc.bottom += cyBorder * 2;
}

/////////////////////////////////////////////////////////////////////////////
inline COLORREF Board::getBackgroundColor() const {
	return bkgColor;
}

/////////////////////////////////////////////////////////////////////////////
inline void Board::setBackgroundColor(COLORREF rgb) {
	bkgColor = rgb;
	bkgBrush.DeleteObject();
	bkgBrush.CreateSolidBrush(bkgColor);
}

/////////////////////////////////////////////////////////////////////////////
inline COLORREF Board::getGridColor() const {
	return gridColor;
}

/////////////////////////////////////////////////////////////////////////////
inline void Board::setGridColor(COLORREF rgb) {
	gridColor = rgb;
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 0, gridColor);
}

/////////////////////////////////////////////////////////////////////////////
inline bool Board::isValidPiece(int x, int y)
{
	if (x < 0 || y < 0)
		return false;

	CPoint extent = getBoardSize();
	if (x >= extent.x || y >= extent.y)
		return false;

	return true;
}


#endif // __BOARD_H__