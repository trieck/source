// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"
#include "baseinc.h"
#include "MainFrm.h"
#include "score.h"
#include "resource.h"

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
	ON_CBN_SELCHANGE(IDC_CB_INSTRUMENT, OnInstrumentChange)
	ON_WM_INITMENUPOPUP()
	ON_WM_CLOSE()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] = {
	ID_SEPARATOR,           // status line indicator
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

	if (!m_wndToolBar.CreateEx(this) ||
	        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME,
	                        CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR)) {
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
	        !m_wndReBar.AddBar(&m_wndToolBar) ||
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

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
	                         CBRS_TOOLTIPS | CBRS_FLYBY);

	BuildInstruments();
	SetActiveInstrument();

	CenterWindow();

	return 0;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if ( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.cx = 500;
	cs.cy = 400;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

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

//
// BuildInstruments
//
void MainFrame :: BuildInstruments()
{
	CComboBox * pInstruments =
	    (CComboBox *)m_wndDlgBar.GetDlgItem(IDC_CB_INSTRUMENT);
	ASSERT_VALID(pInstruments);

	HRSRC hResource = ::FindResource(AfxGetResourceHandle(),
	                                 MAKEINTRESOURCE(IDR_INSTRUMENTS),
	                                 "TEXT");
	ASSERT(hResource != NULL);

	HGLOBAL hGlobal = ::LoadResource(AfxGetResourceHandle(), hResource);
	ASSERT(hGlobal != NULL);

	LPCSTR pResource = (LPCSTR)::LockResource(hGlobal);
	ASSERT(pResource != NULL);
	LPSTR pdata = strdup(pResource);

	LPCSTR ptok = strtok(pdata, "\r\n");
	while (ptok != NULL) {
		pInstruments->AddString(ptok);
		ptok = strtok(NULL, "\r\n");
	}

	if (pdata != NULL) delete [] pdata;

	if (pInstruments->GetCount() > 0)
		pInstruments->SetCurSel(0);
}

//
// SetActiveInstrument
//
void MainFrame :: SetActiveInstrument()
{
	ScoreApp * pApp = (ScoreApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	BYTE instrument = pApp->GetInstrument();

	CComboBox * pInstruments =
	    (CComboBox *)m_wndDlgBar.GetDlgItem(IDC_CB_INSTRUMENT);
	ASSERT_VALID(pInstruments);

	pInstruments->SetCurSel(instrument);
}

//
// OnInstrumentChange
//
void MainFrame :: OnInstrumentChange()
{
	ScoreApp * pApp = (ScoreApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	CComboBox * pInstruments =
	    (CComboBox *)m_wndDlgBar.GetDlgItem(IDC_CB_INSTRUMENT);
	ASSERT_VALID(pInstruments);

	int index = pInstruments->GetCurSel();

	pApp->SetInstrument((BYTE)index);
}

//
// OnInitMenuPopup
//
void MainFrame :: OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}

//
// OnClose
//
void MainFrame::OnClose()
{
	ScoreApp * pApp = (ScoreApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->Stop();

	CFrameWnd::OnClose();
}

//
// OnDropFiles
//
void MainFrame::OnDropFiles(HDROP hDropInfo)
{
	ScoreApp * pApp = (ScoreApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->Stop();

	CFrameWnd::OnDropFiles(hDropInfo);
}

