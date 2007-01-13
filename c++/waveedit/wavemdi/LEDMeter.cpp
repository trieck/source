// LEDMeter.cpp : implementation file
//

#include "stdafx.h"
#include "LEDMeter.h"

/////////////////////////////////////////////////////////////////////////////
// CLEDMeter

CLEDMeter :: CLEDMeter()
{
	m_nPosition		= 0;
	m_nLowerRange	= 0;
	m_nUpperRange	= 100;
	m_nStep			= 10;
	m_nGapSize		= 1;
	m_nBackColor	= 0L;
}

CLEDMeter::~CLEDMeter()
{
}

BEGIN_MESSAGE_MAP(CLEDMeter, CProgressCtrl)
	//{{AFX_MSG_MAP(CLEDMeter)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLEDMeter message handlers

void CLEDMeter::OnPaint() 
{
	CPaintDC dc(this);
	
	// Paint the background
	dc.FillSolidRect(&dc.m_ps.rcPaint, m_nBackColor);

	// Draw the meter chunks
	DrawChunks(&dc);
}

int CLEDMeter::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CProgressCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CLEDMeter :: SetRange(UINT nLower, UINT nUpper)
{
	m_nLowerRange = nLower;
	m_nUpperRange = nUpper;
}

UINT CLEDMeter :: OffsetPos(UINT nPos)
{
	UINT nOldPos = m_nPosition;

	m_nPosition += nPos;
	Invalidate();

	return nOldPos;
}

UINT CLEDMeter :: SetPos(UINT nPos)
{
	UINT nOldPos = m_nPosition;

	m_nPosition = nPos;
	Invalidate();

	return nOldPos;
}

UINT CLEDMeter :: SetStep(UINT nStep)
{
	UINT nOldStep = m_nStep;

	m_nStep = nStep;
	
	return nOldStep;
}

UINT CLEDMeter :: StepIt()
{
	UINT nOldPosition = m_nPosition;

	m_nPosition += m_nStep;
	Invalidate();

	return nOldPosition;
}

VOID CLEDMeter :: DrawChunks(CDC * pDC)
{
	CBrush	*pOldBrush;
	CBitmap	aBitmap, *pOldBitmap;
	CDC		dcMem;
	CRect	aRect;
	
	ASSERT_VALID(pDC);

	GetClientRect(&aRect);

	INT nChunkSize	= 3;
	INT nStartPos	= 0;

	// Create a compatible memory dc and bitmap.
	dcMem.CreateCompatibleDC(pDC);
	aBitmap.CreateCompatibleBitmap(pDC, 
			aRect.Width(), aRect.Height());

	pOldBitmap = dcMem.SelectObject(&aBitmap);

	// Clear out the bitmap with our background color.
	CBrush br(m_nBackColor);
	pOldBrush = dcMem.SelectObject(&br);
	dcMem.PatBlt(0, 0, aRect.Width(), aRect.Height(), PATCOPY);
	dcMem.SelectObject(pOldBrush);
	br.DeleteObject();

	float	fPercent					= (float)m_nPosition / m_nUpperRange;
	UINT	nNumberOfPossibleChunks		= aRect.Width() / (nChunkSize + m_nGapSize);
	UINT	nChunks						= (UINT)((float)nNumberOfPossibleChunks * fPercent);
	
    for (UINT i = 0; i < nChunks; i++)
	{
		// Select the brush into our memory dc.
		COLORREF lColor;
		float f = (float) i / nNumberOfPossibleChunks;

		if (f < .33)
			lColor = COLOR_GREEN;
		else if (f < .66)
			lColor = COLOR_YELLOW;
		else
			lColor = COLOR_RED;

		CBrush aBrush(lColor);
		pOldBrush = dcMem.SelectObject(&aBrush);

		dcMem.PatBlt(nStartPos, 0, nChunkSize, aRect.Height(), PATCOPY);
    	pDC->BitBlt(nStartPos, 0, nChunkSize + m_nGapSize, aRect.Height(), 
						&dcMem, nStartPos, 0, SRCCOPY);

		dcMem.SelectObject(pOldBrush);
		aBrush.DeleteObject();

		nStartPos += nChunkSize + m_nGapSize;
    }
	
	dcMem.SelectObject(pOldBitmap);

    aBitmap.DeleteObject();
    dcMem.DeleteDC();
}

