// ddraw2.cpp : Defines the class behaviors for the application.
//

#include "StdAfx.h"
#include "ddraw2.h"
#include "draw.h"

#include "MainFrm.h"
#include "DDrawDoc.h"
#include "DDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DDrawApp

BEGIN_MESSAGE_MAP(DDrawApp, CWinApp)
    //{{AFX_MSG_MAP(DDrawApp)
    //}}AFX_MSG_MAP
    // Standard file based document commands
    ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DDrawApp construction

DDrawApp::DDrawApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only DDrawApp object

DDrawApp theApp;

/////////////////////////////////////////////////////////////////////////////
// DDrawApp initialization

BOOL DDrawApp::InitInstance()
{
    // Standard initialization

    // Change the registry key under which our settings are stored.
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    // Register document templates

    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(DDrawDoc),
        RUNTIME_CLASS(MainFrame),       // main SDI frame window
        RUNTIME_CLASS(DDrawView));
    AddDocTemplate(pDocTemplate);

    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // Create DirectDraw Object
    if (!CreateDirectDraw())
        return FALSE;

    // Dispatch commands specified on the command line
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// DDrawApp message handlers

BOOL DDrawApp::CreateDirectDraw()
{
    HRESULT hr;

    // create direct draw object
    hr = DirectDrawCreateEx(NULL, (void**)&m_pdraw, IID_IDirectDraw7, nullptr);
    if (hr != DD_OK) {
        TRACE0("unable to create DirectDraw object.\n");
        return FALSE;
    }

    return TRUE;
}

int DDrawApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}
