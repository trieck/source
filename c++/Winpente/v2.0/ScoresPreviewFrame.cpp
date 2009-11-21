// ScoresPreviewFrame.cpp : implementation file
//

#include "stdafx.h"
#include "ScoresPreviewFrame.h"
#include "resource.h"
#include "ResDll\resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoresPreviewFrame

IMPLEMENT_DYNCREATE(CScoresPreviewFrame, CFrameWnd)

CScoresPreviewFrame::CScoresPreviewFrame()
{
	m_pClientWnd	= NULL;
	m_pPrinterDC	= NULL;
	m_pPrintButton	= NULL;
}

CScoresPreviewFrame::~CScoresPreviewFrame()
{
	if (m_pClientWnd) {
		if (::IsWindow(m_pClientWnd->GetSafeHwnd())) {
			m_pClientWnd->DestroyWindow();
		}
		delete m_pClientWnd;
	}

	if (m_pPrinterDC) {
		m_pPrinterDC->DeleteDC();
	}

	if (m_pPrintButton) {
		delete m_pPrintButton;
	}
}


BEGIN_MESSAGE_MAP(CScoresPreviewFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CScoresPreviewFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScoresPreviewFrame message handlers

BOOL CScoresPreviewFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// Register a new window class
	cs.lpszClass = AfxRegisterWndClass(
	                   CS_HREDRAW | CS_VREDRAW |
	                   CS_SAVEBITS | CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW,		// Class Style
	                   NULL,														//	No Cursor
	                   NULL,														//	No background brush
	                   AfxGetApp()->LoadIcon(IDR_MAINFRAME));						//	App icon

	ASSERT(cs.lpszClass);

	cs.style		=	WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
	cs.dwExStyle	=	WS_EX_OVERLAPPEDWINDOW;

	return CFrameWnd::PreCreateWindow(cs);
}

int CScoresPreviewFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Create the status bar
	if (!(m_StatusBar.Create(this, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | CBRS_BOTTOM))) {
		TRACE0("Could not create status bar.");
		return -1;
	}

	// Create the print button
	m_pPrintButton = new CButton;
	if (!m_pPrintButton) {
		TRACE0("Could not create print button.");
		return -1;
	}

	if (!(m_pPrintButton->Create(_T("Print"), WS_VISIBLE | WS_CHILD,
	                             CRect(0, 0, 75, 20), &m_StatusBar, 1))) {
		TRACE0("Could not create print button.");
		return -1;
	}

	// Create the child window
	m_pClientWnd = new CScoresPreviewWnd;
	ASSERT_VALID(m_pClientWnd);

	if (!(m_pClientWnd->Create(NULL, _T(""), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
	                           CRect(0, 0, 0, 0), this, ID_SCORECLIENT, NULL))) {
		TRACE0("Could not create child window.");
		return -1;
	}

	// Create the Printer DC
	CPrintDialog dlg(FALSE);

	if (!dlg.GetDefaults()) {
		// Problem getting default printer information
		return -1;
	}

	HDC hDC = dlg.CreatePrinterDC();
	ASSERT(hDC);

	m_pPrinterDC = CDC::FromHandle(hDC);
	ASSERT_VALID(m_pPrinterDC);

	::GlobalFree(dlg.m_pd.hDevNames);
	::GlobalFree(dlg.m_pd.hDevMode);


	// Modify Frame Window since client window is providing edge
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

	RecalcLayout();

	return CFrameWnd::OnCreate(lpCreateStruct);
}

void CScoresPreviewFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	m_StatusBar.SendMessage(WM_SIZE, (WPARAM)cx, (LPARAM)cy);

	CRect aRect;
	m_StatusBar.GetWindowRect(&aRect);

	if (m_pClientWnd) {
		m_pClientWnd->MoveWindow(0, 0, cx, cy - aRect.Height());
	}
}

CStatusBar * CScoresPreviewFrame::GetStatusBar()
{
	return &m_StatusBar;
}

void CScoresPreviewFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}
