///////////////////////////////////////
// Module Name	:	RootView.cpp	 //
// Author		:	Thomas A. Rieck  //
// Purpose		:	Splitter Example //
// Date			:	4/11/97			 //
///////////////////////////////////////

#include "SplitterFrame.h"
#include "RootView.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CRootView, CListView)

BEGIN_MESSAGE_MAP(CRootView, CListView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// Initialize static data members
LPCTSTR CRootView :: szHeaders[1] = {_T("Filename")};

///////////////////////////////////////////////////////////////////
// CRootView construction/destruction

CRootView::CRootView()
{
}

CRootView::~CRootView()
{
}

BOOL CRootView :: PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style = cs.style | WS_CLIPSIBLINGS | LVS_ICON;
	return CListView :: PreCreateWindow(cs);
}


void CRootView::OnInitialUpdate()
{
}

INT	CRootView :: OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT nRtn;

	nRtn = CListView :: OnCreate(lpCreateStruct);

	// Set List View Backcolor
	GetListCtrl().SetBkColor(::GetSysColor(COLOR_APPWORKSPACE));

	// Add the columns
	GetListCtrl().InsertColumn(1, szHeaders[0], LVCFMT_CENTER, lpCreateStruct->cx);

	// Create the image list
	m_ImageList.Create(IDB_DOCUMENT, 32, 1, 0);
	GetListCtrl().SetImageList(&m_ImageList, LVSIL_NORMAL);

	// Add the items
	GetListCtrl().InsertItem(1, _T("Hello"));

	return nRtn;
}

