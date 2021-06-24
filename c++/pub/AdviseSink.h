#pragma once

class ATL_NO_VTABLE AdviseSink :
    public CComObjectRootEx<CComSingleThreadModel>,
    public IAdviseSink
{
public:
BEGIN_COM_MAP(AdviseSink)
            COM_INTERFACE_ENTRY(IAdviseSink)
    END_COM_MAP()
    DECLARE_PROTECT_FINAL_CONSTRUCT()

    // IAdviseSink members
    void __stdcall OnDataChange(FORMATETC* pFormatetc, STGMEDIUM* pStgmed) override;
    void __stdcall OnViewChange(DWORD dwAspect, LONG lindex) override;
    void __stdcall OnRename(IMoniker* pmk) override;
    void __stdcall OnSave() override;
    void __stdcall OnClose() override;

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    HRESULT FinalRelease()
    {
        return S_OK;
    }

    void SetRenderTarget(HWND hWnd)
    {
        m_hWndTarget = hWnd;
    }

private:
    HWND m_hWndTarget = nullptr;
};

inline void AdviseSink::OnDataChange(FORMATETC* pFormatetc, STGMEDIUM* pStgmed)
{
    if (pFormatetc == nullptr || pStgmed == nullptr || m_hWndTarget == nullptr) {
        return;
    }

    if (!(pFormatetc->dwAspect == DVASPECT_CONTENT && pFormatetc->cfFormat == CF_ENHMETAFILE)) {
        return;
    }

    CClientDC dc(m_hWndTarget);

    CRect rc;
    dc.GetClipBox(rc);

    InvalidateRect(m_hWndTarget, rc, FALSE);
}

inline void AdviseSink::OnViewChange(DWORD dwAspect, LONG lindex)
{
}

inline void AdviseSink::OnRename(IMoniker* pmk)
{
}

inline void AdviseSink::OnSave()
{
}

inline void AdviseSink::OnClose()
{
}
