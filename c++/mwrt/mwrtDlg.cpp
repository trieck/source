// mwrtDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mwrt.h"
#include "mwrtDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog {
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CmwrtDlg dialog

static uint32_t getRegType(LPCTSTR t)
{
	if (_tcscmp(t, _T("REG_SZ")) == 0) {
		return REG_SZ;
	}

	if (_tcscmp(t, _T("REG_EXPAND_SZ")) == 0) {
		return REG_EXPAND_SZ;
	}

	if (_tcscmp(t, _T("REG_DWORD")) == 0) {
		return REG_DWORD;
	}

	if (_tcscmp(t, _T("REG_BINARY")) == 0) {
		return REG_BINARY;
	}

	if (_tcscmp(t, _T("REG_MULTI_SZ")) == 0) {
		return REG_MULTI_SZ;
	}

	return REG_NONE;
}

CmwrtDlg::CmwrtDlg(CWnd* pParent /*=NULL*/)
		: CDialog(CmwrtDlg::IDD, pParent)
		, m_Status(_T(""))
		, m_Detail(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmwrtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATUS, m_Status);
	DDX_Text(pDX, IDC_DETAIL, m_Detail);
	DDX_Control(pDX, IDOK, m_Go);
}

BEGIN_MESSAGE_MAP(CmwrtDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CmwrtDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CmwrtDlg message handlers

BOOL CmwrtDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CmwrtApp *pApp = (CmwrtApp*)AfxGetApp();

	CString provider = pApp->GetProfileString(_T("Settings"), _T("ADO.Provider"));
	CString connstr = pApp->GetProfileString(_T("Settings"), _T("ADO.ConnStr"));
	CString logfile = pApp->GetProfileString(_T("Settings"), _T("LogFile"));

	SetDlgItemText(IDC_PROVIDER, provider);
	SetDlgItemText(IDC_CONNSTR, connstr);
	SetDlgItemText(IDC_LOGFILE, logfile);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmwrtDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else {
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CmwrtDlg::OnPaint()
{
	if (IsIconic()) {
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
	} else {
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmwrtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmwrtDlg::OnBnClickedOk()
{
	m_Go.EnableWindow(FALSE);

	try {
		process();
	} catch (_com_error &E) {
		AfxMessageBox(E.Description());
	}

	m_Status.Empty();
	m_Detail.Empty();
	UpdateData(FALSE);

	m_Go.EnableWindow(TRUE);
}

void CmwrtDlg::process() throw()
{
	CString provider, connstr, logfile;

	GetDlgItemText(IDC_PROVIDER, provider);
	GetDlgItemText(IDC_CONNSTR, connstr);
	GetDlgItemText(IDC_LOGFILE, logfile);

	// open logfile
	if (!m_logfile.open(logfile)) {
		AfxMessageBox(LastError());
		return;
	}

	// open database connection
	m_db.open(provider, connstr);
	RecPtr results = m_db.execute(_T("select id, name from malware"));

	bstr_t bstrName;
	uint32_t id;
	while (!results->GetEndOfFile()) {
		id = results->Fields->GetItem(_T("ID"))->Value;
		bstrName = results->Fields->GetItem(_T("Name"))->Value;
		m_Status.Format(IDS_STATUS, (LPCTSTR)bstrName);
		UpdateData(FALSE);

		processFiles(id);
		processRegistry(id);

		results->MoveNext();
	}
}

void CmwrtDlg::processFiles(uint32_t id) throw()
{
	CString query, filename;
	query.Format(_T("select filename from [Files_Added] where ")
	             _T("[MalwareID] = %d"), id);

	RecPtr results = m_db.execute(query);

	bstr_t bstrFilename;
	while (!results->GetEndOfFile()) {
		bstrFilename = results->Fields->GetItem(_T("Filename"))->Value;
		filename = expandString(bstrFilename);
		removeFile(filename);
		results->MoveNext();
	}
}

CString CmwrtDlg::expandString(LPCTSTR input)
{
	DWORD len = _tcslen(input) * 2;

	CString output;
	LPTSTR pbuf = output.GetBuffer(len);

	DWORD count = ExpandEnvironmentStrings(input, pbuf, len);

	output.ReleaseBuffer(count);

	return output;
}

bool CmwrtDlg::removeFile(LPCTSTR filename)
{
	m_Detail.Format(_T("Processing file \"%s\"..."), filename);
	UpdateData(FALSE);

	if (GetFileAttributes(filename) == INVALID_FILE_ATTRIBUTES)
		return false;	// no such file

	m_logfile.log(_T("Attempting to delete file \"%s\"..."),
	              filename);

	if (!DeleteFile(filename)) {
		m_logfile.log(_T("Unable to delete file \"%s\"."),
		              filename);
		return false;
	}

	m_logfile.log(_T("Deleted file \"%s\"."), filename);

	return true;
}

void CmwrtDlg::processRegistry(uint32_t id)
{
	CString query, filename;
	query.Format(_T("select RegKey, Type, ValName, Value from ")
	             _T("[qryRegValues_Added] where ")
	             _T("[MalwareID] = %d"), id);

	RecPtr results = m_db.execute(query);

	bstr_t regKey, type, valName, value;
	while (!results->GetEndOfFile()) {
		regKey = results->Fields->GetItem(_T("RegKey"))->Value;
		type = results->Fields->GetItem(_T("Type"))->Value;
		valName = results->Fields->GetItem(_T("ValName"))->Value;
		value = results->Fields->GetItem(_T("Value"))->Value;

		removeRegValue(regKey, getRegType(type), valName, value);

		results->MoveNext();
	}
}

struct RegEntry {
	HKEY key;
	LPCTSTR rep;
} entries[] = {
	{ HKEY_CLASSES_ROOT, _T("HKCR") },
	{ HKEY_CURRENT_USER, _T("HKCU") },
	{ HKEY_LOCAL_MACHINE, _T("HKLM") },
};

static HKEY getRegKey(LPCTSTR rep)
{

	uint32_t n = sizeof(entries) / sizeof(RegEntry);

	for (uint32_t i = 0; i < n; i++) {
		if (_tcscmp(rep, entries[i].rep) == 0)
			return entries[i].key;
	}

	return NULL;
}

void CmwrtDlg::removeRegValue(LPCTSTR regKey, uint32_t type, LPCTSTR valName,
                              LPCTSTR value)
{
	HKEY hKey;
	CString keyName;
	if ((hKey = splitKey(regKey, keyName)) == NULL) {	// bad key
		return;
	}

	CRegKey K;
	if (K.Open(hKey, keyName, KEY_ALL_ACCESS) != ERROR_SUCCESS) {	// can't open
		return;
	}

	if (K.DeleteValue(valName) != ERROR_SUCCESS) {	// no such value
		return;
	}

	m_logfile.log(_T("Deleted registry value \"%s\\%s\"."),
	              regKey, valName);
}

HKEY CmwrtDlg::splitKey(LPCTSTR regKey, CString & path)
{
	path.Empty();

	LPCTSTR pkey = _tcschr(regKey, '\\');
	if (pkey == NULL || pkey == regKey)
		return NULL;

	CString rootKey(regKey, pkey - regKey);

	HKEY hKey = getRegKey(rootKey);
	if (hKey == NULL)
		return NULL;	// unknown parent key

	path = ++pkey;		// key name

	return hKey;
}
