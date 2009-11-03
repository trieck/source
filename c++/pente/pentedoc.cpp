// pentedoc.cpp : implementation of the PenteDoc class
//
#include "stdafx.h"
#include "pente.h"
#include "pentedoc.h"
#include "timer.h"
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
	ON_COMMAND(IDM_BOARDBKGCOLOR, OnBoardbkgcolor)
	ON_COMMAND(IDM_GRIDCOLOR, OnGridColor)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(IDM_OPTIONS, OnUpdateOptions)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDS_TURN, onUpdateTurn)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// PenteDoc construction/destruction

PenteDoc::PenteDoc()
{
}

PenteDoc::~PenteDoc()
{
	PenteBoard *pBoard = game.getBoard();
	ASSERT_VALID(pBoard);
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("BoardColor"), 
		pBoard->getBackgroundColor());
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("GridColor"), 
		pBoard->getGridColor());
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
	Timer t;
	PointVec pts;
	if (!game.addPiece(square.x, square.y, pts))
		return false;
	SetModifiedFlag();
	PointVec::const_iterator it = pts.begin();
	for ( ; it != pts.end(); it++) {
		UpdateAllViews(NULL, MAKELONG((*it).x, (*it).y), 
			game.getBoard());
	}
	LOG_MESSAGE(_T("PenteDoc::addPiece took %0.2f seconds."), t.getSeconds());
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
	PenteGame::Turn turn = game.getTurn();
	str.Format(IDS_TURN, turn == PenteGame::turnPlayerOne ? 
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
void PenteDoc::OnBoardbkgcolor() 
{
	CColorDialog dlg;
	
	COLORREF rgb = game.getBoard()->getBackgroundColor();
	dlg.m_cc.Flags |= CC_RGBINIT;
	dlg.m_cc.rgbResult = rgb;
	if (dlg.DoModal() == IDOK) {
		game.getBoard()->setBackgroundColor(dlg.m_cc.rgbResult);
		UpdateAllViews(NULL);
	}
}
/////////////////////////////////////////////////////////////////////////////
void PenteDoc::OnGridColor() 
{
	CColorDialog dlg;
	
	COLORREF rgb = game.getBoard()->getGridColor();
	dlg.m_cc.Flags |= CC_RGBINIT;
	dlg.m_cc.rgbResult = rgb;
	if (dlg.DoModal() == IDOK) {
		game.getBoard()->setGridColor(dlg.m_cc.rgbResult);
		UpdateAllViews(NULL);
	}
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
