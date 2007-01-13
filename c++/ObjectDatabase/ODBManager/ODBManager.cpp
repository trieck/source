/////////////////////////////////////////////////////////////////////////////
//
// ODBMANAGER.CPP : Object database manager
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "ODBMgrData.h"
#include "ODBManager.h"
#include "ODBMgrFactory.h"
#include "guids.h"

LONG ODBManager::m_cCount = 0;

/////////////////////////////////////////////////////////////////////////////
ODBManager::ODBManager()
 : m_cRef(0)
{
	m_pData = new ODBMgrData(this);
	InterlockedIncrement(&m_cCount);
}

/////////////////////////////////////////////////////////////////////////////
ODBManager::~ODBManager()
{
	delete m_pData;
	InterlockedDecrement(&m_cCount);
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP ODBManager::QueryInterface(REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;

    if (riid == IID_IUnknown)
        *ppv = this;
    
	if (riid == IID_IComponentData)
		*ppv = m_pData;

    if (*ppv) {
        ((LPUNKNOWN)*ppv)->AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) ODBManager::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) ODBManager::Release()
{
	if (InterlockedDecrement(&m_cRef) == 0) {
		delete this;
		return 0;
	}

	return m_cRef;
}

