#pragma once

class AdvisableSink :
    public CComObjectRoot,
    public IAdviseSink
{
public:
    DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(AdvisableSink)
        COM_INTERFACE_ENTRY(IAdviseSink)
    END_COM_MAP()

    AdvisableSink()
    {
        InternalAddRef();
    }

    virtual ~AdvisableSink() = default;

    // IAdviseSink members
    void __stdcall OnDataChange(FORMATETC* pFormatetc, STGMEDIUM* pStgmed) override
    {
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

protected:
    HRESULT Advise(LPUNKNOWN pUnk)
    {
        if (!pUnk) {
            return E_POINTER;
        }

        Unadvise(pUnk);

        FORMATETC fe;
        fe.cfFormat = CF_ENHMETAFILE;
        fe.dwAspect = DVASPECT_CONTENT;
        fe.ptd = nullptr;
        fe.tymed = TYMED_ENHMF;
        fe.lindex = -1;

        CComQIPtr<IDataObject> pDataObject(pUnk);
        if (pDataObject == nullptr) {
            return E_NOINTERFACE;
        }

        auto hr = pDataObject->DAdvise(&fe, 0, this, &m_dwConn);

        return hr;
    }

    HRESULT Unadvise(LPUNKNOWN pUnk)
    {
        if (!pUnk) {
            return E_POINTER;
        }

        CComQIPtr<IDataObject> pDataObject(pUnk);
        if (pDataObject == nullptr) {
            return E_NOINTERFACE;
        }

        auto hr = pDataObject->DUnadvise(m_dwConn);

        m_dwConn = 0;

        return hr;
    }

private:
    DWORD m_dwConn = 0;
};
