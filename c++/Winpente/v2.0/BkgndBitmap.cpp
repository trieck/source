// BkgndBitmap.cpp: implementation of the CBkgndBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "BkgndBitmap.h"
#include "BkgndPage.h"
#include "OurConstants.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CBkgndBitmap, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

CBkgndBitmap::CBkgndBitmap(HBITMAP hBitmap, HPALETTE hPalette, UINT ResID) :
 m_hBitmap(hBitmap), m_hPalette(hPalette), m_ResID(ResID)
{
	m_pCustomBitmap = NULL;
	m_fFrameBitmap	= FALSE;
}

CBkgndBitmap::~CBkgndBitmap()
{
	if (m_pCustomBitmap)
	{
		delete m_pCustomBitmap;
	}
}

INT CBkgndBitmap::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_pCustomBitmap = new CCustomBitmap();
	ASSERT_VALID(m_pCustomBitmap);

	return CWnd::OnCreate(lpCreateStruct);
}

VOID CBkgndBitmap::OnPaint()
{
	CPaintDC	dc(this);
	CRect		rc;

	ASSERT(m_hBitmap);
	ASSERT(m_hPalette);

	::SelectPalette(dc.GetSafeHdc(), m_hPalette, TRUE);
	::RealizePalette(dc.GetSafeHdc());
		
	m_pCustomBitmap->PaintDCByHBitmap(&dc, m_hBitmap, TRUE);

	if (m_fFrameBitmap)
	{
		FrameBitmap(&dc);
	}
}

VOID CBkgndBitmap::FrameBitmap(CDC* pDC)
{
	CBrush		aBrush, *pOldBrush;
	CRect		rc;
		
	ASSERT_VALID(pDC);

	GetClientRect(&rc);
	
	aBrush.CreateSolidBrush(COLOR_WHITE);
	ASSERT_VALID(&aBrush);
	
	pOldBrush = pDC->SelectObject(&aBrush);
	ASSERT_VALID(pOldBrush);

	// Frame the rectangle emulate
	// a pen with a 2 pixel width
	rc.InflateRect(-2,-2,-2,-2);
	pDC->FrameRect(&rc, &aBrush);
	rc.InflateRect(-1,-1,-1,-1);
	pDC->FrameRect(&rc, &aBrush);
	
	pDC->SelectObject(pOldBrush);
	aBrush.DeleteObject();
}

VOID CBkgndBitmap::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_fFrameBitmap = TRUE;

	CBkgndPage * pPage = (CBkgndPage*)GetParent();
	ASSERT_VALID(pPage);

	pPage->m_pCurrentBitmap = this;

	pPage->SetModified();
	pPage->RedrawBitmaps();
}