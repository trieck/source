// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"
#include "ddraw2.h"

#include "MainFrm.h"

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

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
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
	DDrawApp *pApp = (DDrawApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	LPDIRECTDRAW pdd = pApp->GetDirectDraw();
	pdd->AddRef();

	// set cooperative level
	HRESULT hr = pdd->SetCooperativeLevel(*this, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
	if (hr != DD_OK) {
		TRACE0("unable to set cooperative level.\n");
		pdd->Release();
		return FALSE;
	}

	hr = pdd->SetDisplayMode(1152, 864, 32);
	if (hr != DD_OK) {
		TRACE0("unable to set display mode.\n");
		pdd->Release();
		return FALSE;
	}

	pdd->Release();

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	CenterWindow();

	return 0;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.cx = 400;
	cs.cy = 400;

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

