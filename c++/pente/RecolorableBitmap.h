#pragma once

#include "TransparentBitmap.h"

// RecolorableBitmap command target

class RecolorableBitmap : public TransparentBitmap {
public:
	RecolorableBitmap(COLORREF nSourceColor);
	virtual ~RecolorableBitmap();

	void Load(UINT nID);

	void setColor(COLORREF nColor);
	COLORREF getColor() const;

private:
	COLORREF m_Color;
	BYTE *m_Bits;
	DWORD m_dwBmpSize;
};


