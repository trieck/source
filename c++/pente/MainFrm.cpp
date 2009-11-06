// MainFrm.cpp : implementation of the MainFrame class
//
#include "stdafx.h"
#include "pente.h"
#include "MainFrm.h"
#include "PenteBoard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(MainFrame)
	ON_WM_CREATE()
	ON_WM_SETTINGCHANGE()
	ON_MESSAGE(WM_APPSETTING_CHANGE, OnAppSettingChange)
	ON_UPDATE_COMMAND_UI(IDS_CAPTURES, onUpdateCaptures)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MainFrame construction/destruction

MainFrame::MainFrame()
{
}

MainFrame::~MainFrame()
{
}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!toolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || 
		!toolBar.LoadToolBar(IDR_MAINFRAME)) {
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!statusBar.Create(this)) {
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	toolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&toolBar);
	RecalcLayout();
	CenterWindow();
	
	return 0;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~(WS_THICKFRAME | WS_MAXIMIZE | WS_MAXIMIZEBOX);
	if(!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MainFrame message handlers

void MainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CFrameWnd::OnSettingChange(uFlags, lpszSection);
	RecalcLayout();
}
/////////////////////////////////////////////////////////////////////////////
void MainFrame::adjustFrameByBoard()
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(*this));
	ASSERT(::IsWindow(statusBar));
	ASSERT(::IsWindow(toolBar));
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST);

	CRect rc;
	PenteBoard::getBoundingRect(rc);

	// make room for the status bar
	CRect rcStatus;
	statusBar.GetWindowRect(rcStatus);
	rcStatus.OffsetRect(-rcStatus.left, -rcStatus.top);

	// make room for the toolbar
	CRect rcToolbar;
	toolBar.GetWindowRect(rcToolbar);
	rcToolbar.OffsetRect(-rcToolbar.left, -rcToolbar.top);

	// make adjustments for the docking bar
	CDockBar *dockBar = toolBar.m_pDockBar;
	if (dockBar != NULL && IsWindow(*dockBar)) {
		CRect rcDockbar;
		dockBar->GetWindowRect(rcDockbar);
		rcDockbar.OffsetRect(-rcDockbar.left, -rcDockbar.top);
		if (toolBar.m_dwStyle & CBRS_ORIENT_HORZ)
			rcToolbar.bottom -= abs(rcDockbar.Height() - rcToolbar.Height());
		else if (toolBar.m_dwStyle & CBRS_ORIENT_VERT)
			rcToolbar.right -= abs(rcDockbar.Width() - rcToolbar.Width());
	}
	if (statusBar.IsWindowVisible())
		rc.bottom += rcStatus.Height();
	if (!toolBar.IsFloating() && toolBar.IsWindowVisible()) {
		if (toolBar.m_dwStyle & CBRS_ORIENT_HORZ)
			rc.bottom += rcToolbar.Height();
		else if (toolBar.m_dwStyle & CBRS_ORIENT_VERT)
			rc.right += rcToolbar.Width();
	}
	DWORD style = GetStyle();
	DWORD dwExStyle = GetExStyle() | WS_EX_CLIENTEDGE;
	AdjustWindowRectEx(&rc, style, TRUE, dwExStyle);
	
	SetWindowPos(NULL, 0, 0, rc.Width(), rc.Height(), 
		SWP_NOMOVE | SWP_FRAMECHANGED | SWP_NOZORDER);
}

/////////////////////////////////////////////////////////////////////////////
void MainFrame::RecalcLayout(BOOL bNotify) 
{
	if (IsWindow(statusBar) && IsWindow(toolBar))
		adjustFrameByBoard();
	
	CFrameWnd::RecalcLayout(bNotify);
}

/////////////////////////////////////////////////////////////////////////////
void MainFrame::onUpdateCaptures(CCmdUI *pCmdUI)
{
}

/////////////////////////////////////////////////////////////////////////////
LRESULT MainFrame::OnAppSettingChange(WPARAM wParam, LPARAM lParam)
{
	SendMessageToDescendants(WM_APPSETTING_CHANGE, wParam, lParam);
	return 0;
}
