///////////////////////////////////////////////////////////////////////
//
//	NEPTUNE.CPP : commonly used functions
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "neptune.h"

//
// DrawBitmap
//
void Neptune :: DrawBitmap (CBitmap * pBitmap, CDC * pDC, int x, int y)
{
	ASSERT_VALID(pBitmap);
	ASSERT_VALID(pDC);

	BITMAP bm;
	pBitmap->GetObject(sizeof(BITMAP), &bm);
	CPoint size (bm.bmWidth, bm.bmHeight);

	pDC->DPtoLP(&size);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap * pOldBitmap = memDC.SelectObject(pBitmap);

	memDC.SetMapMode(pDC->GetMapMode());
	pDC->BitBlt(x, y, size.x, size.y, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
}

//
// DrawTransparentBitmap
//
// Borrowed from MSJ 1997
void Neptune :: DrawTransparentBitmap (CBitmap * pBitmap, CDC * pDC, int x, int y, COLORREF transparent)
{
	ASSERT_VALID(pBitmap);
	ASSERT_VALID(pDC);

	CBitmap bmAndBack, bmAndObject, bmAndMem, bmSave;
	CDC dcMem, dcBack, dcObject, dcTemp, dcSave;

	dcTemp.CreateCompatibleDC(pDC);
	dcTemp.SelectObject(pBitmap);

	BITMAP bm;
	pBitmap->GetObject(sizeof(BITMAP), (LPSTR)&bm);

	CPoint ptSize;
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;
	dcTemp.DPtoLP(&ptSize, 1);

	// Create some DCs to hold temporary data.
	dcBack.CreateCompatibleDC(pDC);
	dcObject.CreateCompatibleDC(pDC);
	dcMem.CreateCompatibleDC(pDC);
	dcSave.CreateCompatibleDC(pDC);

	// Create a bitmap for each DC. DCs are required for a number of GDI functions.

	// Monochrome DC
	bmAndBack.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	// Monochrome DC
	bmAndObject.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	bmAndMem.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);
	bmSave.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);

	// Each DC must select a bitmap object to store pixel data.
	CBitmap* pbmBackOld   = dcBack.SelectObject(&bmAndBack);
	CBitmap* pbmObjectOld = dcObject.SelectObject(&bmAndObject);
	CBitmap* pbmMemOld    = dcMem.SelectObject(&bmAndMem);
	CBitmap* pbmSaveOld   = dcSave.SelectObject(&bmSave);

	// Set proper mapping mode.
	dcTemp.SetMapMode(pDC->GetMapMode());

	// Save the bitmap sent here, because it will be overwritten.
	dcSave.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC to the color
	// contained in the parts of the bitmap that should be transparent
	COLORREF cColor = dcTemp.SetBkColor(transparent);

	// Create the object mask for the bitmap by performing a BitBlt
	// from the source bitmap to a monochrome bitmap.
	dcObject.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC back to the original
	// color.
	dcTemp.SetBkColor(cColor);

	// Create the inverse of the object mask.
	dcBack.BitBlt(0, 0, ptSize.x, ptSize.y, &dcObject, 0, 0, NOTSRCCOPY);

	// Copy the background of the main DC to the destination.
	dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, pDC, x, y, SRCCOPY);

	// Mask out the places where the bitmap will be placed.
	dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, &dcObject, 0, 0, SRCAND);

	// Mask out the transparent colored pixels on the bitmap.
	dcTemp.BitBlt(0, 0, ptSize.x, ptSize.y, &dcBack, 0, 0, SRCAND);

	// XOR the bitmap with the background on the destination DC.
	dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0, SRCPAINT);

	// Copy the destination to the screen.
	pDC->BitBlt(x, y, ptSize.x, ptSize.y, &dcMem, 0, 0, SRCCOPY);

	// Place the original bitmap back into the bitmap sent here.
	dcTemp.BitBlt(0, 0, ptSize.x, ptSize.y, &dcSave, 0, 0, SRCCOPY);

	// Reset the memory bitmaps.
	dcBack.SelectObject(pbmBackOld);
	dcObject.SelectObject(pbmObjectOld);
	dcMem.SelectObject(pbmMemOld);
	dcSave.SelectObject(pbmSaveOld);

	// Memory DCs and Bitmap objects will be deleted automatically
}

//
// LoadImage
//
HANDLE Neptune :: LoadImage(UINT Resource, UINT Type)
{
	return ::LoadImage(AfxGetResourceHandle(),
	                   MAKEINTRESOURCE(Resource),
	                   Type,
	                   0, 0,
	                   LR_DEFAULTCOLOR | LR_SHARED);
}

//
// AfxCopyMemory
//
LPVOID Neptune :: AfxCopyMemory(LPVOID pdest, LPVOID psrc, size_t count)
{
	ASSERT(AfxIsValidAddress(psrc, count, FALSE));
	ASSERT(AfxIsValidAddress(pdest, count, TRUE));

	return memcpy(pdest, psrc, count);
}

