/////////////////////////////////////////////////////////////////////////////
//
// ODBMGRFACTORY.CPP : Object database manager class factory
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "ODBMgrFactory.h"
#include "ODBManager.h"

LONG ODBMgrFactory::m_cLock = 0;

/////////////////////////////////////////////////////////////////////////////
ODBMgrFactory::ODBMgrFactory()
		: m_cRef(0)
{
}

/////////////////////////////////////////////////////////////////////////////
ODBMgrFactory::~ODBMgrFactory()
{
}

/////////////////////////////////////////////////////////////////////////////
ODBMgrFactory * ODBMgrFactory::Create()
{
	return new ODBMgrFactory();
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrFactory::QueryInterface(REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;

	if (riid == IID_IUnknown || riid == IID_IClassFactory)
		*ppv = this;

	if (*ppv) {
		((LPUNKNOWN)*ppv)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) ODBMgrFactory::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) ODBMgrFactory::Release()
{
	if (InterlockedDecrement(&m_cRef) == 0) {
		delete this;
		return 0;
	}

	return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid,
        LPVOID * ppv)
{
	if (pUnkOuter != NULL)
		return CLASS_E_NOAGGREGATION;

	ODBManagerPtr manager;
	manager.Attach(new ODBManager());

	if (manager == NULL)
		return E_OUTOFMEMORY;

	HRESULT hr = manager->QueryInterface(riid, ppv);
	if (FAILED(hr))
		return hr;

	manager.Detach();	// release ownership

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBMgrFactory::LockServer(BOOL fLock)
{
	if (fLock) {
		InterlockedIncrement(&m_cLock);
	} else {
		InterlockedDecrement(&m_cLock);
	}

	return S_OK;
}
