#pragma once
#include "DrawUtil.h"

extern PubApp _Module;

using ClientWndTraits = CWinTraits<WS_OVERLAPPED | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_CLIENTEDGE>;

class ClientWnd :
    public CWindowImpl<ClientWnd, CWindow, ClientWndTraits>,
    public CMessageFilter,
    public CComObjectRoot,
    public IAdviseSink
{
public:
    DECLARE_PROTECT_FINAL_CONSTRUCT()
    DECLARE_WND_CLASS(NULL)

BEGIN_COM_MAP(ClientWnd)
            COM_INTERFACE_ENTRY(IAdviseSink)
    END_COM_MAP()

BEGIN_MSG_MAP(ClientWnd)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_OBJECT_CREATED, OnObjectCreated)
        MSG_WM_PAINT2(OnPaint)
    END_MSG_MAP()

    ClientWnd()
    {
        InternalAddRef();
    }

    void FinalRelease()
    {
        Unadvise();
    }

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

    void __stdcall OnViewChange(DWORD dwAspect, LONG lindex) override
    {
    }

    void __stdcall OnRename(IMoniker* pmk) override
    {
    }

    void __stdcall OnSave() override
    {
    }

    void __stdcall OnClose() override
    {
    }

    BOOL PreTranslateMessage(MSG* pMsg) override
    {
        ATLASSERT(pMsg->message != WM_OBJECT_CREATED);

        return FALSE;
    }

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled = FALSE;

        return 1;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        Unadvise();

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
        auto hBrush = static_cast<HBRUSH>(GetSysColorBrush(COLOR_WINDOW));
        auto hOldBrush = dc.SelectBrush(hBrush);

        dc.PatBlt(dc.m_ps.rcPaint.left, dc.m_ps.rcPaint.top,
                  dc.m_ps.rcPaint.right - dc.m_ps.rcPaint.left,
                  dc.m_ps.rcPaint.bottom - dc.m_ps.rcPaint.top,
                  PATCOPY);

        auto pDrawObject = _Module.GetDrawObject();
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
        auto pDrawObject = _Module.GetDrawObject();
        if (pDrawObject) {
            Advise();
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
        if (!pDrawObject) {
            return E_POINTER;
        }

        FORMATETC fe;
        fe.cfFormat = CF_ENHMETAFILE;
        fe.dwAspect = DVASPECT_CONTENT;
        fe.ptd = nullptr;
        fe.tymed = TYMED_ENHMF;
        fe.lindex = -1;

        CComQIPtr<IDataObject> pDataObject(pDrawObject);
        if (pDataObject == nullptr) {
            return E_NOINTERFACE;
        }

        auto hr = pDataObject->DAdvise(&fe, 0, this, &m_dwConn);

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

    DWORD m_dwConn = 0;
};
