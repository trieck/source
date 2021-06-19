/*-----------------------------------------------
    Module	:	PERSTREAM.CPP
    Date	:	07/25/1997
    Purpose	:	IPersistStream implementation
------------------------------------------------*/
#include "pch.h"
#include "object.h"

CImpIPersistStream::CImpIPersistStream(PCDrawObject pObj) : m_cRef(1), m_pObj(pObj)
{
}

CImpIPersistStream::~CImpIPersistStream()
{
}

STDMETHODIMP CImpIPersistStream::QueryInterface(REFIID riid, PPVOID ppv)
{
    return m_pObj->QueryInterface(riid, ppv);
}

DWORD CImpIPersistStream::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

DWORD CImpIPersistStream::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}

STDMETHODIMP CImpIPersistStream::GetClassID(LPCLSID pClsID)
{
    *pClsID = m_pObj->m_clsID;
    return NOERROR;
}

STDMETHODIMP CImpIPersistStream::IsDirty()
{
    return ResultFromScode(m_pObj->m_fDirty ? S_OK : S_FALSE);
}

STDMETHODIMP CImpIPersistStream::Load(LPSTREAM pIStream)
{
    ULONG cb;
    HRESULT hr;

    if (!pIStream)
        return ResultFromScode(E_POINTER);

    hr = pIStream->Read(m_pObj->m_pRender, sizeof(RENDERING), &cb);

    if (FAILED(hr) || cb != sizeof(RENDERING)) {
        pIStream->Release();
        return (hr);
    }

    m_pObj->RenderData();

    // inform advise sink of data change
    if (m_pObj->m_pIDataAdviseHolder)
        m_pObj->m_pIDataAdviseHolder->SendOnDataChange
            (m_pObj->m_pImpIDataObject, DVASPECT_CONTENT, ADVF_NODATA);

    return NOERROR;
}

STDMETHODIMP CImpIPersistStream::Save(LPSTREAM pIStream, BOOL fClearDirty)
{
    ULONG cb;
    HRESULT hr;

    if (!pIStream)
        return ResultFromScode(E_POINTER);

    hr = pIStream->Write(m_pObj->m_pRender, sizeof(RENDERING), &cb);

    if (FAILED(hr) || cb != sizeof(RENDERING))
        return ResultFromScode(STG_E_WRITEFAULT);

    m_pObj->m_fDirty = fClearDirty;
    return NOERROR;
}

STDMETHODIMP CImpIPersistStream::GetSizeMax(ULARGE_INTEGER* pcbSize)
{
    if (!pcbSize)
        return ResultFromScode(E_POINTER);

    ULISet32(*pcbSize, sizeof(RECT));

    return NOERROR;
}
