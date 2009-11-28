// ScoreView.cpp : implementation of the ScoreView class
//

#include "stdafx.h"
#include "baseinc.h"
#include "ScoreDoc.h"
#include "ScoreView.h"
#include "score.h"
#include "ToolboxDlg.h"
#include "neptune.h"
#include "TempoDlg.h"
#include "keysigdg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ScoreView

IMPLEMENT_DYNCREATE (ScoreView, CScrollView)

ScoreView::ScoreView()
{
	m_Tool.button = IDC_QUARTERNOTE;
	m_Tool.icon = IDI_QUARTERNOTE;
	m_Tool.cursor = IDC_QNOTE;
	m_Tool.user = QuarterNote;
}

ScoreView::~ScoreView()
{
}

BEGIN_MESSAGE_MAP(ScoreView, CScrollView)
	//{{AFX_MSG_MAP(ScoreView)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(IDM_PLAYMEASURE, OnUpdatePlayMeasure)
	ON_COMMAND(IDM_PLAYMEASURE, OnPlayMeasure)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(IDM_PLAYALL, OnPlayAll)
	ON_UPDATE_COMMAND_UI(IDM_PLAYALL, OnUpdatePlayAll)
	ON_COMMAND(IDM_SETMEASURETEMPO, OnSetMeasureTempo)
	ON_UPDATE_COMMAND_UI(IDM_SETMEASURETEMPO, OnUpdateSetMeasureTempo)
	ON_COMMAND(IDM_TOOLBOX, OnToolbox)
	ON_COMMAND(IDM_KEYSIGNATURE, OnKeySignature)
	ON_UPDATE_COMMAND_UI(IDM_KEYSIGNATURE, OnUpdateKeySignature)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(IDM_SELECT, IDM_ERASENOTE, OnUpdateMode)
	ON_COMMAND_RANGE(IDM_SELECT, IDM_ERASENOTE, OnMode)
END_MESSAGE_MAP()

#ifdef _DEBUG
ScoreDoc* ScoreView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ScoreDoc)));
	return (ScoreDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ScoreView message handlers

BOOL ScoreView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CView::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
	                                   ::LoadCursor(NULL, IDC_ARROW), NULL, NULL);

	return TRUE;
}

//
// OnDraw
//
void ScoreView :: OnDraw(CDC* pDC)
{
	GetDocument()->GetStaff()->Render(pDC);
}

//
// SetTool
//
void ScoreView :: SetTool(Tool * pTool)
{
	ASSERT(pTool != NULL);

	m_Tool = *pTool;
}

//
// OnEraseBkgnd
//
BOOL ScoreView :: OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(rc);

	pDC->FillSolidRect(rc, COLOR_WHITE);

	return CView::OnEraseBkgnd(pDC);
}

//
// OnLButtonDown
//
void ScoreView :: OnLButtonDown(UINT nFlags, CPoint point)
{
	ScoreApp * pApp = (ScoreApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	ScoreDoc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	const Staff * pStaff = pDoc->GetStaff();
	ASSERT(pStaff != NULL);

	DPtoLP(point);

	Measure * pMeasure = pStaff->GetMeasure(point);
	if (pMeasure == NULL)
		return;

	// Move the note on the measure
	if (m_nMode == IDM_SELECT) {
		Note * pNote = pMeasure->GetNote(point);
		if (pNote != NULL) {
			m_pSelectedNote = pNote;
			m_ptPrev = m_pSelectedNote->GetPos();
			SetCapture();
		}
	}
	// Add / modify a note on the measure
	else if (m_nMode == IDM_ADDNOTE) {
		if (m_Tool.type == NoteTool)
			AddNote(pMeasure, point);
		else if (m_Tool.type == ModifierTool) {
			Note * pNote = pMeasure->GetNote(point);
			if (pNote != NULL)
				pDoc->ModifyNote(pMeasure, pNote, m_Tool);
		}
	}
	// Erase a note
	else if (m_nMode == IDM_ERASENOTE) {
		Note * pNote = pMeasure->GetNote(point);
		if (pNote != NULL)
			pDoc->RemoveNote(pMeasure, pNote);
	}

	CScrollView :: OnLButtonDown(nFlags, point);
}

//
// OnLButtonUP
//
void ScoreView :: OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd * pWnd = CWnd::GetCapture();
	if (pWnd == NULL || *pWnd != *this)
		return;

	DPtoLP(point);

	ScoreApp * pApp = (ScoreApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	const Staff * pStaff = GetDocument()->GetStaff();
	ASSERT(pStaff != NULL);

	// Have we selected a note?
	if (m_pSelectedNote != NULL) {
		// Invalidate the previous note
		Note note;
		note.SetPos(m_ptPrev);
		InvalidateNote(&note);

		// Move the selected note
		PANCHOR pAnchor= pStaff->GetAnchor(point);
		if (pAnchor != NULL) {
			CPoint pt;
			pt.x = m_ptPrev.x;
			pt.y = pAnchor->cy;
			InvalidateNote(m_pSelectedNote);
			m_pSelectedNote->SetPos(pt);
			m_pSelectedNote->SetData(pAnchor->data);
			m_pSelectedNote->SetName(pAnchor->name);
			m_pSelectedNote->SetModifier(NULL);
			InvalidateNote(m_pSelectedNote);
			GetDocument()->SetModifiedFlag();
		}
		m_pSelectedNote = NULL;
		memset(&m_ptPrev, 0, sizeof(CPoint));
	}
	// Are we playing a note?
	else if (m_pLastNote != NULL) {
		pApp->ReleaseNote(m_pLastNote);
		m_pLastNote;
	}

	ReleaseCapture();

	CScrollView::OnLButtonUp(nFlags, point);
}

//
// InvalidateNote
//
void ScoreView :: InvalidateNote(const Note * pNote)
{
	ASSERT(pNote != NULL);

	CClientDC dc(this);
	OnPrepareDC(&dc);

	CRect rc, rcModifier;
	pNote->GetRect(rc);
	pNote->GetModifierRect(rcModifier);

	rc.UnionRect(rc, rcModifier);

	dc.LPtoDP(rc);

	if (dc.RectVisible(rc)) {
		InvalidateRect(&rc);
	}
}

//
// OnSetCursor
//
BOOL ScoreView :: OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CPoint pt;
	GetCursorPos(&pt);
	DPtoLP(pt);
	ScreenToClient(&pt);

	const Staff * pStaff = GetDocument()->GetStaff();
	ASSERT(pStaff != NULL);

	if (m_nMode != IDM_SELECT && pStaff->GetMeasure(pt) != NULL) {
		UINT cursor = m_nMode == IDM_ADDNOTE ? m_Tool.cursor : IDC_ERASENOTE;
		HCURSOR hCursor = (HCURSOR)Neptune::LoadImage(cursor, IMAGE_CURSOR);
		ASSERT(hCursor != NULL);
		::SetCursor(hCursor);

		return TRUE;
	}

	return CScrollView :: OnSetCursor(pWnd, nHitTest, message);
}

//
// OnToolbox
//
void ScoreView :: OnToolbox()
{
	if (CWnd::FindWindow(NULL, "Toolbox") != NULL)
		return; // Existing toolbox window

	ToolboxDlg * pDlg = new ToolboxDlg(this);
	ASSERT_VALID(pDlg);

	pDlg->Create(IDD_TOOLBOX);
	pDlg->ShowWindow(SW_SHOW);
	pDlg->UpdateWindow();
}

//
// OnInitialUpdate
//
void ScoreView :: OnInitialUpdate()
{
	CScrollView :: OnInitialUpdate();

	m_pLastNote = NULL;
	m_nMode = IDM_SELECT;
	m_Tool.type = NoteTool;
	m_Tool.button = IDC_QUARTERNOTE;
	m_Tool.icon = IDI_QUARTERNOTE;
	m_Tool.cursor = IDC_QNOTE;
	m_Tool.user = QuarterNote;
	m_pSelectedNote = NULL;
	m_pSelectedMeasure = NULL;
	m_ptPrev.x = 0;
	m_ptPrev.y = 0;

	const Staff * pStaff = GetDocument()->GetStaff();
	ASSERT(pStaff != NULL);

	int cx = borderOffset + pStaff->Width();
	SetScrollSizes(MM_TEXT, CSize(cx, 100));
}

//
// OnMouseMove
//
void ScoreView :: OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd * pWnd = CWnd::GetCapture();
	if (!pWnd || *pWnd != *this || !m_pSelectedNote)
		return;

	DPtoLP(point);

	// Invalidate the previous move
	Note note = *m_pSelectedNote;
	note.SetPos(m_ptPrev);
	InvalidateNote(&note);
	UpdateWindow();

	// Set the new position and render the note
	m_ptPrev.y = point.y;
	note.SetPos(m_ptPrev);

	CClientDC dc(this);
	OnPrepareDC(&dc);
	note.Render(&dc);

	CScrollView :: OnMouseMove(nFlags, point);
}

//
// OnContextMenu
//
void ScoreView :: OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	if (m_nMode != IDM_SELECT)
		return; // Only accept a context menu with selection

	ScreenToClient(&point);

	CMenu menu;
	menu.LoadMenu(IDR_CONTEXTMENU);

	CMenu * pSubMenu = menu.GetSubMenu(0);
	ASSERT_VALID(pSubMenu);

	ClientToScreen(&point);

	pSubMenu->TrackPopupMenu(
	    TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
	    point.x, point.y,
	    GetParentFrame());
}

//
// OnUpdatePlayMeasure
//
void ScoreView :: OnUpdatePlayMeasure(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI != NULL);

	ScoreApp * pApp = (ScoreApp *)AfxGetApp();
	ASSERT_VALID(pApp);

	if (m_pSelectedMeasure != NULL)
		pCmdUI->Enable(m_pSelectedMeasure->HasData() && !pApp->IsPlaying());
	else pCmdUI->Enable(FALSE);
}

//
// DPtoLP
//
void ScoreView :: DPtoLP(CPoint & pt)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);

	dc.DPtoLP(&pt);
}

//
// OnPlayMeasure
//
void ScoreView :: OnPlayMeasure()
{
	CWaitCursor cursor;

	ASSERT(m_pSelectedMeasure != NULL);

	ScoreApp * pApp = (ScoreApp*)AfxGetApp();
	pApp->PlayMeasure(m_pSelectedMeasure);
}

//
// OnLButtonDblClk
//
void ScoreView :: OnLButtonDblClk(UINT /*nFlags*/, CPoint point)
{
	if (m_nMode != IDM_SELECT)
		return; // Only accept a selection with select

	DPtoLP(point);

	const Staff * pStaff = GetDocument()->GetStaff();
	ASSERT(pStaff != NULL);

	m_pSelectedMeasure = pStaff->GetMeasure(point);

	// Select the measure
	GetDocument()->SelectMeasure(m_pSelectedMeasure);
}

//
// OnUpdateMode
//
void ScoreView :: OnUpdateMode(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI != NULL);

	pCmdUI->SetRadio(pCmdUI->m_nID == m_nMode);
}

//
// OnMode
//
void ScoreView :: OnMode(UINT nID)
{
	m_nMode = nID;
}

//
// OnPlayAll
//
void ScoreView :: OnPlayAll()
{
	ScoreApp * pApp = (ScoreApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->PlayStaff(GetDocument()->GetStaff());
}

//
// OnUpdatePlayAll
//
void ScoreView :: OnUpdatePlayAll(CCmdUI* pCmdUI)
{
	ScoreApp * pApp = (ScoreApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pCmdUI->Enable(!pApp->IsPlaying());
}

//
// OnSetMeasureTempo
//
void ScoreView :: OnSetMeasureTempo()
{
	TempoDlg dlg(m_pSelectedMeasure, this);

	if (dlg.DoModal() == IDOK)
		GetDocument()->SetModifiedFlag();
}

//
// OnUpdateSetMeasureTempo
//
void ScoreView :: OnUpdateSetMeasureTempo(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI != NULL);

	pCmdUI->Enable(m_pSelectedMeasure != NULL);
}

//
// OnUpdate
//
void ScoreView :: OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (pHint != NULL) {
		CClientDC dc(this);
		OnPrepareDC(&dc);

		CRect rc;
		switch (lHint) {
		case measureHint:
			((Measure *)pHint)->Render(&dc);
			GetDocument()->GetStaff()->Render(&dc);
			break;
		case noteHint:
			((Note *)pHint)->Render(&dc);
			break;
		case modifierHint:
			((Note *)pHint)->GetModifierRect(rc);
			rc.OffsetRect(-GetScrollPosition());
			InvalidateRect(rc);
		default:
			break;
		}
	} else CScrollView :: OnUpdate(pSender, lHint, pHint);
}

//
// AddNote
//
BOOL ScoreView :: AddNote(Measure * pMeasure, const CPoint & pt)
{
	ASSERT_VALID(pMeasure);

	PANCHOR pAnchor = pMeasure->GetStaff()->GetAnchor(pt);
	ASSERT(pAnchor != NULL);

	Note * pNote = new Note();
	ASSERT(pNote != NULL);

	pNote->SetIcon((HICON)Neptune::LoadImage(m_Tool.icon, IMAGE_ICON));
	pNote->SetData(pAnchor->data);
	pNote->SetName(pAnchor->name);
	pNote->SetPos(CPoint(pt.x, pAnchor->cy));
	pNote->SetDuration(Duration(m_Tool.user));

	// Attempt to add the note to the document
	if (GetDocument()->AddNote(pMeasure, pNote)) {
		ScoreApp * pApp = (ScoreApp *)AfxGetApp();
		ASSERT_VALID(pApp);
		pApp->PlayNote(pNote);
		m_pLastNote = pNote;
		SetCapture();
		return TRUE;
	}

	delete pNote;

	return FALSE;
}

//
// OnKeySignature
//
void ScoreView :: OnKeySignature()
{
	KeySignatureDlg dlg(m_pSelectedMeasure, this);

	if (dlg.DoModal() == IDOK) {
		GetDocument()->UpdateAllViews(NULL,
		                              0, NULL);
		GetDocument()->SetModifiedFlag();
	}
}

//
// OnUpdateKeySignature
//
void ScoreView::OnUpdateKeySignature(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI != NULL);

	pCmdUI->Enable(m_pSelectedMeasure != NULL);
}

