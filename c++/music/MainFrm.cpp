// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"
#include "music.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SMALLICON_CX	16
#define SMALLICON_CY	16

/////////////////////////////////////////////////////////////////////////////
// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(MainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] = {
	ID_SEPARATOR	// status line indicator
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

	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME,
	                        CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
	        !m_wndReBar.AddBar(&m_wndDlgBar)) {
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
	        !m_wndStatusBar.SetIndicators(indicators,
	                                      sizeof(indicators)/sizeof(UINT))) {
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Set dialog button images
	if (!setButtonImage(&m_wndDlgBar,		/* parent dialog */
	                    IDM_ADDRECORD,						/* button resource */
	                    IDB_ADDRECORD,						/* image resource */
	                    IMAGE_BITMAP,						/* image type */
	                    SMALLICON_CX, SMALLICON_CY,			/* image size */
	                    LR_LOADMAP3DCOLORS | LR_SHARED)) {	/* load flags */
		TRACE0("Failed to set button image.\n");
		return -1;
	}

	if (!setButtonImage(&m_wndDlgBar,		/* parent dialog */
	                    IDM_DELRECORD,						/* button resource */
	                    IDB_DELRECORD,						/* image resource */
	                    IMAGE_BITMAP,						/* image type */
	                    SMALLICON_CX, SMALLICON_CY,			/* image size */
	                    LR_LOADMAP3DCOLORS | LR_SHARED)) {	/* load flags */
		TRACE0("Failed to set button image.\n");
		return -1;
	}

	CenterWindow();

	return 0;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if ( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style &= ~(AFX_IDS_APP_TITLE | WS_MAXIMIZEBOX | WS_THICKFRAME);

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


