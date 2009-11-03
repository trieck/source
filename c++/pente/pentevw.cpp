// pentevw.cpp : implementation of the PenteView class
//
#include "stdafx.h"
#include "pente.h"
#include "pentedoc.h"
#include "pentevw.h"
#include "mainfrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PenteView

IMPLEMENT_DYNCREATE(PenteView, CView)

BEGIN_MESSAGE_MAP(PenteView, CView)
	//{{AFX_MSG_MAP(PenteView)
	ON_WM_ERASEBKGND()
	ON_WM_SETTINGCHANGE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDM_TABLECOLOR, OnTableColor)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// PenteView construction/destruction

PenteView::PenteView()
{
	bkgColor = AfxGetApp()->GetProfileInt(_T("Settings"), _T("TableColor"),
		GetSysColor(COLOR_APPWORKSPACE));
	bkgBrush.CreateSolidBrush(bkgColor);
}

PenteView::~PenteView()
{
	AfxGetApp()->WriteProfileInt(_T("Settings"), 
		_T("TableColor"), bkgColor);
}

BOOL PenteView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
// PenteView drawing

void PenteView::OnDraw(CDC* pDC)
{
	PenteDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	PenteGame *pGame = pDoc->getGame();
	ASSERT_VALID(pGame);
	CRect rc;
	GetClientRect(rc);
	// render the game
	pGame->render(pDC, rc);
}
/////////////////////////////////////////////////////////////////////////////
// PenteView printing

BOOL PenteView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void PenteView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void PenteView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
/////////////////////////////////////////////////////////////////////////////
// PenteView diagnostics

#ifdef _DEBUG
void PenteView::AssertValid() const
{
	CView::AssertValid();
}

void PenteView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

PenteDoc* PenteView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(PenteDoc)));
	return (PenteDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// PenteView message handlers

BOOL PenteView::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	pDC->SetBkMode(TRANSPARENT);
	pDC->GetClipBox(&rc);
	pDC->FillRect(&rc, &bkgBrush);
	return TRUE;
}

void PenteView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
}
/////////////////////////////////////////////////////////////////////////////
void PenteView::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CView::OnSettingChange(uFlags, lpszSection);
}
/////////////////////////////////////////////////////////////////////////////
void PenteView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PenteBoard *pBoard = GetDocument()->getGame()->getBoard();
	ASSERT_VALID(pBoard);
	if (pBoard->ptOnBoard(point)) {
		CPoint square = pBoard->getSquare(point);
		GetDocument()->addPiece(square);
	}
	
	CView::OnLButtonDown(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
void PenteView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (pHint != NULL) {
		PenteBoard *pBoard = (PenteBoard*)pHint;
		ASSERT_VALID(pBoard);
		int x = LOWORD(lHint);
		int y = HIWORD(lHint);
		CRect rc;
		pBoard->getSquareRect(x, y, rc);
		InvalidateRect(rc);
	} else CView::OnUpdate(pSender, lHint, pHint);
	// update the status bar
	PenteBar &bar = ((MainFrame*)GetParentFrame())->getPenteBar();
	bar.SendMessage(WM_IDLEUPDATECMDUI);
	bar.RedrawWindow();   
}

/////////////////////////////////////////////////////////////////////////////
void PenteView::OnTableColor() 
{
	CColorDialog dlg;
	
	dlg.m_cc.Flags |= CC_RGBINIT;
	dlg.m_cc.rgbResult = bkgColor;
	if (dlg.DoModal() == IDOK) {
		bkgColor = dlg.m_cc.rgbResult;
		bkgBrush.DeleteObject();
		bkgBrush.CreateSolidBrush(bkgColor);
		Invalidate();
	}	
}
