// ChildView.cpp : implementation of the ChildView class
//
#include "stdafx.h"
#include "fetch.h"
#include "ChildView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// List headers
static LPCTSTR headers[] = {
    _T("Machine"),
    _T("Resource"),
    _T("File")
};
typedef struct {
    HWND hWnd;
    HANDLE hEvent;
} threadData;
static void EnumerateResources(threadData *T, LPNETRESOURCEENUM penum);
static void ParseResource(LPTSTR input, CString & machine, CString & resource);
#define WM_SEARCHCOMPLETE (WM_APP + 1)
/////////////////////////////////////////////////////////////////////////////
// ChildView
ChildView::ChildView()
    : m_event(TRUE, TRUE)
{
    m_pThread = NULL;
}
ChildView::~ChildView()
{
    if (m_pThread != NULL)
        m_pThread->Delete();
}

BEGIN_MESSAGE_MAP(ChildView, CListView)
    //{{AFX_MSG_MAP(ChildView)
    ON_WM_CREATE()
    ON_COMMAND(IDM_SEARCH, OnSearch)
    ON_UPDATE_COMMAND_UI(IDM_SEARCH, OnUpdateSearch)
    ON_BN_CLICKED(IDC_STOP, OnStop)
    ON_UPDATE_COMMAND_UI(IDC_SEARCH, OnUpdateSearch)
    ON_BN_CLICKED(IDC_SEARCH, OnSearch)
    ON_UPDATE_COMMAND_UI(IDM_STOP, OnUpdateStop)
    ON_COMMAND(IDM_STOP, OnStop)
    ON_UPDATE_COMMAND_UI(IDC_STOP, OnUpdateStop)
    ON_MESSAGE(WM_SEARCHCOMPLETE, OnSearchComplete)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ChildView message handlers
int ChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CListView::OnCreate(lpCreateStruct) == -1)
        return -1;
    if (!m_ImageList.Create(16, 16, ILC_MASK | ILC_COLOR8, 0, 4)) {
        TRACE0("Could not create image list.\n");
        return -1;
    }
    HICON hIcon = (HICON)::LoadImage(AfxGetResourceHandle(),
                                     MAKEINTRESOURCE(IDI_FOLDER),
                                     IMAGE_ICON,
                                     16, 16,
                                     LR_LOADTRANSPARENT | LR_SHARED);
    ASSERT(hIcon != NULL);
    m_ImageList.Add(hIcon);
    CListCtrl & ctrl = GetListCtrl();
    ctrl.SetImageList(&m_ImageList, LVSIL_SMALL);
    return 0;
}
void ChildView::InsertHeaders()
{
    UINT count = sizeof(headers) / sizeof(LPCTSTR);

    CRect rc;
    GetListCtrl().GetClientRect(rc);
    //UINT width = rc.Width() / count;
    LV_COLUMN lvc;
    for (UINT n = 0; n < count; n++) {
        lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
        lvc.fmt = LVCFMT_LEFT;
        lvc.pszText = (LPTSTR)headers[n];
        lvc.cchTextMax = 255;
        lvc.cx = 0; //width;
        GetListCtrl().InsertColumn(n, &lvc);
        GetListCtrl().SetColumnWidth(n, LVSCW_AUTOSIZE_USEHEADER);
    }
}
BOOL ChildView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= LVS_REPORT;

    return CListView::PreCreateWindow(cs);
}
void ChildView::OnInitialUpdate()
{
    CListView::OnInitialUpdate();
    ListView_SetExtendedListViewStyleEx(*this,
                                        0,
                                        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES
                                       );
    InsertHeaders();
}
UINT ChildView::PerformSearch(LPVOID pdata)
{
    threadData *T = (threadData*)pdata;
    ASSERT(T != NULL);
    try {
        LPNETRESOURCEENUM proot = GetRootEnum();
        EnumerateResources(T, proot);
    } catch (NetError & E) {
        TRACE3("Network Error: Error Code: %d, Provider: %s, Description: %s.\n",
               E.GetErrorCode(),
               E.GetProvider(),
               E.GetDescription());
        E.GetErrorCode();
    }
    ::SendMessage(T->hWnd, WM_SEARCHCOMPLETE, 0, 0);
    delete T;
    AfxEndThread(0, FALSE);
    return 0;
}
void EnumerateResources(threadData *T, LPNETRESOURCEENUM penum)
{
    ASSERT(T != NULL);
    DWORD rtn = WaitForSingleObject(T->hEvent, 0);
    if (rtn == WAIT_OBJECT_0)
        return;
    if (penum->dwUsage & RESOURCEUSAGE_CONNECTABLE) {
        LV_ITEM lvi;
        CString machine, resource;
        ParseResource(penum->lpRemoteName, machine, resource);
        lvi.mask = LVIF_TEXT | LVIF_IMAGE;
        lvi.iItem = ListView_GetItemCount(T->hWnd);
        lvi.iSubItem = 0;
        lvi.pszText = (LPTSTR)(LPCTSTR)machine;
        lvi.iImage = 0;
        ListView_InsertItem(T->hWnd, &lvi);
        ListView_SetItemText(T->hWnd, lvi.iItem, 1, (LPTSTR)(LPCTSTR)resource);
    }
    for (DWORD i = 0; i < penum->count(); i++) {
        try {
            LPNETRESOURCEENUM p = penum->GetAt(i);
            EnumerateResources(T, p);
        } catch (const NetError & E) {
            TRACE3("Network Error: Error Code: %d, Provider: %s, Description: %s.\n",
                   E.GetErrorCode(),
                   E.GetProvider(),
                   E.GetDescription());
            E.GetErrorCode();
        }
    }
}
void ChildView::OnSearch()
{
    if (m_pThread != NULL) {
        m_pThread->Delete();
        m_pThread = NULL;
    }
    m_event.ResetEvent();
    GetListCtrl().DeleteAllItems();
    threadData *T = new threadData;
    T->hWnd = *this;
    T->hEvent = m_event;
    m_pThread = AfxBeginThread(ChildView::PerformSearch, T);
}
void ChildView::OnUpdateSearch(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!IsSearching());
}
BOOL ChildView::IsSearching() const
{
    DWORD rtn = WaitForSingleObject(m_event, 0);
    if (rtn != WAIT_OBJECT_0)
        return TRUE;
    return FALSE;
}
void ParseResource(LPTSTR input, CString & machine, CString & resource)
{
    // resource specified as \\machine\resource
    size_t i;
    size_t N = _tcslen(input);
    for (i = 2; i < N; i++) {
        if (input[i] == '\\')
            break;
    }
    machine = CString(input + 2, N - (N - i) - 2);
    resource = &input[i + 1];
}
void ChildView::OnStop()
{
    OnSearchComplete(0, 0);
}
void ChildView::OnUpdateStop(CCmdUI* pCmdUI)
{
}
LRESULT ChildView::OnSearchComplete(WPARAM wParam, LPARAM lParam)
{
    m_event.SetEvent();
    return 0;
}

