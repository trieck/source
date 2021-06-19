/*-----------------------------------------
    Module	:	OBJECT.CPP
    Date	:	07/19/1997
    Purpose	:	Public DLL OLE Component
                for Drawing
------------------------------------------*/

#include "pch.h"
#include <initguid.h>
#include "object.h"

// Count number of objects and number of locks.
ULONG g_cObj = 0;
ULONG g_cLock = 0;
HINSTANCE g_hInst = nullptr;

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason
                    , LPVOID pvReserved)
{
    if (DLL_PROCESS_DETACH == ulReason)
        return TRUE;
    if (DLL_PROCESS_ATTACH != ulReason)
        return TRUE;

    g_hInst = hInstance;
    return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, PPVOID ppv)
{
    if (CLSID_DrawObject != rclsid)
        return ResultFromScode(E_FAIL);

    auto pObj = new CDrawClassFactory();

    auto hr = pObj->QueryInterface(riid, ppv);

    pObj->Release();

    return hr;
}

STDAPI DllCanUnloadNow()
{
    SCODE sc;

    sc = (!g_cObj && !g_cLock) ? S_OK : S_FALSE;
    return ResultFromScode(sc);
}

STDAPI DllRegisterServer()
{
    OLECHAR szTemp[128];
    TCHAR szID[128];
    TCHAR szCLSID[128];
    TCHAR szModule[512];

    StringFromGUID2(CLSID_DrawObject, szTemp, 128);
    lstrcpy(szCLSID, _T("CLSID\\"));

#ifndef UNICODE
    WideCharToMultiByte(CP_ACP, 0, szTemp, -1, szID, 128, NULL, NULL);
#else
    lstrcpy(szID, szTemp);
#endif

    lstrcat(szCLSID, szID);

    // Create ProgID keys
    auto result = SetKeyAndValue(_T("DrawObject1.0"), nullptr
                                 , _T("Drawing Object"));
    result = result && SetKeyAndValue(_T("DrawObject1.0"), _T("CLSID"), szID);

    // Create VersionIndependentProgID keys
    result = result && SetKeyAndValue(_T("DrawObject"), nullptr
                                      , _T("Drawing Object"));
    result = result && SetKeyAndValue(_T("DrawObject"), _T("CurVer")
                                      , _T("DrawObject1.0"));
    result = result && SetKeyAndValue(_T("DrawObject"), _T("CLSID"), szID);

    // Create entries under CLSID
    result = result && SetKeyAndValue(szCLSID, nullptr, _T("Drawing Object"));
    result = result && SetKeyAndValue(szCLSID, _T("ProgID"), _T("DrawObject1.0"));
    result = result && SetKeyAndValue(szCLSID, _T("VersionIndependentProgID")
                                      , _T("DrawObject"));
    result = result && SetKeyAndValue(szCLSID, _T("NotInsertable"), nullptr);

    result = result && SetKeyAndValue(szCLSID, _T("DataFormats\\GetSet\\0"), _T("3,1,32,3"));

    GetModuleFileName(g_hInst, szModule
                      , sizeof(szModule) / sizeof(TCHAR));

    result = result && SetKeyAndValue(szCLSID, _T("InprocServer32"), szModule);
    if (!result) {
        return E_FAIL;
    }

    return NOERROR;
}

STDAPI DllUnregisterServer()
{
    OLECHAR wszTemp[128];
    TCHAR szID[128];
    TCHAR szCLSID[128];
    TCHAR szTemp[256];

    StringFromGUID2(CLSID_DrawObject, wszTemp, 128);
    lstrcpy(szCLSID, _T("CLSID\\"));

#ifndef UNICODE
    WideCharToMultiByte(CP_ACP, 0, wszTemp, -1, szID, 128, NULL, NULL);
#else
    lstrcpy(szID, wszTemp);
#endif

    lstrcat(szCLSID, szID);

    RegDeleteKey(HKEY_CLASSES_ROOT, _T("DrawObject\\CurVer"));
    RegDeleteKey(HKEY_CLASSES_ROOT, _T("DrawObject\\CLSID"));
    RegDeleteKey(HKEY_CLASSES_ROOT, _T("DrawObject"));

    RegDeleteKey(HKEY_CLASSES_ROOT, _T("DrawObject1.0\\CLSID"));
    RegDeleteKey(HKEY_CLASSES_ROOT, _T("DrawObject1.0"));

    wsprintf(szTemp, _T("%s\\%s"), szCLSID, _T("ProgID"));
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    wsprintf(szTemp, _T("%s\\%s"), szCLSID, _T("VersionIndependentProgID"));
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    wsprintf(szTemp, _T("%s\\%s"), szCLSID, _T("NotInsertable"));
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    wsprintf(szTemp, _T("%s\\%s"), szCLSID, _T("DataFormats\\GetSet\\0"));
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    wsprintf(szTemp, _T("%s\\%s"), szCLSID, _T("DataFormats\\GetSet"));
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    wsprintf(szTemp, _T("%s\\%s"), szCLSID, _T("DataFormats"));
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    wsprintf(szTemp, _T("%s\\%s"), szCLSID, _T("InprocServer32"));
    RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

    RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);
    return NOERROR;
}

BOOL SetKeyAndValue(LPCTSTR pszKey, LPCTSTR pszSubkey, LPCTSTR pszValue)
{
    HKEY hKey;
    TCHAR szKey[256];

    lstrcpy(szKey, pszKey);

    if (pszSubkey) {
        lstrcat(szKey, _T("\\"));
        lstrcat(szKey, pszSubkey);
    }

    auto result = RegCreateKeyEx(HKEY_CLASSES_ROOT,
                                 szKey, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &hKey, nullptr);
    if (result != ERROR_SUCCESS) {
        return FALSE;
    }

    if (pszValue) {
        result = RegSetValueEx(hKey, nullptr, 0, REG_SZ, (BYTE*)pszValue, (lstrlen(pszValue) + 1) * sizeof(TCHAR));
        if (result != ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return FALSE;
        }
    }

    result = RegCloseKey(hKey);
    if (result != ERROR_SUCCESS) {
        return FALSE;
    }

    return TRUE;
}


void ObjectDestroyed()
{
    g_cObj--;
}

CDrawClassFactory::CDrawClassFactory() : m_cRef(1)
{
}

STDMETHODIMP CDrawClassFactory::QueryInterface(REFIID riid
                                               , PPVOID ppv)
{
    *ppv = nullptr;

    if (IID_IUnknown == riid || IID_IClassFactory == riid)
        *ppv = this;

    if (*ppv) {
        static_cast<LPUNKNOWN>(*ppv)->AddRef();
        return NOERROR;
    }

    return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CDrawClassFactory::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CDrawClassFactory::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}

STDMETHODIMP CDrawClassFactory::CreateInstance(LPUNKNOWN pUnkOuter
                                               , REFIID riid, PPVOID ppvObj)
{
    *ppvObj = nullptr;

    // Verify that a controlling unknown asks for IUnknown
    if (nullptr != pUnkOuter && IID_IUnknown != riid)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    // Create the object passing function to notify on destruction.
    auto pObj = new CDrawObject(pUnkOuter, ObjectDestroyed);

    auto hr = S_OK;

    if (pObj->Init()) {
        hr = pObj->QueryInterface(riid, ppvObj);
        if (SUCCEEDED(hr)) {
            g_cObj++;
        }
    }

    pObj->Release();

    return hr;
}

STDMETHODIMP CDrawClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
}

CDrawObject::CDrawObject(LPUNKNOWN pUnkOuter, PFNDESTROYED pfnDestroy) : m_cRef(1)
{
    m_fDirty = FALSE;
    m_pRender = nullptr;
    m_pSTM = nullptr;
    m_pImpIPersistStream = nullptr;
    m_pImpIDataObject = nullptr;
    m_pImpIViewObject2 = nullptr;
    m_pIDataAdviseHolder = nullptr;
    m_pUnkOuter = pUnkOuter;
    m_pfnDestroy = pfnDestroy;
    m_clsID = CLSID_DrawObject;
}

STDMETHODIMP CDrawObject::Randomize()
{
    m_pRender->aRect.left = rand() % m_pRender->aBoundsRect.right;
    m_pRender->aRect.top = rand() % m_pRender->aBoundsRect.bottom;
    m_pRender->aRect.right = rand() % m_pRender->aBoundsRect.right;
    m_pRender->aRect.bottom = rand() % m_pRender->aBoundsRect.bottom;

    RenderData();

    // inform advise sink of data change
    if (m_pIDataAdviseHolder)
        m_pIDataAdviseHolder->SendOnDataChange
            (m_pImpIDataObject, DVASPECT_CONTENT, ADVF_NODATA);

    return NOERROR;
}

STDMETHODIMP CDrawObject::SetBounds(LPRECT prcBounds)
{
    if (!prcBounds)
        return ResultFromScode(E_POINTER);

    CopyRect(&m_pRender->aBoundsRect, prcBounds);

    RenderData();

    // inform advise sink of data change
    if (m_pIDataAdviseHolder)
        m_pIDataAdviseHolder->SendOnDataChange
            (m_pImpIDataObject, DVASPECT_CONTENT, ADVF_NODATA);

    return NOERROR;
}

STDMETHODIMP CDrawObject::GetColor(LPCOLORREF pColor)
{
    if (!pColor)
        return E_POINTER;

    *pColor = m_pRender->aColor;

    return NOERROR;
}

STDMETHODIMP CDrawObject::SetColor(COLORREF lColor)
{
    m_pRender->aColor = lColor;

    RenderData();

    // inform advise sink of data change
    if (m_pIDataAdviseHolder)
        m_pIDataAdviseHolder->SendOnDataChange
            (m_pImpIDataObject, DVASPECT_CONTENT, ADVF_NODATA);

    return NOERROR;
}

CDrawObject::~CDrawObject()
{
    // Free allocated memory
    delete m_pRender;
}

BOOL CDrawObject::Init()
{
    m_pRender = new RENDERING;
    if (!m_pRender)
        return FALSE;

    m_pSTM = new STGMEDIUM;
    if (!m_pSTM)
        return FALSE;

    // initialize data members
    m_pRender->aColor = 0L;

    m_pSTM->tymed = TYMED_MFPICT;
    m_pSTM->hGlobal = nullptr;
    m_pSTM->pUnkForRelease = nullptr;

    // Create implemented interface objects
    m_pImpIPersistStream = new CImpIPersistStream(this);
    m_pImpIDataObject = new CImpIDataObject(this);
    m_pImpIViewObject2 = new CImpIViewObject2(this);

    return TRUE;
}

STDMETHODIMP CDrawObject::QueryInterface(REFIID riid, PPVOID ppv)
{
    *ppv = nullptr;

    if (riid == IID_IUnknown || riid == IID_IDrawObject)
        *ppv = this;

    if (riid == IID_IPersistStream)
        *ppv = m_pImpIPersistStream;

    if (riid == IID_IDataObject)
        *ppv = m_pImpIDataObject;

    if (riid == IID_IViewObject || riid == IID_IViewObject2)
        *ppv = m_pImpIViewObject2;

    if (*ppv) {
        static_cast<LPUNKNOWN>(*ppv)->AddRef();
        return NOERROR;
    }

    return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CDrawObject::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CDrawObject::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        if (m_pfnDestroy)
            (*m_pfnDestroy)();

        if (m_pSTM) {
            ReleaseStgMedium(m_pSTM);
            delete m_pSTM;
            m_pSTM = nullptr;
        }

        if (m_pImpIPersistStream != nullptr) {
            m_pImpIPersistStream->Release();
            m_pImpIPersistStream = nullptr;
        }

        if (m_pIDataAdviseHolder != nullptr) {
            m_pIDataAdviseHolder->Release();
            m_pIDataAdviseHolder = nullptr;
        }

        if (m_pImpIDataObject != nullptr) {
            m_pImpIDataObject->Release();
            m_pImpIDataObject = nullptr;
        }

        if (m_pImpIViewObject2 != nullptr) {
            m_pImpIViewObject2->Release();
            m_pImpIViewObject2 = nullptr;
        }

        delete this;

        return 0;
    }

    return m_cRef;
}

HRESULT CDrawObject::RenderData()
{
    if (!RenderMetafile())
        return ResultFromScode(STG_E_MEDIUMFULL);

    return NOERROR;
}

BOOL CDrawObject::RenderMetafile()
{
    HDC hDC;
    HMETAFILE hMF;
    HGLOBAL hMem;
    LPMETAFILEPICT pMF;

    // Create a memory metafile and return its handle.
    hDC = static_cast<HDC>(CreateMetaFile(nullptr));

    hMF = nullptr;

    if (hDC) {
        Draw(hDC);

        hMF = CloseMetaFile(hDC);
    }

    // Allocate the METAFILEPICT structure.
    hMem = GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE
                       , sizeof(METAFILEPICT));

    if (!hMem) {
        DeleteMetaFile(hMF);
        return FALSE;
    }

    pMF = static_cast<LPMETAFILEPICT>(GlobalLock(hMem));

    pMF->hMF = hMF;
    pMF->mm = MM_ANISOTROPIC;
    pMF->xExt = 1024;
    pMF->yExt = 1024;

    GlobalUnlock(hMem);

    ReleaseStgMedium(m_pSTM);

    m_pSTM->hGlobal = hMem;
    m_pSTM->tymed = TYMED_MFPICT;
    m_pSTM->pUnkForRelease = nullptr;

    return TRUE;
}

VOID CDrawObject::Draw(HDC hDC)
{
    HPEN hPen, hPenOld;
    HBRUSH hBrush, hBrushOld;

    hPen = CreatePen(PS_SOLID, 2, GetSysColor(COLOR_3DLIGHT));
    hBrush = CreateSolidBrush(m_pRender->aColor);

    hPenOld = static_cast<HPEN>(SelectObject(hDC, hPen));
    hBrushOld = static_cast<HBRUSH>(SelectObject(hDC, hBrush));

    SetMapMode(hDC, MM_ANISOTROPIC);
    SetWindowExtEx(hDC, 1024, 1024, nullptr);
    SetViewportExtEx(hDC, m_pRender->aBoundsRect.right - m_pRender->aBoundsRect.left,
                     m_pRender->aBoundsRect.bottom - m_pRender->aBoundsRect.top, nullptr);

    Rectangle(hDC,
              m_pRender->aRect.left,
              m_pRender->aRect.top,
              m_pRender->aRect.right,
              m_pRender->aRect.bottom);

    SelectObject(hDC, hBrushOld);

    SelectObject(hDC, hPenOld);

    DeleteObject(hPen);
    DeleteObject(hBrush);
}
