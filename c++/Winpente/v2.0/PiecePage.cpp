/*---------------------------------------
	Module Name	:	PiecePage.cpp
	Author		:	Thomas A. Rieck
	Purpose		:	Pieces Preference
					Property Page
					implementation
	Date		:	08/24/1997
---------------------------------------*/

#include "stdafx.h"
#include "PiecePage.h"
#include "MainFrame.h"
#include "OurConstants.h"

IMPLEMENT_DYNCREATE(CPiecePage, CPropertyPage)

BEGIN_MESSAGE_MAP(CPiecePage, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDC_PLAYERONEPIECE, OnPlayerOnePiece1)
	ON_COMMAND(IDC_PLAYERONEPIECE2, OnPlayerOnePiece2)
	ON_COMMAND(IDC_PLAYERONEPIECE3, OnPlayerOnePiece3)
	ON_COMMAND(IDC_PLAYERONEPIECE4, OnPlayerOnePiece4)
	ON_COMMAND(IDC_PLAYERONEPIECE5, OnPlayerOnePiece5)
	ON_COMMAND(IDC_PLAYERTWOPIECE, OnPlayerTwoPiece1)
	ON_COMMAND(IDC_PLAYERTWOPIECE2, OnPlayerTwoPiece2)
	ON_COMMAND(IDC_PLAYERTWOPIECE3, OnPlayerTwoPiece3)
	ON_COMMAND(IDC_PLAYERTWOPIECE4, OnPlayerTwoPiece4)
	ON_COMMAND(IDC_PLAYERTWOPIECE5, OnPlayerTwoPiece5)
END_MESSAGE_MAP()

// Initialize static data members
UINT CPiecePage::nRes[] = {IDI_REDBALL, IDI_GREENBALL, IDI_LTBLUEBALL,
                           IDI_PURPLEBALL, IDI_BLUEBALL
                          };
UINT CPiecePage::PlayerOneCtrls[] = {IDC_PLAYERONEPIECE, IDC_PLAYERONEPIECE2, IDC_PLAYERONEPIECE3,
                                     IDC_PLAYERONEPIECE4, IDC_PLAYERONEPIECE5
                                    };
UINT CPiecePage::PlayerTwoCtrls[] = {IDC_PLAYERTWOPIECE, IDC_PLAYERTWOPIECE2, IDC_PLAYERTWOPIECE3,
                                     IDC_PLAYERTWOPIECE4, IDC_PLAYERTWOPIECE5
                                    };

CPiecePage::CPiecePage() : CPropertyPage(CPiecePage::IDD)
{
	m_pDoc				= NULL;
	m_pCurrentPlayerOne = NULL;
	m_pCurrentPlayerTwo	= NULL;

	m_pPlayerOnePieces	= NULL;
	m_pPlayerTwoPieces	= NULL;
}

BOOL CPiecePage::OnInitDialog()
{
	CMainFrame* pFrame;
	INT			i;

	pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	ASSERT_VALID(pFrame);

	m_pDoc = (CPenteDoc*)pFrame->GetActiveDocument();
	ASSERT_VALID(m_pDoc);

	// allocate memory for data members
	m_pPlayerOnePieces = new PLAYERPIECE[5];
	ASSERT(m_pPlayerOnePieces);

	m_pPlayerTwoPieces = new PLAYERPIECE[5];
	ASSERT(m_pPlayerTwoPieces);

	// Build array for pieces
	// and frame current selections
	for (i = 0; i < 5; i++) {
		m_pPlayerOnePieces[i].pWnd = GetDlgItem((IDC_PLAYERONEPIECE)+i);
		ASSERT_VALID(m_pPlayerOnePieces[i].pWnd);

		m_pPlayerOnePieces[i].nResource = CPiecePage::nRes[i];

		m_pPlayerTwoPieces[i].pWnd = GetDlgItem((IDC_PLAYERTWOPIECE)+i);
		ASSERT_VALID(m_pPlayerTwoPieces[i].pWnd);

		m_pPlayerTwoPieces[i].nResource = CPiecePage::nRes[i];

		if (m_pPlayerOnePieces[i].nResource == m_pDoc->GetPlayerOneRes())
			m_pCurrentPlayerOne = m_pPlayerOnePieces[i].pWnd;

		if (m_pPlayerTwoPieces[i].nResource == m_pDoc->GetPlayerTwoRes())
			m_pCurrentPlayerTwo = m_pPlayerTwoPieces[i].pWnd;
	}
	return CPropertyPage::OnInitDialog();
}

VOID CPiecePage::OnOK()
{
	INT nRes;

	if (!m_pCurrentPlayerOne && !m_pCurrentPlayerTwo)
		return;

	if (m_pCurrentPlayerOne) {
		nRes = GetPieceOneResFromWnd(m_pCurrentPlayerOne);
		ASSERT(nRes);

		m_pDoc->SetPlayerOneRes(nRes);
	}

	if (m_pCurrentPlayerTwo) {
		nRes = GetPieceTwoResFromWnd(m_pCurrentPlayerTwo);
		ASSERT(nRes);

		m_pDoc->SetPlayerTwoRes(nRes);
	}
}

INT CPiecePage::GetPieceOneResFromWnd(CWnd* pWnd)
{
	ASSERT_VALID (pWnd);

	for (int i = 0; i < 5; i++) {
		if (m_pPlayerOnePieces[i].pWnd == pWnd)
			return m_pPlayerOnePieces[i].nResource;
	}

	return 0;
}

INT CPiecePage::GetPieceTwoResFromWnd(CWnd* pWnd)
{
	ASSERT_VALID (pWnd);

	for (int i = 0; i < 5; i++) {
		if (m_pPlayerTwoPieces[i].pWnd == pWnd)
			return m_pPlayerTwoPieces[i].nResource;
	}

	return 0;
}

BOOL CPiecePage::OnApply()
{
	return CPropertyPage::OnApply();
}

VOID CPiecePage::OnPaint()
{
	CPropertyPage::OnPaint();

	if (m_pCurrentPlayerOne)
		FramePlayerPiece(m_pCurrentPlayerOne, FRAME_COLOR);

	if (m_pCurrentPlayerTwo)
		FramePlayerPiece(m_pCurrentPlayerTwo, FRAME_COLOR);
}

VOID CPiecePage::FramePlayerPiece(CWnd* pWnd, COLORREF lColor)
{
	CRect		rc;
	CBrush		*pBrush;

	ASSERT_VALID(pWnd);

	CClientDC dc(pWnd);

	pWnd->GetClientRect(&rc);

	pBrush = new CBrush(lColor);
	ASSERT_VALID(pBrush);

	dc.FrameRect(&rc, pBrush);

	delete pBrush;
}

CPiecePage::~CPiecePage()
{
	if (m_pPlayerOnePieces)
		delete []m_pPlayerOnePieces;

	if (m_pPlayerTwoPieces)
		delete []m_pPlayerTwoPieces;
}

VOID CPiecePage::OnPlayerOnePiece1()
{
	CWnd* pWnd = GetDlgItem(PlayerOneCtrls[0]);
	ASSERT_VALID(pWnd);

	m_pCurrentPlayerOne = pWnd;

	RedrawPieces();

	SetModified();
}

VOID CPiecePage::OnPlayerOnePiece2()
{
	CWnd* pWnd = GetDlgItem(PlayerOneCtrls[1]);
	ASSERT_VALID(pWnd);

	m_pCurrentPlayerOne = pWnd;

	RedrawPieces();

	SetModified();
}

VOID CPiecePage::OnPlayerOnePiece3()
{
	CWnd* pWnd = GetDlgItem(PlayerOneCtrls[2]);
	ASSERT_VALID(pWnd);

	m_pCurrentPlayerOne = pWnd;

	RedrawPieces();

	SetModified();
}

VOID CPiecePage::OnPlayerOnePiece4()
{
	CWnd* pWnd = GetDlgItem(PlayerOneCtrls[3]);
	ASSERT_VALID(pWnd);

	m_pCurrentPlayerOne = pWnd;

	RedrawPieces();

	SetModified();
}

VOID CPiecePage::OnPlayerOnePiece5()
{
	CWnd* pWnd = GetDlgItem(PlayerOneCtrls[4]);
	ASSERT_VALID(pWnd);

	m_pCurrentPlayerOne = pWnd;

	RedrawPieces();

	SetModified();
}

VOID CPiecePage::OnPlayerTwoPiece1()
{
	CWnd* pWnd = GetDlgItem(PlayerTwoCtrls[0]);
	ASSERT_VALID(pWnd);

	m_pCurrentPlayerTwo = pWnd;

	RedrawPieces();

	SetModified();
}

VOID CPiecePage::OnPlayerTwoPiece2()
{
	CWnd* pWnd = GetDlgItem(PlayerTwoCtrls[1]);
	ASSERT_VALID(pWnd);

	m_pCurrentPlayerTwo = pWnd;

	RedrawPieces();

	SetModified();
}

VOID CPiecePage::OnPlayerTwoPiece3()
{
	CWnd* pWnd = GetDlgItem(PlayerTwoCtrls[2]);
	ASSERT_VALID(pWnd);

	m_pCurrentPlayerTwo = pWnd;

	RedrawPieces();

	SetModified();
}

VOID CPiecePage::OnPlayerTwoPiece4()
{
	CWnd* pWnd = GetDlgItem(PlayerTwoCtrls[3]);
	ASSERT_VALID(pWnd);

	m_pCurrentPlayerTwo = pWnd;

	RedrawPieces();

	SetModified();
}

VOID CPiecePage::OnPlayerTwoPiece5()
{
	CWnd* pWnd = GetDlgItem(PlayerTwoCtrls[4]);
	ASSERT_VALID(pWnd);

	m_pCurrentPlayerTwo = pWnd;

	RedrawPieces();

	SetModified();
}

VOID CPiecePage::RedrawPieces()
{
	UINT n, nCount = sizeof(PlayerOneCtrls) / sizeof(UINT);

	for (n = 0; n < nCount; n++) {
		CWnd * pWnd = GetDlgItem(PlayerOneCtrls[n]);
		if (pWnd == m_pCurrentPlayerOne) {
			FramePlayerPiece(pWnd, FRAME_COLOR);
		} else {
			FramePlayerPiece(pWnd, ::GetSysColor(COLOR_BTNFACE));
		}
	}

	for (n = 0; n < nCount; n++) {
		CWnd * pWnd = GetDlgItem(PlayerTwoCtrls[n]);
		if (pWnd == m_pCurrentPlayerTwo) {
			FramePlayerPiece(pWnd, FRAME_COLOR);
		} else {
			FramePlayerPiece(pWnd, ::GetSysColor(COLOR_BTNFACE));
		}
	}
}






