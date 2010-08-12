
// Global helper functions

#include "stdafx.h"
#include "globals.h"

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
	::GetTextExtentPoint32(*pDC, str, (int)_tcslen(str), &sz);
	pDC->SelectObject(pOldFont);
	pWnd->ReleaseDC(pDC);
	return sz.cx;
}

