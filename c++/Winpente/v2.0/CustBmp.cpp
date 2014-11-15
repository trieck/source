/*---------------------------------------
	Module Name	:	CustBmp.cpp
	Author		:	Thomas A. Rieck
	Purpose		:	Custom Bitmap
					Drawing implementation
	Date		:	08/31/1997
---------------------------------------*/

#include "stdafx.h"
#include "CustBmp.h"

IMPLEMENT_DYNCREATE(CCustomBitmap, CObject)

CCustomBitmap::CCustomBitmap()
{
}

CCustomBitmap::~CCustomBitmap()
{
}

HBITMAP CCustomBitmap::LoadResourceBitmap(INT nResourceID, HPALETTE* lphPalette)
{
    HRSRC 					hRsrc;
    HGLOBAL					hGlobal;
    HBITMAP					hBitmap = NULL;
    LPBITMAPINFOHEADER		lpbi;
    HDC						hDC;
    INT						nNumColors;

    if (!(hRsrc = FindResource(AfxGetResourceHandle(),
                               MAKEINTRESOURCE(nResourceID),
                               RT_BITMAP)))
        return NULL;

    hGlobal = LoadResource(AfxGetResourceHandle(), hRsrc);
    if (!hGlobal)
        return NULL;

    lpbi = (LPBITMAPINFOHEADER)LockResource(hGlobal);

    hDC = ::GetDC(NULL);

    *lphPalette = CreateDIBPalette((LPBITMAPINFO)lpbi, &nNumColors);
    if (*lphPalette) {
        SelectPalette(hDC, *lphPalette, FALSE);
        RealizePalette(hDC);
    }

    hBitmap = CreateDIBitmap(hDC,
                             (LPBITMAPINFOHEADER)lpbi,
                             (LONG)CBM_INIT,
                             (LPTSTR)lpbi + lpbi->biSize + nNumColors *
                             sizeof(RGBQUAD),
                             (LPBITMAPINFO)lpbi,
                             DIB_RGB_COLORS);

    ::ReleaseDC(NULL, hDC);

    UnlockResource(hGlobal);

    FreeResource(hGlobal);

    return hBitmap;
}

HPALETTE CCustomBitmap::CreateDIBPalette(LPBITMAPINFO lpbmi, LPINT lpiNumColors)
{
    LPBITMAPINFOHEADER	lpbi;
    LPLOGPALETTE		lpPal;
    HANDLE				hLogPal;
    HPALETTE			hPal = NULL;
    INT					i;

    lpbi = (LPBITMAPINFOHEADER)lpbmi;

    if (lpbi->biBitCount <= 8)
        *lpiNumColors = (1 << lpbi->biBitCount);
    else
        *lpiNumColors = 0;	// No palette for 24 BPP DIB

    if (lpbi->biClrUsed > 0)
        *lpiNumColors = lpbi->biClrUsed;

    if (*lpiNumColors) {
        hLogPal = GlobalAlloc(GHND, sizeof(LOGPALETTE) +
                              sizeof(PALETTEENTRY) * (*lpiNumColors));

        lpPal = (LPLOGPALETTE)GlobalLock(hLogPal);

        lpPal->palVersion = 0x300;

        lpPal->palNumEntries = *lpiNumColors;

        for (i = 0; i < *lpiNumColors; i++) {
            lpPal->palPalEntry[i].peRed 	= lpbmi->bmiColors[i].rgbRed;
            lpPal->palPalEntry[i].peGreen	= lpbmi->bmiColors[i].rgbGreen;
            lpPal->palPalEntry[i].peBlue 	= lpbmi->bmiColors[i].rgbBlue;
            lpPal->palPalEntry[i].peFlags	= 0;
        }

        hPal = CreatePalette(lpPal);
        GlobalUnlock(hLogPal);
        GlobalFree(hLogPal);
    }

    return hPal;
}

VOID CCustomBitmap::PaintDCByHBitmap(CDC* pDC, HBITMAP hBitmap, BOOL fSaveHandle)
{
    CWnd			*pWnd;
    HBITMAP			hBitmapOld;
    HWND			hWnd;
    CDC				dcMem;
    BITMAP			bm;
    CRect			rc;

    ASSERT_VALID(pDC);
    ASSERT(hBitmap);

    GetObject(hBitmap, sizeof(BITMAP), &bm);

    dcMem.CreateCompatibleDC(pDC);

    hBitmapOld = (HBITMAP)::SelectObject(dcMem.GetSafeHdc(), hBitmap);

    hWnd = ::WindowFromDC(pDC->GetSafeHdc());
    ASSERT(hWnd);

    pWnd = CWnd::FromHandle(hWnd);
    ASSERT_VALID(pWnd);

    pWnd->GetClientRect(&rc);

    // Paint the DC
    for (int k = 0; k < rc.Height(); k += bm.bmHeight)
        for (int j = 0; j < rc.Width(); j+= bm.bmWidth)
            pDC->BitBlt(j, k, bm.bmWidth, bm.bmHeight,
                        &dcMem, 0, 0, SRCCOPY);

    ::SelectObject(dcMem.GetSafeHdc(), hBitmapOld);

    if (!fSaveHandle)
        ::DeleteObject(hBitmap);


    dcMem.DeleteDC();
}

VOID CCustomBitmap::PaintDCByResource(CDC* pDC, INT nResourceID)
{

    HBITMAP			hBitmap;
    HPALETTE		hPalette;

    ASSERT_VALID(pDC);

    // Load bitmap handle from resource
    hBitmap = LoadResourceBitmap(nResourceID, &hPalette);

    ASSERT(hBitmap);
    ASSERT(hPalette);

    // Paint the DC
    PaintDCByHBitmap(pDC, hBitmap, FALSE);
}

VOID CCustomBitmap::PaintDCByColor(CDC* pDC, COLORREF lColor)
{
    HWND	hWnd;
    CRect	aRect;

    ASSERT_VALID(pDC);

    hWnd = ::WindowFromDC(pDC->GetSafeHdc());
    ASSERT(hWnd);

    ::GetClientRect(hWnd, &aRect);

    pDC->FillSolidRect(&aRect, lColor);
}



