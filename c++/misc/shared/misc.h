/*---------------------------------------
	Module	:	MISC.H
	Date	:	10/26/1997
	Purpose	:	Miscellaneous Function
				Library
----------------------------------------*/

#ifndef __MISC_H__
#define __MISC_H__

#ifdef UNICODE
#define _UNICODE
#endif

#include <tchar.h>
#include <wchar.h>
#include <objbase.h>
#include "iface.h"
#include "registry.h"
#include "comtypes.h"
#include "commacs.h"

// Friendly name of component
const TCHAR g_szFriendlyName[] 	= _T("Miscellaneous Component");

// Version independent ProgID
const TCHAR	g_szVerIndProgID[] 	= _T("Miscellaneous.Component");

// ProgID
const TCHAR	g_szProgID[] 		= _T("Miscellaneous.Component.1");

// Forward declarations
extern "C" const CLSID	CLSID_Miscellaneous;
extern "C" const GUID	LIBID_MiscLib;

class CImpISupportErrorInfo;

class CMiscellaneous : public IMiscellaneous {
public:

	friend CImpISupportErrorInfo;

	// IUnknown Methods
	virtual HRESULT 	__stdcall QueryInterface(REFIID iid, PPVOID ppv);
	virtual ULONG		__stdcall AddRef();
	virtual ULONG		__stdcall Release();

	// IDispatch Methods
	virtual HRESULT		__stdcall GetTypeInfoCount(UINT* pctInfo);
	virtual HRESULT		__stdcall GetTypeInfo(UINT nTypeInfo, LCID, LPTYPEINFO* ppITypeInfo);
	virtual HRESULT		__stdcall GetIDsOfNames(REFIID riid,
	        LPOLESTR* rgzNames,
	        UINT cNames,
	        LCID lcid,
	        DISPID* rgDispId);
	virtual HRESULT		__stdcall Invoke(DISPID dispIdMember,
	                                     REFIID riid,
	                                     LCID lcid,
	                                     WORD wFlags,
	                                     DISPPARAMS* pDispParams,
	                                     VARIANT* pVarResult,
	                                     EXCEPINFO* pExcepInfo,
	                                     UINT* puArgErr);

	// IMiscellaneous Methods
	virtual HRESULT __stdcall GetDate(BSTR*);
	virtual HRESULT __stdcall GetTime(BSTR*);
	virtual HRESULT __stdcall GetDateTime(BSTR*);
	virtual HRESULT __stdcall GetDriveSpace(const BSTR, __int64*);
	virtual HRESULT __stdcall EnumDrives(BSTR*);

	// Initialization
	HRESULT Init(HMODULE);

	// Constructor
	CMiscellaneous(PFNDESTROYED);

	// Destructor
	~CMiscellaneous();

	static LONG GetComponentCount () {
		return m_cComponents;
	}

private:
	// Reference count
	LONG					m_cRef;
	static LONG				m_cComponents;
	PFNDESTROYED			m_pfnDestroy;
	LPTYPEINFO				m_pITypeInfo;
	CImpISupportErrorInfo*	m_pISupportErrorInfo;
protected:
	HRESULT GenerateError(LPCTSTR);
};

typedef CMiscellaneous* LPMISCELLANEOUS;

/////////////////////////////////////////////
//
// CImpISupportErrorInfo
//
class CImpISupportErrorInfo : public ISupportErrorInfo {
public:
	CImpISupportErrorInfo(LPMISCELLANEOUS pIMisc) : m_cRef(0) {
		m_pIMisc = pIMisc;
	}
	~CImpISupportErrorInfo() {}

	// IUnknown Methods
	virtual HRESULT 	__stdcall QueryInterface(REFIID iid, PPVOID ppv) {
		return m_pIMisc->QueryInterface(iid, ppv);
	}
	virtual ULONG		__stdcall AddRef() {
		InterlockedIncrement(&m_cRef);
		return m_pIMisc->AddRef();
	}
	virtual ULONG		__stdcall Release() {
		InterlockedDecrement(&m_cRef);
		return m_pIMisc->Release();
	}

	// ISupportErrorInfo Methods
	virtual HRESULT __stdcall InterfaceSupportsErrorInfo(REFIID riid) {
		return (riid == IID_IMiscellaneous) ? S_OK : S_FALSE;
	}
protected:
	LPMISCELLANEOUS m_pIMisc;	// Back pointer to the object
	LONG 			m_cRef;
};

/////////////////////////////////////////////
//
// Class factory
//
class CFactory : public IClassFactory {
public:
	// IUnknown methods
	virtual HRESULT __stdcall QueryInterface(REFIID iid, PPVOID ppv);
	virtual ULONG	__stdcall AddRef();
	virtual ULONG 	__stdcall Release();

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


#endif // __MISC_H__


