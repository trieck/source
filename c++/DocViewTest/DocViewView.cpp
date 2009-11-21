//////////////////////////////////////
// Module Name	:	DocViewView.cpp	//
// Author		:	Thomas A. Rieck //
// Purpose		:	Simple Document //
//					 - View Test	//
// Date			:	4/11/97			//
//////////////////////////////////////

#include "MainFrame.h"
#include "DocViewView.h"

IMPLEMENT_DYNCREATE(CDocViewView, CView)

BEGIN_MESSAGE_MAP(CDocViewView, CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////
// CDocViewView construction/destruction

CDocViewView::CDocViewView()
{
}

CDocViewView::~CDocViewView()
{
}

BOOL CDocViewView :: PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style = cs.style | WS_CLIPSIBLINGS;
	return CView :: PreCreateWindow(cs);
}

void CDocViewView::OnDraw(CDC* pDC)
{
	CRect	rc;
	CBrush	aBrush, *pBrushOld;
	INT		x, y;

	pDC->GetClipBox(&rc);

	if (pDC->RectVisible(&rc)) {
		// Paint the background
		x		= rc.left;
		y		= rc.top;

		aBrush.CreateSolidBrush(::GetSysColor(COLOR_WINDOW));

		pBrushOld = pDC->SelectObject(&aBrush);

		pDC->PatBlt(x, y, rc.Width(), rc.Height(), PATCOPY);

		pDC->SelectObject(pBrushOld);

		aBrush.DeleteObject();
	}
}

void CDocViewView::OnInitialUpdate()
{
}

INT	CDocViewView :: OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return CView :: OnCreate(lpCreateStruct);
}

