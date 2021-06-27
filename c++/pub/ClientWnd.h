#pragma once
#include "DrawUtil.h"
#include "AdvisableSink.h"

using ClientWndTraits = CWinTraits<WS_OVERLAPPED | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_CLIENTEDGE>;

class ClientWnd : public CWindowImpl<ClientWnd, CWindow, ClientWndTraits>,
                  public AdvisableSink,
                  public CMessageFilter
{
public:
    DECLARE_WND_CLASS(NULL)

BEGIN_MSG_MAP(ClientWnd)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_OBJECT_CREATED, OnObjectCreated)
        MSG_WM_PAINT2(OnPaint)
    END_MSG_MAP()

    // IAdviseSink members
    void __stdcall OnDataChange(FORMATETC* pFormatetc, STGMEDIUM* pStgmed) override
    {
        if (pFormatetc == nullptr || pStgmed == nullptr) {
            return;
        }

        if (!(pFormatetc->dwAspect == DVASPECT_CONTENT && pFormatetc->cfFormat == CF_ENHMETAFILE)) {
            return;
        }

        if (pStgmed->tymed != TYMED_ENHMF) {
            return;
        }

        ENHMETAHEADER header;
        if (!GetEnhMetaFileHeader(pStgmed->hEnhMetaFile, sizeof(ENHMETAHEADER), &header)) {
            return;
        }

        CRect rc(header.rclFrame.left,
                 header.rclFrame.top,
                 header.rclFrame.right,
                 header.rclFrame.bottom);

        HimetricToPixel(rc);

        InvalidateRect(&rc, TRUE);
    }

    BOOL PreTranslateMessage(MSG* pMsg) override
    {
        return FALSE;
    }

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled = FALSE;

        return 1;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        auto pDrawObject = theApp.GetDrawObject();
        if (pDrawObject) {
            Unadvise(pDrawObject);
        }

        bHandled = TRUE;

        return 0;
    }

    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
    {
        auto pDrawObject = theApp.GetDrawObject();
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
        auto hBrush = GetSysColorBrush(COLOR_WINDOW);
        auto hOldBrush = dc.SelectBrush(hBrush);

        dc.PatBlt(dc.m_ps.rcPaint.left, dc.m_ps.rcPaint.top,
                  dc.m_ps.rcPaint.right - dc.m_ps.rcPaint.left,
                  dc.m_ps.rcPaint.bottom - dc.m_ps.rcPaint.top,
                  PATCOPY);

        auto pDrawObject = theApp.GetDrawObject();
        if (pDrawObject && pDrawObject->HasData() == S_OK) {
            auto hr = OleDraw(pDrawObject, DVASPECT_CONTENT, dc.m_ps.hdc, &dc.m_ps.rcPaint);
            if (FAILED(hr)) {
                GetParent().SendMessage(WM_SETSTATUS, IDS_CANTDRAW);
            }
        }

        dc.SelectBrush(hOldBrush);
        DeleteObject(hBrush);
    }

    LRESULT OnObjectCreated(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        auto pDrawObject = theApp.GetDrawObject();
        if (pDrawObject) {
            Advise(pDrawObject);
            CRect rc;
            GetClientRect(rc);
            pDrawObject->SetBounds(rc);
            Invalidate();
        }

        bHandled = TRUE;

        return 0;
    }
};
