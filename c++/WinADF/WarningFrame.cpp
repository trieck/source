// WarningFrame.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "WarningFrame.h"


// WarningFrame

IMPLEMENT_DYNCREATE(WarningFrame, CMDIChildWnd)

WarningFrame::WarningFrame()
{

}

WarningFrame::~WarningFrame()
{
}

BEGIN_MESSAGE_MAP(WarningFrame, CMDIChildWnd)
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WarningFrame message handlers

/////////////////////////////////////////////////////////////////////////////
void WarningFrame::PostNcDestroy() 
{
	CMDIChildWnd::PostNcDestroy();
}

/////////////////////////////////////////////////////////////////////////////
void WarningFrame::OnNcDestroy()
{
	CMDIChildWnd::OnNcDestroy();
}

/////////////////////////////////////////////////////////////////////////////
BOOL WarningFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}

/////////////////////////////////////////////////////////////////////////////
int WarningFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	view = new CListView;
	if (!view->Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0),
			this, AFX_IDW_PANE_FIRST, NULL))
			return -1;
	view->GetListCtrl().InsertColumn(0, NULL, LVCFMT_LEFT, 
		lpCreateStruct->cx);
	view->ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL | LVS_NOCOLUMNHEADER);
	
	view->GetListCtrl().SetTextColor(RGB(128, 0, 0));

	// register ourselves as a warning handler
	ADFWarningRegistrar::Register(this);
	
	SetWindowText(_T("Warnings"));

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
void WarningFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	if (view && IsWindow(*view)) {
		view->SetWindowPos(NULL, 0, 0, cx, cy, SWP_SHOWWINDOW);
		view->GetListCtrl().SetColumnWidth(0, cx);
	}
}

/////////////////////////////////////////////////////////////////////////////
BOOL WarningFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_CHILD;
	cs.cx = 250;
	cs.cy = 300;

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
void WarningFrame::OnClose() 
{
	ShowWindow(SW_HIDE);
}

void WarningFrame::OnDestroy() 
{
	CMDIChildWnd::OnDestroy();
	
	if (view != NULL) {
		view->DestroyWindow();
	}	
}

void WarningFrame::handle(const string &s) const
{
	CListCtrl & ctrl = view->GetListCtrl();
	int count = ctrl.GetItemCount();
	ctrl.InsertItem(count, s.c_str());
	ctrl.EnsureVisible(count, FALSE);

	if (!IsWindowVisible()) {
		::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	}
	::ShowWindow(m_hWnd, SW_RESTORE);
}


