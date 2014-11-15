// RecolorableBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "RecolorableBitmap.h"


// RecolorableBitmap

RecolorableBitmap::RecolorableBitmap(COLORREF nSourceColor)
    : TransparentBitmap(TRANSPARENT_COLOR), m_dwBmpSize(0), m_Bits(0),
      m_Color(nSourceColor)
{
}

RecolorableBitmap::~RecolorableBitmap()
{
    FreeBits();
}

// RecolorableBitmap member functions
void RecolorableBitmap::Load(UINT nID)
{
    LoadBitmap(nID);

    BITMAP bm;
    GetBitmap(&bm);

    m_dwBmpSize = ((bm.bmWidth * bm.bmBitsPixel + 31) / 32) * 4 * bm.bmHeight;

    FreeBits();

    m_Bits = new BYTE[m_dwBmpSize];

    Repaint();
}

void RecolorableBitmap::setColor(COLORREF nColor)
{
    if (GetBitmapBits(m_dwBmpSize, m_Bits) != m_dwBmpSize)
        AfxThrowResourceException();

    for (uint32_t i = 0; i < m_dwBmpSize; i++) {
        BYTE &b = m_Bits[i++];
        BYTE &g = m_Bits[i++];
        BYTE &r = m_Bits[i++];
        BYTE z = m_Bits[i];

        COLORREF dwColor = RGB(r, g, b);
        if (dwColor == m_Color) {
            r = GetRValue(nColor);
            g = GetGValue(nColor);
            b = GetBValue(nColor);
        }
    }

    BITMAP bm;
    GetBitmap(&bm);

    if (!DeleteObject())
        AfxThrowResourceException();

    if (!CreateBitmapIndirect(&bm))
        AfxThrowResourceException();

    if (SetBitmapBits(m_dwBmpSize, m_Bits) != m_dwBmpSize)
        AfxThrowResourceException();

    Repaint();

    m_Color = nColor;
}

COLORREF RecolorableBitmap::getColor() const
{
    return m_Color;
}

void RecolorableBitmap::FreeBits()
{
    if (m_Bits != NULL)
        delete [] m_Bits;

    m_Bits = NULL;
}
