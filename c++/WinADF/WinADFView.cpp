// WinADFView.cpp : implementation of the WinADFView class
//

#include "stdafx.h"
#include "WinADF.h"
#include "WinADFDoc.h"
#include "WinADFView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// WinADFView

IMPLEMENT_DYNCREATE(WinADFView, CListView)

BEGIN_MESSAGE_MAP(WinADFView, CListView)
	ON_WM_CREATE()
	ON_WM_STYLECHANGED()

	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)	
END_MESSAGE_MAP()

// WinADFView construction/destruction

WinADFView::WinADFView()
{
}

WinADFView::~WinADFView()
{
}

BOOL WinADFView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void WinADFView::OnInitialUpdate()
{
	ListView_SetExtendedListViewStyleEx(*this, 		0, 		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |		LVS_EX_INFOTIP | LVS_EX_DOUBLEBUFFER |
		LVS_EX_SNAPTOGRID | LVS_EX_JUSTIFYCOLUMNS |
		LVS_EX_TRANSPARENTBKGND | LVS_EX_AUTOSIZECOLUMNS	);
	
	InsertHeaders();

	CListView::OnInitialUpdate();	
}

void WinADFView::InsertHeaders()
{
	LPCTSTR headers[] = {
		_T("Name"),
		_T("Comment"),
		_T("Size"),
		_T("Permissions"),
		_T("Last Modified")
	};

	uint32_t ncount = sizeof (headers) / sizeof (LPCTSTR);

	LV_COLUMN lvc;
	CRect rc;
	GetListCtrl().GetClientRect(&rc);
		
	for (uint32_t i = 0; i < ncount; i++) {	
		lvc.mask = LVCF_TEXT | LVCF_WIDTH;
		lvc.cx = rc.Width() / ncount;
		lvc.pszText	= (LPTSTR)headers[i];
		lvc.cchTextMax = lstrlen(headers[i]);		
		GetListCtrl().InsertColumn(i, &lvc);
	}
}

void WinADFView::OnUpdate(CView* pSender, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	WinADFDoc *pdoc = GetDocument();
	EntryList entries = pdoc->readdir();
	
	CListCtrl &list = GetListCtrl();
	list.DeleteAllItems();
	
	LVITEM item;
	memset(&item, 0, sizeof(LVITEM));
	item.mask = LVIF_TEXT | LVIF_IMAGE;
	item.iSubItem = 0;

	EntryList::const_iterator it = entries.begin();
	uint32_t i;
	for (i = 0; it != entries.end(); it++, i++) {
		const Entry &entry = *it;

		item.iItem = i;		
		item.iImage = entry.type == ST_DIR ? 0 : 1;
		item.pszText = (LPSTR)entry.name.c_str();
		item.cchTextMax = strlen(item.pszText);
		list.InsertItem(&item);

		list.SetItemText(i, 1, entry.comment.c_str());

		if (entry.type != ST_DIR) {
			CString size;
			size.Format("%d", entry.size);
			list.SetItemText(i, 2, size);
		}
	}
}

int WinADFView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_ImageList.Create(16, 16, ILC_MASK | ILC_COLOR8, 2, 0)) {
		TRACE0("Could not create image list.\n");
		return -1;
	}

	AddImages();

	CListCtrl &list = GetListCtrl();
	list.SetImageList(&m_ImageList, LVSIL_NORMAL);
	
	return 0;
}

void WinADFView::AddImages()
{
	static uint32_t images[] = {
		IDR_FOLDER,	
		IDR_DOCUMENT
	};

	int nimages = sizeof(images) / sizeof(UINT);

	for (int i = 0; i < nimages; i++) {
		HICON hIcon = (HICON)::LoadImage(AfxGetResourceHandle(),
			MAKEINTRESOURCE(images[i]),
			IMAGE_ICON,
			16, 16,
			LR_LOADTRANSPARENT | LR_SHARED);
		ASSERT(hIcon != NULL);
		m_ImageList.Add(hIcon);
	}
}


// WinADFView printing

BOOL WinADFView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void WinADFView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void WinADFView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}


// WinADFView diagnostics

#ifdef _DEBUG
void WinADFView::AssertValid() const
{
	CListView::AssertValid();
}

void WinADFView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

WinADFDoc* WinADFView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WinADFDoc)));
	return (WinADFDoc*)m_pDocument;
}
#endif //_DEBUG


// WinADFView message handlers
void WinADFView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	CListView::OnStyleChanged(nStyleType, lpStyleStruct);
}
