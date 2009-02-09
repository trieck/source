// WinADF.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WinADF.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "WinADFDoc.h"
#include "LeftView.h"
#include "FileViewFrame.h"
#include "TextFileView.h"
#include "BinaryFileView.h"
#include <algorithm>

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
 : m_pTextFileViewTemplate(NULL), m_pBinaryFileViewTemplate(NULL)
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
	pDocTemplate = new CMultiDocTemplate(IDR_WINADFTYPE,
		RUNTIME_CLASS(WinADFDoc),
		RUNTIME_CLASS(ChildFrame), // custom MDI child frame
		RUNTIME_CLASS(LeftView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	m_pTextFileViewTemplate = new CMultiDocTemplate(IDR_FILEVIEWTYPE,
		RUNTIME_CLASS(WinADFDoc),
		RUNTIME_CLASS(FileViewFrame), // custom MDI child frame
		RUNTIME_CLASS(TextFileView));
	if (!m_pTextFileViewTemplate)
		return FALSE;
	AddDocTemplate(m_pTextFileViewTemplate);

	m_pBinaryFileViewTemplate = new CMultiDocTemplate(IDR_FILEVIEWTYPE,
		RUNTIME_CLASS(WinADFDoc),
		RUNTIME_CLASS(FileViewFrame), // custom MDI child frame
		RUNTIME_CLASS(BinaryFileView));
	if (!m_pBinaryFileViewTemplate)
		return FALSE;
	AddDocTemplate(m_pBinaryFileViewTemplate);

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

void WinADFApp::ShowTextFileView(CDocument *pDoc)
{
	CFrameWnd* pFrame = m_pTextFileViewTemplate->CreateNewFrame(pDoc, NULL);
	if (pFrame != NULL) {
		TextFileView *pView = (TextFileView*)pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
		ASSERT(pView != NULL);
		ASSERT(pView->IsKindOf(RUNTIME_CLASS(TextFileView)));
		m_pTextFileViewTemplate->InitialUpdateFrame(pFrame, pDoc);
	} 
}

void WinADFApp::ShowBinaryFileView(CDocument *pDoc)
{
	CFrameWnd* pFrame = m_pBinaryFileViewTemplate->CreateNewFrame(pDoc, NULL);
	if (pFrame != NULL) {
		BinaryFileView *pView = (BinaryFileView*)pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
		ASSERT(pView != NULL);
		ASSERT(pView->IsKindOf(RUNTIME_CLASS(BinaryFileView)));
		m_pBinaryFileViewTemplate->InitialUpdateFrame(pFrame, pDoc);
	}
}

// Utility functions
string comma(uint64_t i)
{
	string output;

    char buff[20];
    sprintf(buff,"%I64u", i);

    int n = strlen(buff);

    for (int j = n - 1, k = 1; j >= 0; j--, k++) {
        output += buff[j];
        if (k % 3 == 0 && j > 0 && j < n - 1)
            output += ',';
    }
	
	std::reverse(output.begin(), output.end());

    return output;
}

/////////////////////////////////////////////////////////////////////////////
CString LastError()
{
	CString output;

	LPTSTR pmsg = NULL;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&pmsg, 0, NULL);
	
	if (pmsg != NULL) {
		uint32_t N = _tcslen(pmsg);
        if (N > 1 && pmsg[N - 1] == _T('\n'))
			pmsg[N - 1] = _T('\0');
 
		if (N > 1 && pmsg[N - 2] == _T('\r'))
			pmsg[N - 2] = _T('\0');

		output = pmsg;
		LocalFree(pmsg);
	} else {
		AfxMessageBox(LastError());
	}

    return output;                     
}

/////////////////////////////////////////////////////////////////////////////
CDocument *MDIGetActiveDoc()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)AfxGetMainWnd();
	ASSERT_VALID(pFrame);
	ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)));

	CMDIChildWnd* pChild = pFrame->MDIGetActive();
	ASSERT_VALID(pChild);

	return pChild->GetActiveDocument();
}

