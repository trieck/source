#pragma once
#include "resource.h"
#include "ClientWnd.h"
#include "ComponentDlg.h"

typedef CWinTraits<WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
    WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_EX_APPWINDOW |
    WS_EX_WINDOWEDGE> CMainFrameTraits;

class MainFrame;
using MainFrameImpl = CFrameWindowImpl<MainFrame, CWindow, CMainFrameTraits>;

class MainFrame final : public MainFrameImpl, public CMessageFilter
{
public:
    DECLARE_FRAME_WND_CLASS_EX(nullptr, IDR_MAINFRAME, CS_NOCLOSE, COLOR_WINDOW)

BEGIN_MSG_MAP(MainFrame)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_SETSTATUS, OnSetStatus)
        MESSAGE_HANDLER(WM_OBJECT_CREATED, OnObjectCreated)
        MESSAGE_HANDLER(WM_OBJECT_DESTROYED, OnObjectDestroyed)
        CHAIN_MSG_MAP(MainFrameImpl)
    END_MSG_MAP()

    BOOL PreTranslateMessage(MSG* pMsg) override
    {
        if (MainFrameImpl::PreTranslateMessage(pMsg))
            return TRUE;

        if (m_pView) {
            return m_pView->PreTranslateMessage(pMsg);
        }

        return FALSE;
    }

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        auto* pLoop = theApp.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->AddMessageFilter(this);

        if (!CreateSimpleStatusBar(ATL_IDS_IDLEMESSAGE, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                                   ATL_IDW_STATUS_BAR)) {
            return -1;
        }

        auto hr = CComObject<ClientWnd>::CreateInstance(&m_pView);
        if (FAILED(hr)) {
            return -1;
        }

        m_hWndClient = m_pView->Create(m_hWnd, nullptr, nullptr,
                                       WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
        if (m_hWndClient == nullptr) {
            return -1;
        }

        hr = CComObject<ComponentDlg>::CreateInstance(&m_pDlg);
        if (FAILED(hr)) {
            return -1;
        }

        if (!m_pDlg->Create(m_hWnd, reinterpret_cast<LPARAM>(this))) {
            return -1;
        }

        SendMessage(WM_SETSTATUS, IDS_OK, 0);

        return 0;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        // unregister message filtering and idle updates
        auto pLoop = theApp.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->RemoveMessageFilter(this);

        bHandled = FALSE;

        return 1;
    }

    LRESULT OnSetStatus(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        TCHAR buffer[256] = {};

        auto result = LoadString(theApp.m_hInstResource, static_cast<UINT>(wParam), buffer, sizeof(buffer));
        if (result > 0) {
            buffer[result] = _T('\0');
            ::SetWindowText(m_hWndStatusBar, buffer);
        }

        bHandled = TRUE;

        return 0;
    }

    LRESULT OnObjectCreated(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
    {
        if (m_pView) {
            m_pView->SendMessage(WM_OBJECT_CREATED);
        }

        bHandled = FALSE;

        return 1;
    }

    LRESULT OnObjectDestroyed(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
    {
        if (m_pView) {
            m_pView->SendMessage(WM_OBJECT_DESTROYED);
        }

        bHandled = FALSE;

        return 1;
    }

private:
    CComPtr<CComObject<ClientWnd>> m_pView;
    CComPtr<CComObject<ComponentDlg>> m_pDlg;
};
