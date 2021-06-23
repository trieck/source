#pragma once

#include "DrawObject_i.h"

class ATL_NO_VTABLE DataObject :
    public CComObjectRootEx<CComSingleThreadModel>,
    public IDataObject
{
public:
DECLARE_ONLY_AGGREGATABLE(DataObject)

BEGIN_COM_MAP(DataObject)
            COM_INTERFACE_ENTRY(IDataObject)
    END_COM_MAP()

    // IDataObject members
    STDMETHODIMP GetData(LPFORMATETC, LPSTGMEDIUM) override;
    STDMETHODIMP GetDataHere(LPFORMATETC, LPSTGMEDIUM) override;
    STDMETHODIMP QueryGetData(LPFORMATETC) override;
    STDMETHODIMP GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC) override;
    STDMETHODIMP SetData(LPFORMATETC, LPSTGMEDIUM, BOOL) override;
    STDMETHODIMP EnumFormatEtc(DWORD, LPENUMFORMATETC*) override;
    STDMETHODIMP DAdvise(LPFORMATETC, DWORD, LPADVISESINK, LPDWORD) override;
    STDMETHODIMP DUnadvise(DWORD) override;
    STDMETHODIMP EnumDAdvise(LPENUMSTATDATA*) override;

    HRESULT FinalConstruct()
    {
        auto hr = CreateDataAdviseHolder(&m_pDataAdviseHolder);
        if (FAILED(hr))
            return hr;

        return hr;
    }

    HRESULT FinalRelease()
    {
        ReleaseStgMedium(&m_stg);

        m_pDataAdviseHolder.Release();

        return S_OK;
    }

private:
    CComPtr<IDataAdviseHolder> m_pDataAdviseHolder;
    STGMEDIUM m_stg{};
};

inline HRESULT DataObject::GetData(LPFORMATETC pFEIn, LPSTGMEDIUM pSTM)
{
    if (!(pFEIn && pSTM)) {
        return E_POINTER;
    }

    if (!(DVASPECT_CONTENT & pFEIn->dwAspect)) {
        return DATA_E_FORMATETC;
    }

    if (pFEIn->cfFormat != CF_ENHMETAFILE) {
        return DATA_E_FORMATETC;
    }

    pSTM->tymed = TYMED_ENHMF;
    pSTM->hGlobal = m_stg.hGlobal;
    pSTM->pUnkForRelease = nullptr;

    return S_OK;
}

inline HRESULT DataObject::GetDataHere(LPFORMATETC, LPSTGMEDIUM)
{
    return E_NOTIMPL;
}

inline HRESULT DataObject::QueryGetData(LPFORMATETC pFE)
{
    if (!(DVASPECT_CONTENT & pFE->dwAspect)) {
        return DATA_E_FORMATETC;
    }

    if (pFE->cfFormat != CF_ENHMETAFILE) {
        return DATA_E_FORMATETC;
    }

    if (!(pFE->tymed & TYMED_ENHMF)) {
        return DATA_E_FORMATETC;
    }

    return S_OK;
}

inline HRESULT DataObject::SetData(LPFORMATETC pFE, LPSTGMEDIUM pSTM, BOOL fRelease)
{
    // We have to remain responsible for the data.
    if (!fRelease) {
        return E_FAIL;
    }

    if (!(DVASPECT_CONTENT & pFE->dwAspect)) {
        return DATA_E_FORMATETC;
    }

    if (pFE->cfFormat != CF_ENHMETAFILE) {
        return DATA_E_FORMATETC;
    }

    if (!(pFE->tymed & TYMED_ENHMF)) {
        return DATA_E_FORMATETC;
    }

    // Release storage
    ReleaseStgMedium(&m_stg);

    m_stg.tymed = TYMED_ENHMF;
    m_stg.hEnhMetaFile = pSTM->hEnhMetaFile;

    auto hr = S_OK;

    if (m_pDataAdviseHolder) {
        hr = m_pDataAdviseHolder->SendOnDataChange(this, DVASPECT_CONTENT, ADVF_NODATA);
    }

    return hr;
}

inline HRESULT DataObject::EnumFormatEtc(DWORD dwDirection, LPENUMFORMATETC* ppEnum)
{
    auto hr = OleRegEnumFormatEtc(CLSID_DrawObject, dwDirection, ppEnum);

    return hr;
}

inline HRESULT DataObject::DAdvise(LPFORMATETC pFE, DWORD grfAdv, LPADVISESINK pSink, LPDWORD pConn)
{
    auto hr = m_pDataAdviseHolder->Advise(this, pFE, grfAdv, pSink, pConn);

    return hr;
}

inline HRESULT DataObject::DUnadvise(DWORD dwConn)
{
    auto hr = m_pDataAdviseHolder->Unadvise(dwConn);

    return hr;
}

inline HRESULT DataObject::EnumDAdvise(LPENUMSTATDATA* ppEnum)
{
    auto hr = m_pDataAdviseHolder->EnumAdvise(ppEnum);

    return hr;
}

inline HRESULT DataObject::GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC)
{
    return E_NOTIMPL;
}
