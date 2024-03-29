/*-----------------------------------------
    Module  :   OBJECT.CPP
    Date    :   07/19/1997
    Purpose :   Public DLL OLE Component
                for Drawing
------------------------------------------*/

#include "pch.h"
#include "DrawObject.h"
#include "DrawObjectModule.h"

CDrawObjectModule _Module;

static constexpr LPCTSTR STREAM = _T("MyStream");

extern "C" BOOL WINAPI DllMain(HINSTANCE /*hInstance*/, DWORD dwReason, LPVOID lpReserved)
{
    return _Module.DllMain(dwReason, lpReserved);
}

STDAPI DllCanUnloadNow()
{
    return _Module.DllCanUnloadNow();
}

STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
    return _Module.DllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllRegisterServer()
{
    return _Module.DllRegisterServer();
}

STDAPI DllUnregisterServer()
{
    return _Module.DllUnregisterServer();
}

STDAPI DllInstall(BOOL bInstall, _In_opt_ LPCWSTR pszCmdLine)
{
    static constexpr TCHAR szUserSwitch[] = _T("user");

    HRESULT hr;
    if (pszCmdLine != nullptr) {
        if (_tcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0) {
            AtlSetPerUserRegistration(true);
        }
    }

    if (bInstall) {
        hr = DllRegisterServer();
        if (FAILED(hr)) {
            DllUnregisterServer();
        }
    } else {
        hr = DllUnregisterServer();
    }

    return hr;
}

inline HRESULT CDrawObject::GetClassID(LPCLSID pClsID)
{
    if (!pClsID) {
        return E_POINTER;
    }

    *pClsID = CLSID_DrawObject;

    return S_OK;
}

inline HRESULT CDrawObject::IsDirty()
{
    return m_fDirty ? S_OK : S_FALSE;
}

HRESULT CDrawObject::SaveCompleted(LPCOLESTR pszFileName)
{
    return E_NOTIMPL;
}

HRESULT CDrawObject::GetCurFile(LPOLESTR* ppszFileName)
{
    return E_NOTIMPL;
}

HRESULT CDrawObject::HandsOffStorage()
{
    return S_OK;
}

HRESULT CDrawObject::InitNew(LPSTORAGE pStorage)
{
    if (!pStorage) {
        return E_POINTER;
    }

    return S_OK;
}

HRESULT CDrawObject::Load(LPSTORAGE pStorage)
{
    if (!pStorage) {
        return E_POINTER;
    }
    
    CComPtr<IStream> pStream;
    auto hr = pStorage->OpenStream(STREAM, nullptr, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pStream);
    if (FAILED(hr)) {
        return hr;
    }

    hr = Load(pStream);

    return hr;
}

HRESULT CDrawObject::Save(LPSTORAGE pStorage, BOOL fSameAsLoad)
{
    if (!pStorage) {
        return E_POINTER;
    }

    // Mark this as one of our class
    auto hr = WriteClassStg(pStorage, CLSID_DrawObject);
    if (FAILED(hr)) {
        return hr;
    }

    CComBSTR bstrType(CLSID_DrawObject);
    hr = WriteFmtUserTypeStg(pStorage, CF_ENHMETAFILE, bstrType);
    if (FAILED(hr)) {
        return hr;
    }

    CComPtr<IStream> pStream;
    hr = pStorage->CreateStream(STREAM, STGM_CREATE | STGM_SIMPLE | STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &pStream);
    if (FAILED(hr)) {
        return hr;
    }

    hr = Save(pStream, TRUE);

    return hr;
}

HRESULT CDrawObject::SaveCompleted(LPSTORAGE pStorage)
{
    if (!pStorage) {
        return E_POINTER;
    }

    return S_OK;
}

HRESULT CDrawObject::Save(LPCOLESTR pszFileName, BOOL fRemember)
{
    if (!pszFileName) {
        return E_POINTER;
    }

    CComPtr<IStorage> pStorage;
    auto hr = StgCreateDocfile(pszFileName, STGM_WRITE | STGM_CREATE | STGM_SHARE_EXCLUSIVE, 0,
                               &pStorage);
    if (FAILED(hr)) {
        return hr;
    }

    hr = Save(pStorage, fRemember);

    return hr;
}

HRESULT CDrawObject::Save(LPSTREAM pStream, BOOL fClearDirty)
{
    if (!pStream) {
        return E_POINTER;
    }

    ULONG written;
    auto hr = pStream->Write(&m_rendering, sizeof(RENDERING), &written);
    if (FAILED(hr)) {
        return hr;
    }

    if (written != sizeof(RENDERING)) {
        return STG_E_WRITEFAULT;
    }

    m_fDirty = !fClearDirty;

    return S_OK;
}

HRESULT CDrawObject::GetSizeMax(ULARGE_INTEGER*)
{
    return E_NOTIMPL;
}

HRESULT CDrawObject::HasData()
{
    return m_hasData ? S_OK : S_FALSE;
}

HRESULT CDrawObject::Load(LPCOLESTR pszFileName, DWORD dwMode)
{
    if (!pszFileName) {
        return E_POINTER;
    }

    auto hr = StgIsStorageFile(pszFileName);
    if (FAILED(hr)) {
        return hr;
    }

    dwMode |= STGM_SHARE_EXCLUSIVE;

    CComPtr<IStorage> pStorage;
    hr = StgOpenStorage(pszFileName, nullptr, dwMode, nullptr, 0, &pStorage);
    if (FAILED(hr)) {
        return hr;
    }

    hr = Load(pStorage);

    return hr;
}

HRESULT CDrawObject::Load(LPSTREAM pStream)
{
    if (!pStream) {
        return E_POINTER;
    }

    CComQIPtr<IDataObject> pDataObject(GetUnknown());
    if (pDataObject == nullptr) {
        return E_FAIL;
    }

    ULONG cbRead;
    auto hr = pStream->Read(&m_rendering, sizeof(RENDERING), &cbRead);
    if (FAILED(hr) || cbRead != sizeof(RENDERING)) {
        return hr;
    }

    hr = SetData();
    if (FAILED(hr)) {
        return hr;
    }

    return S_OK;
}

HRESULT CDrawObject::Randomize()
{
    if (m_rendering.rcBounds.IsRectEmpty()) {
        return E_UNEXPECTED;
    }

    auto width = m_rendering.rcBounds.right - m_rendering.rcBounds.left;
    auto height = m_rendering.rcBounds.bottom - m_rendering.rcBounds.top;

    m_rendering.rc.left = rand() % width / 2;
    m_rendering.rc.top = rand() % height / 2;

    m_rendering.rc.right = m_rendering.rc.left + width / 2;
    m_rendering.rc.bottom = m_rendering.rc.top + height / 2;

    m_rendering.type = rand() % 3;

    auto hr = SetData();

    return hr;
}

HRESULT CDrawObject::SetBounds(LPRECT bounds)
{
    if (!bounds) {
        return E_POINTER;
    }

    m_rendering.rcBounds = *bounds;

    (void)SetData();

    return S_OK;
}

HRESULT CDrawObject::SetColor(COLORREF color)
{
    m_rendering.color = color;

    (void)SetData();

    return S_OK;
}

HRESULT CDrawObject::GetColor(LPCOLORREF pColor)
{
    if (!pColor) {
        return E_POINTER;
    }

    *pColor = m_rendering.color;

    return S_OK;
}

HRESULT CDrawObject::SetData()
{
    if (m_rendering.rcBounds.IsRectEmpty() || m_rendering.rc.IsRectEmpty()) {
        return E_UNEXPECTED;
    }

    auto rcHiMetric(m_rendering.rc);
    PixelToHimetric(rcHiMetric);

    auto hDC = CreateEnhMetaFile(nullptr, nullptr, &rcHiMetric, nullptr);
    if (hDC == nullptr) {
        return E_FAIL;
    }

    Draw(hDC);

    auto hMetafile = CloseEnhMetaFile(hDC);
    if (hMetafile == nullptr) {
        return E_FAIL;
    }

    CComQIPtr<IDataObject> pDataObject(GetUnknown());
    if (pDataObject == nullptr) {
        return E_NOINTERFACE;
    }

    FORMATETC fe;
    fe.cfFormat = CF_ENHMETAFILE;
    fe.dwAspect = DVASPECT_CONTENT;
    fe.ptd = nullptr;
    fe.tymed = TYMED_ENHMF;
    fe.lindex = -1;

    STGMEDIUM stg{};
    stg.tymed = TYMED_ENHMF;
    stg.hEnhMetaFile = hMetafile;

    auto hr = pDataObject->SetData(&fe, &stg, TRUE);

    m_hasData = SUCCEEDED(hr);

    return hr;
}

void CDrawObject::Draw(HDC hDC)
{
    auto hPen = CreatePen(PS_SOLID, 2, GetSysColor(COLOR_3DLIGHT));
    auto hBrush = CreateSolidBrush(m_rendering.color);

    auto hPenOld = static_cast<HPEN>(SelectObject(hDC, hPen));
    auto hBrushOld = static_cast<HBRUSH>(SelectObject(hDC, hBrush));

    if (m_rendering.type == DRAWOBJECTTYPE_RECTANGLE) {
        // rectangle
        Rectangle(hDC, m_rendering.rc.left, m_rendering.rc.top, m_rendering.rc.right, m_rendering.rc.bottom);
    } else if (m_rendering.type == DRAWOBJECTTYPE_ELLIPSE) {
        // ellipse
        Ellipse(hDC, m_rendering.rc.left, m_rendering.rc.top, m_rendering.rc.right, m_rendering.rc.bottom);
    } else if (m_rendering.type == DRAWOBJECTTYPE_TRIANGLE) {
        // triangle
        POINT pts[] = {
            { m_rendering.rc.left + ((m_rendering.rc.right - m_rendering.rc.left) / 2), m_rendering.rc.top },
            { m_rendering.rc.left, m_rendering.rc.bottom },
            { m_rendering.rc.right, m_rendering.rc.bottom },
            { m_rendering.rc.left + ((m_rendering.rc.right - m_rendering.rc.left) / 2), m_rendering.rc.top }
        };

        Polygon(hDC, pts, sizeof(pts) / sizeof(POINT));
    } else {
        ATLASSERT(0); // invalid
    }

    SelectObject(hDC, hBrushOld);
    SelectObject(hDC, hPenOld);

    DeleteObject(hPen);
    DeleteObject(hBrush);
}

HRESULT CDrawObject::Draw(DWORD dwAspect, LONG /*lindex*/, LPVOID /*pvAspect*/, DVTARGETDEVICE* /*ptd*/,
                          HDC /*hicTargetDev*/, HDC hDC, LPCRECTL prcBounds, LPCRECTL /*prcWBounds*/,
                          BOOL (CALLBACK* /*pfnContinue*/)(ULONG_PTR), DWORD_PTR /*dwContinue*/)
{
    if (!(hDC && prcBounds)) {
        return E_POINTER;
    }

    if (dwAspect != DVASPECT_CONTENT) {
        return E_FAIL;
    }

    CComQIPtr<IDataObject> pDataObject(GetUnknown());
    if (pDataObject == nullptr) {
        return E_NOINTERFACE;
    }

    FORMATETC fe;
    fe.cfFormat = CF_ENHMETAFILE;
    fe.dwAspect = dwAspect;
    fe.ptd = nullptr;
    fe.tymed = TYMED_ENHMF;
    fe.lindex = -1;

    AutoStgMedium stg{};
    auto hr = pDataObject->GetData(&fe, &stg);
    if (FAILED(hr)) {
        return hr;
    }

    auto result = PlayEnhMetaFile(hDC, stg.hEnhMetaFile, &m_rendering.rc);

    hr = result ? S_OK : HRESULT_FROM_WIN32(GetLastError());

    return hr;
}

HRESULT CDrawObject::GetColorSet(DWORD, LONG, LPVOID, DVTARGETDEVICE*, HDC, LPLOGPALETTE*)
{
    return E_NOTIMPL;
}

HRESULT CDrawObject::Freeze(DWORD, LONG, LPVOID, LPDWORD)
{
    return E_NOTIMPL;
}

HRESULT CDrawObject::Unfreeze(DWORD)
{
    return E_NOTIMPL;
}

HRESULT CDrawObject::SetAdvise(DWORD aspects, DWORD advf, LPADVISESINK pSink)
{
    return E_NOTIMPL;
}

HRESULT CDrawObject::GetAdvise(LPDWORD, LPDWORD, LPADVISESINK*)
{
    return E_NOTIMPL;
}
