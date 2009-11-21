// BackendsView.cpp : implementation file
//

#include "stdafx.h"
#include "backends.h"
#include "backendsDoc.h"
#include "BackendsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BackendsView

IMPLEMENT_DYNCREATE(BackendsView, CFormView)

BackendsView::BackendsView()
		: CFormView(BackendsView::IDD)
{
	//{{AFX_DATA_INIT(BackendsView)
	m_osversion = _T("");
	m_reposCount = _T("");
	m_FileCache = _T("");
	m_CompilerVersion = _T("");
	m_rawCount = _T("");
	//}}AFX_DATA_INIT
}

BackendsView::~BackendsView()
{
}

void BackendsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BackendsView)
	DDX_Control(pDX, IDC_LST_PRODUCTS, m_ProductList);
	DDX_Text(pDX, IDC_OSVER, m_osversion);
	DDX_Text(pDX, IDC_REPOS_COUNT, m_reposCount);
	DDX_Text(pDX, IDC_FILECACHE, m_FileCache);
	DDX_Text(pDX, IDC_COMPILERVER, m_CompilerVersion);
	DDX_Text(pDX, IDC_RAW_COUNT, m_rawCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BackendsView, CFormView)
	//{{AFX_MSG_MAP(BackendsView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BackendsView diagnostics

#ifdef _DEBUG
void BackendsView::AssertValid() const
{
	CFormView::AssertValid();
}

void BackendsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// BackendsView message handlers

void BackendsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	Config *pconfig = (Config *)lHint;
	if (pconfig == NULL)
		return;

	m_FileCache.Format(_T("%d%%"), pconfig->fileCache);
	m_CompilerVersion.Format(_T("Microsoft Visual Studio 6.0 Service Pack %d"),
	                         pconfig->servicePack);
	m_osversion =  pconfig->osversion;
	m_reposCount.Format(_T("%d"), pconfig->reposCount);
	m_rawCount.Format(_T("%d"), pconfig->rawCount);

	m_ProductList.DeleteAllItems();

	for (int i = 0; i < pconfig->pcount; i++) {
		CString product = pconfig->products[i];
		product.MakeUpper();
		m_ProductList.InsertItem(i, product);
	}

	UpdateData(FALSE);
}

void BackendsView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_ProductList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

	ListView_SetExtendedListViewStyleEx(m_ProductList, 0, dwStyle);
	InsertHeaders();
}

/////////////////////////////////////////////////////////////////////////////
void BackendsView::InsertHeaders()
{
	static LPCTSTR headers[] = { _T("Products") };

	UINT count = sizeof(headers) / sizeof(LPCTSTR);
	CRect rc;

	m_ProductList.GetClientRect(rc);

	UINT width = rc.Width() / count;

	LV_COLUMN lvc;
	for (UINT i = 0; i < count; i++) {
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
		lvc.fmt	= LVCFMT_LEFT;
		lvc.cx = width;
		lvc.pszText = (LPTSTR)headers[i];
		lvc.cchTextMax = MAX_PATH;

		m_ProductList.InsertColumn(i, &lvc);
	}
}

int BackendsView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
