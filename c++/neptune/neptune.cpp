
#include <windows.h>
#include <tchar.h>
#include <comdef.h>
#include <initguid.h>
#include <atlbase.h>
#include <string>
#include <math.h>
#include "neptune.h"
#include "neptune_i.c"
#include "resource.h"

namespace  	// anonymous
{

typedef std::basic_string<TCHAR> tstring;

// token type enumeration
enum tokenType {
    TK_EMPTY = 0,
    TK_INDEX = 1,
    TK_TEXT = 2
};

// token structure
typedef struct {
    tstring value;
    tokenType type;
} Token, *LPTOKEN;

// get next token from input
bool gettok(LPCTSTR *ppin, LPTOKEN ptok);

}	// anonymous

/////////////////////////////////////////////////////////////////////////////
class Neptune : public IStringUtil, public IComputer
{
public:
    Neptune();
    virtual ~Neptune();

// IUnknown methods
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    STDMETHODIMP QueryInterface(REFIID iid, LPVOID *ppv);

// IStringUtil methods
    STDMETHODIMP FormatString(/*[in]*/ BSTR fmt, /*[out] */ BSTR *output,
                                       /*[in]*/ SAFEARRAY **args);

// IComputer methods
    STDMETHODIMP get_Name(/*[out, retval]*/ BSTR *pVal);
    STDMETHODIMP get_SystemDirectory(/*[out, retval]*/ BSTR *pVal);
private:
    ULONG m_cRef;
};

/////////////////////////////////////////////////////////////////////////////
class NeptuneClassFactory : public IClassFactory
{
public:
    NeptuneClassFactory();
    ~NeptuneClassFactory();

// IUnknown methods
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    STDMETHODIMP QueryInterface(REFIID iid, LPVOID *ppv);

// IClassFactory members
    STDMETHODIMP CreateInstance(IUnknown *, REFIID iid, void **ppv);
    STDMETHODIMP LockServer(BOOL);

private:
    ULONG m_cRef;
};

static NeptuneClassFactory g_neptuneFactory;
static LONG g_cObjects;
static LONG g_cLocks;
static HINSTANCE g_hInstance;
static TCHAR progId[] = _T("Neptune.Component.1");
static TCHAR verIndProgId[] = _T("Neptune.Component");

static HRESULT RegisterComponent(const CLSID& clsid, LPCTSTR progID,
                                 LPCTSTR verIndProgID, UINT desc, DWORD flags);
static HRESULT RegisterProgID(LPCSTR clsid, LPCTSTR progID, LPCTSTR desc);
static HRESULT ModuleRegisterTypeLib();
static HRESULT ModuleLoadTypeLib(BSTR* pbstrPath, ITypeLib** ppTypeLib);

#define THREADFLAGS_APARTMENT 0x1
#define THREADFLAGS_BOTH 0x2
#define AUTPRXFLAG 0x4

/////////////////////////////////////////////////////////////////////////////
Neptune::Neptune()
    : m_cRef(1)
{
    InterlockedIncrement(&g_cObjects);
}

/////////////////////////////////////////////////////////////////////////////
Neptune::~Neptune()
{
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) Neptune::AddRef()
{
    return InterlockedIncrement((LPLONG)&m_cRef);
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) Neptune::Release()
{
    if (InterlockedDecrement((LPLONG)&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP Neptune::QueryInterface(REFIID iid, LPVOID *ppv)
{
    *ppv = NULL;

    if (iid == IID_IUnknown)
        *ppv = static_cast<IStringUtil*>(this);
    else if (iid == IID_IStringUtil)
        *ppv = static_cast<IStringUtil*>(this);
    else if (iid == IID_IComputer)
        *ppv = static_cast<IComputer*>(this);
    else return E_NOINTERFACE;

    reinterpret_cast<LPUNKNOWN>(*ppv)->AddRef();

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP Neptune::FormatString(/*[in]*/ BSTR fmt, /*[out] */ BSTR *output,
        /*[in]*/ SAFEARRAY **args)
{
    if (fmt == NULL || output == NULL)
        return E_POINTER;

    // initialize "output" parameter
    *output = NULL;

    // determine number of dimensions, only 1 is supported
    UINT dims = SafeArrayGetDim(*args);
    if (dims != 1)
        return E_INVALIDARG;

    // determine the size of the array
    long elements = (*args)->rgsabound->cElements;

    VARIANT *pargs;
    HRESULT hr = SafeArrayAccessData(*args, (LPVOID*)&pargs);
    if (FAILED(hr))
        return hr;

    USES_CONVERSION;
    LPCTSTR pfmt = OLE2T(fmt);

    CComBSTR bstrOutput;
    Token currTok;

    // substitute parameters onto output string
    while (gettok(&pfmt, &currTok)) {
        if (currTok.type == TK_INDEX) {
            int index = _ttoi(currTok.value.c_str());
            if (index >= elements)
                continue;	// out of range

            hr = VariantChangeType(&pargs[index], &pargs[index], 0, VT_BSTR);
            if (FAILED(hr)) {
                SafeArrayUnaccessData(*args);
                return hr;
            }

            bstrOutput += V_BSTR(&pargs[index]);
        } else bstrOutput += currTok.value.c_str();
    }

    hr = SafeArrayUnaccessData(*args);
    if (FAILED(hr))
        return hr;

    bstrOutput.CopyTo(output);

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP Neptune::get_Name(/*[out, retval]*/ BSTR *pVal)
{
    if (pVal == NULL)
        return E_POINTER;

    DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1;
    TCHAR machine[MAX_COMPUTERNAME_LENGTH + 1] = { 0 };
    BOOL bSuccess = GetComputerName(machine, &dwSize);
    if (!bSuccess)
        return HRESULT_FROM_WIN32(GetLastError());

    *pVal = CComBSTR(machine).Detach();

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP Neptune::get_SystemDirectory(/*[out, retval]*/ BSTR *pVal)
{
    if (pVal == NULL)
        return E_POINTER;

    TCHAR path[MAX_PATH + 1] = { 0 };
    UINT len = GetSystemDirectory(path, MAX_PATH);
    if (len == 0)
        return HRESULT_FROM_WIN32(GetLastError());

    *pVal = CComBSTR(path).Detach();

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
NeptuneClassFactory::NeptuneClassFactory()
    : m_cRef(0)
{
}

/////////////////////////////////////////////////////////////////////////////
NeptuneClassFactory::~NeptuneClassFactory()
{
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) NeptuneClassFactory::AddRef()
{
    return InterlockedIncrement((LPLONG)&m_cRef);
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) NeptuneClassFactory::Release()
{
    return InterlockedDecrement((LPLONG)&m_cRef);
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP NeptuneClassFactory::QueryInterface(REFIID iid,
        LPVOID *ppv)
{
    *ppv = NULL;

    if (iid == IID_IUnknown || iid == IID_IClassFactory) {
        *ppv = static_cast<LPCLASSFACTORY>(this);
        reinterpret_cast<LPUNKNOWN>(*ppv)->AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP NeptuneClassFactory::CreateInstance(IUnknown *pUnkOuter,
        REFIID iid, void **ppv)
{
    *ppv = NULL;

    // no aggregation.
    if (pUnkOuter != NULL)
        return CLASS_E_NOAGGREGATION;

    // Create the object
    Neptune *neptune = new Neptune();
    if (neptune == NULL)
        return E_OUTOFMEMORY;

    // Obtain the first interface pointer (which does an AddRef)
    HRESULT hr = neptune->QueryInterface(iid, ppv);

    // Delete object if interface not available.
    // Assume the initial reference count was one
    neptune->Release();

    return hr;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP NeptuneClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
        InterlockedIncrement(&g_cLocks);
    else
        InterlockedDecrement(&g_cLocks);

    return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID reserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        g_hInstance = hInst;
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID *ppv)
{
    // initialize "out" parameter
    *ppv = NULL;

    if (clsid != CLSID_Neptune)
        return CLASS_E_CLASSNOTAVAILABLE;

    // get the interface from the global class factory object
    return g_neptuneFactory.QueryInterface(iid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
STDAPI DllCanUnloadNow(void)
{
    if (g_cObjects == 0 && g_cLocks == 0)
        return S_OK;

    return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
STDAPI DllRegisterServer(void)
{
    return RegisterComponent(CLSID_Neptune, progId, verIndProgId,
                             IDS_NEPTUNE_COMPONENT_NAME, THREADFLAGS_APARTMENT);
}

/////////////////////////////////////////////////////////////////////////////
STDAPI DllUnregisterServer(void)
{
    return SELFREG_E_CLASS;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RegisterComponent(const CLSID& clsid, LPCTSTR progID,
                          LPCTSTR verIndProgID, UINT desc, DWORD dwFlags)
{
    static const TCHAR szProgID[] = _T("ProgID");
    static const TCHAR szVIProgID[] = _T("VersionIndependentProgID");
    static const TCHAR szLS32[] = _T("LocalServer32");
    static const TCHAR szIPS32[] = _T("InprocServer32");
    static const TCHAR szThreadingModel[] = _T("ThreadingModel");
    static const TCHAR szAUTPRX32[] = _T("AUTPRX32.DLL");
    static const TCHAR szApartment[] = _T("Apartment");
    static const TCHAR szBoth[] = _T("both");

    USES_CONVERSION;
    HRESULT hRes = S_OK;
    TCHAR szDesc[_MAX_PATH];
    LoadString(g_hInstance, desc, szDesc, _MAX_PATH);
    TCHAR szModule[_MAX_PATH];
    GetModuleFileName(g_hInstance, szModule, _MAX_PATH);

    LPOLESTR lpOleStr;
    StringFromCLSID(clsid, &lpOleStr);
    LPTSTR lpsz = OLE2T(lpOleStr);

    hRes = RegisterProgID(lpsz, progID, szDesc);
    if (hRes == S_OK)
        hRes = RegisterProgID(lpsz, verIndProgID, szDesc);
    LONG lRes = ERROR_SUCCESS;
    if (hRes == S_OK) {
        CRegKey key;
        lRes = key.Open(HKEY_CLASSES_ROOT, _T("CLSID"), KEY_READ | KEY_WRITE);
        if (lRes == ERROR_SUCCESS) {
            lRes = key.Create(key, lpsz, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE);
            if (lRes == ERROR_SUCCESS) {
                key.SetValue(szDesc);
                key.SetKeyValue(szProgID, progID);
                key.SetKeyValue(szVIProgID, verIndProgID);

                key.SetKeyValue(szIPS32, (dwFlags & AUTPRXFLAG) ? szAUTPRX32 : szModule);
                LPCTSTR lpszModel = (dwFlags & THREADFLAGS_BOTH) ? szBoth :
                                    (dwFlags & THREADFLAGS_APARTMENT) ? szApartment : NULL;
                if (lpszModel != NULL)
                    key.SetKeyValue(szIPS32, lpszModel, szThreadingModel);
            }
        }
    }

    CoTaskMemFree(lpOleStr);
    if (lRes != ERROR_SUCCESS)
        hRes = HRESULT_FROM_WIN32(lRes);

    if (SUCCEEDED(hRes))
        return ModuleRegisterTypeLib();

    return hRes;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RegisterProgID(LPCTSTR lpszCLSID, LPCTSTR lpszProgID, LPCTSTR lpszUserDesc)
{
    CRegKey keyProgID;
    LONG lRes = keyProgID.Create(HKEY_CLASSES_ROOT, lpszProgID, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE);
    if (lRes == ERROR_SUCCESS) {
        keyProgID.SetValue(lpszUserDesc);
        keyProgID.SetKeyValue(_T("CLSID"), lpszCLSID);
        return S_OK;
    }
    return HRESULT_FROM_WIN32(lRes);
}

/////////////////////////////////////////////////////////////////////////////
HRESULT ModuleRegisterTypeLib()
{
    CComBSTR bstrPath;
    ITypeLibPtr pTypeLib;
    HRESULT hr = ModuleLoadTypeLib(&bstrPath, &pTypeLib);
    if (SUCCEEDED(hr)) {
        OLECHAR szDir[_MAX_PATH];
        ocscpy(szDir, bstrPath);
        szDir[AtlGetDirLen(szDir)] = 0;
        hr = ::RegisterTypeLib(pTypeLib, bstrPath, szDir);
    }

    return hr;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT ModuleLoadTypeLib(BSTR* pbstrPath, ITypeLib** ppTypeLib)
{
    *pbstrPath = NULL;
    *ppTypeLib = NULL;

    USES_CONVERSION;

    TCHAR szModule[_MAX_PATH + _MAX_FNAME];
    GetModuleFileName(g_hInstance, szModule, _MAX_PATH);

    LPOLESTR lpszModule = T2OLE(szModule);

    HRESULT hr = LoadTypeLib(lpszModule, ppTypeLib);
    if (SUCCEEDED(hr))
        *pbstrPath = OLE2BSTR(lpszModule);

    return hr;
}

namespace  	// anonymous
{

/////////////////////////////////////////////////////////////////////////////
bool gettok(LPCTSTR *ppin, LPTOKEN ptok)
{
    ptok->type = TK_EMPTY;
    ptok->value = _T("");

    LPCTSTR pin = *ppin;
    int index = 0, digits = 0, i;

    for (;;) {
        switch (*pin) {
        case '\0':
            if (pin > *ppin) {
                ptok->value = tstring(*ppin, pin - *ppin);
                ptok->type = TK_TEXT;
                *ppin = pin;
            }
            return ptok->value.length() ? true : false;
        case '{':
            if (pin > *ppin) {
                ptok->value = tstring(*ppin, pin - *ppin);
                ptok->type = TK_TEXT;
                *ppin = pin;
                return true;
            }
            pin++;
            (*ppin)++;

            // eat characters up to first digit
            while (!_istdigit(*pin) && *pin)
                pin++;

            // count the number of digits
            while (_istdigit(*pin) && *pin) {
                digits++;
                pin++;
            }

            // calculate the index value
            pin -= digits;
            for (i = 0; i < digits; i++) {
                index += (*pin - '0') * pow(10, digits - i - 1);
                pin++;
            }

            // set the token index
            if (pin > *ppin) {
                TCHAR buf[20];
                _itot(index, buf, 10);
                ptok->value = buf;
                ptok->type = TK_INDEX;
            }

            // eat characters up to and including closing brace
            while (*pin) {
                if (*pin == '}') {
                    pin++;
                    break;
                }
                pin++;
            }

            *ppin = pin;
            return ptok->value.length() ? true : false;
        default:
            break;
        }
        pin++;
    }

    return false;	// can't happen
}

}	// anonymous

