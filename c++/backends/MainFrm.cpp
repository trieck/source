// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"
#include "backends.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "backendsView.h"

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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] = {
	ID_SEPARATOR           // status line indicator
};

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

	if (!m_wndStatusBar.Create(this) ||
	        !m_wndStatusBar.SetIndicators(indicators,
	                                      sizeof(indicators)/sizeof(UINT)))	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	BackendsApp *pApp = (BackendsApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	CenterWindow();

	return 0;
}

BOOL MainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
                               CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(LeftView), CSize(100, 100), pContext) ||
	        !m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(BackendsView), CSize(100, 100), pContext)) {
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~FWS_ADDTOTITLE;
	cs.cx = 530;
	cs.cy = 500;

	if ( !CFrameWnd::PreCreateWindow(cs) )
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

