// pentedoc.cpp : implementation of the PenteDoc class
//
#include "stdafx.h"
#include "pente.h"
#include "pentedoc.h"
#include "SettingsSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PenteDoc

IMPLEMENT_DYNCREATE(PenteDoc, CDocument)

BEGIN_MESSAGE_MAP(PenteDoc, CDocument)
    //{{AFX_MSG_MAP(PenteDoc)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
    //}}AFX_MSG_MAP
    ON_UPDATE_COMMAND_UI(IDS_TURN, onUpdateTurn)
    ON_COMMAND(ID_TOOLS_SETTINGS, &PenteDoc::OnToolsSettings)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PenteDoc construction/destruction

PenteDoc::PenteDoc()
{
}

PenteDoc::~PenteDoc()
{
}

BOOL PenteDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// PenteDoc serialization

void PenteDoc::Serialize(CArchive& ar)
{
    game.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// PenteDoc diagnostics

#ifdef _DEBUG
void PenteDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void PenteDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// PenteDoc commands

bool PenteDoc::addPiece(const CPoint & square)
{
    CaptureVec captures;
    if (!game.addPiece(square.x, square.y, captures))
        return false;

    updateBoard(square, captures);

    return true;
}

/////////////////////////////////////////////////////////////////////////////
bool PenteDoc::checkWinner()
{
    uint32_t winner;
    const Vector *vector;

    uint32_t playerOneCaptures = game.getPlayerOne()->getCaptures();
    uint32_t playerTwoCaptures = game.getPlayerTwo()->getCaptures();

    if ((vector = game.winner(winner)) != NULL ||
            playerOneCaptures == Player::MAX_CAPTURES ||
            playerTwoCaptures == Player::MAX_CAPTURES) {

        if (vector != NULL) {
            UpdateAllViews(NULL); // winning vector
        }

        if (vector == NULL && playerOneCaptures == Player::MAX_CAPTURES)
            winner = ET_PLAYER_ONE;
        if (vector == NULL && playerTwoCaptures == Player::MAX_CAPTURES)
            winner = ET_PLAYER_TWO;

        SetModifiedFlag(FALSE);
        CString message = (winner == ET_PLAYER_ONE) ?
                          _T("Player One Wins!") : _T("Player Two Wins!");
        message += _T("\nPlay Again?");

        int nRtn = AfxMessageBox(message,
                                 MB_YESNO | MB_ICONQUESTION);
        if (nRtn == IDNO) {
            AfxGetMainWnd()->PostMessage(WM_CLOSE);
        } else {
            AfxGetApp()->OnCmdMsg(ID_FILE_NEW, 0, 0, 0);
            UpdateAllViews(NULL);
        }
        return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////
bool PenteDoc::move(CPoint & square)
{
    CaptureVec captures;
    if (!game.move(square, captures))
        return false;

    updateBoard(square, captures);

    return true;
}

void PenteDoc::updateBoard(const CPoint& square, const CaptureVec& captures)
{
    SetModifiedFlag();
    UpdateAllViews(NULL, MAKELONG(square.x, square.y), game.getBoard());

    CaptureVec::const_iterator it = captures.begin();
    for ( ; it != captures.end(); it++) {
        const Capture &capture = *it;
        const POINT &pt1 = capture.getPoint1();
        const POINT &pt2 = capture.getPoint2();

        UpdateAllViews(NULL, MAKELONG(pt1.x, pt1.y), game.getBoard());
        UpdateAllViews(NULL, MAKELONG(pt2.x, pt2.y), game.getBoard());
    }

    checkWinner();
}

void PenteDoc::DeleteContents()
{
    game.clear();
    CDocument::DeleteContents();
}

/////////////////////////////////////////////////////////////////////////////
void PenteDoc::onUpdateTurn(CCmdUI *pCmdUI)
{
    CString str, strTurn;
    ASSERT(pCmdUI != NULL);
    uint32_t turn = game.getTurn();
    str.Format(IDS_TURN, turn == ET_PLAYER_ONE ?
               _T("One") : _T("Two"));
    pCmdUI->SetText(str);
    CStatusBar* pBar = (CStatusBar*)pCmdUI->m_pOther;
    ASSERT_VALID(pBar);
    UINT id, style;
    int width;
    pBar->GetPaneInfo(2, id, style, width);
    width = getTextWidth(pBar, str);
    pBar->SetPaneInfo(2, id, style, width);
}

/////////////////////////////////////////////////////////////////////////////
void PenteDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    ASSERT(pCmdUI != NULL);
    pCmdUI->Enable(IsModified());
}

BOOL PenteDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    WORD number;
    try {
        CFile file(lpszPathName, CFile::modeRead);
        file.Read(&number, sizeof(WORD));
        file.Close();
    } catch (CFileException *E) {
        E->ReportError(MB_ICONINFORMATION | MB_OK);
        E->Delete();
        return FALSE;
    }

    if (number != PenteGame::getFileMagicNumber()) {
        AfxMessageBox(IDS_INVALIDFILEFORMAT, MB_ICONINFORMATION | MB_OK);
        return FALSE;
    }

    return CDocument::OnOpenDocument(lpszPathName);
}

/////////////////////////////////////////////////////////////////////////////
void PenteDoc::OnUpdateOptions(CCmdUI* pCmdUI)
{
    ASSERT(pCmdUI != NULL);
    pCmdUI->Enable(!IsModified());
}

void PenteDoc::OnToolsSettings()
{
    SettingsSheet sheet(IDS_SETTINGS, AfxGetMainWnd());
    sheet.DoModal();
}


