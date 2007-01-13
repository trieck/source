// LogWnd.cpp : implementation file
//
#include "stdafx.h"
#include "pente.h"
#include "LogWnd.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// LogWnd
IMPLEMENT_DYNCREATE(LogWnd, CMiniFrameWnd)
/////////////////////////////////////////////////////////////////////////////
LogWnd::LogWnd() 
 : view(0)
{
}
/////////////////////////////////////////////////////////////////////////////
LogWnd::~LogWnd()
{
}
BEGIN_MESSAGE_MAP(LogWnd, CMiniFrameWnd)
	//{{AFX_MSG_MAP(LogWnd)
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// LogWnd message handlers
/////////////////////////////////////////////////////////////////////////////
void LogWnd::PostNcDestroy() 
{
	CMiniFrameWnd::PostNcDestroy();
}
/////////////////////////////////////////////////////////////////////////////
void LogWnd::OnNcDestroy()
{
	CMiniFrameWnd::OnNcDestroy();
}
/////////////////////////////////////////////////////////////////////////////
BOOL LogWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	return CMiniFrameWnd::OnCreateClient(lpcs, pContext);
}
/////////////////////////////////////////////////////////////////////////////
int LogWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMiniFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	view = new CListView;
	if (!view->Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0),
			this, IDR_LISTVIEW, NULL))
			return -1;
	view->GetListCtrl().InsertColumn(0, _T("Message"), LVCFMT_LEFT, lpCreateStruct->cx);
	view->ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL);
	view->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
void LogWnd::OnSize(UINT nType, int cx, int cy) 
{
	CMiniFrameWnd::OnSize(nType, cx, cy);
	if (view && IsWindow(*view)) {
		view->SetWindowPos(NULL, 0, 0, cx, cy, SWP_SHOWWINDOW);
		view->GetListCtrl().SetColumnWidth(0, cx);
	}
}
/////////////////////////////////////////////////////////////////////////////
BOOL LogWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.lpszClass = AfxRegisterWndClass(0,
		0, (HBRUSH)GetStockObject(WHITE_BRUSH), 
		AfxGetApp()->LoadStandardIcon(IDI_APPLICATION));
	return CMiniFrameWnd::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
void LogWnd::logMessage(LPCTSTR message)
{
	ASSERT(message != NULL);
	ASSERT_VALID(view);
	CListCtrl & ctrl = view->GetListCtrl();
	int count = ctrl.GetItemCount();
	ctrl.InsertItem(count, message);
	ctrl.EnsureVisible(count, FALSE);
}
/////////////////////////////////////////////////////////////////////////////
void LogWnd::OnClose() 
{
	ShowWindow(SW_HIDE);
}
void LogWnd::OnDestroy() 
{
	CMiniFrameWnd::OnDestroy();
	
	if (view != NULL) {
		view->DestroyWindow();
	}	
}
