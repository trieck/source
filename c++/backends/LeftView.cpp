// LeftView.cpp : implementation of the LeftView class
//

#include "stdafx.h"
#include "backends.h"

#include "backendsDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LeftView

IMPLEMENT_DYNCREATE(LeftView, CTreeView)

BEGIN_MESSAGE_MAP(LeftView, CTreeView)
	//{{AFX_MSG_MAP(LeftView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteitem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

namespace {	// anonymous

bool ReadFromRegistry(LPCTSTR server, Config *config);
DWORD ReadPagePool(const HKEY hParentKey);
DWORD ReadCompiler(const HKEY hParentKey);
CString ReadOSVersion(const HKEY hParentKey);
DWORD GetReposCount(LPCTSTR server);
DWORD GetRawCount(LPCTSTR server);
void GetProducts(LPCTSTR server, Config *config);
DWORD recurseRepos(LPCTSTR path);
DWORD recurseRawContent(LPCTSTR path);
void recurseProducts(LPCTSTR path, Config *config);
void DisplayError(DWORD err);

} // anonymous

/////////////////////////////////////////////////////////////////////////////
// LeftView construction/destruction

LeftView::LeftView()
{
}

LeftView::~LeftView()
{
}

BOOL LeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= TVS_SHOWSELALWAYS | TVS_HASBUTTONS | TVS_FULLROWSELECT;

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// LeftView drawing

void LeftView::OnDraw(CDC* pDC)
{
	BackendsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


void LeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// set image list in tree control
	GetTreeCtrl().SetImageList(&imageList, TVSIL_NORMAL);

	BackendsApp *pApp = (BackendsApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	GetTreeCtrl().SetFont(pApp->getFont());

	BackendsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	TVINSERTSTRUCT tvInsert;
	memset(&tvInsert, 0, sizeof(TVINSERTSTRUCT));

	tvInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_PARAM;

	StringVector::const_iterator it = pDoc->getMachines();
	for ( ; it != pDoc->getMachinesEnd(); it++) {
		tvInsert.item.pszText = (LPTSTR)(LPCTSTR)*it;
		tvInsert.item.lParam = NULL;
		GetTreeCtrl().InsertItem(&tvInsert);
	}
}

/////////////////////////////////////////////////////////////////////////////
// LeftView diagnostics

#ifdef _DEBUG
void LeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void LeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

BackendsDoc* LeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(BackendsDoc)));
	return (BackendsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// LeftView message handlers

BOOL LeftView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// create the image list
	if (!imageList.Create(16, 16, ILC_COLOR8 | ILC_MASK, 1, 8)) {
		TRACE0("unable to create image list.");
		return FALSE;
	}

	// add initial image
	if (imageList.Add(AfxGetApp()->LoadIcon(IDI_MACHINE)) == -1) {
		TRACE0("unable to add to image list.");
		return FALSE;
	}

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

/////////////////////////////////////////////////////////////////////////////
void LeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	*pResult = 0;
	CWaitCursor wait;

	Config *pconfig = (Config*)pNMTreeView->itemNew.lParam;
	if (pconfig == NULL) {
		pconfig = new Config();
		memset(pconfig, 0, sizeof(Config));

		HTREEITEM hItem = pNMTreeView->itemNew.hItem;
		CString server = GetTreeCtrl().GetItemText(hItem);

		ReadFromRegistry(server, pconfig);
		pconfig->reposCount = GetReposCount(server);
		pconfig->rawCount = GetRawCount(server);
		GetProducts(server, pconfig);
		GetTreeCtrl().SetItemData(hItem, (LPARAM)pconfig);
	}
	GetDocument()->UpdateAllViews(this, (LPARAM)pconfig, this);
}

/////////////////////////////////////////////////////////////////////////////
namespace {	// anonymous

/////////////////////////////////////////////////////////////////////////////
bool ReadFromRegistry(LPCTSTR server, Config *config)
{
	HKEY hParentKey = NULL;

	LONG result = ::RegConnectRegistry(server, HKEY_LOCAL_MACHINE, &hParentKey);
	if (result != ERROR_SUCCESS) {
		DisplayError(result);
		return false;
	}

	// read page pool settings
	DWORD dwFileCache = ReadPagePool(hParentKey);
	if (dwFileCache != (DWORD)-1)
		config->fileCache = dwFileCache;

	// read compiler settings
	DWORD svcPack = ReadCompiler(hParentKey);
	if (svcPack != (DWORD)-1)
		config->servicePack = svcPack;

	// read operating system version
	CString version = ReadOSVersion(hParentKey);
	_tcsncpy(config->osversion, version, MAX_PATH);

	::RegCloseKey(hParentKey);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
DWORD ReadPagePool(const HKEY hParentKey)
{
	static LPCTSTR KeyName = _T("SYSTEM\\CurrentControlSet\\Control\\Session Manager")
	                         _T("\\Memory Management");
	static LPCTSTR ValueName = _T("UnusedFileCache");

	HKEY hKey;

	LONG result = ::RegOpenKeyEx(hParentKey, KeyName, 0, KEY_QUERY_VALUE, &hKey);
	if (result != ERROR_SUCCESS) {
		DisplayError(result);
		return -1;
	}

	DWORD dwValue;
	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof(DWORD);

	result = ::RegQueryValueEx(hKey,
	                           ValueName, NULL,
	                           &dwType,
	                           (LPBYTE)&dwValue,
	                           &dwSize);

	if (result != ERROR_SUCCESS) {
		::RegCloseKey(hKey);
		DisplayError(result);
		return -1;
	}

	::RegCloseKey(hKey);

	return dwValue;
}

/////////////////////////////////////////////////////////////////////////////
DWORD ReadCompiler(const HKEY hParentKey)
{
	static LPCTSTR KeyName = _T("SOFTWARE\\Microsoft\\VisualStudio\\6.0\\ServicePacks");
	static LPCTSTR ValueName = _T("latest");

	HKEY hKey;

	LONG result = ::RegOpenKeyEx(hParentKey, KeyName, 0, KEY_QUERY_VALUE, &hKey);
	if (result != ERROR_SUCCESS) {
		DisplayError(result);
		return -1;
	}

	DWORD dwValue;
	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof(DWORD);

	result = ::RegQueryValueEx(hKey,
	                           ValueName, NULL,
	                           &dwType,
	                           (LPBYTE)&dwValue,
	                           &dwSize);

	if (result != ERROR_SUCCESS) {
		::RegCloseKey(hKey);
		DisplayError(result);
		return -1;
	}

	::RegCloseKey(hKey);

	return dwValue;
}

/////////////////////////////////////////////////////////////////////////////
CString ReadOSVersion(const HKEY hParentKey)
{
	static LPCTSTR KeyName = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");

	HKEY hKey;
	CString output;

	LONG result = ::RegOpenKeyEx(hParentKey, KeyName, 0, KEY_QUERY_VALUE, &hKey);
	if (result != ERROR_SUCCESS) {
		DisplayError(result);
		return _T("");
	}

	DWORD dwType = REG_SZ;
	TCHAR currentVersion[MAX_PATH], CSDVersion[MAX_PATH];
	DWORD dwSize = MAX_PATH;

	result = ::RegQueryValueEx(hKey,
	                           _T("CurrentVersion"), NULL,
	                           &dwType,
	                           (LPBYTE)currentVersion,
	                           &dwSize);
	if (result != ERROR_SUCCESS) {
		::RegCloseKey(hKey);
		DisplayError(result);
		return _T("");
	}

	dwSize = MAX_PATH;

	result = ::RegQueryValueEx(hKey,
	                           _T("CSDVersion"), NULL,
	                           &dwType,
	                           (LPBYTE)CSDVersion,
	                           &dwSize);
	if (result != ERROR_SUCCESS) {
		::RegCloseKey(hKey);
		DisplayError(result);
		output.Format(_T("Microsoft Windows NT %s"), currentVersion);
		return output;
	}

	output.Format(_T("Microsoft Windows NT %s %s"), currentVersion,
	              CSDVersion);

	::RegCloseKey(hKey);

	return output;
}

/////////////////////////////////////////////////////////////////////////////
void DisplayError(DWORD error)
{
	LPVOID lpMsgBuf;

	FormatMessage(
	    FORMAT_MESSAGE_ALLOCATE_BUFFER |
	    FORMAT_MESSAGE_FROM_SYSTEM |
	    FORMAT_MESSAGE_IGNORE_INSERTS,
	    NULL,
	    error,
	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
	    (LPTSTR) &lpMsgBuf,
	    0,
	    NULL
	);

	TRACE0((LPCTSTR)lpMsgBuf);

	// Free the buffer.
	LocalFree(lpMsgBuf);
}

/////////////////////////////////////////////////////////////////////////////
DWORD GetReposCount(LPCTSTR server)
{
	CString path;
	path.Format(_T("\\\\%s\\DDrive\\XContent"), server);

	return recurseRepos(path);
}

/////////////////////////////////////////////////////////////////////////////
DWORD recurseRepos(LPCTSTR path)
{
	WIN32_FIND_DATA data;

	CString pattern;
	pattern.Format(_T("%s\\*"), path);

	HANDLE hFile = FindFirstFile(pattern, &data);
	if (hFile == INVALID_HANDLE_VALUE) {
		DisplayError(GetLastError());
		return 0;
	}

	DWORD count = 0;

	do {
		if (_tcscmp(data.cFileName, _T(".")) == 0)
			continue;

		if (_tcscmp(data.cFileName, _T("..")) == 0)
			continue;

		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			CString dir;
			dir.Format(_T("%s\\%s"), path, data.cFileName);
			count += recurseRepos(dir);
		} else {
			TCHAR ext[_MAX_EXT];
			_tsplitpath(data.cFileName, NULL, NULL, NULL, ext);
			if (_tcsicmp(ext, _T(".xml")) == 0)
				count++;
		}
	} while (FindNextFile(hFile, &data));

	FindClose(hFile);

	return count;
}

/////////////////////////////////////////////////////////////////////////////
void GetProducts(LPCTSTR server, Config *config)
{
	CString path;
	path.Format(_T("\\\\%s\\DDrive\\XContent"), server);

	recurseProducts(path, config);
}

/////////////////////////////////////////////////////////////////////////////
void recurseProducts(LPCTSTR path, Config *config)
{
	WIN32_FIND_DATA data;

	CString pattern;
	pattern.Format(_T("%s\\*"), path);

	HANDLE hFile = FindFirstFile(pattern, &data);
	if (hFile == INVALID_HANDLE_VALUE) {
		DisplayError(GetLastError());
		return;
	}

	do {
		if (_tcscmp(data.cFileName, _T(".")) == 0)
			continue;

		if (_tcscmp(data.cFileName, _T("..")) == 0)
			continue;

		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			_tcscpy(config->products[config->pcount++], data.cFileName);
			CString dir;
			dir.Format(_T("%s\\%s"), path, data.cFileName);
			recurseProducts(dir, config);
		}
	} while (FindNextFile(hFile, &data));

	FindClose(hFile);
}

/////////////////////////////////////////////////////////////////////////////
DWORD GetRawCount(LPCTSTR server)
{
	CString path;
	path.Format(_T("\\\\%s\\DDrive\\Infoamdata"), server);

	return recurseRawContent(path);
}

/////////////////////////////////////////////////////////////////////////////
DWORD recurseRawContent(LPCTSTR path)
{
	WIN32_FIND_DATA data;

	CString pattern;
	pattern.Format(_T("%s\\*"), path);

	HANDLE hFile = FindFirstFile(pattern, &data);
	if (hFile == INVALID_HANDLE_VALUE) {
		DisplayError(GetLastError());
		return 0;
	}

	DWORD count = 0;

	do {
		if (_tcscmp(data.cFileName, _T(".")) == 0)
			continue;

		if (_tcscmp(data.cFileName, _T("..")) == 0)
			continue;

		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			CString dir;
			dir.Format(_T("%s\\%s"), path, data.cFileName);
			count += recurseRawContent(dir);
		} else {
			TCHAR ext[_MAX_EXT];
			_tsplitpath(data.cFileName, NULL, NULL, NULL, ext);
			if (_tcsicmp(ext, _T(".seq")) == 0)
				count++;
		}
	} while (FindNextFile(hFile, &data));

	FindClose(hFile);

	return count;
}


} // anonymous

void LeftView::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	Config *pconfig = (Config*)pNMTreeView->itemOld.lParam;
	if (pconfig != NULL)
		delete pconfig;

	*pResult = 0;
}
