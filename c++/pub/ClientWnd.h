#pragma once
#include "AdviseSink.h"

extern PubApp _Module;

using ClientWndTraits = CWinTraits<WS_OVERLAPPED | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_CLIENTEDGE>;

class ClientWnd : public CWindowImpl<ClientWnd, CWindow, ClientWndTraits>, CMessageFilter
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

    BOOL PreTranslateMessage(MSG* pMsg) override
    {
        ATLASSERT(pMsg->message != WM_OBJECT_CREATED);

        return FALSE;
    }

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled = TRUE;

        using AdviseSinkObject = CComObject<AdviseSink>;

        AdviseSinkObject* pSink;
        auto hr = AdviseSinkObject::CreateInstance(&pSink);
        if (FAILED(hr)) {
            return -1;
        }

        pSink->SetRenderTarget(*this);

        m_pAdviseSink = pSink;

        return 0;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        Unadvise();

        bHandled = TRUE;

        m_pAdviseSink.Release();

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

    LRESULT OnObjectCreated(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
    {
        Advise();

        auto pDrawObject = _Module.GetDrawObject();
        if (pDrawObject) {
            CRect rc;
            GetClientRect(rc);
            pDrawObject->SetBounds(rc);
            Invalidate();
        }

        bHandled = TRUE;

        return 0;
    }

private:
    HRESULT Advise()
    {
        Unadvise();

        auto pDrawObject = _Module.GetDrawObject();
        if (!(m_pAdviseSink && pDrawObject)) {
            return E_POINTER;
        }

        FORMATETC fe{};
        fe.cfFormat = CF_ENHMETAFILE;
        fe.dwAspect = DVASPECT_CONTENT;
        fe.ptd = nullptr;
        fe.tymed = TYMED_ENHMF;
        fe.lindex = -1;

        CComQIPtr<IDataObject> pDataObject(pDrawObject);
        if (pDataObject == nullptr) {
            return E_NOINTERFACE;
        }

        auto hr = pDataObject->DAdvise(&fe, ADVF_NODATA, m_pAdviseSink, &m_dwConn);

        return hr;
    }

    HRESULT Unadvise()
    {
        auto pDrawObject = _Module.GetDrawObject();
        if (!pDrawObject) {
            return E_POINTER;
        }

        CComQIPtr<IDataObject> pDataObject(pDrawObject);
        if (pDataObject == nullptr) {
            return E_NOINTERFACE;
        }

        auto hr = pDataObject->DUnadvise(m_dwConn);

        m_dwConn = 0;

        return hr;
    }

    CComPtr<IAdviseSink> m_pAdviseSink;
    DWORD m_dwConn = 0;
};
