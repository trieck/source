
// Global helper functions

#include "stdafx.h"
#include "globals.h"
#include "pente.h"
#include <stdarg.h>
/////////////////////////////////////////////////////////////////////////////
int getTextWidth(CWnd *pWnd, LPCTSTR str)
{
	ASSERT_VALID(pWnd);
	ASSERT(IsWindow(*pWnd));
	ASSERT(str != NULL);
	CDC * pDC = pWnd->GetDC();
	ASSERT_VALID(pDC);
	CFont * pFont = pWnd->GetFont();
	ASSERT_VALID(pFont);
	CFont * pOldFont = pDC->SelectObject(pFont);
	SIZE sz;
	::GetTextExtentPoint32(*pDC, str, _tcslen(str), &sz);
	pDC->SelectObject(pOldFont);
	pWnd->ReleaseDC(pDC);
	return sz.cx;
}
/////////////////////////////////////////////////////////////////////////////
void DrawTransparentBitmap(CDC *pDC, CBitmap *pBitmap, short xStart,
 short yStart, COLORREF cTransparentColor)
{
	ASSERT_VALID(pDC);
	ASSERT_VALID(pBitmap);
	CDC dcTemp;
	dcTemp.CreateCompatibleDC(pDC);
	dcTemp.SelectObject(pBitmap);   // Select the bitmap

	BITMAP bm;
	pBitmap->GetBitmap(&bm);
	
	POINT ptSize;
	ptSize.x = bm.bmWidth;		// Get width of bitmap
	ptSize.y = bm.bmHeight;     // Get height of bitmap
	dcTemp.DPtoLP(&ptSize, 1);  // Convert from device
								// to logical points

	// Create some DCs to hold temporary data
	CDC dcMem, dcBack, dcObject, dcSave;
	dcBack.CreateCompatibleDC(pDC);
	dcObject.CreateCompatibleDC(pDC);
	dcMem.CreateCompatibleDC(pDC);
	dcSave.CreateCompatibleDC(pDC);
	CBitmap bmAndBack, bmAndObject, bmAndMem, bmSave;
	// Monochrome DC
	bmAndBack.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	// Monochrome DC
	bmAndObject.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);
	bmSave.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);
	// Each DC must select a bitmap object to store pixel data.
	CBitmap *bmBackOld = dcBack.SelectObject(&bmAndBack);
	CBitmap *bmObjectOld = dcObject.SelectObject(&bmAndObject);
	CBitmap *bmMemOld = dcMem.SelectObject(&bmAndMem);
	CBitmap *bmSaveOld = dcSave.SelectObject(&bmSave);
	// Set proper mapping mode.
	dcTemp.SetMapMode(pDC->GetMapMode());
	// Save the bitmap sent here, because it will be overwritten.
	dcSave.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0, SRCCOPY);
	// Set the background color of the source DC to the color.
	// contained in the parts of the bitmap that should be transparent
	COLORREF cColor = dcTemp.SetBkColor(cTransparentColor);
	// Create the object mask for the bitmap by performing a BitBlt
	// from the source bitmap to a monochrome bitmap.
	dcObject.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0,
		  SRCCOPY);
	// Set the background color of the source DC back to the original
	// color.
	dcTemp.SetBkColor(cColor);
	// Create the inverse of the object mask.
	dcBack.BitBlt(0, 0, ptSize.x, ptSize.y, &dcObject, 0, 0,
		  NOTSRCCOPY);
	// Copy the background of the main DC to the destination.
	dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, pDC, xStart, yStart,
		  SRCCOPY);
	// Mask out the places where the bitmap will be placed.
	dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, &dcObject, 0, 0, SRCAND);
	// Mask out the transparent colored pixels on the bitmap.
	dcTemp.BitBlt(0, 0, ptSize.x, ptSize.y, &dcBack, 0, 0, SRCAND);
	// XOR the bitmap with the background on the destination DC.
	dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0, SRCPAINT);
	// Copy the destination to the screen.
	pDC->BitBlt(xStart, yStart, ptSize.x, ptSize.y, &dcMem, 0, 0,
		  SRCCOPY);
	// Place the original bitmap back into the bitmap sent here.
	dcTemp.BitBlt(0, 0, ptSize.x, ptSize.y, &dcSave, 0, 0, SRCCOPY);
	// Delete the memory bitmaps.
	dcBack.SelectObject(&bmBackOld);
	dcObject.SelectObject(&bmObjectOld);
	dcMem.SelectObject(&bmMemOld);
	dcSave.SelectObject(&bmSaveOld);
	// Delete the memory DCs.
	dcMem.DeleteDC();
	dcBack.DeleteDC();
	dcObject.DeleteDC();
	dcSave.DeleteDC();
	dcTemp.DeleteDC();
}
/////////////////////////////////////////////////////////////////////////////
void throwException(UINT nID)
{
	CString str;
	if (str.LoadString(nID))
		AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);
	AfxThrowUserException();
}
/////////////////////////////////////////////////////////////////////////////
void logMessage(LPCTSTR fmt, ...)
{
	TCHAR buff[4096];
	va_list list;
	va_start(list, fmt);
	_vstprintf(buff, fmt, list);
	va_end(list);
	PenteApp *pApp = (PenteApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	LogWnd *pWnd = pApp->getLogWindow();
	ASSERT_VALID(pWnd);
	pWnd->logMessage(buff);
}
/////////////////////////////////////////////////////////////////////////////
void pumpMessages()
{
	CWinThread *pThread = AfxGetApp();
	MSG msg;
    while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) { 
        if (!pThread->PumpMessage()) {
            break; 
        } 
    } 
    LONG lIdle = 0;
    while (pThread->OnIdle(lIdle++))
        ;  
}