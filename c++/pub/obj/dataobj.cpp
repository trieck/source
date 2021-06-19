/*-----------------------------------------
    Module	:	DATAOBJ.CPP
    Date	:	08/01/1997
    Purpose	:	IDataObject implementation
------------------------------------------*/

#include "pch.h"
#include "object.h"

CImpIDataObject::CImpIDataObject(PCDrawObject pObj) : m_cRef(1), m_pObj(pObj)
{
}

CImpIDataObject::~CImpIDataObject()
{
}

DWORD CImpIDataObject::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

DWORD CImpIDataObject::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}

STDMETHODIMP CImpIDataObject::QueryInterface(REFIID riid, PPVOID ppv)
{
    return m_pObj->QueryInterface(riid, ppv);
}

STDMETHODIMP CImpIDataObject::DAdvise(LPFORMATETC pFE, DWORD grfAdv, LPADVISESINK pAdvSink, LPDWORD pdwConnection)
{
    HRESULT hr;

    if (!m_pObj->m_pIDataAdviseHolder) {
        hr = CreateDataAdviseHolder(&m_pObj->m_pIDataAdviseHolder);
        if (FAILED(hr))
            return hr;
    }

    hr = m_pObj->m_pIDataAdviseHolder->Advise(static_cast<LPDATAOBJECT>(this), pFE,
                                              grfAdv, pAdvSink, pdwConnection);

    return hr;
}

STDMETHODIMP CImpIDataObject::DUnadvise(DWORD dwConnection)
{
    HRESULT hr;

    if (!m_pObj->m_pIDataAdviseHolder)
        return ResultFromScode(E_FAIL);

    hr = m_pObj->m_pIDataAdviseHolder->Unadvise(dwConnection);

    return hr;
}

STDMETHODIMP CImpIDataObject::EnumDAdvise(LPENUMSTATDATA* ppEnum)
{
    HRESULT hr;

    if (!m_pObj->m_pIDataAdviseHolder)
        return ResultFromScode(E_FAIL);

    hr = m_pObj->m_pIDataAdviseHolder->EnumAdvise(ppEnum);

    return hr;
}

STDMETHODIMP CImpIDataObject::EnumFormatEtc(DWORD dwDirection, LPENUMFORMATETC* ppEnum)
{
    return OleRegEnumFormatEtc(m_pObj->m_clsID, dwDirection, ppEnum);
}

STDMETHODIMP CImpIDataObject::GetCanonicalFormatEtc(LPFORMATETC pFEIn, LPFORMATETC pFEOut)
{
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CImpIDataObject::GetData(LPFORMATETC pFEIn, LPSTGMEDIUM pSTM)
{
    UINT cf = pFEIn->cfFormat;

    if (!(DVASPECT_CONTENT & pFEIn->dwAspect))
        return ResultFromScode(DATA_E_FORMATETC);

    if (cf != CF_METAFILEPICT)
        return ResultFromScode(DATA_E_FORMATETC);

    pSTM->tymed = TYMED_MFPICT;
    pSTM->hGlobal = m_pObj->m_pSTM->hGlobal;
    pSTM->pUnkForRelease = nullptr;

    return NOERROR;
}

STDMETHODIMP CImpIDataObject::GetDataHere(LPFORMATETC pFE, LPSTGMEDIUM pSTM)
{
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CImpIDataObject::QueryGetData(LPFORMATETC pFE)
{
    UINT cf = pFE->cfFormat;
    BOOL fRet;

    if (!(DVASPECT_CONTENT & pFE->dwAspect))
        return ResultFromScode(DATA_E_FORMATETC);

    switch (cf) {
    case CF_METAFILEPICT:
        fRet = static_cast<BOOL>(pFE->tymed & TYMED_MFPICT);
        break;
    default:
        fRet = FALSE;
        break;
    }

    return fRet ? NOERROR : ResultFromScode(S_FALSE);
}

STDMETHODIMP CImpIDataObject::SetData(LPFORMATETC pFE, LPSTGMEDIUM pSTM, BOOL fRelease)
{
    UINT cf = pFE->cfFormat;

    // We have to remain responsible for the data.
    if (!fRelease)
        return ResultFromScode(E_FAIL);

    if (!(DVASPECT_CONTENT & pFE->dwAspect))
        return ResultFromScode(DATA_E_FORMATETC);

    if (cf != CF_METAFILEPICT)
        return ResultFromScode(DATA_E_FORMATETC);

    // Release storage
    ReleaseStgMedium(m_pObj->m_pSTM);

    m_pObj->m_pSTM->tymed = TYMED_MFPICT;
    m_pObj->m_pSTM->hGlobal = pSTM->hGlobal;
    m_pObj->m_pSTM->pUnkForRelease = this;

    this->AddRef();

    return NOERROR;
}
