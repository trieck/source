//////////////////////////////////////
// Module Name	:	DocViewApp.cpp	//
// Author		:	Thomas A. Rieck //
// Purpose		:	Simple Document //
//					 - View Test	//
// Date			:	4/11/97			//
//////////////////////////////////////

#include "DocViewApp.h"
#include "MainFrame.h"     
#include "DocViewDoc.h"
#include "DocViewView.h"
#include "resource.h"

///////////////////////////////////////////////////////////////////
// CDocViewApp construction/destruction

CDocViewApp::CDocViewApp()
{
}

CDocViewApp::~CDocViewApp()
{
} 

///////////////////////////////////////////////////////////////////
// CDocViewApp initialization

BOOL CDocViewApp::InitInstance()
{
	//
   // Register the application's document template
	//
   CSingleDocTemplate* pDocTemplate;
	
   pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDocViewDoc),
		RUNTIME_CLASS(CMainFrame),      // main SDI frame window
		RUNTIME_CLASS(CDocViewView));

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
// Declare and initialize the sole CDocViewApp object

CDocViewApp MyApp;
