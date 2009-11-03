// pente.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "pente.h"
#include "MainFrm.h"
#include "pentedoc.h"
#include "pentevw.h"
#include "optdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PenteApp

BEGIN_MESSAGE_MAP(PenteApp, CWinApp)
	//{{AFX_MSG_MAP(PenteApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(IDM_SHOWLOG, OnShowlog)
	ON_COMMAND(IDM_OPTIONS, OnOptions)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// PenteApp construction

PenteApp::PenteApp() 
: logWnd(0), twoPlayerGame(true)
{
}

PenteApp::~PenteApp()
{
}
/////////////////////////////////////////////////////////////////////////////
// The one and only PenteApp object

PenteApp theApp;
/////////////////////////////////////////////////////////////////////////////
// PenteApp initialization

BOOL PenteApp::InitInstance()
{
	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings();  // Load standard IhI file options (including MRU)

	twoPlayerGame = GetProfileInt(_T("Settings"), 
		_T("TwoPlayerGame"), 1) == 1 ? true : false;

	// Register document templates
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(PenteDoc),
		RUNTIME_CLASS(MainFrame),       // main SDI frame window
		RUNTIME_CLASS(PenteView));
	AddDocTemplate(pDocTemplate);

	RegisterShellFileTypes(TRUE);
	EnableShellOpen();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	m_pMainWnd->DragAcceptFiles();
#ifdef _ENABLE_LOGGING
	createLogWnd();
#endif // _ENABLE_LOGGING

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// AboutDlg dialog used for App About

class AboutDlg : public CDialog
{
public:
	AboutDlg();
	// Dialog Data
	//{{AFX_DATA(AboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	//{{AFX_MSG(AboutDlg)
	// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

AboutDlg::AboutDlg() : CDialog(AboutDlg::IDD)
{
	//{{AFX_DATA_INIT(AboutDlg)
	//}}AFX_DATA_INIT
}

void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(AboutDlg, CDialog)
	//{{AFX_MSG_MAP(AboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
// App command to run the dialog
void PenteApp::OnAppAbout()
{
	AboutDlg aboutDlg;
	aboutDlg.DoModal();
}
/////////////////////////////////////////////////////////////////////////////
// PenteApp message handlers

/////////////////////////////////////////////////////////////////////////////
int PenteApp::ExitInstance() 
{
	WriteProfileInt(_T("Settings"), _T("TwoPlayerGame"),
		twoPlayerGame ? 1 : 0);
	return CWinApp::ExitInstance();
}

void PenteApp::OnFileNew() 
{
	CWinApp::OnFileNew();
}
/////////////////////////////////////////////////////////////////////////////
void PenteApp::OnShowlog() 
{
#ifdef _ENABLE_LOGGING
	ASSERT_VALID(logWnd);
	logWnd->ShowWindow(SW_SHOW);
#endif // _ENABLE_LOGGING
}
/////////////////////////////////////////////////////////////////////////////
void PenteApp::createLogWnd()
{
	ASSERT(logWnd == NULL);
	logWnd = new LogWnd;
	if (!logWnd->Create(NULL, _T("Pente Log"), MFS_THICKFRAME | 
		WS_OVERLAPPEDWINDOW, CRect(0, 0, 250, 500), m_pMainWnd, 0))
		return;
	logWnd->ShowWindow(SW_SHOW);
	logWnd->UpdateWindow();
}
/////////////////////////////////////////////////////////////////////////////
void PenteApp::OnOptions() 
{
	OptionDlg dlg;
	dlg.m_TwoPlayerGame = twoPlayerGame ? 0 : 1;

	if (dlg.DoModal() == IDOK) {
		twoPlayerGame = dlg.m_TwoPlayerGame == 0 ? true : false;
		OnFileNew();
	}
}
