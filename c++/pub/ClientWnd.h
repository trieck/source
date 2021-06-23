#pragma once

extern PubApp _Module;

using ClientWndTraits = CWinTraits<WS_OVERLAPPED | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_CLIENTEDGE>;

class ClientWnd : public CWindowImpl<ClientWnd, CWindow, ClientWndTraits>, CMessageFilter
{
public:
    DECLARE_WND_CLASS(NULL)

BEGIN_MSG_MAP(ClientWnd)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MSG_WM_PAINT2(OnPaint)
    END_MSG_MAP()

    BOOL PreTranslateMessage(MSG* /*pMsg*/) override
    {
        return FALSE;
    }

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled = TRUE;
        return 0;
    }

    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
    {
        auto pDrawObject = _Module.GetDrawObject();
        if (pDrawObject) {
            auto cx = LOWORD(lParam);
            auto cy = HIWORD(lParam);

            CRect rc;
            rc.SetRect(0, 0, cx, cy);

            pDrawObject->SetBounds(&rc);
        }

        bHandled = TRUE;

        return 0;
    }

    void OnPaint(CPaintDC& dc)
    {
        // dc.SetMapMode(MM_ANISOTROPIC);
        // dc.SetWindowExt({ 1024, 1024 });
        // dc.SetViewportExt(dc.m_ps.rcPaint.right - dc.m_ps.rcPaint.left, dc.m_ps.rcPaint.bottom - dc.m_ps.rcPaint.top,
        //                   nullptr);

        auto hBrush = static_cast<HBRUSH>(GetSysColorBrush(COLOR_WINDOW));
        auto hOldBrush = dc.SelectBrush(hBrush);

        dc.PatBlt(dc.m_ps.rcPaint.left, dc.m_ps.rcPaint.top,
               dc.m_ps.rcPaint.right - dc.m_ps.rcPaint.left,
               dc.m_ps.rcPaint.bottom - dc.m_ps.rcPaint.top,
               PATCOPY);

        auto pDrawObject = _Module.GetDrawObject();
        if (pDrawObject) {
            OleDraw(pDrawObject, DVASPECT_CONTENT, dc.m_ps.hdc, &dc.m_ps.rcPaint);
        }

        dc.SelectBrush(hOldBrush);
        DeleteObject(hBrush);
    }
};
