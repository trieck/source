// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MainFrm.h"
#include "BeatGrid.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
        ON_WM_CREATE()
        ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
END_MESSAGE_MAP()

static UINT indicators[] = {
    ID_SEPARATOR, // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndMenuBar.Create(this)) {
        TRACE0("Failed to create menubar\n");
        return -1; // fail to create
    }

    m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_TOOLTIPS);

    // prevent the menu bar from taking the focus on activation
    CMFCPopupMenu::SetForceMenuFocus(FALSE);

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT,
                               WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS) ||
        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
        TRACE0("Failed to create toolbar\n");
        return -1; // fail to create
    }

    if (!m_wndSettingsPane.Create(
        nullptr, this, FALSE,
        MAKEINTRESOURCE(IDD_SETTINGS),
        WS_CHILD | WS_VISIBLE | CBRS_TOP,
        ID_SETTINGS_PANE)) {
        TRACE0("Failed to create settings bar\n");
        return -1; // fail to create
    }

    if (!m_wndStatusBar.Create(this)) {
        TRACE0("Failed to create status bar\n");
        return -1; // fail to create
    }

    m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

    m_wndMenuBar.EnableDocking(CBRS_ALIGN_TOP);
    m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);
    m_wndSettingsPane.EnableDocking(CBRS_ALIGN_TOP);

    EnableDocking(CBRS_ALIGN_TOP);
    DockPane(&m_wndMenuBar);
    DockPane(&m_wndToolBar);
    DockPane(&m_wndSettingsPane);

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CFrameWndEx::PreCreateWindow(cs))
        return FALSE;

    cs.style &= ~(WS_THICKFRAME | WS_MAXIMIZE | WS_MAXIMIZEBOX);

    return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp, LPARAM lp)
{
    auto lres = CFrameWndEx::OnToolbarCreateNew(wp, lp);
    if (lres == 0) {
        return 0;
    }

    auto pUserToolbar = reinterpret_cast<CMFCToolBar*>(lres);
    ASSERT_VALID(pUserToolbar);

    CString strCustomize;
    auto bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
    ASSERT(bNameValid);

    pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
    return lres;
}

void CMainFrame::RecalcLayout(BOOL bNotify)
{
    ResizeFrame();
    CFrameWndEx::RecalcLayout(bNotify);
}

void CMainFrame::ResizeFrame()
{
    RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST);

    CRect rc;
    BeatGrid::GetBoundingRect(rc);

    // make room for the menu bar
    CRect rcMenu;
    if (IsWindow(m_wndMenuBar)) {
        m_wndMenuBar.GetWindowRect(rcMenu);
    }

    // make room for the toolbar
    CRect rcToolbar;
    if (IsWindow(m_wndToolBar)) {
        m_wndToolBar.GetWindowRect(rcToolbar);
    }

    // make room for the settings pane
    CRect rcPane;
    if (IsWindow(m_wndSettingsPane)) {
        m_wndSettingsPane.GetWindowRect(rcPane);
    }

    // make room for the status bar
    CRect rcStatus;
    if (IsWindow(m_wndStatusBar)) {
        m_wndStatusBar.GetWindowRect(rcStatus);
    }

    if (IsWindow(m_wndMenuBar) && !m_wndMenuBar.IsFloating()
        && m_wndMenuBar.IsWindowVisible()) {
        if (m_wndMenuBar.GetPaneStyle() & CBRS_ORIENT_HORZ)
            rc.bottom += rcMenu.Height();
        else if (m_wndMenuBar.GetPaneStyle() & CBRS_ORIENT_VERT)
            rc.right += rcMenu.Width();
    }

    if (IsWindow(m_wndToolBar) && !m_wndToolBar.IsFloating() &&
        m_wndToolBar.IsWindowVisible()) {
        if (m_wndToolBar.GetPaneStyle() & CBRS_ORIENT_HORZ)
            rc.bottom += rcToolbar.Height();
        else if (m_wndToolBar.GetPaneStyle() & CBRS_ORIENT_VERT)
            rc.right += rcToolbar.Width();
    }

    if (IsWindow(m_wndSettingsPane) && !m_wndSettingsPane.IsFloating()
        && m_wndSettingsPane.IsWindowVisible()) {
        if (m_wndSettingsPane.GetPaneStyle() & CBRS_ORIENT_HORZ)
            rc.bottom += rcPane.Height();
        else if (m_wndSettingsPane.GetPaneStyle() & CBRS_ORIENT_VERT)
            rc.right += rcPane.Width();
    }

    if (IsWindow(m_wndStatusBar) && !m_wndStatusBar.IsWindowVisible()) {
        rc.bottom -= rcStatus.Height();
    }

    auto style = GetStyle();
    auto dwExStyle = GetExStyle() | WS_EX_CLIENTEDGE;
    AdjustWindowRectEx(&rc, style, TRUE, dwExStyle);

    SetWindowPos(nullptr, 0, 0, rc.Width(), rc.Height(),
                 SWP_NOMOVE | SWP_FRAMECHANGED | SWP_NOZORDER);
}

void CMainFrame::AdjustClientArea()
{
    ResizeFrame();
    return CFrameWndEx::AdjustClientArea();
}

void CMainFrame::AdjustDockingLayout(HDWP hdwp)
{
    ResizeFrame();
    return CFrameWndEx::AdjustDockingLayout(hdwp);
}
