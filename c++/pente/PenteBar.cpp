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
	BITMAP bm;
	bmPlayerOne.GetBitmap(&bm);

	CRect rc(dis->rcItem);
	int cy = rc.top + ((rc.Height() - bm.bmHeight) / 2);
	int offset = rc.left;

	unsigned i;
	for (i = 0; i < playerOne->getCaptures(); i++) {
		bmPlayerOne.Draw(&dc, offset, cy);
		offset += bm.bmWidth;
	}

	for (i = 0; i < playerTwo->getCaptures(); i++) {
		bmPlayerTwo.Draw(&dc, offset, cy);
		offset += bm.bmWidth;
	}

	dc.Detach();
}

BEGIN_MESSAGE_MAP(PenteBar, CStatusBar)
	//{{AFX_MSG_MAP(PenteBar)
	ON_WM_CREATE()
	ON_MESSAGE(WM_APPSETTING_CHANGE, OnAppSettingChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PenteBar message handlers

int PenteBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	GetParentFrame()->RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST);

	CWinApp *pApp = AfxGetApp();
	COLORREF playerOneColor = pApp->GetProfileInt(_T("Settings"),
	                          _T("playerOneColor"), PenteBoard::DEFAULT_PLAYER_ONE_COLOR);
	COLORREF playerTwoColor = pApp->GetProfileInt(_T("Settings"),
	                          _T("playerTwoColor"), PenteBoard::DEFAULT_PLAYER_TWO_COLOR);

	bmPlayerOne.setColor(playerOneColor);
	bmPlayerTwo.setColor(playerTwoColor);

	BITMAP bm;
	bmPlayerOne.GetBitmap(&bm);

	unsigned id, style;
	int width, captureWidth;

	CRect rc;
	GetWindowRect(rc);

	captureWidth = (Player::MAX_CAPTURES * bm.bmWidth) * 2;
	GetPaneInfo(0, id, style, width);
	SetPaneInfo(0, id, style & ~SBPS_NOBORDERS, rc.Width() / 3);
	GetPaneInfo(1, id, style, width);
	SetPaneInfo(1, id, style | SBT_OWNERDRAW, captureWidth);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
LRESULT PenteBar::OnAppSettingChange(WPARAM wParam, LPARAM lParam)
{
	CWinApp *pApp = AfxGetApp();
	COLORREF playerOneColor = pApp->GetProfileInt(_T("Settings"),
	                          _T("playerOneColor"), PenteBoard::DEFAULT_PLAYER_ONE_COLOR);
	COLORREF playerTwoColor = pApp->GetProfileInt(_T("Settings"),
	                          _T("playerTwoColor"), PenteBoard::DEFAULT_PLAYER_TWO_COLOR);

	bmPlayerOne.setColor(playerOneColor);
	bmPlayerTwo.setColor(playerTwoColor);

	return 0;
}
