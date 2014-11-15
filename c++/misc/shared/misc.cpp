/*---------------------------------------
	Module	:	MISC.CPP
	Date	:	10/26/1997
	Purpose	:	Miscellaneous Function
				Library
----------------------------------------*/

#include "misc.h"

LONG CMiscellaneous :: m_cComponents = 0;
//
// Constructor
//
CMiscellaneous :: CMiscellaneous(PFNDESTROYED pfnDestroy) : m_cRef(1)
{
    m_pfnDestroy 			= pfnDestroy;
    m_pITypeInfo			= NULL;
    m_pISupportErrorInfo	= NULL;

    InterlockedIncrement(&m_cComponents);
}

//
// Destructor
//
CMiscellaneous :: ~CMiscellaneous()
{
    ReleaseInterface(m_pITypeInfo);
    DeleteInterfaceImp(m_pISupportErrorInfo);

    InterlockedDecrement(&m_cComponents);
}

/////////////////////
//
// Init() Function
//
HRESULT CMiscellaneous :: Init(HMODULE hModule)
{
    HRESULT hr;

    assert(hModule);

    // Load TypeInfo on demand if we have not already loaded it.
    if (!m_pITypeInfo) {
        LPTYPELIB pITypeLib = NULL;

        hr = ::LoadRegTypeLib(LIBID_MiscLib,
                              1, 0, // Version numbers
                              0x00,
                              &pITypeLib);

        if (FAILED(hr)) {
            // Get the module's fullname.
            TCHAR 	szModule[_MAX_PATH + _MAX_FNAME];
            OLECHAR	wszModule[_MAX_PATH + _MAX_FNAME];

            ::GetModuleFileName(hModule, szModule, 512);

            // Load and register the type library
#ifndef _UNICODE
            MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szModule,
                                -1 , wszModule, _MAX_PATH + _MAX_FNAME);
#else
            wcscpy(wszModule, szModule);
#endif // _UNICODE

            hr = ::LoadTypeLib(wszModule, &pITypeLib);
            if (FAILED(hr))
                return hr;

            // Ensure that the type library is registered.
            hr = RegisterTypeLib(pITypeLib, wszModule, NULL);
            if (FAILED(hr))
                return hr;

        }

        // Get the type information for the interface
        // of the  object.
        hr = pITypeLib->GetTypeInfoOfGuid(IID_IMiscellaneous, &m_pITypeInfo);

        pITypeLib->Release();

        if (FAILED(hr))
            return hr;
    }

    // Create an instance of CImpISupportErrorInfo object
    m_pISupportErrorInfo = new CImpISupportErrorInfo(this);
    if (m_pISupportErrorInfo == NULL)
        return E_OUTOFMEMORY;

    return NOERROR;
}


//////////////////////////////////////////
//
// GetDate() Function
//
HRESULT CMiscellaneous :: GetDate(BSTR* pbstrDate)
{
    SYSTEMTIME	st;
    OLECHAR*	pszDate;
    TCHAR		szMonth[3], szDay[3];

    GetLocalTime(&st);

    if (st.wMonth < 10)
        wsprintf(szMonth, _T("0%d"), st.wMonth);
    else
        wsprintf(szMonth, _T("%d"), st.wMonth);

    if (st.wDay < 10)
        wsprintf(szDay, _T("0%d"), st.wDay);
    else
        wsprintf(szDay, _T("%d"), st.wDay);

    pszDate = (OLECHAR*)CoTaskMemAlloc(128);
    if (!pszDate)
        return E_OUTOFMEMORY;

#ifndef _UNICODE
    TCHAR szTemp[128];

    wsprintf(szTemp, _T("%s/%s/%d"), szMonth, szDay, st.wYear);

    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szTemp,
                        -1 , pszDate, 128);
#else
    wsprintf(pszDate, _T("%s/%s/%d"), szMonth, szDay, st.wYear);
#endif // _UNICODE

    *pbstrDate = ::SysAllocString(pszDate);

    CoTaskMemFree(pszDate);

    if (!*pbstrDate)
        return E_OUTOFMEMORY;

    return NOERROR;
}

//////////////////////////////////////////
//
// GetTime() Function
//
HRESULT CMiscellaneous :: GetTime(BSTR* pbstrTime)
{
    SYSTEMTIME	st;
    TCHAR		szHour[3], szMinute[3];
    OLECHAR*	pszTime;
    WORD		wHour;

    GetLocalTime(&st);

    wHour = (st.wHour > 12 ? st.wHour - 12 : st.wHour);

    if (wHour == 0)
        wHour = 12;

    if (wHour < 10)
        wsprintf(szHour, _T("0%d"), wHour);
    else
        wsprintf(szHour, _T("%d"), wHour);

    if (st.wMinute < 10)
        wsprintf(szMinute, _T("0%d"), st.wMinute);
    else
        wsprintf(szMinute, _T("%d"), st.wMinute);

    pszTime = (OLECHAR*)CoTaskMemAlloc(128);
    if (!pszTime)
        return E_OUTOFMEMORY;

#ifndef _UNICODE
    TCHAR szTemp[128];

    wsprintf(szTemp, _T("%s:%s %s"), szHour, szMinute, st.wHour >= 12 ? _T("PM") : _T("AM"));

    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szTemp,
                        -1 , pszTime, 128);
#else
    wsprintf(pszTime, _T("%s:%s %s"), szHour, szMinute, st.wHour >= 12 ? _T("PM") : _T("AM"));
#endif // _UNICODE

    *pbstrTime = ::SysAllocString(pszTime);

    CoTaskMemFree(pszTime);

    if (!*pbstrTime)
        return E_OUTOFMEMORY;

    return NOERROR;
}

//////////////////////////////////////////
//
// GetDateTime() Function
//
HRESULT CMiscellaneous :: GetDateTime(BSTR* pbstrDateTime)
{
    OLECHAR		*lpszDateTime;
    BSTR		bstrDate, bstrTime;
    HRESULT		hr;

    // Allocate memory
    lpszDateTime = (OLECHAR*)CoTaskMemAlloc(256);
    if (!lpszDateTime)
        return E_OUTOFMEMORY;

    // GetDate
    hr = GetDate(&bstrDate);
    if (FAILED(hr)) {
        CoTaskMemFree(lpszDateTime);
        return hr;
    }

    // GetTime
    hr = GetTime(&bstrTime);
    if (FAILED(hr)) {
        CoTaskMemFree(lpszDateTime);
        ::SysFreeString(bstrDate);
        return hr;
    }

#ifndef _UNICODE
    TCHAR szTemp[256];
    TCHAR szDate[128];
    TCHAR szTime[128];

    wcstombs(szDate, bstrDate, 128);
    wcstombs(szTime, bstrTime, 128);

    wsprintf(szTemp, _T("%s %s"), szDate, szTime);

    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szTemp,
                        -1 , lpszDateTime, 256);
#else
    wsprintf(lpszDateTime, _T("%s %s"), bstrDate, bstrTime);
#endif // _UNICODE

    ::SysFreeString(bstrDate);
    ::SysFreeString(bstrTime);

    *pbstrDateTime = ::SysAllocString(lpszDateTime);

    CoTaskMemFree(lpszDateTime);

    if (!*pbstrDateTime)
        return E_OUTOFMEMORY;

    return NOERROR;
}

///////////////////////////
//
// GetDriveSpace() Function
//
HRESULT CMiscellaneous :: GetDriveSpace(const BSTR bstrDrive, __int64* pBytes)
{
    ULARGE_INTEGER free;
    if (!bstrDrive || !pBytes)
        return E_POINTER;

    // Get Disk Free Space for given drive
    TCHAR szDrive[8];

#ifndef _UNICODE
    WideCharToMultiByte(CP_ACP, 0, bstrDrive, - 1,
                        szDrive, 8, NULL, NULL);
#else
    wcscpy(szDrive, bstrDrive);
#endif // _UNICODE

    BOOL fRtn = GetDiskFreeSpaceEx(szDrive, NULL, NULL, &free);
    if (!fRtn) {
        GenerateError(_T("Error getting drive space."));
        return E_FAIL;
    }

    *pBytes = free.QuadPart;

    return NOERROR;
}

//////////////////////////////
//
// EnumDrives() Function
//
HRESULT CMiscellaneous :: EnumDrives(BSTR* pbstrDrives)
{
    DWORD		dwDrives;
    OLECHAR		szDriveLetter[5];
    OLECHAR*	pszDrives;
    INT			i, j;
    HRESULT		hr;
    LPMALLOC	pIMalloc;

    // Get an IMalloc Pointer
    hr = CoGetMalloc(1, &pIMalloc);
    if (FAILED(hr))
        return E_FAIL;

    pszDrives = (OLECHAR*)pIMalloc->Alloc(1024);
    if (!pszDrives) {
        pIMalloc->Release();
        return E_OUTOFMEMORY;
    }

    ZeroMemory(pszDrives, pIMalloc->GetSize(pszDrives));

    dwDrives = GetLogicalDrives();

    j = 1;

    for (i = 0; i < 26; i++) {
        if (i != 0) j <<= 1;

        if (dwDrives & j) {
#ifndef _UNICODE
            TCHAR szTemp[5];
            wsprintf(szTemp, _T("%c:\\~"), i + 65);

            MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szTemp,
                                -1, szDriveLetter, 5);
#else
            wsprintf(szDriveLetter, _T("%c:\\~"), i + 65);
#endif // _UNICODE
            wcsncat(pszDrives, szDriveLetter, 4);
        }
    }

    wcsncat(pszDrives, L"~", 1);

    *pbstrDrives = ::SysAllocString(pszDrives);

    CoTaskMemFree(pszDrives);

    pIMalloc->Release();

    if (!*pbstrDrives)
        return E_OUTOFMEMORY;

    return NOERROR;
}

//
// IUnknown implementation
//
HRESULT __stdcall CMiscellaneous :: QueryInterface(REFIID iid, PPVOID ppv)
{
    if (iid == IID_IUnknown)
        *ppv = static_cast<LPUNKNOWN>(this);
    else if (iid == IID_IDispatch)
        *ppv = static_cast<LPDISPATCH>(this);
    else if (iid == IID_IMiscellaneous)
        *ppv = static_cast<LPMISCELLANEOUS>(this);
    else if (iid == IID_ISupportErrorInfo)
        *ppv = m_pISupportErrorInfo;
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    reinterpret_cast<LPUNKNOWN>(*ppv)->AddRef();

    return S_OK;
}

//
// AddRef() Function
//
ULONG __stdcall CMiscellaneous :: AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

//
// Release() Function
//
ULONG __stdcall CMiscellaneous :: Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        if (m_pfnDestroy)
            m_pfnDestroy();

        delete this;
        return 0;
    }

    return m_cRef;
}

//
// IDispatch implementation
//
HRESULT __stdcall CMiscellaneous :: GetTypeInfoCount(UINT* pCountTypeInfo)
{
    if (!pCountTypeInfo)
        return E_POINTER;

    *pCountTypeInfo = 1;

    return NOERROR;
}

HRESULT __stdcall CMiscellaneous :: GetTypeInfo(UINT nTypeInfo, LCID, LPTYPEINFO* ppITypeInfo)
{
    // Initialize the out parameter
    *ppITypeInfo = NULL;

    if (nTypeInfo != 0)			// only accept IDispatch interface
        return DISP_E_BADINDEX;

    assert (m_pITypeInfo);

    m_pITypeInfo->AddRef();

    *ppITypeInfo = m_pITypeInfo;

    return NOERROR;
}

HRESULT __stdcall CMiscellaneous :: GetIDsOfNames(REFIID riid, LPOLESTR* arrayNames,
        UINT countNames, LCID, DISPID* arrayDispIDs)
{
    if (riid != IID_NULL)
        return DISP_E_UNKNOWNINTERFACE;

    assert (m_pITypeInfo);

    HRESULT hr = m_pITypeInfo->GetIDsOfNames(arrayNames, countNames, arrayDispIDs);

    return hr;
}

HRESULT __stdcall CMiscellaneous :: Invoke(
    DISPID dispidMember,
    REFIID riid,
    LCID,
    WORD wFlags,
    DISPPARAMS* pDispParams,
    VARIANT* pVarResult,
    EXCEPINFO* pExcepInfo,
    UINT* pArgErr)
{
    if (riid != IID_NULL)
        return DISP_E_UNKNOWNINTERFACE;

    ::SetErrorInfo(0, NULL);

    HRESULT hr = m_pITypeInfo->Invoke(
                     static_cast<LPDISPATCH>(this),
                     dispidMember, wFlags, pDispParams,
                     pVarResult, pExcepInfo, pArgErr);

    return hr;
}

//////////////////////////////
//
// GenerateError() Function
//
HRESULT CMiscellaneous :: GenerateError(LPCTSTR lpszErrDescription)
{
    OLECHAR	wszDescription[256];

    ICreateErrorInfo* pICreateErr;
    HRESULT hr = ::CreateErrorInfo(&pICreateErr);
    if (FAILED(hr))
        return E_FAIL;

    pICreateErr->SetSource(L"Miscellaneous.Component");

#ifndef _UNICODE
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpszErrDescription,
                        -1 , wszDescription, 255);
#else
    wcscpy(wszDescription, lpszErrDescription);
#endif

    BSTR bstrDescription = ::SysAllocString(wszDescription);

    pICreateErr->SetDescription(bstrDescription);

    IErrorInfo* pIErrorInfo = NULL;
    hr = pICreateErr->QueryInterface(IID_IErrorInfo,
                                     (PPVOID)&pIErrorInfo);

    if (SUCCEEDED(hr)) {
        ::SetErrorInfo(0L, pIErrorInfo);
        pIErrorInfo->Release();
    }

    ::SysFreeString(bstrDescription);

    pICreateErr->Release();

    return NOERROR;
}
