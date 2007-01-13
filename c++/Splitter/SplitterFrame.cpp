///////////////////////////////////////
// Module Name	:	MainFrame.cpp	 //
// Author		:	Thomas A. Rieck  //
// Purpose		:	Splitter Example //
// Date			:	4/11/97			 //
///////////////////////////////////////

#include "SplitterFrame.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

///////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_EXIT, OnExit)
END_MESSAGE_MAP()

CMainFrame :: CMainFrame()
{
	m_pWndStatus = NULL;
}

BOOL CMainFrame :: PreCreateWindow(CREATESTRUCT& cs)
{
	return CFrameWnd :: PreCreateWindow(cs);
}

INT CMainFrame :: OnCreate(LPCREATESTRUCT lpCreateStruct)
{	
	m_pWndStatus = new CStatusBar();
	ASSERT_VALID(m_pWndStatus);

	m_pWndStatus->Create(this,  WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, ID_STATUS);

	return CFrameWnd :: OnCreate(lpCreateStruct);
}

BOOL CMainFrame :: OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	m_wndSplitter.CreateStatic(this, 1, 2);

	m_wndSplitter.CreateView(0, 0, 
		RUNTIME_CLASS(CRootView), CSize(200,100), pContext);

	m_wndSplitter.CreateView(0, 1, 
		RUNTIME_CLASS(CSplitterView), CSize(100,100), pContext);

	return TRUE;
}

VOID CMainFrame :: OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd :: OnSize (nType, cx, cy);
}

VOID CMainFrame :: OnExit()
{
	DestroyWindow();
}

CMainFrame::~CMainFrame()
{
	if (m_pWndStatus) delete m_pWndStatus;
}
