/*---------------------------------------

	Module	:	WAVELIB.CPP
	Purpose	:	Wave Library
				Implementations
	Date	:	11/22/1997

---------------------------------------*/

#include "wavelib.h"

// initialize component count
LONG CWaveLib :: m_cComponents = 0;

CWaveLib :: CWaveLib() : m_cRef(1)
{
	InterlockedIncrement(&m_cComponents);
}

CWaveLib :: ~CWaveLib()
{
	InterlockedDecrement(&m_cComponents);
}

// IUnknown Methods
HRESULT __stdcall CWaveLib :: QueryInterface(REFIID riid, PPVOID ppv)
{
	// Initialize 'out' parameter
	*ppv = NULL;

	if (riid == IID_IUnknown)
		*ppv = static_cast<LPUNKNOWN>(this);
	else if (riid == IID_IWaveLib)
		*ppv = static_cast<LPWAVELIB>(this);
	else
		return E_NOINTERFACE;

	reinterpret_cast<LPUNKNOWN>(*ppv)->AddRef();

	return S_OK;
}


ULONG __stdcall CWaveLib :: AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

ULONG __stdcall CWaveLib :: Release()
{
	ULONG lRtn = InterlockedDecrement(&m_cRef);

	if (lRtn == 0)
		delete this;

	return lRtn;
}

// IWaveLib methods
HRESULT __stdcall CWaveLib :: GetInputDevices(PPSAFEARRAY ppsa)
{
	// Initialize 'out' parameter
	*ppsa = NULL;

	UINT nNumDevs = ::waveInGetNumDevs();
	if (nNumDevs == 0)
		return E_FAIL;

	// Allocate a safe array to hold the
	// device names.
	LPSAFEARRAYBOUND psab = new SAFEARRAYBOUND[nNumDevs];
	if (!psab)
		return E_OUTOFMEMORY;

	UINT i;
	for (i = 0; i < nNumDevs; i++) {
		psab[i].lLbound		= 0;
		psab[i].cElements	= 1;
	}

	*ppsa = SafeArrayCreate(VT_BSTR, nNumDevs, psab);

	delete []psab;

	if (!*ppsa)
		return E_OUTOFMEMORY;

	for (i = 0; i < nNumDevs; i++) {
		WAVEINCAPS	wic;
		BSTR		bstrTemp;
		LONG		ix[1];

		::waveInGetDevCaps(i, &wic, sizeof(WAVEINCAPS));

		OLECHAR wszPName[MAXPNAMELEN];

		MultiByteToWideChar(CP_ACP, 0, wic.szPname,
		                    -1, wszPName, MAXPNAMELEN);

		bstrTemp = ::SysAllocString(wszPName);
		if (!bstrTemp) {
			SafeArrayDestroy(*ppsa);
			*ppsa = NULL;
			return E_OUTOFMEMORY;
		}

		ix[0] = i;
		SafeArrayPutElement(*ppsa, ix, bstrTemp);

		::SysFreeString(bstrTemp);
	}

	return S_OK;
}

HRESULT __stdcall CWaveLib :: GetOutputDevices(PPSAFEARRAY ppsa)
{
	// Initialize 'out' parameter
	*ppsa = NULL;

	UINT nNumDevs = ::waveOutGetNumDevs();
	if (nNumDevs == 0)
		return E_FAIL;

	// Allocate a safe array to hold the
	// device names.
	LPSAFEARRAYBOUND psab = new SAFEARRAYBOUND[nNumDevs];
	if (!psab)
		return E_OUTOFMEMORY;

	UINT i;
	for (i = 0; i < nNumDevs; i++) {
		psab[i].lLbound		= 0;
		psab[i].cElements	= 1;
	}

	*ppsa = SafeArrayCreate(VT_BSTR, nNumDevs, psab);

	delete []psab;

	if (!*ppsa)
		return E_OUTOFMEMORY;

	for (i = 0; i < nNumDevs; i++) {
		WAVEOUTCAPS	woc;
		BSTR		bstrTemp;
		LONG		ix[1];

		::waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS));

		OLECHAR wszPName[MAXPNAMELEN];

		MultiByteToWideChar(CP_ACP, 0, woc.szPname,
		                    -1, wszPName, MAXPNAMELEN);

		bstrTemp = ::SysAllocString(wszPName);
		if (!bstrTemp) {
			SafeArrayDestroy(*ppsa);
			*ppsa = NULL;
			return E_OUTOFMEMORY;
		}

		ix[0] = i;
		SafeArrayPutElement(*ppsa, ix, bstrTemp);

		::SysFreeString(bstrTemp);
	}

	return S_OK;
}

HRESULT __stdcall CWaveLib :: GetDeviceInCaps(UINT nIndex, WAVEINCAPS ** ppwic)
{
	// Initialize 'out' parameter
	*ppwic = NULL;

	*ppwic = (WAVEINCAPS*)::CoTaskMemAlloc(sizeof(WAVEINCAPS));
	if (!*ppwic)
		return E_OUTOFMEMORY;

	MMRESULT rtn = ::waveInGetDevCaps(nIndex, *ppwic, sizeof(WAVEINCAPS));
	if (rtn != MMSYSERR_NOERROR) {
		::CoTaskMemFree(*ppwic);
		*ppwic = NULL;
		return E_FAIL;
	}

	return S_OK;
}

HRESULT __stdcall CWaveLib :: GetDeviceOutCaps(UINT nIndex, WAVEOUTCAPS ** ppwoc)
{
	// Initialize 'out' parameter
	*ppwoc = NULL;

	*ppwoc = (WAVEOUTCAPS*)::CoTaskMemAlloc(sizeof(WAVEOUTCAPS));
	if (!*ppwoc)
		return E_OUTOFMEMORY;

	MMRESULT rtn = ::waveOutGetDevCaps(nIndex, *ppwoc, sizeof(WAVEOUTCAPS));
	if (rtn != MMSYSERR_NOERROR) {
		::CoTaskMemFree(*ppwoc);
		*ppwoc = NULL;
		return E_FAIL;
	}

	return S_OK;
}

