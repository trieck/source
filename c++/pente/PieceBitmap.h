#pragma once

#include "TransparentBitmap.h"

class PieceBitmap : public TransparentBitmap
{
public:
	PieceBitmap();
	virtual ~PieceBitmap();

	void setColor(COLORREF nColor);
	COLORREF getColor() const;

private:
	enum { DEFAULT_COLOR = RGB(0x00, 0x80, 0x00) };

	COLORREF m_Color;
};


