// PieceBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "PieceBitmap.h"


// PieceBitmap

PieceBitmap::PieceBitmap() : TransparentBitmap(TRANSPARENT_COLOR), 
	m_Color(DEFAULT_COLOR)
{
	LoadBitmap(IDB_PIECE);
	Repaint();
}

PieceBitmap::~PieceBitmap()
{
}

// PieceBitmap member functions
void PieceBitmap::setColor(COLORREF nColor)
{
	BITMAP bm;
	GetBitmap(&bm);

	DWORD dwBmpSize = ((bm.bmWidth * bm.bmBitsPixel + 31) / 32) * 4 * bm.bmHeight;

	BYTE *bits = new BYTE[dwBmpSize];
	if (GetBitmapBits(dwBmpSize, bits) != dwBmpSize)
		AfxThrowResourceException();

	for (uint32_t i = 0; i < dwBmpSize; i++) {
		BYTE &b = bits[i++];
		BYTE &g = bits[i++];
		BYTE &r = bits[i++];
		BYTE z = bits[i];

		COLORREF dwColor = RGB(r, g, b);
		if (dwColor == m_Color) {
			r = GetRValue(nColor);
			g = GetGValue(nColor);
			b = GetBValue(nColor);
		}
	}

	if (!DeleteObject())
		AfxThrowResourceException();

	if (!CreateBitmapIndirect(&bm))
		AfxThrowResourceException();

	if (SetBitmapBits(dwBmpSize, bits) != dwBmpSize)
		AfxThrowResourceException();

	delete [] bits;

	Repaint();

	m_Color = nColor;
}

COLORREF PieceBitmap::getColor() const
{
	return m_Color;
}

