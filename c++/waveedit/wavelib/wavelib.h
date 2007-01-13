/*---------------------------------------

	Module	:	WAVELIB.H
	Purpose	:	Wave Library Declarations
	Date	:	11/22/1997

---------------------------------------*/

#ifndef __WAVELIB_H__
#define __WAVELIB_H__

#include "iwavelib.h"
#include "wavemacs.h"

// Forward declarations
DECLARE_MY_GUIDS

/////////////////////////////////
//
// CWaveLib
//
class CWaveLib : public IWaveLib
{
public:

	// IUnknown methods
	virtual HRESULT __stdcall QueryInterface(REFIID, PPVOID);
	virtual ULONG	__stdcall AddRef();
	virtual ULONG	__stdcall Release();

	// IWaveLib Methods
	virtual HRESULT __stdcall GetInputDevices(PPSAFEARRAY);
	virtual HRESULT __stdcall GetOutputDevices(PPSAFEARRAY);
	virtual HRESULT __stdcall GetDeviceInCaps(UINT, WAVEINCAPS **);
	virtual HRESULT __stdcall GetDeviceOutCaps(UINT, WAVEOUTCAPS **);

	static inline LONG GetComponentCount() { return m_cComponents; }
	
	CWaveLib();
	~CWaveLib();

protected:
	LONG m_cRef;				// internal reference count
	static LONG m_cComponents;	// Component count
};

/////////////////////////////////////////////
//
// Class factory
//
class CFactory : public IClassFactory
{
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
	CFactory () : m_cRef(1){}
	
	// Destructor
	~CFactory(){}

private:
	LONG m_cRef;
};

#endif // __WAVELIB_H__