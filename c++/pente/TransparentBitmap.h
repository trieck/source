#pragma once

// TransparentBitmap command target

class TransparentBitmap : public CBitmap
{
public:
	TransparentBitmap(COLORREF transparent);
	virtual ~TransparentBitmap();

	void Draw(CDC *pDC, int x, int y);
private:
	COLORREF m_Transparent;	// transparent mask
};


