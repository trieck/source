// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "aboutdlg.h"
#include "Board.h"
#include "resource.h"
#include "Direct2DView.h"
#include <atlctrlw.h>

typedef CWinTraits<WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
                   WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_MINIMIZEBOX, WS_EX_APPWINDOW |
                   WS_EX_WINDOWEDGE> CMainFrameTraits;

class CMainFrame;
typedef CFrameWindowImpl<CMainFrame, CWindow, CMainFrameTraits> CMainFrameImpl;

class CMainFrame :
    public CMainFrameImpl,
    public CUpdateUI<CMainFrame>,
    public CMessageFilter, public CIdleHandler
{
public:
    DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

    CDirect2DView m_view;
    CCommandBarCtrl m_CmdBar;

    BOOL PreTranslateMessage(MSG* pMsg) override
    {
        if (CMainFrameImpl::PreTranslateMessage(pMsg))
            return TRUE;

        return m_view.PreTranslateMessage(pMsg);
    }

    BOOL OnIdle() override
    {
        UIUpdateToolBar();
        return FALSE;
    }

    BEGIN_UPDATE_UI_MAP(CMainFrame)
            UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
            UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
    END_UPDATE_UI_MAP()

BEGIN_MSG_MAP(CMainFrame)
        MSG_WM_CREATE(OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
        COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
        COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
        COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
        COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
        CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
        CHAIN_MSG_MAP(CMainFrameImpl)
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnCreate(LPCREATESTRUCT pcs)
    {
        // create command bar window
        const auto hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, nullptr, ATL_SIMPLE_CMDBAR_PANE_STYLE);
        // attach menu
        m_CmdBar.AttachMenu(GetMenu());
        // load command bar images
        m_CmdBar.LoadImages(IDR_MAINFRAME);
        // remove old menu
        SetMenu(nullptr);

        const auto hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

        CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
        AddSimpleReBarBand(hWndCmdBar);
        AddSimpleReBarBand(hWndToolBar, nullptr, TRUE);

        CreateSimpleStatusBar(ATL_IDS_IDLEMESSAGE, WS_CHILD | WS_VISIBLE |
                              WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

        UIAddToolBar(hWndToolBar);
        UISetCheck(ID_VIEW_TOOLBAR, 1);
        UISetCheck(ID_VIEW_STATUS_BAR, 1);

        m_hWndClient = m_view.Create(m_hWnd, rcDefault, nullptr,
                                     WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

        // register object for message filtering and idle updates
        auto* pLoop = _Module.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->AddMessageFilter(this);
        pLoop->AddIdleHandler(this);

        ResizeFrameByBoard();
        CenterWindow();

        return 0;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        // unregister message filtering and idle updates
        auto* pLoop = _Module.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->RemoveMessageFilter(this);
        pLoop->RemoveIdleHandler(this);

        bHandled = FALSE;
        return 1;
    }

    LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        PostMessage(WM_CLOSE);
        return 0;
    }

    LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        // TODO: add code to initialize document

        return 0;
    }

    LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        static BOOL bVisible = TRUE;	// initially visible
        bVisible = !bVisible;
        CReBarCtrl rebar = m_hWndToolBar;
        const auto nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
        rebar.ShowBand(nBandIndex, bVisible);
        UISetCheck(ID_VIEW_TOOLBAR, bVisible);
        UpdateLayout();
        ResizeFrameByBoard();
        return 0;
    }

    LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        const auto bVisible = !::IsWindowVisible(m_hWndStatusBar);
        ::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
        UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
        UpdateLayout();
        ResizeFrameByBoard();
        return 0;
    }

    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CAboutDlg dlg;
        dlg.DoModal();
        return 0;
    }

    void ResizeFrameByBoard()
    {
        auto rc = Board::GetBoundingRect();

        // make room for the status bar
        CRect rcStatus;
        const CStatusBarCtrl wndStatus(m_hWndStatusBar);
        wndStatus.GetWindowRect(rcStatus);
        rcStatus.OffsetRect(-rcStatus.left, -rcStatus.top);

        // make room for the toolbar
        CRect rcToolbar;
        const CReBarCtrl rebar = m_hWndToolBar;
        rebar.GetWindowRect(rcToolbar);
        rcToolbar.OffsetRect(-rcToolbar.left, -rcToolbar.top);

        // toolbar is 2nd added band
        const auto nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);

        REBARBANDINFO rbbi;
        memset(&rbbi, 0, sizeof(REBARBANDINFO));
        rbbi.cbSize = sizeof(REBARBANDINFO);
        rbbi.fMask = RBBIM_STYLE;
        rebar.GetBandInfo(nBandIndex, &rbbi);

        if (wndStatus.IsWindowVisible())
            rc.bottom += rcStatus.Height();

        if ((rbbi.fStyle & RBBS_HIDDEN) == 0)
            rc.bottom += rcToolbar.Height();

        const auto style = GetStyle();
        const auto dwExStyle = GetExStyle() | WS_EX_CLIENTEDGE;
        AdjustWindowRectEx(&rc, style, TRUE, dwExStyle);

        SetWindowPos(nullptr, 0, 0, rc.Width(), rc.Height(),
                     SWP_NOMOVE | SWP_FRAMECHANGED | SWP_NOZORDER);
    }
};
