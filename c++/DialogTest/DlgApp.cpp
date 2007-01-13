// DLGAPP.CPP

#include "DlgApp.h"
#include "DlgWnd.h"

BOOL CDlgApp::InitInstance()
{
	CDlgWin* pDlg = new CDlgWin();

	this->m_pMainWnd = pDlg;
	
	pDlg->Create(0, _T("Dialog Test"),
				WS_OVERLAPPED | WS_MINIMIZEBOX
				| WS_SYSMENU | WS_DLGFRAME | WS_CLIPCHILDREN,
				CRect(0,0,530,320));

	// Create controls
	pDlg->CreateControls();
	
	// Set child fonts
	pDlg->SetChildFonts(ID_OPENBTN, ID_PROGRESSCTRL, 
			"MS Sans Serif", 8);
	
	pDlg->CenterWindow();
	pDlg->ShowWindow(m_nCmdShow);
	pDlg->UpdateWindow();

	return (TRUE);
}

CDlgApp TheApp;