// TransparentBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "TransparentBitmap.h"


// TransparentBitmap

TransparentBitmap::TransparentBitmap(COLORREF transparent)
 : m_Transparent(transparent)
{
}

TransparentBitmap::~TransparentBitmap()
{
}


// TransparentBitmap member functions

void TransparentBitmap::Draw(CDC *pDC, int x, int y)
{
	CDC dcTemp;
	dcTemp.CreateCompatibleDC(pDC);
	dcTemp.SelectObject(this);     

	BITMAP bm;
	GetBitmap(&bm);

    CPoint ptSize;
    ptSize.x = bm.bmWidth;               
    ptSize.y = bm.bmHeight;              

    dcTemp.DPtoLP(&ptSize, 1);           

    // Create some DCs to hold temporary data
	CDC dcMem, dcBack, dcObject, dcSave;
	dcBack.CreateCompatibleDC(pDC);
    dcObject.CreateCompatibleDC(pDC);
    dcMem.CreateCompatibleDC(pDC);
    dcSave.CreateCompatibleDC(pDC);

	CBitmap bmAndBack, bmAndObject, bmAndMem, bmSave;
	bmAndBack.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
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

    COLORREF cColor = dcTemp.SetBkColor(m_Transparent);

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
}

