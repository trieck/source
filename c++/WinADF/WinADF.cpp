// WinADF.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WinADF.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "WinADFDoc.h"
#include "LeftView.h"

#include "FileViewFrame.h"
#include "FileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// WinADFApp

BEGIN_MESSAGE_MAP(WinADFApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &WinADFApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &WinADFApp::OnFileOpen)
END_MESSAGE_MAP()


// WinADFApp construction

WinADFApp::WinADFApp()
 : m_pFileViewTemplate(NULL)
{
}


// The one and only WinADFApp object

WinADFApp theApp;


// WinADFApp initialization

BOOL WinADFApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	SetRegistryKey(_T("Rieck Enterprises"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_WinADFTYPE,
		RUNTIME_CLASS(WinADFDoc),
		RUNTIME_CLASS(ChildFrame), // custom MDI child frame
		RUNTIME_CLASS(LeftView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	m_pFileViewTemplate = new CMultiDocTemplate(IDR_FILEVIEWTYPE,
		RUNTIME_CLASS(WinADFDoc),
		RUNTIME_CLASS(FileViewFrame), // custom MDI child frame
		RUNTIME_CLASS(FileView));
	if (!m_pFileViewTemplate)
		return FALSE;
	AddDocTemplate(m_pFileViewTemplate);

	// create main MDI Frame window
	MainFrame* pMainFrame = new MainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME)) {
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void WinADFApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// WinADFApp message handlers


int WinADFApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
	MSGBOXPARAMS mbp;
	
	mbp.cbSize = sizeof(MSGBOXPARAMS);
	mbp.hwndOwner = GetMainWnd()->GetSafeHwnd();
	mbp.hInstance = AfxGetResourceHandle();
	mbp.lpszText = lpszPrompt;
	mbp.lpszCaption	= m_pszAppName;
	mbp.dwStyle = nType | MB_USERICON;
	mbp.lpszIcon = MAKEINTRESOURCE(IDR_MAINFRAME);
	mbp.dwContextHelpId	= nIDPrompt;
	mbp.lpfnMsgBoxCallback	= NULL;
	mbp.dwLanguageId = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

	return ::MessageBoxIndirect(&mbp);
}

void WinADFApp::ShowFileView(CDocument *pDoc)
{
	CFrameWnd* pFrame = m_pFileViewTemplate->CreateNewFrame(pDoc, NULL);
	FileView *pView = (FileView*)pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
	ASSERT(pView != NULL);
	ASSERT(pView->IsKindOf(RUNTIME_CLASS(FileView)));

	m_pFileViewTemplate->InitialUpdateFrame(pFrame, pDoc);
}
