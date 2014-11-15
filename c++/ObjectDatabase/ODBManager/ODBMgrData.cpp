/////////////////////////////////////////////////////////////////////////////
//
// ODBMGRDATA.CPP : Object database manager data
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "ODBMgrData.h"
#include "ODBMgrComponent.h"
#include "ODBMgrDataObj.h"

/////////////////////////////////////////////////////////////////////////////
ODBMgrData::ODBMgrData(LPUNKNOWN pUnknown)
    : m_cRef(0), m_pUnknown(pUnknown), m_pConsoleNameSpace(NULL),
      m_pConsole(NULL)
{
}

/////////////////////////////////////////////////////////////////////////////
ODBMgrData::~ODBMgrData()
{
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrData::QueryInterface(REFIID riid, LPVOID *ppv)
{
    *ppv = NULL;

    if (riid == IID_IUnknown || riid == IID_IComponentData)
        *ppv = this;

    if (*ppv) {
        ((LPUNKNOWN)*ppv)->AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) ODBMgrData::AddRef()
{
    InterlockedIncrement(&m_cRef);
    return m_pUnknown->AddRef();
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) ODBMgrData::Release()
{
    InterlockedDecrement(&m_cRef);
    return m_pUnknown->Release();
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrData::Initialize(LPUNKNOWN pUnknown)
{
    if (pUnknown == NULL)
        return E_POINTER;

    HRESULT hr = pUnknown->QueryInterface(IID_IConsoleNameSpace,
                                          (LPVOID*)&m_pConsoleNameSpace);
    if (FAILED(hr))
        return hr;

    hr = pUnknown->QueryInterface(IID_IConsole,
                                  (LPVOID*)&m_pConsole);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrData::CreateComponent(LPCOMPONENT *ppComponent)
{
    *ppComponent = new ODBMgrComponent(this);
    if (*ppComponent == NULL)
        return E_OUTOFMEMORY;

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrData::Notify(LPDATAOBJECT lpDataObject,
                                MMC_NOTIFY_TYPE event, LPARAM arg, LPARAM param)
{
    return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrData::Destroy(void)
{
    if (m_pConsoleNameSpace != NULL) {
        m_pConsoleNameSpace->Release();
        m_pConsoleNameSpace = NULL;
    }

    if (m_pConsole != NULL) {
        m_pConsole->Release();
        m_pConsole = NULL;
    }

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrData::QueryDataObject(MMC_COOKIE cookie,
        DATA_OBJECT_TYPES type, LPDATAOBJECT *ppDataObject)
{
    switch (type) {
    case CCT_SCOPE:
    case CCT_RESULT:
    case CCT_SNAPIN_MANAGER:
    case CCT_UNINITIALIZED:
        break;
    }

    *ppDataObject = new ODBMgrDataObj(this);
    if (*ppDataObject == NULL)
        return E_OUTOFMEMORY;

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrData::GetDisplayInfo(SCOPEDATAITEM *pScopeDataItem)
{
    return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrData::CompareObjects(LPDATAOBJECT lpDataObjectA,
                                        LPDATAOBJECT lpDataObjectB)
{
    return E_NOTIMPL;
}
