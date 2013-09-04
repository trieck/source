/*---------------------------------------
	Module Name	:	MainFrame.cpp
	Author		:	Thomas A. Rieck
	Purpose		:	Main Frame Window
					Module
	Date		:	08/21/1997
---------------------------------------*/

#include "stdafx.h"
#include "MainFrame.h"
#include "PenteApp.h"
#include "PenteDoc.h"
#include "ResDll\resource.h"
#include "OurConstants.h"

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_INITMENUPOPUP()
	ON_WM_EXITMENULOOP()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	CRect				rc;
	int					wndStyle	=	WS_OVERLAPPED | WS_BORDER | WS_CAPTION |
	                                    WS_SYSMENU | WS_MINIMIZEBOX | FWS_ADDTOTITLE;
	int					wndExStyle	=	WS_EX_OVERLAPPEDWINDOW;
	int					cyOffset;
	NONCLIENTMETRICS	ncm;

	// Adjust frame window based on
	// needed client area size
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);

	cyOffset =	ncm.iMenuHeight + TOOLBARHEIGHT;

	rc.SetRect(0, 0, 21 * 21, 21 * 21 + cyOffset);

	::AdjustWindowRectEx(rc, wndStyle, TRUE, wndExStyle);

	cs.cx			= rc.right - rc.left;
	cs.cy			= rc.bottom - rc.top;
	cs.style		= wndStyle;
	cs.dwExStyle	= wndExStyle;

	// Register a new window class
	cs.lpszClass = AfxRegisterWndClass(
	                   CS_SAVEBITS | CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW,		//	Window style
	                   NULL,														//	No Cursor
	                   NULL,														//	No background brush
	                   AfxGetApp()->LoadIcon(IDR_MAINFRAME));						//	App icon

	ASSERT(cs.lpszClass);

	return CFrameWnd::PreCreateWindow(cs);
}

INT CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Create the status bar
	if (!(m_StatusBar.Create(this))) {
		TRACE0("Could not create status bar.");
		return -1;
	}

	SetStatusIndicators(lpCreateStruct->cx / 3);

	// Create the toolbar
	if (!(m_ToolBar.Create(this))) {
		TRACE0("Could not create toolbar.");
		return -1;
	}

	m_ToolBar.LoadToolBar(IDR_MAINFRAME);

	// Set the toolbar style
	m_ToolBar.SetBarStyle(m_ToolBar.GetBarStyle() |	CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED);

	// Center the window
	CenterWindow();

	// Start playing some music
	CPenteApp* pApp = (CPenteApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->PlayWave(MAKEINTRESOURCE(IDR_THEME),
	               SND_ASYNC | SND_MEMORY| SND_LOOP);

	return CFrameWnd::OnCreate(lpCreateStruct);
}

VOID CMainFrame::OnSize(UINT nType, INT cx, INT cy)
{
	m_StatusBar.SendMessage(WM_SIZE, (WPARAM)cx, (LPARAM)cy);
	CFrameWnd::OnSize (nType, cx, cy);
}

VOID CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	UINT sbpIndicators[] = {ID_SEPARATOR};
	m_StatusBar.SetIndicators(sbpIndicators, sizeof(sbpIndicators) / sizeof(UINT));

	CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}

VOID CMainFrame::OnExitMenuLoop(BOOL bIsTrackPopupMenu)
{
	CRect aRect;
	GetWindowRect(&aRect);

	SetStatusIndicators(aRect.Width() / 3);

	// Ensure the command handlers have been
	// updated.  In the case that a modal window
	// is shown, our main thread will be blocked
	// and the updates will not fire.
	m_StatusBar.OnUpdateCmdUI(this, FALSE);

	CFrameWnd::OnExitMenuLoop(bIsTrackPopupMenu);
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::SetStatusIndicators(int nWidth)
{
	UINT sbpIndicators[] = {
		IDS_PLAYERTURN,
		IDS_PLAYERONECAPTURES,
		IDS_PLAYERTWOCAPTURES
	};

	UINT nElements = sizeof(sbpIndicators) / sizeof(UINT);

	m_StatusBar.SetIndicators(sbpIndicators, nElements);

	// Offset width with borders
	INT aBorders[3];
	m_StatusBar.SendMessage(SB_GETBORDERS, 0, (LPARAM)aBorders);
	nWidth -= (aBorders[2] * 4) + 1;

	// Set Pane Widths
	for (UINT i = 0; i < nElements; i++) {
		UINT	nID, nStyle;
		INT		cxWidth;

		m_StatusBar.GetPaneInfo(i, nID, nStyle, cxWidth);
		m_StatusBar.SetPaneInfo(i, nID, nStyle, nWidth);
	}
}
