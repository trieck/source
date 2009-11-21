/*---------------------------------------
	Module Name	:	PenteApp.cpp
	Author		:	Thomas A. Rieck
	Purpose		:	Pente Application
					Module
	Date		:	08/21/1997
---------------------------------------*/

#include "stdafx.h"
#include "PenteApp.h"
#include "MainFrame.h"
#include "PenteDoc.h"
#include "PenteView.h"
#include "ScoresDlg.h"
#include "Scores.h"
#include "SettingsDlg.h"
#include "ResDll\resource.h"
#include "OurConstants.h"

// Initialize static data members
LPCTSTR CPenteApp::m_lpszRegPath = _T("SOFTWARE\\Rieck Enterprises\\WinPente\\v2.0\\");

IMPLEMENT_DYNCREATE(CPenteApp, CWinApp)

BEGIN_MESSAGE_MAP(CPenteApp, CWinApp)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(IDM_SCORES, OnViewScores)
	ON_COMMAND(IDM_SETTINGS, OnSettings)
	ON_COMMAND(ID_FILE_NEW, CPenteApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CPenteApp::OnFileOpen)
	ON_COMMAND(ID_FILE_EXIT, OnExit)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CPenteApp construction/destruction
CPenteApp::CPenteApp()
{
	m_hDllInst			= NULL;
	m_fInitialized		= FALSE;
	m_fEnableDebug		= FALSE;
}

CPenteApp::~CPenteApp()
{
}

VOID CPenteApp::OnFileNew()
{
	CWinApp::OnFileNew();
}

VOID CPenteApp::OnFileOpen()
{
	CString		newName;
	CMainFrame* pFrame = (CMainFrame*)m_pMainWnd;
	ASSERT_VALID(pFrame);

	CPenteDoc* pDoc = (CPenteDoc*)pFrame->GetActiveDocument();
	ASSERT_VALID(pDoc);

	if (!DoPromptFileName(newName, AFX_IDS_OPENFILE,
	                      OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
		return; // open cancelled

	// Check for a valid document
	if (!pDoc->IsValidDocument(newName)) {
		AfxMessageBox(IDS_INVALIDGAME);
		return;
	}

	OpenDocumentFile(newName);
}

VOID CPenteApp::OnAbout()
{
	CDialog dlg(IDD_ABOUT, m_pMainWnd);

	dlg.DoModal();
}

VOID CPenteApp::OnViewScores()
{
	BeginWaitCursor();

	CScoresDlg dlg(m_pMainWnd);

	dlg.DoModal();

	EndWaitCursor();
}

BOOL CPenteApp::PlayWave(LPTSTR szWaveName, UINT nFlags)
{
	HRSRC		hWaveRes;
	HGLOBAL		hGlobMem;
	HINSTANCE	hInstance = AfxGetResourceHandle();
	BOOL		fRtn;

	hWaveRes = FindResource(hInstance, szWaveName, _T("WAVE"));

	hGlobMem = LoadResource(hInstance, hWaveRes);

	fRtn = PlaySound((LPTSTR)LockResource(hGlobMem), hInstance, nFlags);

	UnlockResource(hGlobMem);

	FreeResource(hGlobMem);

	return fRtn;
}

VOID CPenteApp::OnHelp()
{
	::WinHelp(m_pMainWnd->GetSafeHwnd(),
	          m_pszHelpFilePath,
	          HELP_CONTENTS, 0);
}

int CPenteApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
	MSGBOXPARAMS	mbp;

	mbp.cbSize				= sizeof(MSGBOXPARAMS);
	mbp.hwndOwner			= GetMainWnd()->GetSafeHwnd();
	mbp.hInstance			= AfxGetResourceHandle();
	mbp.lpszText			= lpszPrompt;
	mbp.lpszCaption			= _T("Pente for Windows");
	mbp.dwStyle				= nType | MB_USERICON;
	mbp.lpszIcon			= MAKEINTRESOURCE(IDR_MAINFRAME);
	mbp.dwContextHelpId		= nIDPrompt;
	mbp.lpfnMsgBoxCallback	= NULL;
	mbp.dwLanguageId		= MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

	return ::MessageBoxIndirect(&mbp);
}

BOOL CPenteApp::IsValidResolution()
{
	INT		cx, cy;
	CDC		*pDC;
	HDC		hDC;
	BOOL	fRtn;
	CString	cs;

	hDC = GetDC(NULL);
	ASSERT(hDC);

	pDC = CDC::FromHandle(hDC);
	ASSERT_VALID(pDC);

	cx = pDC->GetDeviceCaps(HORZRES);
	cy = pDC->GetDeviceCaps(VERTRES);

	fRtn = (cx >= MINIMUM_HORZRES || cy >= MINIMUM_VERTRES);

	if (!fRtn) {
		cs.Format(IDS_BADRES, MINIMUM_HORZRES, MINIMUM_VERTRES);
		AfxMessageBox(cs);
	}

	ReleaseDC(NULL, hDC);

	return fRtn;
}

VOID CPenteApp::DoFinish()
{
	CPenteDoc *	pDoc;
	CString		strMessage, strDateTime;

	// Play the winner music
	PlayWave(MAKEINTRESOURCE(IDR_WINNER), SND_ASYNC | SND_MEMORY);

	CTime tm = CTime::GetCurrentTime();
	strDateTime = tm.Format(_T("%A, %B %d, %Y"));

	pDoc = (CPenteDoc*)((CMainFrame*)m_pMainWnd)->GetActiveDocument();
	ASSERT_VALID(pDoc);

	CString strPlayerOne = pDoc->GetPlayerOne();
	CString strPlayerTwo = pDoc->GetPlayerTwo();

	ASSERT(!strPlayerOne.IsEmpty());
	ASSERT(!strPlayerTwo.IsEmpty());

	// Who won the game
	UINT nWinner = pDoc->GetCurrentTurn();

	// Add the Score to the registry
	AddScore(strPlayerOne, strPlayerTwo, nWinner == PLAYER_ONE_TURN ? 0 : 1, strDateTime);

	// Show the winner and prompt for new game
	if (pDoc->GetPlayMode() == PLAYER_VS_PLAYER) {
		if (nWinner == PLAYER_ONE_TURN) {
			strMessage.Format(IDS_WINNER, strPlayerOne);
		} else {
			strMessage.Format(IDS_WINNER, strPlayerTwo);
		}
	} else {
		if (nWinner == PLAYER_ONE_TURN) {
			strMessage.LoadString(IDS_HUMANWIN);
		} else {
			strMessage.LoadString(IDS_COMPUTERWIN);
		}
	}

	if (AfxMessageBox(strMessage, MB_USERICON | MB_YESNO) == IDYES) {
		pDoc->OnNewDocument();
	} else {
		OnExit();
	}
}

VOID CPenteApp::OnExit()
{
	CPenteDoc*	pDoc;
	CMainFrame* pFrame;

	pFrame = (CMainFrame*)m_pMainWnd;
	ASSERT_VALID(pFrame);

	pDoc = (CPenteDoc*)pFrame->GetActiveDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->CanCloseFrame((CFrameWnd*)this)) {
		GetMainWnd()->DestroyWindow();
	}
}

BOOL CPenteApp::GetRegistryInformation(LPCTSTR lpszKeyName, LPCTSTR lpszValueName, PPBYTE ppData, UINT nType)
{
	BOOL fRtn = FALSE;
	HKEY hKey = NULL;

	// Initialize 'out' parameter
	*ppData = NULL;

	CString strRegKey (m_lpszRegPath);
	strRegKey += lpszKeyName;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		DWORD dwType;
		DWORD dwSize;

		// Get size of needed buffer
		if (RegQueryValueEx(hKey, lpszValueName, NULL, NULL, NULL, &dwSize) == ERROR_SUCCESS) {
			*ppData = new BYTE[dwSize];
			if (!ppData) {
				RegCloseKey(hKey);
				return fRtn;
			}

			if (RegQueryValueEx(hKey, lpszValueName, NULL, &dwType, *ppData, &dwSize) == ERROR_SUCCESS) {
				if (dwType == nType) {
					fRtn = TRUE;
				}
			}
		}
	}

	if (hKey) {
		RegCloseKey(hKey);
	}

	return fRtn;
}

BOOL CPenteApp::UpdateRegistryInformation(LPCTSTR lpszKeyName, LPCTSTR lpszValueName, LPBYTE pData, UINT nType, UINT nBytes /* = 0 */)
{
	BOOL fRtn = FALSE;
	HKEY hKey = NULL;

	CString strRegKey (m_lpszRegPath);
	strRegKey += lpszKeyName;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegKey, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
		DWORD dwSize;
		switch (nType) {
		case REG_SZ:
			dwSize = lstrlen((LPTSTR)pData);
			break;
		case REG_DWORD:
			dwSize = sizeof(DWORD);
			break;
		case REG_BINARY:
			ASSERT(nBytes);
			dwSize = nBytes;
			break;
		default:
			// Unknown Type
			RegCloseKey(hKey);
			return fRtn;
		}

		if (RegSetValueEx(hKey, lpszValueName, 0, nType, (LPBYTE)pData, dwSize) == ERROR_SUCCESS) {
			fRtn = TRUE;
		}
	}

	if (hKey) {
		RegCloseKey(hKey);
	}

	return fRtn;
}

VOID CPenteApp::AddScore(const CString & strPlayerOne, const CString & strPlayerTwo, UINT nWinner, const CString & strDateTime)
{
	CString	strNewScore;

	ASSERT(!strPlayerOne.IsEmpty());
	ASSERT(!strPlayerTwo.IsEmpty());
	ASSERT(!strDateTime.IsEmpty());

	strNewScore.Format(_T("%s\t%s\t%s\t%s\t"), strPlayerOne, strPlayerTwo,
	                   nWinner == 0 ? strPlayerOne : strPlayerTwo, strDateTime);

	CScores scores;

	scores.Init();

	// Delegate this function to the CSCores object
	scores.AddScore(strNewScore);
}

VOID CPenteApp::OnSettings()
{
	CSettingsDlg dlg(IDS_SETTINGS, AfxGetMainWnd());

	// Initialize the dialog and
	// build property pages
	dlg.Init();

	dlg.DoModal();
}

///////////////////////////////////////////////////////////////////
// CPenteApp initialization

BOOL CPenteApp::InitInstance()
{
	// Load the resource dll
	m_hDllInst = ::LoadLibrary(_T("wpres32.dll"));
	if (!m_hDllInst) {
		return FALSE;
	}

	// set the default resource handle
	AfxSetResourceHandle(m_hDllInst);

	// Ensure valid screen resolution
	if (!IsValidResolution()) {
		return FALSE;
	}

	// Set debug options
	LPDWORD	lpdwValue;
	if (GetRegistryInformation(_T("option"), _T("EnableDebug"), (PPBYTE)&lpdwValue, REG_DWORD)) {
		m_fEnableDebug = (*lpdwValue == 1);
		delete lpdwValue;
	}

	// Register the application's document template
	CSingleDocTemplate* pDocTemplate;

	pDocTemplate = new CSingleDocTemplate(
	    IDR_MAINFRAME,
	    RUNTIME_CLASS(CPenteDoc),
	    RUNTIME_CLASS(CMainFrame),      // main SDI frame window
	    RUNTIME_CLASS(CPenteView));

	AddDocTemplate(pDocTemplate);

	// Parse command line (this is required by doc/view)
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo)) {
		return FALSE;
	}

	// Enable file manager drag/drop and DDE Execute open
	RegisterShellFileTypes();
	EnableShellOpen();

	ASSERT_VALID(m_pMainWnd);

	return TRUE;
}

INT CPenteApp::ExitInstance()
{
	if (m_hDllInst) ::FreeLibrary(m_hDllInst);

	return CWinApp::ExitInstance();
}

///////////////////////////////////////////////////////////////////
// Declare and initialize the sole CPenteApp object
CPenteApp ThePenteApp;


