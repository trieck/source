// emu6502.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "emu6502.h"

#include "MainFrm.h"
#include "emu6502Doc.h"
#include "emu6502View.h"
//{{AFX_INCLUDES()
#include "labelcontrol.h"
//}}AFX_INCLUDES

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Emu6502App

BEGIN_MESSAGE_MAP(Emu6502App, CWinApp)
    //{{AFX_MSG_MAP(Emu6502App)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    //}}AFX_MSG_MAP
    // Standard file based document commands
    ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Emu6502App construction

Emu6502App::Emu6502App()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only Emu6502App object

Emu6502App theApp;

/////////////////////////////////////////////////////////////////////////////
// Emu6502App initialization

BOOL Emu6502App::InitInstance()
{
    AfxEnableControlContainer();

    LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    // Register document templates
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(Emu6502Doc),
        RUNTIME_CLASS(MainFrame),       // main SDI frame window
        RUNTIME_CLASS(Emu6502View));
    AddDocTemplate(pDocTemplate);

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
// AboutDlg dialog used for App About

class AboutDlg : public CDialog {
public:
    AboutDlg();

// Dialog Data
    //{{AFX_DATA(AboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    CLabelControl	m_CompanyName;
    CLabelControl	m_ProductName;
    CLabelControl	m_Version;
    CLabelControl	m_Copyright;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(AboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(AboutDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysColorChange();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    void UpdateCtrlColor();
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
    DDX_Control(pDX, IDC_COMPANYNAME, m_CompanyName);
    DDX_Control(pDX, IDC_PRODUCTNAME, m_ProductName);
    DDX_Control(pDX, IDC_VERSION, m_Version);
    DDX_Control(pDX, IDC_COPYRIGHT, m_Copyright);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(AboutDlg, CDialog)
    //{{AFX_MSG_MAP(AboutDlg)
    ON_WM_SYSCOLORCHANGE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void Emu6502App::OnAppAbout()
{
    AboutDlg aboutDlg;
    aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
void Emu6502App::RegisterConstruct(int id, CWnd *pWnd)
{
    states[id] = pWnd;
}

/////////////////////////////////////////////////////////////////////////////
void Emu6502App::RegisterDestruct(int id)
{
    states[id] = NULL;
}

/////////////////////////////////////////////////////////////////////////////
CWnd *Emu6502App::GetState(int id)
{
    CWnd *wnd = NULL;
    states.Lookup(id, wnd);
    return wnd;
}

/////////////////////////////////////////////////////////////////////////////
// Emu6502App message handlers

/////////////////////////////////////////////////////////////////////////////
// Global Helper Functions
static const char hexish[] = "0123456789ABCDEF";

/////////////////////////////////////////////////////////////////////////////
BOOL IsHexChar(char c)
{
    c = toupper(c);

    for (int i = 0; i < sizeof(hexish) / sizeof(char); i++) {
        if (c == hexish[i])
            return TRUE;
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
CString ByteToHex(BYTE b)
{
    BYTE lo, hi;

    lo = b & 0xf;
    hi = (b & 0xf0) >> 4;

    CString output;
    output.Format(_T("%c%c"), hexish[hi], hexish[lo]);

    return output;
}

BOOL AboutDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    UpdateCtrlColor();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void AboutDlg::OnSysColorChange()
{
    CDialog::OnSysColorChange();
    UpdateCtrlColor();
}

void AboutDlg::UpdateCtrlColor()
{
    DWORD backColor = GetSysColor(COLOR_BTNFACE);
    m_CompanyName.SetBackColor(backColor);
    m_Copyright.SetBackColor(backColor);
    m_ProductName.SetBackColor(backColor);
    m_Version.SetBackColor(backColor);
}
