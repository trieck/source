/////////////////////////////////////////////////////////////////////////////
//
// ODBMGRCOMPONENT.CPP : Object database manager component
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "ODBMgrComponent.h"

/////////////////////////////////////////////////////////////////////////////
ODBMgrComponent::ODBMgrComponent(LPUNKNOWN pUnknown)
	: m_cRef(0), m_pUnknown(pUnknown)
{
}

/////////////////////////////////////////////////////////////////////////////
ODBMgrComponent::~ODBMgrComponent()
{
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrComponent::QueryInterface(REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;

	if (riid == IID_IUnknown || riid == IID_IComponent)
		*ppv = this;

	if (*ppv) {
		((LPUNKNOWN)*ppv)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) ODBMgrComponent::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return m_pUnknown->AddRef();
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) ODBMgrComponent::Release()
{
	InterlockedDecrement(&m_cRef);
	return m_pUnknown->Release();
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrComponent::Initialize(LPCONSOLE lpConsole)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrComponent::Notify(LPDATAOBJECT lpDataObject,
                                     MMC_NOTIFY_TYPE event, LPARAM arg, LPARAM param)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrComponent::Destroy(MMC_COOKIE cookie)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrComponent::QueryDataObject(MMC_COOKIE cookie,
        DATA_OBJECT_TYPES type, LPDATAOBJECT *ppDataObject)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrComponent::GetResultViewType(MMC_COOKIE cookie,
        LPOLESTR *ppViewType, long *pViewOptions)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrComponent::GetDisplayInfo(RESULTDATAITEM *pResultDataItem)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrComponent::CompareObjects(LPDATAOBJECT lpDataObjectA,
        LPDATAOBJECT lpDataObjectB)
{
	return E_NOTIMPL;
}

