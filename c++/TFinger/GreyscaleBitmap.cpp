// GreyscaleBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "GreyscaleBitmap.h"

// relative luminance
#define LUMINANCE(R,G,B)	\
	(BYTE)((0.2126 * R) + (0.7152 * G) + (0.0722 * B))

// GreyscaleBitmap

GreyscaleBitmap::GreyscaleBitmap()
{
    CImage image;
}

GreyscaleBitmap::~GreyscaleBitmap()
{
}

BOOL GreyscaleBitmap::LoadBitmap(LPCTSTR szFilename)
{
    HRESULT hr = Load(szFilename);
    if (FAILED(hr))
        return FALSE;

    // only allow 256-color images
    if (GetBPP() != 8) {
        Destroy();
        return FALSE;
    }

    return Monochrome();
}

BOOL GreyscaleBitmap::Monochrome()
{
    int nColors = GetMaxColorTableEntries();
    RGBQUAD *prgbColors = (RGBQUAD*)GlobalAlloc(GMEM_FIXED, sizeof(RGBQUAD) * nColors);
    if (prgbColors == NULL)
        return FALSE;

    GetColorTable(0, nColors, prgbColors);

    for (int i = 0; i < nColors; i++) {
        BYTE &R = prgbColors[i].rgbRed;
        BYTE &G = prgbColors[i].rgbGreen;
        BYTE &B = prgbColors[i].rgbBlue;

        R = G = B = LUMINANCE(R,G,B);
    }

    SetColorTable(0, nColors, prgbColors);

    GlobalFree(prgbColors);

    return TRUE;
}
