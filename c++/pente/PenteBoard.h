/////////////////////////////////////////////////////////////////////////////
//
//	PENTEBOARD.H	: pente board
//

#ifndef __PENTEBOARD_H__
#define __PENTEBOARD_H__

/////////////////////////////////////////////////////////////////////////////
class PenteBoard : public CObject
{
// Construction / Destruction
public:
	PenteBoard();
	~PenteBoard();

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
inline bool PenteBoard::isValidPiece(int x, int y)
{
	if (x < 0 || y < 0)
		return false;

	CPoint extent = getBoardSize();
	if (x >= extent.x || y >= extent.y)
		return false;

	return true;
}


#endif // __PENTEBOARD_H__