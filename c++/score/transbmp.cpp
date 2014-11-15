///////////////////////////////////////////////////////////////////////
//
//	TRANSBMP.CPP : transparent bitmap
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "transbmp.h"

//
// Constructor
//
TransparentBitmap :: TransparentBitmap(UINT nID, COLORREF transparent)
{
    m_fInitialized = FALSE;
    m_pOldBitmapMem = NULL;
    m_pOldBitmapXor = NULL;
    m_pOldBitmapAnd = NULL;

    m_transparent = transparent;

    if (!LoadBitmap(nID))
        AfxThrowUserException();
}

//
// Initialize
//
BOOL TransparentBitmap :: Initialize(CDC * pDC)
{
    ASSERT((HBITMAP)*this != NULL);
    ASSERT_VALID(pDC);

    if (m_fInitialized)
        return FALSE;

    BITMAP bm;
    GetObject(sizeof(BITMAP), &bm);
    CPoint size(bm.bmWidth, bm.bmHeight);

    CPoint org(0, 0);

    // Create a memory DC and select the bitmap into it
    CDC dcImage;
    dcImage.CreateCompatibleDC(pDC);
    CBitmap * pOldBitmapImage = dcImage.SelectObject(this);
    dcImage.SetMapMode(pDC->GetMapMode());

    // Create a second memory DC and in it create an AND mask
    m_AndDC.CreateCompatibleDC(pDC);
    m_AndDC.SetMapMode(pDC->GetMapMode());

    CBitmap bitmapAnd;
    bitmapAnd.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
    m_pOldBitmapAnd = m_AndDC.SelectObject(&bitmapAnd);

    dcImage.SetBkColor(m_transparent);
    m_AndDC.BitBlt(org.x, org.y, size.x, size.y, &dcImage, org.x, org.y, SRCCOPY);

    // Create a third memory DC and in it create an XOR mask
    m_XOrDC.CreateCompatibleDC(pDC);
    m_XOrDC.SetMapMode(pDC->GetMapMode());

    CBitmap bitmapXor;
    bitmapXor.CreateCompatibleBitmap(&dcImage, bm.bmWidth, bm.bmHeight);
    m_pOldBitmapXor = m_XOrDC.SelectObject(&bitmapXor);

    m_XOrDC.BitBlt(org.x, org.y, size.x, size.y, &dcImage, org.x, org.y, SRCCOPY);

    m_XOrDC.BitBlt(org.x, org.y, size.x, size.y, &m_AndDC, org.x, org.y, 0x220326);

    // Copy the pixels in the destination rectangle to the memory DC
    m_MemDC.CreateCompatibleDC(pDC);
    m_MemDC.SetMapMode(pDC->GetMapMode());

    CBitmap bitmapMem;
    bitmapMem.CreateCompatibleBitmap(&dcImage, bm.bmWidth, bm.bmHeight);
    m_pOldBitmapMem = m_MemDC.SelectObject(&bitmapMem);

    dcImage.SelectObject(pOldBitmapImage);

    m_fInitialized = TRUE;

    return TRUE;
}

//
// Render
//
BOOL TransparentBitmap :: Render(CDC * pDC, int x, int y)
{
    ASSERT_VALID(pDC);

    if (!m_fInitialized)
        return FALSE;

    BITMAP bm;
    GetObject(sizeof(BITMAP), &bm);
    CPoint size(bm.bmWidth, bm.bmHeight);

    CPoint org(0, 0);

    m_MemDC.BitBlt(org.x, org.y, size.x, size.y, pDC, x, y, SRCCOPY);

    // Generate the final image by applying the AND and XOR masks to
    // the image in the temporary memory DC
    m_MemDC.BitBlt(org.x, org.y, size.x, size.y, &m_AndDC, org.x, org.y, SRCAND);
    m_MemDC.BitBlt(org.x, org.y, size.x, size.y, &m_XOrDC, org.x, org.y, SRCINVERT);

    // Blit the resulting image to the screen
    pDC->BitBlt(x, y, size.x, size.y, &m_MemDC, org.x, org.y, SRCCOPY);

    return TRUE;
}

//
// Destructor
//
TransparentBitmap :: ~TransparentBitmap()
{
    if (m_pOldBitmapMem != NULL)
        m_MemDC.SelectObject(m_pOldBitmapMem);

    if (m_pOldBitmapXor != NULL)
        m_XOrDC.SelectObject(m_pOldBitmapXor);

    if (m_pOldBitmapAnd != NULL)
        m_AndDC.SelectObject(m_pOldBitmapAnd);
}

