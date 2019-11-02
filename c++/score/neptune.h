/////////////////////////////////////////////////////////////////////////////
//
//	NEPTUNE.H : commonly used functions
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __NEPTUNE_H__
#define __NEPTUNE_H__

/////////////////////////////////////////////////////////////////////////////
namespace Neptune
{
// Image functions
void DrawBitmap (CBitmap * pBitmap, CDC * pDC, int x, int y);
void DrawTransparentBitmap (CBitmap * pBitmap, CDC * pDC, int x, int y, COLORREF transparent);
HANDLE LoadImage(UINT Resource, UINT Type);

// Common functions
LPVOID AfxCopyMemory(LPVOID pdest, LPVOID psrc, size_t count);
}
/////////////////////////////////////////////////////////////////////////////

#endif // __NEPTUNE_H__

