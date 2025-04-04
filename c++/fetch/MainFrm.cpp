// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"
#include "fetch.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct {
    UINT control;
    UINT resource;
} Button;

static Button buttons[] = {
    IDC_SEARCH, IDB_SEARCH,
    IDC_STOP, IDB_STOP
};

/////////////////////////////////////////////////////////////////////////////
// MainFrame

IMPLEMENT_DYNAMIC(MainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
    //{{AFX_MSG_MAP(MainFrame)
    ON_WM_CREATE()
    ON_WM_SETFOCUS()
    ON_WM_SETTINGCHANGE()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] = {
    ID_SEPARATOR,           // status line indicator
};

/////////////////////////////////////////////////////////////////////////////
// MainFrame construction/destruction

MainFrame::MainFrame()
{
    m_pwndView = new ChildView();
}

MainFrame::~MainFrame()
{
}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create a view to occupy the client area of the frame
    if (!m_pwndView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
                            CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL)) {
        TRACE0("Failed to create view window\n");
        return -1;
    }

    if (!m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP
                             | CBRS_TOOLTIPS) ||
            !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    if (!m_wndSearchBar.Create(this, IDD_SEARCHBAR,
                               WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS, 0)) {
        TRACE0("Failed to create search bar.\n");
        return -1;	// fail to create
    }
    SetButtonBitmaps();

    if (!m_wndStatusBar.Create(this) ||
            !m_wndStatusBar.SetIndicators(indicators,
                                          sizeof(indicators)/sizeof(UINT))) {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    CenterWindow();

    return 0;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if ( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;

    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    cs.lpszClass = AfxRegisterWndClass(0,
                                       0, 0, AfxGetApp()->LoadIcon(IDR_MAINFRAME));
    cs.cx = 400;
    cs.cy = 400;

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MainFrame message handlers
void MainFrame::OnSetFocus(CWnd* pOldWnd)
{
    // forward focus to the view window
    m_pwndView->SetFocus();
}

BOOL MainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    // let the view have first crack at the command
    if (m_pwndView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;

    // otherwise, do default handling
    return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void MainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
    CFrameWnd::OnSettingChange(uFlags, lpszSection);

    SetButtonBitmaps();
}

void MainFrame::SetButtonBitmaps()
{
    size_t count = sizeof(buttons) / sizeof(Button);

    for (size_t i = 0; i < count; i++) {
        HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetResourceHandle(),
                                               MAKEINTRESOURCE(buttons[i].resource),
                                               IMAGE_BITMAP,
                                               16, 16,
                                               LR_LOADMAP3DCOLORS | LR_SHARED);

        ASSERT(hBitmap != NULL);

        CButton *pbutton = (CButton*)m_wndSearchBar.GetDlgItem(buttons[i].control);
        ASSERT_VALID(pbutton);

        pbutton->SendMessage(BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
    }
}
void MainFrame::OnSize(UINT nType, int cx, int cy)
{
    CFrameWnd::OnSize(nType, cx, cy);
}
