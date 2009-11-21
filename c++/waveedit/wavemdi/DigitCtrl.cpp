// DigitCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DigitCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDigitCtrl
BEGIN_MESSAGE_MAP(CDigitCtrl, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// Initialize the const static array of bitmaps
const UINT CDigitCtrl :: nBitmaps[10] = {IDB_DIGIT0, IDB_DIGIT1, IDB_DIGIT2, IDB_DIGIT3,
                                        IDB_DIGIT4, IDB_DIGIT5, IDB_DIGIT6, IDB_DIGIT7,
                                        IDB_DIGIT8, IDB_DIGIT9
                                        };

CDigitCtrl :: CDigitCtrl()
{
	m_nCurrentDigit = 0;
	m_lBackColor	= 0L;
}

CDigitCtrl :: ~CDigitCtrl()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDigitCtrl message handlers

VOID CDigitCtrl :: DrawDigit(CDC* pdc)
{
	CDC					dcMem;
	CBitmap				cbm, *pbmOld;
	CRect				rc;
	UINT				nLeft, nTop;
	BITMAP				bm;

	ASSERT_VALID(pdc);

	dcMem.CreateCompatibleDC(pdc);

	// Load the bitmap
	cbm.LoadBitmap(nBitmaps[m_nCurrentDigit]);
	cbm.GetBitmap(&bm);

	pbmOld = dcMem.SelectObject(&cbm);

	GetClientRect(&rc);

	nLeft = (rc.Width() - bm.bmWidth) / 2;
	nTop  = (rc.Height() - bm.bmHeight) / 2;

	// BitBlt() from the Memory DC.
	pdc->BitBlt(nLeft, nTop, bm.bmWidth, bm.bmHeight,
	            &dcMem, 0, 0, SRCCOPY);

	dcMem.SelectObject(pbmOld);
	dcMem.DeleteDC();

	cbm.DeleteObject();
}

VOID CDigitCtrl :: OnPaint()
{
	CPaintDC dc(this);

	// Fill background black
	dc.FillSolidRect(&dc.m_ps.rcPaint, m_lBackColor);

	// Draw the digit
	DrawDigit(&dc);
}

VOID CDigitCtrl :: SetNextDigit()
{
	if (++m_nCurrentDigit > 9)
		m_nCurrentDigit = 0;
}

BOOL CDigitCtrl :: SetValue(UINT nValue)
{
	if (nValue > 9) return FALSE;

	m_nCurrentDigit = nValue;

	return TRUE;
}

VOID CDigitCtrl :: SetBackColor(COLORREF lColor)
{
	m_lBackColor = lColor;
}
