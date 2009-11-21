/*-----------------------------------
	Module	:	CMPNT2.CPP
	Author	:	Thomas A. Rieck
	Date	:	10/25/1997
	Purpose	:	Aggregation Example
				(Outer Component)
-----------------------------------*/

#include <iostream>
#include <objbase.h>

#include "iface.h"
#include "registry.h"

typedef void**		PPVOID;
typedef IUnknown*	LPUNKNOWN;

using std::cout;
using std::endl;

void trace(LPCSTR msg)
{
	cout << "Component 2:\t" << msg << endl ;
}

///////////////////////////////////
//
// Global variables
//

// Static variables
static	HINSTANCE	g_hModule 		= NULL;		// DLL module handle
static	LONG	g_cComponents	= 0;		// Count of active components
static	LONG	g_cServerLocks	= 0;		// Count of locks

// Friendly name of component
const char g_szFriendlyName[] 	= "Aggregation Component 2";

// Version independent ProgID
const char g_szVerIndProgID[] 	= "Aggregation.Component2";

// ProgID
const char g_szProgID[] 		= "Aggregation.Component2.1";


///////////////////////////////////////////////////////////
//
// Nondelegating IUnknown interface  @N
//
struct INondelegatingUnknown {
	virtual HRESULT __stdcall
	NondelegatingQueryInterface(REFIID, PPVOID) = 0;
	virtual ULONG __stdcall NondelegatingAddRef() = 0;
	virtual ULONG __stdcall NondelegatingRelease() = 0;
};

/////////////////////////////////////
//
// Component
//
class CB : public IY,
			public INondelegatingUnknown {
public:
	// Delegating IUnknown methods
	virtual HRESULT __stdcall QueryInterface(REFIID iid, PPVOID ppv) {
		trace ("Delegate QueryInterface.");
		return m_pUnknownOuter->QueryInterface(iid, ppv);
	}

	virtual ULONG __stdcall AddRef() {
		trace ("Delegate AddRef.");
		return m_pUnknownOuter->AddRef();
	}

	virtual ULONG __stdcall Release() {
		trace ("Delegate release");
		return m_pUnknownOuter->Release();
	}

	// Nondelegating IUnknown methods
	virtual HRESULT __stdcall NondelegatingQueryInterface(REFIID iid, PPVOID);
	virtual ULONG	__stdcall NondelegatingAddRef();
	virtual ULONG	__stdcall NondelegatingRelease();

	// IY Methods
	virtual void __stdcall Fy() {
		trace("Fy");
	}

	// Constructor
	CB(LPUNKNOWN m_pUnknownOuter);

	// Destructor
	~CB();

private:
	// Reference count
	LONG m_cRef;

	// Pointer to outer component's IUnknown
	LPUNKNOWN m_pUnknownOuter;
};

//
// IUnknown implementation
//
HRESULT __stdcall CB :: NondelegatingQueryInterface(REFIID iid, PPVOID ppv)
{
	if (iid == IID_IUnknown) {
		// !!! CAST IS VERY IMPORTANT !!!
		*ppv = static_cast<INondelegatingUnknown*>(this);
	} else if (iid == IID_IY)
		*ppv = static_cast<IY*>(this);
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<LPUNKNOWN>(*ppv)->AddRef();

	return S_OK;
}

ULONG __stdcall CB :: NondelegatingAddRef()
{
	return InterlockedIncrement(&m_cRef);
}

ULONG __stdcall CB :: NondelegatingRelease()
{
	if (InterlockedDecrement(&m_cRef) == 0) {
		delete this;
		return 0;
	}

	return m_cRef;
}

//
// Constructor
//
CB :: CB(LPUNKNOWN pUnknownOuter) : m_cRef(1)
{
	::InterlockedIncrement(&g_cComponents);

	if (pUnknownOuter == NULL) {
		trace ("Not aggregating; delegate to nondelegating IUnknown.");
		m_pUnknownOuter = reinterpret_cast<LPUNKNOWN>
		                  (static_cast<INondelegatingUnknown*>
		                   (this));
	} else {
		trace ("Aggregating; delegate to outer IUnknown.");
		m_pUnknownOuter = pUnknownOuter;
	}
}

//
// Destructor
//
CB :: ~CB()
{
	InterlockedDecrement(&g_cComponents);
	trace("Destroy self.");
}

/////////////////////////////////////////////
//
// Class factory
//
class CFactory : public IClassFactory {
public:
	// IUnknown methods
	virtual HRESULT __stdcall QueryInterface(REFIID iid, PPVOID ppv);
	virtual ULONG	__stdcall AddRef();
	virtual ULONG __stdcall Release();

	// IClassFactory methods
	virtual HRESULT __stdcall CreateInstance(LPUNKNOWN pUnknownOuter,
	        REFIID iid,
	        PPVOID ppv);
	virtual HRESULT __stdcall LockServer(BOOL bLock);

	// Constructor
	CFactory () : m_cRef(1) {}

	// Destructor
	~CFactory() {}

private:
	LONG m_cRef;
};

//
// Class factory IUnknown implementation
//
HRESULT __stdcall CFactory :: QueryInterface(REFIID iid, PPVOID ppv)
{
	if ((iid == IID_IUnknown) || (iid == IID_IClassFactory))
		*ppv = static_cast<LPCLASSFACTORY>(this);
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<LPUNKNOWN>(*ppv)->AddRef();

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
	if ((pUnknownOuter != NULL) && (iid != IID_IUnknown))
		return CLASS_E_NOAGGREGATION;

	// Create component
	CB* pB = new CB(pUnknownOuter);
	if (!pB)
		return E_OUTOFMEMORY;

	// Get the requested interface
	hr = pB->NondelegatingQueryInterface(iid, ppv);
	pB->NondelegatingRelease();
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

//////////////////////////////////////////////////
//
// Exported functions
//

STDAPI DllCanUnloadNow()
{
	if ((g_cComponents == 0) && (g_cServerLocks == 0))
		return S_OK;
	else
		return S_FALSE;
}


//
// GetClassFactory
//
STDAPI DllGetClassObject(REFCLSID clsid,
                         REFIID iid,
                         PPVOID ppv)
{
	// Can we create this component
	if (clsid != CLSID_Component2)
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
	                      CLSID_Component2,
	                      g_szFriendlyName,
	                      g_szVerIndProgID,
	                      g_szProgID);
}

STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_Component2,
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


















