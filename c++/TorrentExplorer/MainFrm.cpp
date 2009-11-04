// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "Dictionary.h"
#include "List.h"
#include "String.h"
#include "Integer.h"
#include "TorrentDoc.h"
#include "TorrentView.h"
#include "ValueView.h"
#include "GripBar.h"
#include "MainFrm.h"
#include "BinaryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEFAULT_CX			(600)
#define DEFAULT_CY			(400)

#define DEFAULT_CX_LPANE	(200)
#define DEFAULT_CX_RPANE	(400)
#define DEFAULT_CY_PANE		(100)

/////////////////////////////////////////////////////////////////////////////
// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(MainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_SETTING_CHANGE, OnSettingChange)
	//}}AFX_MSG_MAP
	// Global help commands
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
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || 
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
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
	RecalcLayout();
	CenterWindow();	

	return 0;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();

	cs.lpszClass = MainFrame::RegisterClass();
	cs.cx = DEFAULT_CX; cs.cy = DEFAULT_CY;
	if (pApp->GetBOOLSetting("ui_save_win")) {
		// Restore frame window size	
		cs.cx = pApp->GetIntSetting("ui_frame_width");
		cs.cy = pApp->GetIntSetting("ui_frame_height");		
	}

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


BOOL MainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	m_wndSplitter.CreateStatic(this, 1, 2);

	CSize lpane(DEFAULT_CX_LPANE, DEFAULT_CY_PANE);
	CSize rpane(DEFAULT_CX_RPANE, DEFAULT_CY_PANE);

	TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
	if (pApp->GetBOOLSetting("ui_save_win")) {
		lpane.cx = pApp->GetIntSetting("ui_lpane_width");
		rpane.cx = pApp->GetIntSetting("ui_rpane_width");
	}

	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(TorrentView), 
		lpane, pContext);

	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(ValueView), 
		rpane, pContext);

	return TRUE;
}

void MainFrame::OnDestroy() 
{
	TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
	if (pApp->GetBOOLSetting("ui_save_win")) {
		CRect rc;
		GetWindowRect(&rc);

		pApp->PutSetting("ui_frame_width", rc.Width());
		pApp->PutSetting("ui_frame_height", rc.Height());

		CWnd *pLeft = m_wndSplitter.GetPane(0, 0);
		if (pLeft && IsWindow(*pLeft)) {
			pLeft->GetWindowRect(&rc);
			pApp->PutSetting("ui_lpane_width", rc.Width());
		}
		CWnd *pRight = m_wndSplitter.GetPane(0, 1);
		if (pRight && IsWindow(*pRight)) {
			pRight->GetWindowRect(&rc);
			pApp->PutSetting("ui_rpane_width", rc.Width());
		}
	}

	CFrameWnd::OnDestroy();	
}

void MainFrame::SwapViews()
{
	CView *pRight = (CView*)m_wndSplitter.GetPane(0, 1);
	
	CRect rc;
	pRight->GetWindowRect(&rc);

	CRuntimeClass* pRuntimeClass;
	if (pRight->IsKindOf(RUNTIME_CLASS(ValueView))) {
		pRuntimeClass = RUNTIME_CLASS(BinaryView);
	} else {
		pRuntimeClass = RUNTIME_CLASS(ValueView);
	}
	
	m_wndSplitter.DeleteView(0, 1);
	m_wndSplitter.CreateView(0, 1, pRuntimeClass, 
		CSize(rc.Width(), DEFAULT_CY_PANE), NULL);
	m_wndSplitter.RecalcLayout();
}

LRESULT MainFrame::OnSettingChange(WPARAM wParam, LPARAM lParam)
{
	SendMessageToDescendants(WM_SETTING_CHANGE, wParam, lParam, TRUE, TRUE);
	return 0;
}

LPCSTR MainFrame::RegisterClass()
{
	HINSTANCE hInst = AfxGetInstanceHandle();

	CString strGUID;	
	strGUID.LoadString(IDS_APP_GUID);
	LPSTR lpszClassName = AfxGetThreadState()->m_szTempClassName;
	wsprintf(lpszClassName, "Afx::%s", strGUID);

	// see if the class already exists
	WNDCLASS wndcls;
	if (::GetClassInfo(hInst, lpszClassName, &wndcls)) {
		wndcls.lpszClassName;
	}

	// otherwise we need to register a new class
	wndcls.style = CS_HREDRAW | CS_VREDRAW | CS_SAVEBITS 
		| CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW;
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
	wndcls.hInstance = hInst;
	wndcls.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	wndcls.hCursor = NULL;
	wndcls.hbrBackground = NULL;
	wndcls.lpszMenuName = NULL;
	wndcls.lpszClassName = lpszClassName;
	if (!AfxRegisterClass(&wndcls))
		AfxThrowResourceException();

	return wndcls.lpszClassName;	
}
