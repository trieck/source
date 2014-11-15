///////////////////////////////////////
// Module Name	:	SplitterApp.cpp	 //
// Author		:	Thomas A. Rieck  //
// Purpose		:	Splitter Example //
// Date			:	4/11/97			 //
///////////////////////////////////////

#include "SplitterApp.h"
#include "SplitterFrame.h"
#include "SplitterDoc.h"
#include "SplitterView.h"
#include "resource.h"

///////////////////////////////////////////////////////////////////
// CSplitterApp construction/destruction

CSplitterApp::CSplitterApp()
{
}

CSplitterApp::~CSplitterApp()
{
}

///////////////////////////////////////////////////////////////////
// CSplitterApp initialization

BOOL CSplitterApp::InitInstance()
{
    //
    // Register the application's document template
    //
    CSingleDocTemplate* pDocTemplate;

    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CSplitterDoc),
        RUNTIME_CLASS(CMainFrame),      // main SDI frame window
        RUNTIME_CLASS(CSplitterView));

    AddDocTemplate(pDocTemplate);

    // Parse command line (this is required by doc/view)
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // Dispatch commands specified on the command line
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    ASSERT_VALID(this->m_pMainWnd);

    return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare and initialize the sole CSplitterApp object

CSplitterApp MyApp;
