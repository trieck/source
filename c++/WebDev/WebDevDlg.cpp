
// WebDevDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WebDev.h"
#include "WebDevDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// helper functions
CString LastError();

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWebDevDlg dialog




CWebDevDlg::CWebDevDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWebDevDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebDevDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWebDevDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE_WEBDEV, &CWebDevDlg::OnBnClickedBrowseWebdev)
	ON_BN_CLICKED(IDC_BROWSE_WEBSITE, &CWebDevDlg::OnBnClickedBrowseWebsite)
	ON_BN_CLICKED(IDOK, &CWebDevDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWebDevDlg::OnExit)
END_MESSAGE_MAP()


// CWebDevDlg message handlers

BOOL CWebDevDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CWebDevApp *pApp = (CWebDevApp*)AfxGetApp();
	CString webDevPath = pApp->GetProfileString(_T("Settings"), _T("WebDev.Path"));
	SetDlgItemText(IDC_WEBDEV_PATH, webDevPath);
		
	USHORT port = pApp->GetProfileInt(_T("Settings"), _T("Port"), 0);
	SetDlgItemInt(IDC_PORT, port);

	CString webSitePath = pApp->GetProfileString(_T("Settings"), _T("WebSite.Path"));
	SetDlgItemText(IDC_WEBSITE_PATH, webSitePath);

	CString vPath = pApp->GetProfileString(_T("Settings"), _T("Virtual.Path"));
	SetDlgItemText(IDC_VPATH, vPath);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWebDevDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWebDevDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWebDevDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWebDevDlg::OnBnClickedBrowseWebdev()
{
	static TCHAR BASED_CODE szFilter[] =
	    _T("WebDev.WebServer Programs|WebDev.WebServer*.exe|")
	    _T("All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.exe"), NULL, OFN_HIDEREADONLY | OFN_READONLY,
		szFilter, this);
	int result = dlg.DoModal();
	if (result == IDOK) {
		CString pathName = dlg.GetPathName();		
		GetDlgItem(IDC_WEBDEV_PATH)->SetWindowText(pathName);
	}
}

void CWebDevDlg::OnBnClickedBrowseWebsite()
{
	BROWSEINFO bi;
	CString displayName, fileName;

	memset(&bi, 0, sizeof(BROWSEINFO));
	bi.hwndOwner = *this;
	bi.pszDisplayName = displayName.GetBuffer(_MAX_PATH);
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	displayName.ReleaseBuffer();

	if (pidl != NULL) {
		BOOL fRtn = SHGetPathFromIDList(pidl,
			fileName.GetBuffer(_MAX_PATH));
		fileName.ReleaseBuffer();
		if (fRtn) {
			GetDlgItem(IDC_WEBSITE_PATH)->SetWindowText(fileName);
		}
		CoTaskMemFree(pidl);
	}
}

void CWebDevDlg::OnBnClickedOk()
{
	CString webDevPath;
	GetDlgItemText(IDC_WEBDEV_PATH, webDevPath);
	webDevPath.Trim();
	
	USHORT port = GetDlgItemInt(IDC_PORT);
	
	CString webSitePath;
	GetDlgItemText(IDC_WEBSITE_PATH, webSitePath);
	webSitePath.Trim();
	
	CString vPath;
	GetDlgItemText(IDC_VPATH, vPath);
	vPath.Trim();
	
	CString commandLine;
	commandLine.Format(_T("\"%s\" /port:%u /path:%s /vpath:%s"),
		(LPCTSTR)webDevPath, port, (LPCTSTR)webSitePath, vPath);

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));

	LPTSTR buffer = commandLine.GetBuffer();

	si.cb = sizeof(STARTUPINFO);
	BOOL retcode = CreateProcess(NULL,
		buffer,
	    NULL,
	    NULL,
	    TRUE,
	    0,
	    NULL,
	    NULL,
	    &si,
	    &pi);

	commandLine.ReleaseBuffer();

	if (!retcode) {
		CString message;
		message.Format(_T("Failed to launch \"%s\".\n%s"), commandLine,
			LastError());
		AfxMessageBox(message);
		return;
	}

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}


void CWebDevDlg::OnExit()
{
	CWebDevApp *pApp = (CWebDevApp*)AfxGetApp();

	CString webDevPath;
	GetDlgItemText(IDC_WEBDEV_PATH, webDevPath);
	webDevPath.Trim();
	pApp->WriteProfileString(_T("Settings"), _T("WebDev.Path"), webDevPath);
	
	USHORT port = GetDlgItemInt(IDC_PORT);
	pApp->WriteProfileInt(_T("Settings"), _T("Port"), port);

	CString webSitePath;
	GetDlgItemText(IDC_WEBSITE_PATH, webSitePath);
	webSitePath.Trim();
	pApp->WriteProfileString(_T("Settings"), _T("WebSite.Path"), webSitePath);

	CString vPath;
	GetDlgItemText(IDC_VPATH, vPath);
	vPath.Trim();
	pApp->WriteProfileString(_T("Settings"), _T("Virtual.Path"), vPath);
	
	CDialogEx::OnCancel();
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
		size_t N = _tcslen(pmsg);
		if (N > 1 && pmsg[N - 1] == _T('\n'))
			pmsg[N - 1] = _T('\0');

		if (N > 1 && pmsg[N - 2] == _T('\r'))
			pmsg[N - 2] = _T('\0');

		output = pmsg;
		LocalFree(pmsg);
	}

	return output;
}
