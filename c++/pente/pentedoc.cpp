// pentedoc.cpp : implementation of the PenteDoc class
//
#include "stdafx.h"
#include "pente.h"
#include "pentedoc.h"
#include "ColorsDlg.h"

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
	ON_UPDATE_COMMAND_UI(IDM_OPTIONS, OnUpdateOptions)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDS_TURN, onUpdateTurn)
	ON_COMMAND(ID_TOOLS_COLORS, &PenteDoc::OnToolsColors)
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
	if (!game.addPiece(square.x, square.y))
		return false;
	
	SetModifiedFlag();

	UpdateAllViews(NULL, MAKELONG(square.x, square.y), game.getBoard());

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool PenteDoc::move(CPoint & square)
{
	if (!game.move(square))
		return false;

	SetModifiedFlag();

	UpdateAllViews(NULL, MAKELONG(square.x, square.y), game.getBoard());

	return true;
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

void PenteDoc::OnToolsColors()
{
	CColorsDlg dlg;
	if (IDOK == dlg.DoModal()) {
		UpdateAllViews(NULL);
	}
}
