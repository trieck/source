//////////////////////////////////////
// Module Name	:	MainFrame.cpp	//
// Author		:	Thomas A. Rieck //
// Purpose		:	Main Frame		//
//					Implementations	//
// Date			:	11/23/1997		//
//////////////////////////////////////

#include "MainFrame.h"
#include "DeviceDlg.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CMainFrame, CMDIFrameWnd)

UINT CMainFrame::m_nIndicators[] = {ID_SEPARATOR, IDS_TIMELEN};

///////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_EXIT, OnExit)
	ON_COMMAND(ID_DEVICEINFO, OnDeviceInformation)
END_MESSAGE_MAP()

CMainFrame :: CMainFrame()
{
}

BOOL CMainFrame :: PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = 500;
	cs.cy = 400;

	return CMDIFrameWnd :: PreCreateWindow(cs);
}

INT CMainFrame :: OnCreate(LPCREATESTRUCT lpCreateStruct)
{	
	CMDIFrameWnd :: OnCreate(lpCreateStruct);

	// Create the ToolBar
	if (!m_ToolBar.Create(this))
	{
		TRACE0(_T("Failed to create the toolbar."));
		return -1;
	}

	m_ToolBar.LoadToolBar(IDR_MAINFRAME);

	// Create the Status Bar
	if (!m_wndStatus.Create(this))
	{
		TRACE0(_T("Failed to create status bar."));
		return -1;
	}

	m_wndStatus.SetIndicators(CMainFrame::m_nIndicators, 
		sizeof (CMainFrame::m_nIndicators) / sizeof(UINT));
	m_wndStatus.SetPaneStyle(0, SBPS_STRETCH);

	CenterWindow();

	return 0;
}

VOID CMainFrame :: OnSize(UINT nType, int cx, int cy)
{
	CMDIFrameWnd :: OnSize (nType, cx, cy);
}

VOID CMainFrame :: OnExit()
{
	DestroyWindow();
}

VOID CMainFrame :: OnDeviceInformation()
{
	CDeviceDlg dlg(this);

	dlg.DoModal();
}

CMainFrame::~CMainFrame()
{
}
