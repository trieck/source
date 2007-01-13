// PenteBar.cpp : implementation file
//
#include "stdafx.h"
#include "PenteBar.h"
#include "PenteDoc.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TRANSPARENT_COLOR RGB(0xC0, 0xC0, 0xC0)	// light gray

static UINT indicators[] = {
	ID_SEPARATOR,
	IDS_CAPTURES,
	IDS_TURN
};
/////////////////////////////////////////////////////////////////////////////
// PenteBar

PenteBar::PenteBar()
{
}

PenteBar::~PenteBar()
{
}

void PenteBar::DrawItem(LPDRAWITEMSTRUCT dis)
{
	ASSERT(dis != NULL);
	
	PenteDoc *doc = (PenteDoc*)GetParentFrame()->GetActiveDocument();
	ASSERT_VALID(doc);
	const Player *playerOne = doc->getGame()->getPlayerOne();
	const Player *playerTwo = doc->getGame()->getPlayerTwo();
	
	ASSERT_VALID(playerOne);
	ASSERT_VALID(playerTwo);
	CDC dc;
	dc.Attach(dis->hDC);
	BITMAP bm1, bm2;
	bmPlayerOne.GetBitmap(&bm1);
	bmPlayerTwo.GetBitmap(&bm2);
	CRect rc(dis->rcItem);
	int cy1 = rc.top + ((rc.Height() - bm1.bmHeight) / 2);
	int cy2 = rc.top + ((rc.Height() - bm2.bmHeight) / 2);
	int offset = rc.left;
	for (unsigned i = 0; i < playerOne->getCaptures(); i++) {
		imageList.DrawIndirect(&dc, 0, CPoint(offset, cy1), 
			CSize(bm1.bmWidth, bm1.bmHeight), CPoint(0, 0));
		offset += bm1.bmWidth;
	}
	for (i = 0; i < playerTwo->getCaptures(); i++) {
		imageList.DrawIndirect(&dc, 1, CPoint(offset, cy1), 
			CSize(bm2.bmWidth, bm2.bmHeight), CPoint(0, 0));
		offset += bm2.bmWidth;
	}
	dc.Detach();
}

BEGIN_MESSAGE_MAP(PenteBar, CStatusBar)
	//{{AFX_MSG_MAP(PenteBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// PenteBar message handlers

PenteBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	GetParentFrame()->RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST);
	bmPlayerOne.LoadBitmap(IDB_PLAYER1CAP);
	bmPlayerTwo.LoadBitmap(IDB_PLAYER2CAP);
	
	BITMAP bm;
	bmPlayerOne.GetBitmap(&bm);
	if (!imageList.Create(bm.bmWidth, bm.bmHeight, 
		ILC_COLOR | ILC_MASK, 2, 0))
		return -1;
	imageList.Add(&bmPlayerOne, TRANSPARENT_COLOR);
	imageList.Add(&bmPlayerTwo, TRANSPARENT_COLOR);
	unsigned id, style;
	int width, captureWidth;
	CRect rc;
	GetWindowRect(rc);
	captureWidth = (Player::getMaxCaptures() * bm.bmWidth) * 2;
	GetPaneInfo(0, id, style, width);
	SetPaneInfo(0, id, style & ~SBPS_NOBORDERS, rc.Width() / 3);
	GetPaneInfo(1, id, style, width);
	SetPaneInfo(1, id, style | SBT_OWNERDRAW, captureWidth);
	return 0;
}