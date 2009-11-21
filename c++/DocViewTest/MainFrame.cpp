//////////////////////////////////////
// Module Name	:	MainFrame.cpp	//
// Author		:	Thomas A. Rieck //
// Purpose		:	Simple Document //
//					 - View Test	//
// Date			:	4/11/97			//
//////////////////////////////////////

#include "MainFrame.h"
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

VOID CMainFrame :: OnSize(UINT nType, int cx, int cy)
{
	INT		pSizes[3];

	pSizes[0] = cx / 3;
	pSizes[1] = pSizes[0] + (cx / 3);
	pSizes[2] = -1;

	m_pWndStatus->GetStatusBarCtrl().SetParts(3, pSizes);

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
