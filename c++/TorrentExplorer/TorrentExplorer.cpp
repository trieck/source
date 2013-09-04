// TorrentExplorer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TorrentSettings.h"
#include "TorrentExplorer.h"
#include "TorrentObject.h"
#include "Dictionary.h"
#include "String.h"
#include "Integer.h"
#include "List.h"
#include "GripBar.h"
#include "MainFrm.h"
#include "TorrentDoc.h"
#include "TorrentView.h"
#include "SettingsSheet.h"
#include "StringTokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TorrentExplorer

BEGIN_MESSAGE_MAP(TorrentExplorer, CWinApp)
	//{{AFX_MSG_MAP(TorrentExplorer)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TOOLS_SETTINGS, OnSettings)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TorrentExplorer construction

TorrentExplorer::TorrentExplorer()
	: m_pSettings(NULL), m_pPalette(NULL), m_hMutex(INVALID_HANDLE_VALUE)
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only TorrentExplorer object

TorrentExplorer theApp;

/////////////////////////////////////////////////////////////////////////////
// TorrentExplorer initialization

BOOL TorrentExplorer::InitInstance()
{
	// Allow only a single instance
	if (!CheckInstance())
		return FALSE;

	if (!AfxOleInit())
		return FALSE;

	if (!LoadPalette())
		return FALSE;

	SetRegistryKey("Rieck Enterprises");
	LoadStdProfileSettings();

	m_pSettings = new TorrentSettings();

	// Register document templates
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
	    IDR_MAINFRAME,
	    RUNTIME_CLASS(TorrentDoc),
	    RUNTIME_CLASS(MainFrame),       // main SDI frame window
	    RUNTIME_CLASS(TorrentView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

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
void TorrentExplorer::OnAppAbout()
{
	AboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// TorrentExplorer message handlers

/////////////////////////////////////////////////////////////////////////////
// Global functions

/////////////////////////////////////////////////////////////////////////////
void PumpMessages()
{
	CWinThread *pThread = AfxGetApp();
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (!pThread->PumpMessage()) {
			break;
		}
	}
	LONG lIdle = 0;
	while (pThread->OnIdle(lIdle++))
		;
}

//////////////////////////////////////////////////////////////////////
void ThrowUserException(UINT nFormatID, ...)
{
	CString strFormat, strMessage;
	VERIFY(strFormat.LoadString(nFormatID) != 0);

	va_list argList;
	va_start(argList, nFormatID);
	strMessage.FormatV(strFormat, argList);
	va_end(argList);

	AfxMessageBox(strMessage);
	AfxThrowUserException();
}

//////////////////////////////////////////////////////////////////////
// return topmost dialog parent for a window
CDialog *GetTopmostDlgParent(CWnd *pWnd)
{
	if (pWnd->GetSafeHwnd() == NULL) // no Window attached
		return NULL;

	CDialog *pDlg = NULL;

	HWND hWndParent = *pWnd;
	HWND hWndT;
	while ((hWndT = AfxGetParentOwner(hWndParent)) != NULL) {
		CWnd *pParent = CWnd::FromHandle(hWndT);
		if (pParent->IsKindOf(RUNTIME_CLASS(CDialog)))
			pDlg = (CDialog*)pParent;
		hWndParent = hWndT;
	}

	return pDlg;
}

int TorrentExplorer::ExitInstance()
{
	if (m_pSettings) {
		delete m_pSettings;
		m_pSettings = NULL;
	}

	if (m_pPalette) {
		delete m_pPalette;
		m_pPalette = NULL;
	}

	if (m_hMutex != INVALID_HANDLE_VALUE) {
		CloseHandle(m_hMutex);
	}

	return CWinApp::ExitInstance();
}

void TorrentExplorer::OnSettings()
{
	SettingsSheet sheet(IDS_SETTINGS, m_pMainWnd);
	if (sheet.DoModal() == IDOK) {
		;
	}
}

void TorrentExplorer::PutSetting(LPCSTR key, LPCSTR val)
{
	if (m_pSettings) {
		m_pSettings->SetValue(key, new String(val));
	}
}

void TorrentExplorer::PutSetting(LPCSTR key, __int64 val)
{
	if (m_pSettings) {
		m_pSettings->SetValue(key, new Integer(val));
	}
}

LPTORRENTOBJECT TorrentExplorer::GetSetting(LPCSTR key)
{
	if (m_pSettings) {
		return m_pSettings->GetValue(key);
	}
	return NULL;
}

BOOL TorrentExplorer::GetBOOLSetting(LPCSTR key)
{
	if (m_pSettings) {
		LPTORRENTOBJECT o = m_pSettings->GetValue(key);
		if (o == NULL || o->GetElementType() != ET_INTEGER)
			return FALSE;
		return *(LPINTEGER)o;
	}

	return FALSE;
}

__int64 TorrentExplorer::GetIntSetting(LPCSTR key)
{
	if (m_pSettings) {
		LPTORRENTOBJECT o = m_pSettings->GetValue(key);
		if (o == NULL || o->GetElementType() != ET_INTEGER)
			return FALSE;
		return *(LPINTEGER)o;
	}

	return 0;
}

BOOL TorrentExplorer::LoadPalette()
{
	HRSRC hResource = ::FindResource(AfxGetResourceHandle(),
	                                 MAKEINTRESOURCE(IDR_DEF_PALETTE),
	                                 "PALETTE");
	if (hResource == NULL)
		return FALSE;

	HGLOBAL hGlobal = ::LoadResource(AfxGetResourceHandle(), hResource);
	if (hGlobal == NULL)
		return FALSE;

	LPCSTR pResource = (LPCSTR)::LockResource(hGlobal);
	if (pResource == NULL) {
		UnlockResource(hGlobal);
		FreeResource(hGlobal);
		return FALSE;
	}

	StringTokenizer tokenizer(pResource, "\r\n");
	CString tok;

	int red, green, blue;
	COLORREF color;

	m_pPalette = new RGBTRIPLE[NUM_PALETTE_COLORS];
	for (int i = 0; i < NUM_PALETTE_COLORS
	        && (tok = tokenizer.next()) != ""; i++) {
		sscanf(tok, "%d %d %d", &red, &green, &blue);
		color = RGB(red, green, blue);
		m_pPalette[i].rgbtRed = (BYTE)red;
		m_pPalette[i].rgbtGreen = (BYTE)green;
		m_pPalette[i].rgbtBlue = (BYTE)blue;
		m_ColorMap[color] = i;
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return TRUE;
}

BOOL TorrentExplorer::GetPaletteIndex(COLORREF c, int &i) const
{
	if (!m_ColorMap.Lookup(c, i))
		return FALSE;

	return TRUE;
}

BOOL TorrentExplorer::IsSetting(LPCSTR key)
{
	if (m_pSettings) {
		LPTORRENTOBJECT o = m_pSettings->GetValue(key);
		return (o == NULL) ? FALSE : TRUE;
	}

	return FALSE;
}

BOOL TorrentExplorer::CheckInstance()
{
	CString strGUID;
	if (!strGUID.LoadString(IDS_APP_GUID))
		return FALSE;

	m_hMutex = CreateMutex(NULL, FALSE, strGUID);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		LPCSTR lpszClass = MainFrame::RegisterClass();
		CWnd *pWnd = CWnd::FindWindow(lpszClass, NULL);
		if (pWnd != NULL) {
			pWnd->ShowWindow(SW_RESTORE);
		}
		return FALSE;
	}

	return TRUE;
}

