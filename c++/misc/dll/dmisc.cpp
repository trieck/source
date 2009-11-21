/*---------------------------------------
	Module	:	DMISC.CPP
	Date	:	10/26/1997
	Purpose	:	Miscellaneous Function
				Library for In Process
				Components
----------------------------------------*/

#include "misc.h"

// Static variables
static	HINSTANCE	g_hModule 		= NULL;		// DLL module handle
static	LONG	g_cServerLocks	= 0;		// Count of locks

//
// Class factory IUnknown implementation
//
HRESULT __stdcall CFactory :: QueryInterface(REFIID iid, PPVOID ppv)
{
	LPUNKNOWN pI;

	if ((iid == IID_IUnknown) || (iid == IID_IClassFactory))
		pI = static_cast<LPCLASSFACTORY>(this);
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	pI->AddRef();

	*ppv = pI;

	return S_OK;
}

ULONG CFactory :: AddRef()
{
	return ::InterlockedIncrement(&m_cRef);
}

ULONG CFactory :: Release()
{
	if (InterlockedDecrement(&m_cRef) == 0) {
		delete this;
		return 0;
	}
	return m_cRef;
}

//
// IClassFactory implementation
//
HRESULT __stdcall CFactory :: CreateInstance(LPUNKNOWN pUnknownOuter,
        REFIID iid, PPVOID ppv)
{
	HRESULT hr = E_FAIL;

	// Cannot aggregate
	if (pUnknownOuter != NULL)
		return CLASS_E_NOAGGREGATION;

	// Create component
	CMiscellaneous* pMisc = new CMiscellaneous(NULL);
	if (!pMisc)
		return E_OUTOFMEMORY;

	// Initialize the component
	hr = pMisc->Init(g_hModule);
	if (FAILED(hr)) {
		pMisc->Release();
		return hr;
	}

	// Get the requested interface
	hr = pMisc->QueryInterface(iid, ppv);

	pMisc->Release();

	return hr;
}

// LockServer
HRESULT __stdcall CFactory :: LockServer(BOOL bLock)
{
	if (bLock)
		InterlockedIncrement(&g_cServerLocks);
	else
		InterlockedDecrement(&g_cServerLocks);

	return S_OK;
}

//////////////////////////////////
//
// DLL Exported Functions
//

// Can DLL unload now?
//
STDAPI DllCanUnloadNow()
{
	if ((CMiscellaneous :: GetComponentCount() == 0) && (g_cServerLocks == 0))
		return S_OK ;
	else
		return S_FALSE ;
}

// GetClassFactory
//
STDAPI DllGetClassObject(REFCLSID clsid,
                         REFIID iid,
                         PPVOID ppv)
{
	// Can we create this component
	if (clsid != CLSID_Miscellaneous)
		return CLASS_E_CLASSNOTAVAILABLE;

	// Create class factory
	CFactory* pFactory = new CFactory;
	if (!pFactory)
		return E_OUTOFMEMORY;

	// Get requested interface
	HRESULT hr = pFactory->QueryInterface(iid, ppv);
	pFactory->Release();

	return hr;
}

//
// Server registration
//
STDAPI DllRegisterServer()
{
	return RegisterServer(g_hModule,
	                      CLSID_Miscellaneous,
	                      g_szFriendlyName,
	                      g_szVerIndProgID,
	                      g_szProgID,
	                      LIBID_MiscLib);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_Miscellaneous,
	                        g_szVerIndProgID,
	                        g_szProgID);
}

//////////////////////////////////////////
//
// DLL module information
//
BOOL APIENTRY DllMain(HINSTANCE hModule,
                      DWORD dwReason,
                      LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = hModule;

	return TRUE;
}
