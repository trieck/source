// Color Button.cpp : Implementation of CColorButtonApp and DLL registration.

#include "stdafx.h"
#include "Color Button.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CColorButtonApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid = { 0xa3afc613, 0xb347, 0x11d0, { 0x97, 0xf7, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CColorButtonApp::InitInstance - DLL initialization

BOOL CColorButtonApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit) {
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CColorButtonApp::ExitInstance - DLL termination

int CColorButtonApp::ExitInstance()
{
	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
