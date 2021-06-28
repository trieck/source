#pragma once

#include "DrawObject_i.h"
#include "DrawUtil.h"

class ATL_NO_VTABLE DataObject :
    public CComObjectRoot,
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
    HRESULT GetMetafilePict(LPMETAFILEPICT* ppMetafile);

    CComPtr<IDataAdviseHolder> m_pDataAdviseHolder;
    AutoStgMedium m_stg;
};

inline HRESULT DataObject::GetData(LPFORMATETC pFEIn, LPSTGMEDIUM pSTM)
{
    if (!(m_stg.tymed == TYMED_ENHMF && m_stg.hEnhMetaFile != nullptr)) {
        return E_FAIL;
    }

    if (!(pFEIn && pSTM)) {
        return E_POINTER;
    }

    if (!(DVASPECT_CONTENT & pFEIn->dwAspect)) {
        return DATA_E_FORMATETC;
    }

    if (pFEIn->cfFormat == CF_ENHMETAFILE) {
        auto hEnhMetaFile = static_cast<HENHMETAFILE>(OleDuplicateData(m_stg.hEnhMetaFile, CF_ENHMETAFILE, 0));
        if (hEnhMetaFile == nullptr) {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        pSTM->tymed = TYMED_ENHMF;
        pSTM->hEnhMetaFile = hEnhMetaFile;
        pSTM->pUnkForRelease = nullptr; // caller responsible for freeing

        return S_OK;
    }

    if (pFEIn->cfFormat == CF_METAFILEPICT) {
        LPMETAFILEPICT pict;
        auto hr = GetMetafilePict(&pict);
        if (FAILED(hr)) {
            return hr;
        }

        auto hMetafile = OleDuplicateData(pict, CF_METAFILEPICT, 0);
        if (hMetafile == nullptr) {
            DeleteMetaFile(pict->hMF);
            GlobalFree(pict);
            return HRESULT_FROM_WIN32(GetLastError());
        }

        pSTM->tymed = TYMED_MFPICT;
        pSTM->hMetaFilePict = hMetafile;
        pSTM->pUnkForRelease = nullptr; // caller responsible for freeing

        auto result = DeleteMetaFile(pict->hMF);
        if (!result) {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        // caller must free METAFILEPICT

        return S_OK;
    }

    return DATA_E_FORMATETC;
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
    // We have to remain responsible for the data
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
    m_stg.Release();

    m_stg.tymed = TYMED_ENHMF;
    m_stg.hEnhMetaFile = pSTM->hEnhMetaFile; // don't copy; we own this

    auto hr = S_OK;

    if (m_pDataAdviseHolder) {
        hr = m_pDataAdviseHolder->SendOnDataChange(this, DVASPECT_CONTENT, 0);
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

inline HRESULT DataObject::GetMetafilePict(LPMETAFILEPICT* ppMetafile)
{
    if (!(m_stg.tymed == TYMED_ENHMF && m_stg.hEnhMetaFile != nullptr)) {
        return E_FAIL;
    }

    if (!ppMetafile) {
        return E_POINTER;
    }

    auto hDC = GetDC(nullptr);
    auto size = GetWinMetaFileBits(m_stg.hEnhMetaFile, 0, nullptr, MM_TEXT, hDC);
    if (size == 0) {
        ReleaseDC(nullptr, hDC);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    auto* bits = static_cast<BYTE*>(GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, size));
    if (bits == nullptr) {
        ReleaseDC(nullptr, hDC);
        return E_OUTOFMEMORY;
    }

    auto pbits = std::make_unique<BYTE*>(bits);

    size = GetWinMetaFileBits(m_stg.hEnhMetaFile, size, *pbits, MM_TEXT, hDC);

    ReleaseDC(nullptr, hDC);

    if (size == 0) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    auto hMF = SetMetaFileBitsEx(size, *pbits);
    if (hMF == nullptr) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    *ppMetafile = static_cast<tagMETAFILEPICT*>(GlobalAlloc(GPTR, sizeof(METAFILEPICT)));
    if (*ppMetafile == nullptr) {
        return E_OUTOFMEMORY;
    }

    ENHMETAHEADER header;
    if (!GetEnhMetaFileHeader(m_stg.hEnhMetaFile, sizeof(ENHMETAHEADER), &header)) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    CRect rcFrame(header.rclFrame.left,
        header.rclFrame.top,
        header.rclFrame.right,
        header.rclFrame.bottom);

    HimetricToPixel(rcFrame);

    (*ppMetafile)->hMF = hMF; // caller responsible
    (*ppMetafile)->mm = MM_TEXT;
    (*ppMetafile)->xExt = rcFrame.Width();
    (*ppMetafile)->yExt = rcFrame.Height();

    return S_OK;
}
