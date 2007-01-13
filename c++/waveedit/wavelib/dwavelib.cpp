/*---------------------------------------

	Module	:	DWAVELIB.CPP
	Purpose	:	External Wave Library 
				Implementations
	Date	:	11/22/1997

---------------------------------------*/
#include <objbase.h>
#include "wavelib.h"
#include "registry.h"

// Static variables
static	HINSTANCE g_hModule 		= NULL;		// DLL module handle
static	LONG	g_cServerLocks	= 0;		// Count of locks

static const TCHAR g_szProgID[]					= "WaveLib.Component.1";
static const TCHAR g_szVerIndProgID[]			= "WaveLib.Component";
static const TCHAR g_szFriendlyName[]			= "Wave Library Component";

//
// Class factory IUnknown implementation
//
HRESULT __stdcall CFactory :: QueryInterface(REFIID iid, PPVOID ppv)
{
	LPUNKNOWN pI;

	// Initialize 'out' parameter.
	*ppv = NULL;

	if ((iid == IID_IUnknown) || (iid == IID_IClassFactory))
		pI = static_cast<LPCLASSFACTORY>(this);
	else
		return E_NOINTERFACE;
		
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
	ULONG lRtn = InterlockedDecrement(&m_cRef);

	if (lRtn == 0)
		delete this;
	
	return lRtn;
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
	LPWAVELIB pWaveLib = new CWaveLib();
	if (!pWaveLib)
		return E_OUTOFMEMORY;

	// Get the requested interface
	hr = pWaveLib->QueryInterface(iid, ppv);
	
	pWaveLib->Release();
	
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
	if ((CWaveLib :: GetComponentCount() == 0) && (g_cServerLocks == 0))
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
	if (clsid != CLSID_WaveLib)
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
					CLSID_WaveLib,
					g_szFriendlyName,
					g_szVerIndProgID,
					g_szProgID,
					CLSID_NULL);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_WaveLib,
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

