/*---------------------------------------
	Module Name	:	PenteDoc.cpp
	Author		:	Thomas A. Rieck
	Purpose		:	Pente Document
					Module
	Date		:	08/21/1997
---------------------------------------*/

#include "stdafx.h"
#include "PenteDoc.h"
#include "PenteApp.h"
#include "MainFrame.h"
#include "PrefDlg.h"
#include "ColorPage.h"
#include "PlayerNamesDlg.h"
#include "Think\capture.h"
#include "Think\fiverow.h"
#include "Think\compmov.h"
#include "ResDll\resource.h"
#include "OurConstants.h"

IMPLEMENT_SERIAL(CPenteDoc, CDocument, 1)

BEGIN_MESSAGE_MAP(CPenteDoc, CDocument)
	ON_COMMAND(IDM_PREFERENCES, OnPreferences)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(IDS_PLAYERTURN, OnUpdatePlayerTurn)
	ON_UPDATE_COMMAND_UI(IDS_PLAYERONECAPTURES, OnUpdatePlayerOneCaptures)
	ON_UPDATE_COMMAND_UI(IDS_PLAYERTWOCAPTURES, OnUpdatePlayerTwoCaptures)
END_MESSAGE_MAP()

// initialize static member data, this is equivalent to 'PT'
short CPenteDoc::m_nFileMarker = 0x5450;

///////////////////////////////////////////////////////////////////
// CPenteDoc construction/destruction

CPenteDoc::CPenteDoc()
{
	// Initialize variables
	m_nPlayMode	= PLAYER_VS_COMPUTER;
	m_pSquares	= new SQUARE[19][19];
	VERIFY(m_pSquares);

	m_rcBoard.SetRect(0, 0, SQUARE_WIDTH * 19, SQUARE_HEIGHT * 19);

	m_lGridColor	= ::GetSysColor(COLOR_WINDOWTEXT);
	m_lBackColor	= ::GetSysColor(COLOR_APPWORKSPACE);

	m_strPlayerOneName	= _T("");
	m_strPlayerTwoName	= _T("");

	LPDWORD lpdwValue;
	if (CPenteApp::GetRegistryInformation(_T("option"), _T("UseBackColor"), (PPBYTE)&lpdwValue, REG_DWORD)) {
		m_fUseBackColor = (*lpdwValue == 1);
		delete lpdwValue;
	}

	// Set the icon resources
	SetPlayerOneRes(IDI_GREENBALL);
	SetPlayerTwoRes(IDI_REDBALL);
}

VOID CPenteDoc::SetPlayerOneRes(INT nRes)
{
	ASSERT(nRes);

	m_nPlayerOneRes = nRes;

	// Set Player Icon
	m_hPlayerOneIcon = (HICON)LoadImage(AfxGetResourceHandle(),
	                                    MAKEINTRESOURCE(m_nPlayerOneRes),
	                                    IMAGE_ICON,
	                                    PIECE_WIDTH,
	                                    PIECE_HEIGHT,
	                                    LR_SHARED);
	ASSERT(m_hPlayerOneIcon);
}

VOID CPenteDoc::SetPlayerTwoRes(INT nRes)
{
	ASSERT(nRes);

	m_nPlayerTwoRes = nRes;

	m_hPlayerTwoIcon = (HICON)LoadImage(AfxGetResourceHandle(),
	                                    MAKEINTRESOURCE(m_nPlayerTwoRes),
	                                    IMAGE_ICON,
	                                    PIECE_WIDTH,
	                                    PIECE_HEIGHT,
	                                    LR_SHARED);
	ASSERT(m_hPlayerTwoIcon);
}

VOID CPenteDoc::Initialize()
{
	m_nCurrentTurn			= PLAYER_ONE_TURN;
	m_nPlayerOneCaptures	= 0;
	m_nPlayerTwoCaptures	= 0;

	memset(m_pSquares, 0, sizeof(SQUARE) * (19 * 19));

	// set Square dimensions
	SetSquares();
}

CPenteDoc::~CPenteDoc()
{
	if (m_pSquares)	delete []m_pSquares;
}

///////////////////////////////////////////////////////////////////
// CPenteDoc::OnNewDocument()

BOOL CPenteDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) {
		return FALSE;
	}

	CPlayerNamesDlg dlg(this);
	if (dlg.DoModal() != IDOK) {
		CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
		if (pFrame) {
			if (::IsWindow(pFrame->GetSafeHwnd())) {
				pFrame->DestroyWindow();
			}
		}
		return FALSE;
	}

	// Update the views
	UpdateAllViews(NULL);

	return TRUE;
}

VOID CPenteDoc::DeleteContents()
{
	Initialize();
}

BOOL CPenteDoc::IsValidDocument(CString& cs)
{
	CFile f;
	short nData;

	TRY {

		f.Open(cs, CFile::modeRead | CFile::shareExclusive);
	}
	CATCH (CFileException, e) {
		CString csError;
		ASSERT(csError.LoadString(IDS_FILEERROR));
		AfxMessageBox(csError, MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	END_CATCH

	// Ensure this is a Pente game
	f.Read(&nData, sizeof(nData));

	f.Close();

	return (nData == CPenteDoc::m_nFileMarker);
}

VOID CPenteDoc::Serialize(CArchive& ar)
{
	INT		nPlayerOneRes, nPlayerTwoRes;
	short	nTemp;

	if (ar.IsStoring()) {
		ar	<< CPenteDoc::m_nFileMarker
		    << m_lBackColor
		    << m_lGridColor
		    << m_nPlayMode
		    << m_nCurrentTurn
		    << m_nPlayerOneCaptures
		    << m_nPlayerTwoCaptures
		    << m_nPlayerOneRes
		    << m_nPlayerTwoRes;

		for (int i = 0, j = 0; i < 19; j++) {
			ar	<< m_pSquares[i][j].bPiece
			    << m_pSquares[i][j].rcDims;
			if (j == 18) {
				i++;
				j = -1;
			}
		}
	} else {
		ar	>> nTemp
		    >> m_lBackColor
		    >> m_lGridColor
		    >> m_nPlayMode
		    >> m_nCurrentTurn
		    >> m_nPlayerOneCaptures
		    >> m_nPlayerTwoCaptures
		    >> nPlayerOneRes
		    >> nPlayerTwoRes;

		for (int i = 0, j = 0; i < 19; j++) {
			ar	>> m_pSquares[i][j].bPiece
			    >> m_pSquares[i][j].rcDims;
			if (j == 18) {
				i++;
				j = -1;
			}
		}
		SetPlayerOneRes(nPlayerOneRes);
		SetPlayerTwoRes(nPlayerTwoRes);
		UpdateAllViews(NULL);
	}
}

VOID CPenteDoc::SetSquares()
{
	if (!m_pSquares)
		return;

	// Set square dimensions
	for (int i = 0, j = 0; i < 19; j++) {
		m_pSquares[i][j].bPiece	= 0;
		m_pSquares[i][j].rcDims.SetRect(
		    i * SQUARE_WIDTH,
		    j * SQUARE_HEIGHT,
		    (i + 1) * SQUARE_WIDTH,
		    (j + 1) * SQUARE_HEIGHT);
		if (j == 18) {
			i++;
			j=-1;
		}
	}
}

// CPenteDoc::WhichSquare()

// Determines if the given point
// lies within a board square.  If so
// it returns the appropriate index
BOOL CPenteDoc::WhichSquare (CPoint& ptOld, CPoint* pNewPoint)
{
	pNewPoint->x = -1;
	pNewPoint->y = -1;

	for (int i = 0, j = 0; i < 19; j++) {
		if (m_pSquares[i][j].rcDims.PtInRect(ptOld) &&
		        m_pSquares[i][j].bPiece == 0) {
			pNewPoint->x = i;
			pNewPoint->y = j;
			return TRUE;
		}
		if (j == 18) {
			i++;
			j=-1;
		}
	}
	return FALSE;
}

BOOL CPenteDoc::MarkPiece(CPoint& pt)
{
	INT i,j;

	if (pt.x < 0 || pt.x > 18 ||
	        pt.y < 0 || pt.y > 18)
		return FALSE;

	i = pt.x;
	j = pt.y;


	m_pSquares[i][j].bPiece = m_nCurrentTurn;

	return TRUE;
}

VOID CPenteDoc::RenderData(CDC* pDC)
{
	INT		nSavedDC;
	HICON	hIcon;

	nSavedDC = pDC->SaveDC();

	pDC->SetViewportOrg(SQUARE_WIDTH, SQUARE_HEIGHT);

	for (int i = 0, j = 0; i < 19; j++) {
		if (m_pSquares[i][j].bPiece != 0) {
			hIcon = m_pSquares[i][j].bPiece == PLAYER_ONE_TURN ?
			        m_hPlayerOneIcon : m_hPlayerTwoIcon;

			::DrawIconEx(pDC->GetSafeHdc(),
			             m_pSquares[i][j].rcDims.left + ICON_HOFFSET,
			             m_pSquares[i][j].rcDims.top + ICON_VOFFSET,
			             hIcon,
			             PIECE_WIDTH,
			             PIECE_HEIGHT,
			             0,
			             NULL,
			             DI_NORMAL);
		}
		if (j == 18) {
			i++;
			j=-1;
		}
	}

	pDC->RestoreDC(nSavedDC);
}

VOID CPenteDoc::OnPreferences()
{
	BeginWaitCursor();

	CPrefDlg dlg(IDS_PREFERENCES, AfxGetMainWnd(), 0);

	// Initialize the dialog and
	// build property pages
	dlg.Init();

	if (dlg.DoModal() == IDOK) {
		SetModifiedFlag();
	}

	EndWaitCursor();
}

VOID CPenteDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI);

	pCmdUI->Enable(IsModified());
}

VOID CPenteDoc::OnUpdatePlayerOptions(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI);

	pCmdUI->Enable(!IsModified());
}

VOID CPenteDoc::OnUpdatePlayerTurn(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI);

	pCmdUI->Enable();

	CString strTurn;
	strTurn.Format(IDS_PLAYERTURN, m_nCurrentTurn == PLAYER_ONE_TURN ?
	               _T("One") : _T("Two"));

	pCmdUI->SetText(strTurn);
}

VOID CPenteDoc::OnUpdatePlayerOneCaptures(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI);

	pCmdUI->Enable();

	CString strCaptures;

	strCaptures.Format(IDS_PLAYERONECAPTURES, m_nPlayerOneCaptures);

	pCmdUI->SetText(strCaptures);
}

VOID CPenteDoc::OnUpdatePlayerTwoCaptures(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI);

	pCmdUI->Enable();

	CString strCaptures;

	strCaptures.Format(IDS_PLAYERTWOCAPTURES, m_nPlayerTwoCaptures);

	pCmdUI->SetText(strCaptures);
}


BOOL CPenteDoc::GetSquareDims(CPoint& pt, CRect* pRect)
{
	ASSERT(pRect);

	if (pt.x < 0 || pt.x > 18 ||
	        pt.y < 0 || pt.y > 18)
		return FALSE;

	pRect->CopyRect(&(m_pSquares[pt.x][pt.y].rcDims));

	return TRUE;
}

UINT CPenteDoc::CheckCapture(LPPOINT ppt)
{

	INT nRtn;
	INT	(*pBoard)[19];

	if (!CopyBoardToDLLFormat((PPVOID)&pBoard)) {
		return 0;
	}

	ASSERT(pBoard);
	nRtn = ::CheckCapture(pBoard, ppt, m_nCurrentTurn);

	if (nRtn) {	// We have a capture!
		// Copy the board back into our data member
		CopyBoardFromDLLFormat(pBoard);

		// Add the captures
		AddCapture(nRtn);
	}
	delete []pBoard;

	return (UINT)nRtn;
}

BOOL CPenteDoc::CopyBoardToDLLFormat(PPVOID ppData)
{
	VERIFY(ppData);

	// Initialize 'Out' parameter
	*ppData = NULL;

	// Allocate an appropriate structure
	INT	(*pBoard)[19];
	pBoard = new INT[19][19];
	if (!pBoard)
		return FALSE;

	for (int i = 0, j = 0; i < 19; j++) {
		pBoard[i][j] = m_pSquares[i][j].bPiece;

		if (j == 18) {
			i++;
			j=-1;
		}
	}

	*ppData = pBoard;

	return TRUE;
}

BOOL CPenteDoc::CopyBoardFromDLLFormat(INT pBoard[][19])
{
	VERIFY(pBoard);

	for (int i = 0, j = 0; i < 19; j++) {
		m_pSquares[i][j].bPiece = pBoard[i][j];

		if (j == 18) {
			i++;
			j=-1;
		}
	}

	return TRUE;
}

BOOL CPenteDoc::CheckWinByCapture()
{
	return (m_nCurrentTurn == PLAYER_ONE_TURN ?
	        m_nPlayerOneCaptures == 5 :
	        m_nPlayerTwoCaptures == 5);
}

UINT CPenteDoc::CheckFiveInARow(CPoint& pt)
{
	INT nRtn;
	INT	(*pBoard)[19];

	// Check for win by five in a row
	if (!CopyBoardToDLLFormat((PPVOID)&pBoard))
		return 0;

	ASSERT(pBoard);
	nRtn = ::CheckFiveInARow(pBoard, pt, m_nCurrentTurn);

	delete []pBoard;

	return (UINT)nRtn;
}

VOID CPenteDoc::ChangeTurns()
{
	m_nCurrentTurn = (m_nCurrentTurn == PLAYER_ONE_TURN ?
	                  PLAYER_TWO_TURN : PLAYER_ONE_TURN);
}

VOID CPenteDoc::AddCapture(UINT nCount)
{
	m_nCurrentTurn == PLAYER_ONE_TURN ?
	m_nPlayerOneCaptures +=nCount  : m_nPlayerTwoCaptures += nCount;
}

BOOL CPenteDoc::CanCloseFrame(CFrameWnd* pFrame)
{
	CString			cs;
	DWORD			dwStyle;
	BOOL			fRtn;

	if (!IsModified())
		return CDocument::CanCloseFrame(pFrame);;

	cs.Format(IDS_CLOSEDOC, GetTitle());

	dwStyle	= MB_USERICON | MB_YESNOCANCEL;

	int nRtn = AfxMessageBox(cs, dwStyle);
	if (nRtn == IDYES) {
		fRtn = CDocument::DoFileSave();
	} else if (nRtn == IDCANCEL) {
		return FALSE;
	}

	return TRUE;
}

VOID CPenteDoc::ComputerMove()
{
	INT		(*pBoard)[19];
	INT		nCaptures;
	CPoint	pt;
	CRect	rc;

	CPenteApp * pApp = (CPenteApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	CMainFrame * pFrame = (CMainFrame*)pApp->GetMainWnd();
	ASSERT_VALID(pFrame);

	if (!CopyBoardToDLLFormat((PPVOID)&pBoard)) {
		return;
	}

	VERIFY(pBoard);

	// Move computer piece on board
	BOOL fRtn = ::ComputerMove(pBoard, &pt, &nCaptures, pApp->m_fEnableDebug);
	if (fRtn) {
		// Copy the board data back
		CopyBoardFromDLLFormat(pBoard);

		if (nCaptures > 0) {
			// We have a capture
			AddCapture(nCaptures);
			pApp->PlayWave(MAKEINTRESOURCE(IDR_BLIP), SND_ASYNC | SND_MEMORY);
			UpdateAllViews(NULL);
		} else {
			// Play 'piece' sound
			pApp->PlayWave(MAKEINTRESOURCE(IDR_PIECE), SND_ASYNC | SND_MEMORY);

			// Invalidate the piece
			GetSquareDims(pt, &rc);
			pFrame->GetActiveView()->InvalidateRect(&rc, FALSE);
		}

		if (!CheckWinByCapture() && !CheckFiveInARow(pt)) {
			// Display new player turn
			ChangeTurns();
			SetModifiedFlag();
		} else {
			// Ensure our status window is updated
			pFrame->GetStatusBar()->OnUpdateCmdUI(pFrame, FALSE);

			// We don't want to save a finished game
			SetModifiedFlag(FALSE);

			pApp->DoFinish();
		}
	}

	delete []pBoard;
}

///////////////////////////////////////////////////////////////////



