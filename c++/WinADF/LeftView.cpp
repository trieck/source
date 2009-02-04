// LeftView.cpp : implementation of the LeftView class
//

#include "stdafx.h"
#include "WinADF.h"

#include "WinADFDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// LeftView

IMPLEMENT_DYNCREATE(LeftView, CTreeView)

BEGIN_MESSAGE_MAP(LeftView, CTreeView)
	ON_WM_CREATE()

	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTreeView::OnFilePrintPreview)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, &LeftView::OnTvnDeleteitem)
END_MESSAGE_MAP()

static UINT images[] = {
	IDR_FOLDER,	
};

// LeftView construction/destruction

LeftView::LeftView()
{
}

LeftView::~LeftView()
{
}

BOOL LeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= 
		TVS_HASBUTTONS | TVS_HASLINES | TVS_FULLROWSELECT | TVS_INFOTIP
		| TVS_LINESATROOT | TVS_SHOWSELALWAYS;

	return CTreeView::PreCreateWindow(cs);
}

int LeftView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_ImageList.Create(16, 16, ILC_MASK | ILC_COLOR8, 1, 0)) {
		TRACE0("Could not create image list.\n");
		return -1;
	}

	AddImages();

	CTreeCtrl &tree = GetTreeCtrl();
	tree.SetImageList(&m_ImageList, TVSIL_NORMAL);
	
	return 0;
}

void LeftView::AddImages()
{
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

// LeftView printing

BOOL LeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void LeftView::OnDraw(CDC* /*pDC*/)
{
	WinADFDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void LeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void LeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void LeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
}

void LeftView::OnUpdate(CView* pSender, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	ASSERT(pSender != this);
	UNUSED(pSender);     // unused in release builds

	WinADFDoc *pdoc = GetDocument();
	EntryList entries = pdoc->readdir();
	
	CTreeCtrl &tree = GetTreeCtrl();
	tree.DeleteAllItems();
	
	TV_INSERTSTRUCT tvis;
	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = NULL;
	tvis.itemex.mask = TVIF_CHILDREN | TVIF_TEXT | TVIF_IMAGE 
		| TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvis.itemex.iImage = tvis.itemex.iSelectedImage = 0;	
	tvis.itemex.cChildren = 1;

	tvis.itemex.pszText = _T("/");
	tvis.itemex.lParam = NULL;
	tvis.hParent = tree.InsertItem(&tvis);

	EntryList::const_iterator it = entries.begin();
	for ( ; it != entries.end(); it++) {
		const Entry &entry = *it;
		
		if (entry.type != ST_DIR) continue;		
		tvis.itemex.pszText = (LPSTR)(LPCSTR)entry.name.c_str();
		tvis.itemex.lParam = (LPARAM)new Entry(entry);
		tree.InsertItem(&tvis);
	}

	tree.SortChildren(TVI_ROOT);
}


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

WinADFDoc* LeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WinADFDoc)));
	return (WinADFDoc*)m_pDocument;
}
#endif //_DEBUG


// LeftView message handlers

void LeftView::OnTvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	Entry *pEntry = (Entry*)pNMTreeView->itemOld.lParam;
	if (pEntry != NULL) {
		delete pEntry;
	}

	*pResult = 0;
}
