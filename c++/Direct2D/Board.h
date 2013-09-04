/////////////////////////////////////////////////////////////////////////////
//
// BOARD.H
//

#ifndef __BOARD_H__
#define __BOARD_H__

/////////////////////////////////////////////////////////////////////////////
class Board {
public:
	Board();
	virtual ~Board();

	static CSize GetDimensions();
	static CRect GetBoundingRect();

	HRESULT Create(ID2D1RenderTarget *pTarget);
	void Destroy();

	void Render(ID2D1RenderTarget *pTarget, const CRect &rc);
private:
	enum { BOARD_SIZE = 8 };
	enum { CX_PIECE = 53 };
	enum { CY_PIECE = 53 };
	enum { CX_BORDER = 20 };
	enum { CY_BORDER = 20 };
	enum { CX_SQUARES = BOARD_SIZE-1 };
	enum { CY_SQUARES = BOARD_SIZE-1 };
	enum { SQUARE_SIZE = 56 };
	enum { CX_OFFSET = 2 };
	enum { CY_OFFSET = 2 };

	CComPtr<ID2D1Bitmap> m_bitmap;
};

#endif // __BOARD_H__