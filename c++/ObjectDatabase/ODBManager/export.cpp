/////////////////////////////////////////////////////////////////////////////
//
// EXPORT.CPP : exported functions
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include <initguid.h>
#include "ODBManager.h"
#include "ODBMgrFactory.h"
#include "guids.h"

HINSTANCE hInstance = NULL;

namespace {
BOOL SetKeyAndValue(LPCWSTR pKey, LPCWSTR pSubKey, LPCWSTR val);
}

/////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		hInstance = hModule;
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
	if (CLSID_ODBManager != rclsid)
		return E_FAIL;

	ODBMgrFactoryPtr factory;
	factory.Attach(ODBMgrFactory::Create());

	if (factory == NULL)
		return E_OUTOFMEMORY;

	HRESULT hr = factory->QueryInterface(riid, ppv);
	if (FAILED(hr))
		return hr;

	factory.Detach();	// release ownership

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
STDAPI DllCanUnloadNow()
{
	if (ODBMgrFactory::GetLockCount() == 0 &&
	        ODBManager::GetObjectCount() == 0) {
		return S_OK;
	}

	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
STDAPI DllRegisterServer()
{
	CStringW ws, clsid;
	LPOLESTR pclsid = clsid.GetBufferSetLength(64);
	StringFromGUID2(CLSID_ODBManager, pclsid, 64);

	ws.Format(L"CLSID\\%s", clsid);

	// Create ProgID keys
	SetKeyAndValue(L"ODBManager1.0", NULL, L"Object Database Manager");
	SetKeyAndValue(L"ODBManager1.0", L"CLSID", clsid);

	// Create VersionIndependentProgID keys
	SetKeyAndValue(L"ODBManager", NULL, L"Object Database Manager");
	SetKeyAndValue(L"ODBManager", L"CurVer", L"ODBManager1.0");
	SetKeyAndValue(L"ODBManager", L"CLSID", clsid);

	// Create entries under CLSID
	SetKeyAndValue(ws, NULL, L"Object Database Manager");
	SetKeyAndValue(ws, L"ProgID", L"ODBManager1.0");
	SetKeyAndValue(ws, L"VersionIndependentProgID", L"ODBManager");

	WCHAR module[MAX_PATH];
	GetModuleFileName(hInstance, module, MAX_PATH);
	SetKeyAndValue(ws, L"InprocServer32", module);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
STDAPI DllUnregisterServer()
{
	CStringW ws, clsid;
	LPOLESTR pclsid = clsid.GetBufferSetLength(64);
	StringFromGUID2(CLSID_ODBManager, pclsid, 64);

	ws.Format(L"CLSID\\%s", clsid);

	CRegKey key;
	LONG lResult;
	if ((lResult = key.Open(HKEY_CLASSES_ROOT, NULL)) != ERROR_SUCCESS)
		return E_FAIL;

	key.RecurseDeleteKey(ws);
	key.RecurseDeleteKey(L"ODBManager");
	key.RecurseDeleteKey(L"ODBManager1.0");

	return S_OK;
}

namespace {	// anonymous

/////////////////////////////////////////////////////////////////////////////
BOOL SetKeyAndValue(LPCWSTR pKey, LPCWSTR pSubKey, LPCWSTR pVal)
{
	CStringW skey(pKey);

	if (pSubKey != NULL) {
		skey.Format(L"%s\\%s", pKey, pSubKey);
	}

	CRegKey key;
	LONG lResult = key.Create(HKEY_CLASSES_ROOT, skey);
	if (lResult != ERROR_SUCCESS)
		return FALSE;

	if (pVal != NULL) {
		if ((lResult = key.SetStringValue(NULL, pVal)) != ERROR_SUCCESS)
			return FALSE;
	}

	return TRUE;
}

}	// anonymous