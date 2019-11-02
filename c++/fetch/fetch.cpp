// fetch.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "fetch.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FetchApp

BEGIN_MESSAGE_MAP(FetchApp, CWinApp)
    //{{AFX_MSG_MAP(FetchApp)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FetchApp construction

FetchApp::FetchApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only FetchApp object

FetchApp theApp;

/////////////////////////////////////////////////////////////////////////////
// FetchApp initialization

BOOL FetchApp::InitInstance()
{
    MainFrame* pFrame = new MainFrame;
    m_pMainWnd = pFrame;

    // create and load the frame with its resources

    pFrame->LoadFrame(IDR_MAINFRAME,
                      WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
                      NULL);

    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // Dispatch commands specified on the command line
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// FetchApp message handlers

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
void FetchApp::OnAppAbout()
{
    AboutDlg aboutDlg;
    aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// FetchApp message handlers

