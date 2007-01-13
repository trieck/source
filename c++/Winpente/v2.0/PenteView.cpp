/*---------------------------------------
	Module Name	:	PenteView.cpp	
	Author		:	Thomas A. Rieck 
	Purpose		:	Pente View
					Module
	Date		:	08/21/1997
---------------------------------------*/

#include "stdafx.h"
#include "PenteView.h"
#include "PenteApp.h"
#include "ResDll\resource.h"
#include "OurMacros.h"
#include "OurConstants.h"

IMPLEMENT_DYNCREATE(CPenteView, CView)

BEGIN_MESSAGE_MAP(CPenteView, CView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////
// CPenteView construction/destruction

CPenteView::CPenteView()
{
	m_pMainFrame	= NULL;
	m_pCustomBitmap	= NULL;
	m_nBackground	= IDB_GRAIN2;
	m_hBitmap		= NULL;
	m_hPalette		= NULL;
}

CPenteView::~CPenteView()
{
	if (m_pCustomBitmap) delete m_pCustomBitmap;
	DELETEGDIOBJECT(m_hBitmap);
	DELETEGDIOBJECT(m_hPalette);
}

VOID CPenteView::SetBackgroundBitmap(INT nResID)
{
	ASSERT(nResID);
	
	DELETEGDIOBJECT(m_hBitmap);
	DELETEGDIOBJECT(m_hPalette);
	
	m_nBackground = nResID;

	m_hBitmap = m_pCustomBitmap->LoadResourceBitmap(m_nBackground, &m_hPalette);
	
	ASSERT(m_hBitmap);
	ASSERT(m_hPalette);
}

BOOL CPenteView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style = cs.style | WS_CLIPSIBLINGS;
	return CView::PreCreateWindow(cs);
}

void CPenteView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CView::OnPrepareDC (pDC, pInfo);
}

void CPenteView::OnDraw(CDC* pDC)
{
	CPenteDoc*	pDoc;
	CRect		rc;
		
	pDoc = (CPenteDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	GetClientRect(&rc);

	if (pDC->RectVisible(&rc))
	{
		// Paint the background
		if (!pDoc->m_fUseBackColor)
		{
			if (m_hBitmap && m_hPalette)
			{
				HPALETTE hOldPalette;

				hOldPalette = ::SelectPalette(pDC->GetSafeHdc(), m_hPalette, FALSE);
				::RealizePalette(pDC->GetSafeHdc());
				
				::SelectPalette(pDC->GetSafeHdc(), hOldPalette, TRUE);
				::RealizePalette(pDC->GetSafeHdc());

				m_pCustomBitmap->PaintDCByHBitmap(pDC, m_hBitmap, TRUE);
			}
		}
		else
			m_pCustomBitmap->PaintDCByColor(pDC, pDoc->GetBackColor());
	
		// Draw the grid
		DrawGrid(pDoc, pDC);

		// We are done drawing the grid 
		// and background.  Now tell the
		// document to render it's data
		pDoc->RenderData(pDC);
	}
}

BOOL CPenteView::OnQueryNewPalette()
{
	CClientDC dc(this);

	ASSERT(m_hPalette);

	::SelectPalette(dc.GetSafeHdc(), m_hPalette, TRUE);
	::RealizePalette(dc.GetSafeHdc());

	return CView::OnQueryNewPalette();
}

VOID CPenteView::OnPaletteChanged(CWnd* pFocusWnd)
{
	ASSERT_VALID(pFocusWnd);

	CClientDC dc(this);

	ASSERT(m_hPalette);

	::SelectPalette(dc.GetSafeHdc(), m_hPalette, TRUE);
	::RealizePalette(dc.GetSafeHdc());

	CView::OnPaletteChanged(pFocusWnd);
}

void CPenteView::DrawGrid (CPenteDoc* pDoc, CDC* pDC)
{
	CRect			rc;
	CPen			aPen, *pPenOld;
	int				i, nSavedDC;
	
	nSavedDC = pDC->SaveDC();

	// Set the mapping mode
	pDC->SetMapMode(MM_ANISOTROPIC);

	// Set the window and viewport extents
	pDC->SetWindowExt(1, 1);
	pDC->SetViewportExt(21, 21);
	
	aPen.CreatePen(PS_SOLID, 0, pDoc->GetGridColor());
	pPenOld = pDC->SelectObject(&aPen);

	pDoc->GetBoard(&rc);

	pDC->DPtoLP(&rc);

	pDC->SetWindowOrg(-1,-1);

	pDC->MoveTo(0,0);
	pDC->LineTo(rc.Width(), 0);
	pDC->LineTo(rc.Width(), rc.Height());
	pDC->LineTo(0, rc.Height());
	pDC->LineTo(0,0);

	int cx, cx1; 
	int	cy, cy1;

	cx	= rc.left;
	cx1	= rc.right;
	cy	= rc.top;
	cy1 = rc.bottom;

	for (i = cx; i < cx1; i++)
	{
		pDC->MoveTo(i, 0);
		pDC->LineTo(i, cy1);
	}

	for (i = cy; i < cy1; i++)
	{
		pDC->MoveTo(0, i);
		pDC->LineTo(cx1, i);
	}

	pDC->SelectObject(pPenOld);
	pDC->RestoreDC(nSavedDC);
}

void CPenteView::OnInitialUpdate()
{
	m_pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(m_pMainFrame);
}

INT	CPenteView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_pCustomBitmap = new CCustomBitmap();
	ASSERT_VALID(m_pCustomBitmap);

	// Load the initial palette and bitmap
	SetBackgroundBitmap(m_nBackground);
	
	return CView::OnCreate(lpCreateStruct);
}

void CPenteView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPenteApp*	pApp; 
	CPenteDoc*	pDoc;

	CClientDC	dc(this);
	CRect		rc;
	INT			nSavedDC;
	UINT		nCount;

	pApp = (CPenteApp*)AfxGetApp();
	ASSERT_VALID (pApp);

	pDoc = (CPenteDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	nSavedDC = dc.SaveDC();
	
	dc.SetViewportOrg(SQUARE_WIDTH, SQUARE_HEIGHT);
	
	dc.DPtoLP(&point);

	pDoc->GetBoard(&rc);

	if (rc.PtInRect(point))
	{
		CPoint newPoint;

		if (!pDoc->WhichSquare(point, &newPoint))
		{
			dc.RestoreDC(nSavedDC);
			return;
		}

		// Mark the current piece
		pDoc->MarkPiece(newPoint);
		
		int i = newPoint.x;
		int j = newPoint.y;

		CRect	rcSquare;
		CPoint	pt(i,j);

		pDoc->GetSquareDims(pt, &rcSquare);

		dc.LPtoDP(&rcSquare);
		
		// Check whether we
		// have captured a pair of pieces
		if (nCount = pDoc->CheckCapture(&pt))
		{
			// We have a capture
			pApp->PlayWave(MAKEINTRESOURCE(IDR_BLIP), SND_ASYNC | SND_MEMORY);
			pDoc->UpdateAllViews(NULL);
		}
		else
		{
			// Play 'piece' sound
			pApp->PlayWave(MAKEINTRESOURCE(IDR_PIECE), SND_ASYNC | SND_MEMORY);
			InvalidateRect(&rcSquare, FALSE);
		}
		
		// Check for a winner 
		if (!pDoc->CheckWinByCapture() && !pDoc->CheckFiveInARow(pt))
		{
			// Display new player turn
			pDoc->ChangeTurns();
			pDoc->SetModifiedFlag();

			// Check play mode and current turn
			// and allow computer to move
			if (pDoc->GetPlayMode() == PLAYER_VS_COMPUTER &&
				pDoc->GetCurrentTurn() == PLAYER_TWO_TURN)
				pDoc->ComputerMove();
		}
		else
		{	
			// Someone has won the game!

			// Ensure our status window is updated
			m_pMainFrame->GetStatusBar()->OnUpdateCmdUI(m_pMainFrame, FALSE);
			
			// We don't want to save a finished game
			pDoc->SetModifiedFlag(FALSE);
			
			pApp->DoFinish();
		}
	}
	dc.RestoreDC(nSavedDC);
}


			

			
		
	