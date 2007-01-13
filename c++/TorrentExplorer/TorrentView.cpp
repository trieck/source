// TorrentView.cpp : implementation of the TorrentView class
//

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "Dictionary.h"
#include "List.h"
#include "String.h"
#include "Integer.h"
#include "TorrentDoc.h"
#include "TorrentView.h"
#include "GripBar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT images[] = {
	IDI_DICT,	/* dictionary */
	IDI_LIST,	/* list */
	IDI_STRING,	/* string */
	IDI_NUMBER,	/* number */
};

/////////////////////////////////////////////////////////////////////////////
// TorrentView

IMPLEMENT_DYNCREATE(TorrentView, CTreeView)

BEGIN_MESSAGE_MAP(TorrentView, CTreeView)
	//{{AFX_MSG_MAP(TorrentView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_UPDATE_COMMAND_UI(ID_BINARY_VIEW, OnUpdateBinaryView)
	ON_COMMAND(ID_BINARY_VIEW, OnBinaryView)
	ON_UPDATE_COMMAND_UI(ID_DATE_VIEW, OnUpdateDateView)
	ON_COMMAND(ID_DATE_VIEW, OnDateView)
	ON_MESSAGE(WM_SETTING_CHANGE, OnSettingChange)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TorrentView construction/destruction

TorrentView::TorrentView()
 : m_BinaryView(FALSE), m_DateView(FALSE)
{
}

TorrentView::~TorrentView()
{
}

BOOL TorrentView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= 
		TVS_HASBUTTONS | TVS_HASLINES | TVS_FULLROWSELECT | TVS_INFOTIP
		| TVS_LINESATROOT | TVS_SHOWSELALWAYS;

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// TorrentView drawing

void TorrentView::OnDraw(CDC* pDC)
{
	TorrentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void TorrentView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// TorrentView printing

BOOL TorrentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void TorrentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void TorrentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// TorrentView diagnostics

#ifdef _DEBUG
void TorrentView::AssertValid() const
{
	CTreeView::AssertValid();
}

void TorrentView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

TorrentDoc* TorrentView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(TorrentDoc)));
	return (TorrentDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// TorrentView message handlers

void TorrentView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CTreeCtrl &tree = GetTreeCtrl();
	tree.DeleteAllItems();	

	TorrentDoc *pdoc = GetDocument();
	LPDICTIONARY torrent = pdoc->GetTorrent();
	if (torrent != NULL)
		InsertDict(TVI_ROOT, torrent);
}

int TorrentView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_ImageList.Create(16, 16, ILC_MASK | ILC_COLOR8, 0, 4)) {
		TRACE0("Could not create image list.\n");
		return -1;
	}

	AddImages();

	CTreeCtrl &tree = GetTreeCtrl();
	tree.SetImageList(&m_ImageList, TVSIL_NORMAL);

	OnSettingChange(0, 0);
	
	return 0;
}

void TorrentView::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
		
	OnExpanding(&pNMTreeView->itemNew);

	*pResult = 0;
}

void TorrentView::OnExpanding(LPTVITEM item)
{
	CTreeCtrl &tree = GetTreeCtrl();
	HTREEITEM hChild = tree.GetChildItem(item->hItem);
	if (hChild != NULL) return;	// already expanded

	CWaitCursor cursor;
	LPTORRENTOBJECT pitem = (LPTORRENTOBJECT)item->lParam;
	if (pitem != NULL) 
		InsertItem(item->hItem, pitem);
}

void TorrentView::InsertItem(HTREEITEM hParent, LPTORRENTOBJECT Object)
{
	switch (Object->GetElementType()) {
	case ET_DICT:
		InsertDict(hParent, (LPDICTIONARY)Object);
		break;
	case ET_LIST:
		InsertList(hParent, (LPLIST)Object);
		break;
	case ET_INTEGER:
		InsertInt(hParent, (LPINTEGER)Object);
		break;
	case ET_STRING:
		InsertString(hParent, (LPSTRING)Object);
		break;
	}
}

void TorrentView::InsertDict(HTREEITEM hParent, LPDICTIONARY d)
{
	CTreeCtrl &tree = GetTreeCtrl();
	
	TV_INSERTSTRUCT tvis;
	LPTORRENTOBJECT element;
	tvis.hParent = hParent;
	tvis.hInsertAfter = hParent;
	tvis.itemex.mask = TVIF_CHILDREN | TVIF_TEXT | TVIF_PARAM 
		| TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		
	KeyVec keys = d->GetKeys();
	KeyVec::const_iterator it = keys.begin();
	for ( ; it != keys.end(); it++) {
		element = d->Get(*it);
		if (element == NULL) continue;

		switch (element->GetElementType()) {
		case ET_DICT:
			tvis.itemex.iImage = tvis.itemex.iSelectedImage = 0;	
			tvis.itemex.cChildren = 1;
			break;
		case ET_LIST:
			tvis.itemex.iImage = tvis.itemex.iSelectedImage = 1;	
			tvis.itemex.cChildren = 1;
			break;
		case ET_STRING:
			tvis.itemex.iImage = tvis.itemex.iSelectedImage = 2;	
			tvis.itemex.cChildren = 0;
			break;
		case ET_INTEGER:
			tvis.itemex.iImage = tvis.itemex.iSelectedImage = 3;	
			tvis.itemex.cChildren = 0;
			break;
		}		

		tvis.itemex.pszText = (LPSTR)(LPCSTR)*it;
		tvis.itemex.lParam = (LPARAM)element;
		tree.InsertItem(&tvis);
	}

	tree.SortChildren(hParent);
}

void TorrentView::InsertList(HTREEITEM hParent, LPLIST l)
{
	CTreeCtrl &tree = GetTreeCtrl();
	
	for (int i = 0; i < l->size(); i++) {
		InsertListItem(hParent, l->GetAt(i));
	}		
}

void TorrentView::InsertListItem(HTREEITEM hParent, LPTORRENTOBJECT Object)
{
	CTreeCtrl &tree = GetTreeCtrl();

	switch (Object->GetElementType()) {
	case ET_DICT:
		hParent = tree.InsertItem("{Dictionary}", 0, 0, hParent);
		InsertDict(hParent, (LPDICTIONARY)Object);
		break;
	case ET_LIST:
		hParent = tree.InsertItem("{List}", 1, 1, hParent);
		InsertList(hParent, (LPLIST)Object);
		break;
	case ET_INTEGER:
		InsertInt(hParent, (LPINTEGER)Object);
		break;
	case ET_STRING:
		InsertString(hParent, (LPSTRING)Object);
		break;
	}
}

void TorrentView::InsertInt(HTREEITEM hParent, LPINTEGER i)
{
	TV_INSERTSTRUCT tvis;
	tvis.hParent = hParent;
	tvis.hInsertAfter = hParent;
	tvis.itemex.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE 
		| TVIF_SELECTEDIMAGE;
	tvis.itemex.iImage = tvis.itemex.iSelectedImage = 3;	

	CTreeCtrl &tree = GetTreeCtrl();
	
	CString s;
	s.Format("%I64d", (__int64)*i);

	tvis.itemex.pszText = (LPSTR)(LPCSTR)s;
	tvis.itemex.lParam = (LPARAM)i;
	tree.InsertItem(&tvis);	
}

void TorrentView::InsertString(HTREEITEM hParent, LPSTRING s)
{
	TV_INSERTSTRUCT tvis;
	tvis.hParent = hParent;
	tvis.hInsertAfter = hParent;
	tvis.itemex.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE 
		| TVIF_SELECTEDIMAGE;
	tvis.itemex.iImage = tvis.itemex.iSelectedImage = 2;	
	tvis.itemex.pszText = (LPSTR)(LPCSTR)*s;
	tvis.itemex.lParam = (LPARAM)s;

	CTreeCtrl &tree = GetTreeCtrl();
	tree.InsertItem(&tvis);	
}

void TorrentView::AddImages()
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
void TorrentView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (pNMTreeView->action == TVC_UNKNOWN)
		return;

	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	
	CTreeCtrl &tree = GetTreeCtrl();
	CString text = tree.GetItemText(hItem);

	LPTORRENTOBJECT pitem = (LPTORRENTOBJECT)tree.GetItemData(hItem);	
	AutoSwap(pitem);

	GetDocument()->UpdateAllViews(this, m_DateView, pitem);

	*pResult = 0;
}

void TorrentView::OnUpdateBinaryView(CCmdUI* pCmdUI) 
{
	CTreeCtrl &tree = GetTreeCtrl();
	HTREEITEM hItem = tree.GetSelectedItem();
	if (hItem != NULL) {
		LPTORRENTOBJECT pitem = (LPTORRENTOBJECT)tree.GetItemData(hItem);
		if (pitem && pitem->GetElementType() == ET_STRING) {
			pCmdUI->Enable(TRUE);			
			pCmdUI->SetRadio(m_BinaryView);
		} else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetRadio(FALSE);
		}		
	} else {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetRadio(FALSE);
	}		
}

void TorrentView::OnBinaryView() 
{
	m_BinaryView = !m_BinaryView;

	MainFrame *pFrame = (MainFrame*)GetParentFrame();
	pFrame->SwapViews();

	Reselect();
}

void TorrentView::OnUpdateDateView(CCmdUI* pCmdUI) 
{
	CTreeCtrl &tree = GetTreeCtrl();
	HTREEITEM hItem = tree.GetSelectedItem();
	if (hItem != NULL) {
		LPTORRENTOBJECT pitem = (LPTORRENTOBJECT)tree.GetItemData(hItem);
		if (pitem && pitem->GetElementType() == ET_INTEGER) {
			pCmdUI->Enable(TRUE);			
			pCmdUI->SetRadio(m_DateView);
		} else {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetRadio(FALSE);
		}		
	} else {
		pCmdUI->Enable(FALSE);
		pCmdUI->SetRadio(FALSE);
	}		
}

void TorrentView::OnDateView() 
{
	m_DateView = !m_DateView;

	Reselect();
}

void TorrentView::Reselect()
{
	CTreeCtrl &tree = GetTreeCtrl();
	HTREEITEM hItem = tree.GetSelectedItem();
	if (hItem == NULL) return;

	LPTORRENTOBJECT pitem = (LPTORRENTOBJECT)tree.GetItemData(hItem);
	
	GetDocument()->UpdateAllViews(this, m_DateView, pitem);
}

void TorrentView::AutoSwap(LPTORRENTOBJECT pitem)
{
	MainFrame *pFrame = (MainFrame*)GetParentFrame();

	// auto swap for non-string binary view
	if (pitem != NULL && pitem->GetElementType() != ET_STRING) {
		if (m_BinaryView) {
			m_BinaryView = FALSE;			
			pFrame->SwapViews();	
		}
	}

	if (pitem != NULL && pitem->GetElementType() == ET_STRING) {
		const CString &s = *(LPSTRING)pitem;
		UINT nlength = min(s.GetLength(), 20);

		// auto swap for binary strings
		int i, j;
		for (i = 0, j = 0; i < nlength; i++) {
			char c = s.GetAt(i);
			if (!isprint(c) && !m_BinaryView) {
				m_BinaryView = TRUE;
				pFrame->SwapViews();
				return;
			} else if (isprint(c) && m_BinaryView) {
				j++;
			}
		}

		// auto swap for text strings
		if (j == nlength && m_BinaryView) {
			m_BinaryView = FALSE;
			pFrame->SwapViews();
		}
	}
}

void TorrentView::OnSettingChange(WPARAM wParam, LPARAM lParam)
{
	TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
	CTreeCtrl &tree = GetTreeCtrl();
	if (pApp->IsSetting("ui_bkgnd_color")) {
		COLORREF bkgndColor = pApp->GetIntSetting("ui_bkgnd_color");
		tree.SetBkColor(bkgndColor);
	}

	if (pApp->IsSetting("ui_text_color")) {
		COLORREF textColor = pApp->GetIntSetting("ui_text_color");
		tree.SetTextColor(textColor);
	}
	
	tree.RedrawWindow();
}