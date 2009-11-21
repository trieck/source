// mwrt.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "mwrt.h"
#include "mwrtDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmwrtApp

BEGIN_MESSAGE_MAP(CmwrtApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CmwrtApp construction

CmwrtApp::CmwrtApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CmwrtApp object

CmwrtApp theApp;


// CmwrtApp initialization

BOOL CmwrtApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxOleInit())
		return FALSE;

	// Standard initialization
	SetRegistryKey(_T("Rieck Enterprises"));

	CmwrtDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

// Helper functions
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
	}

	return output;
}
