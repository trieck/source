/*-----------------------------------------
	Module	:	OBJECT.CPP
	Date	:	07/19/1997
	Purpose	:	Public DLL OLE Component
				for Drawing
------------------------------------------*/

#include <windows.h>
#include <initguid.h>
#include "object.h"

// Count number of objects and number of locks.
ULONG       g_cObj	= 0;
ULONG       g_cLock	= 0;
HINSTANCE	g_hInst = NULL;

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason
                    , LPVOID pvReserved)
{
    if (DLL_PROCESS_DETACH == ulReason)
        return TRUE;
    else if (DLL_PROCESS_ATTACH != ulReason)
        return TRUE;

    g_hInst = hInstance;
    return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, PPVOID ppv)
{
    HRESULT             hr;
    CDrawClassFactory *pObj;

    if (CLSID_DrawObject != rclsid)
        return ResultFromScode(E_FAIL);

    pObj = new CDrawClassFactory();

    if (!pObj)
        return ResultFromScode(E_OUTOFMEMORY);

    hr = pObj->QueryInterface(riid, ppv);

    if (FAILED(hr))
        delete pObj;

    return (hr);
}

STDAPI DllCanUnloadNow()
{
    SCODE   sc;

    sc = (!g_cObj && !g_cLock) ? S_OK : S_FALSE;
    return ResultFromScode(sc);
}

STDAPI DllRegisterServer()
{
    OLECHAR     szTemp[128];
    TCHAR		szID[128];
    TCHAR       szCLSID[128];
    TCHAR       szModule[512];

    StringFromGUID2(CLSID_DrawObject, szTemp, 128);
    lstrcpy(szCLSID, _T("CLSID\\"));

#ifndef UNICODE
    WideCharToMultiByte(CP_ACP, 0, szTemp, -1, szID, 128, NULL, NULL);
#else
    lstrcpy(szID, szTemp);
#endif

    lstrcat(szCLSID, szID);

    // Create ProgID keys
    SetKeyAndValue(_T("DrawObject1.0"), NULL
                   , _T("Drawing Object"));
    SetKeyAndValue(_T("DrawObject1.0"), _T("CLSID"), szID);

    // Create VersionIndependentProgID keys
    SetKeyAndValue(_T("DrawObject"), NULL
                   , _T("Drawing Object"));
    SetKeyAndValue(_T("DrawObject"), _T("CurVer")
                   , _T("DrawObject1.0"));
    SetKeyAndValue(_T("DrawObject"), _T("CLSID"), szID);

    // Create entries under CLSID
    SetKeyAndValue(szCLSID, NULL, _T("Drawing Object"));
    SetKeyAndValue(szCLSID, _T("ProgID"), _T("DrawObject1.0"));
    SetKeyAndValue(szCLSID, _T("VersionIndependentProgID")
                   , _T("DrawObject"));
    SetKeyAndValue(szCLSID, _T("NotInsertable"), NULL);

    SetKeyAndValue(szCLSID, _T("DataFormats\\GetSet\\0"), _T("3,1,32,3"));

    GetModuleFileName(g_hInst, szModule
                      , sizeof(szModule)/sizeof(TCHAR));

    SetKeyAndValue(szCLSID, _T("InprocServer32"), szModule);

    return NOERROR;
}

STDAPI DllUnregisterServer()
{
    OLECHAR     wszTemp[128];
    TCHAR		szID[128];
    TCHAR       szCLSID[128];
    TCHAR       szTemp[256];

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

BOOL SetKeyAndValue(LPTSTR pszKey, LPTSTR pszSubkey
                    , LPTSTR pszValue)
{
    HKEY        hKey;
    TCHAR       szKey[256];

    lstrcpy(szKey, pszKey);

    if (pszSubkey) {
        lstrcat(szKey, _T("\\"));
        lstrcat(szKey, pszSubkey);
    }

    if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CLASSES_ROOT
                                        , szKey, 0, NULL, REG_OPTION_NON_VOLATILE
                                        , KEY_ALL_ACCESS, NULL, &hKey, NULL))
        return FALSE;

    if (pszValue) {
        RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE *)pszValue
                      , (lstrlen(pszValue)+1) * sizeof(TCHAR));
    }

    RegCloseKey(hKey);
    return TRUE;
}


void ObjectDestroyed()
{
    g_cObj--;
}

CDrawClassFactory :: CDrawClassFactory()
{
    m_cRef=0L;

}

CDrawClassFactory :: ~CDrawClassFactory()
{
}

STDMETHODIMP CDrawClassFactory :: QueryInterface(REFIID riid
        , PPVOID ppv)
{
    *ppv=NULL;

    if (IID_IUnknown == riid || IID_IClassFactory == riid)
        *ppv=this;

    if (*ppv) {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
    }

    return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CDrawClassFactory :: AddRef()
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) CDrawClassFactory :: Release()
{
    if (0L != --m_cRef)
        return m_cRef;

    delete this;
    return 0L;
}

STDMETHODIMP CDrawClassFactory :: CreateInstance(LPUNKNOWN pUnkOuter
        , REFIID riid, PPVOID ppvObj)
{
    PCDrawObject	pObj;
    HRESULT         hr;

    *ppvObj = NULL;
    hr = ResultFromScode(E_OUTOFMEMORY);

    // Verify that a controlling unknown asks for IUnknown
    if (NULL != pUnkOuter && IID_IUnknown != riid)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    // Create the object passing function to notify on destruction.
    pObj = new CDrawObject(pUnkOuter, ObjectDestroyed);

    if (!pObj)
        return hr;

    if (pObj->Init())
        hr = pObj->QueryInterface(riid, ppvObj);

    // Kill the object if initial creation or Init failed.
    if (FAILED(hr))
        delete pObj;
    else
        g_cObj++;

    return hr;
}

STDMETHODIMP CDrawClassFactory :: LockServer(BOOL fLock)
{
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
}

CDrawObject :: CDrawObject(LPUNKNOWN pUnkOuter, PFNDESTROYED pfnDestroy)
{
    m_cRef					= 0;
    m_fDirty				= FALSE;
    m_pRender				= NULL;
    m_pSTM					= NULL;
    m_pImpIPersistStream	= NULL;
    m_pImpIDataObject		= NULL;
    m_pImpIViewObject2		= NULL;
    m_pIDataAdviseHolder	= NULL;
    m_pUnkOuter				= pUnkOuter;
    m_pfnDestroy			= pfnDestroy;
    m_clsID					= CLSID_DrawObject;
}

STDMETHODIMP CDrawObject :: Randomize()
{
    m_pRender->aRect.left	= rand() % m_pRender->aBoundsRect.right;
    m_pRender->aRect.top	= rand() % m_pRender->aBoundsRect.bottom;
    m_pRender->aRect.right	= rand() % m_pRender->aBoundsRect.right;
    m_pRender->aRect.bottom	= rand() % m_pRender->aBoundsRect.bottom;

    RenderData();

    // inform advise sink of data change
    if (m_pIDataAdviseHolder)
        m_pIDataAdviseHolder->SendOnDataChange
        (m_pImpIDataObject, DVASPECT_CONTENT, ADVF_NODATA);

    return NOERROR;
}

STDMETHODIMP CDrawObject :: SetBounds(LPRECT prcBounds)
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

STDMETHODIMP CDrawObject :: GetColor(LPCOLORREF pColor)
{
    if (!pColor)
        return E_POINTER;

    *pColor = m_pRender->aColor;

    return NOERROR;
}

STDMETHODIMP CDrawObject :: SetColor(COLORREF lColor)
{
    m_pRender->aColor = lColor;

    RenderData();

    // inform advise sink of data change
    if (m_pIDataAdviseHolder)
        m_pIDataAdviseHolder->SendOnDataChange
        (m_pImpIDataObject, DVASPECT_CONTENT, ADVF_NODATA);

    return NOERROR;
}

CDrawObject :: ~CDrawObject()
{
    // Free allocated memory
    if (m_pRender) delete m_pRender;

    if (m_pSTM) {
        ReleaseStgMedium(m_pSTM);
        delete m_pSTM;
    }

    // Release implemented interface
    // and object pointers
    DeleteInterfaceImp(m_pImpIPersistStream);
    DeleteInterfaceImp(m_pImpIDataObject);
    DeleteInterfaceImp(m_pImpIViewObject2)
    ReleaseInterface(m_pIDataAdviseHolder);
}

BOOL CDrawObject :: Init()
{
    m_pRender = new RENDERING;
    if (!m_pRender)
        return FALSE;

    m_pSTM = new STGMEDIUM;
    if (!m_pSTM)
        return FALSE;

    // initialize data members
    m_pRender->aColor		= 0L;

    m_pSTM->tymed			= TYMED_MFPICT;
    m_pSTM->hGlobal			= 0;
    m_pSTM->pUnkForRelease	= NULL;

    // Create implemented interface objects
    m_pImpIPersistStream = new CImpIPersistStream(this);
    if (!m_pImpIPersistStream)
        return FALSE;

    m_pImpIDataObject = new CImpIDataObject(this);
    if (!m_pImpIDataObject)
        return FALSE;

    m_pImpIViewObject2 = new CImpIViewObject2(this);
    if (!m_pImpIViewObject2)
        return FALSE;

    return TRUE;
}

STDMETHODIMP CDrawObject :: QueryInterface(REFIID riid, PPVOID ppv)
{
    *ppv=NULL;

    if (riid == IID_IUnknown || riid == IID_IDrawObject)
        *ppv=this;

    if (riid == IID_IPersistStream)
        *ppv = m_pImpIPersistStream;

    if (riid == IID_IDataObject)
        *ppv = m_pImpIDataObject;

    if (riid == IID_IViewObject || riid == IID_IViewObject2)
        *ppv = m_pImpIViewObject2;

    if (*ppv) {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
    }
    return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CDrawObject :: AddRef()
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) CDrawObject :: Release()
{
    if (0L!=--m_cRef)
        return m_cRef;

    if (m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0;
}

HRESULT CDrawObject :: RenderData()
{
    if (!RenderMetafile())
        return ResultFromScode(STG_E_MEDIUMFULL);

    return NOERROR;
}

BOOL CDrawObject :: RenderMetafile()
{
    HDC				hDC;
    HMETAFILE		hMF;
    HGLOBAL			hMem;
    LPMETAFILEPICT	pMF;

    // Create a memory metafile and return its handle.
    hDC = (HDC)CreateMetaFile(NULL);

    hMF = NULL;

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

    pMF = (LPMETAFILEPICT)GlobalLock(hMem);

    pMF->hMF	= hMF;
    pMF->mm		= MM_ANISOTROPIC;
    pMF->xExt	= 1024;
    pMF->yExt	= 1024;

    GlobalUnlock(hMem);

    ReleaseStgMedium(m_pSTM);

    m_pSTM->hGlobal				= hMem;
    m_pSTM->tymed				= TYMED_MFPICT;
    m_pSTM->pUnkForRelease		= NULL;

    return TRUE;
}

VOID CDrawObject :: Draw (HDC hDC)
{
    HPEN	hPen, hPenOld;
    HBRUSH	hBrush, hBrushOld;

    hPen		= CreatePen(PS_SOLID, 2, GetSysColor(COLOR_3DLIGHT));
    hBrush		= CreateSolidBrush(m_pRender->aColor);

    hPenOld		= (HPEN)SelectObject(hDC, hPen);
    hBrushOld	= (HBRUSH)SelectObject(hDC, hBrush);

    SetMapMode(hDC, MM_ANISOTROPIC);
    SetWindowExtEx(hDC, 1024, 1024, NULL);
    SetViewportExtEx(hDC, m_pRender->aBoundsRect.right - m_pRender->aBoundsRect.left,
                     m_pRender->aBoundsRect.bottom - m_pRender->aBoundsRect.top, NULL);

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