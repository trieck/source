#pragma once

#include "DataObject.h"
#include "DrawObject_i.h"
#include "ComCreator.h"
#include "resource.h"

class ATL_NO_VTABLE CDrawObject :
    public CComObjectRoot,
    public CComCoClass<CDrawObject, &CLSID_DrawObject>,
    public IPersistFile,
    public IPersistStream,
    public IViewObject,
    public IDrawObject
{
public:
    DECLARE_REGISTRY_RESOURCEID(IDR_DRAWOBJECT)
    DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_NOT_AGGREGATABLE(CDrawObject)

BEGIN_COM_MAP(CDrawObject)
        COM_INTERFACE_ENTRY(IViewObject)
        COM_INTERFACE_ENTRY(IPersistFile)
        COM_INTERFACE_ENTRY(IPersistStream)
        COM_INTERFACE_ENTRY(IDrawObject)
        COM_INTERFACE_ENTRY_AGGREGATE(IID_IDataObject, m_pDataObject)
    END_COM_MAP()

    HRESULT FinalConstruct()
    {
        srand(static_cast<int>(GetTickCount64()));

        m_fDirty = m_hasData = FALSE;
        m_rendering = {};

        auto pOuter = GetControllingUnknown();
        auto hr = ComCreator::CreateAgg<DataObject>(pOuter, m_pDataObject);
        if (FAILED(hr)) {
            return hr;
        }

        return S_OK;
    }

    void FinalRelease()
    {
        m_pDataObject.Release();
    }

    // IPersist members
    STDMETHOD(GetClassID)(LPCLSID) override;

    // IPersistFile members
    STDMETHOD(IsDirty)() override;
    STDMETHOD(Load)(LPCOLESTR pszFileName, DWORD dwMode) override;
    STDMETHOD(Save)(LPCOLESTR pszFileName, BOOL fRemember) override;
    STDMETHOD(SaveCompleted)(LPCOLESTR pszFileName) override;
    STDMETHOD(GetCurFile)(LPOLESTR* ppszFileName) override;

    // IPersistStream members
    // STDMETHOD (IsDirty()) override;
    STDMETHOD(Load)(LPSTREAM) override;
    STDMETHOD(Save)(LPSTREAM, BOOL) override;
    STDMETHOD(GetSizeMax)(ULARGE_INTEGER*) override;

    // IViewObject members
    STDMETHOD(Draw)(DWORD, LONG, LPVOID, DVTARGETDEVICE*,
                    HDC, HDC, LPCRECTL, LPCRECTL, BOOL (CALLBACK*)(ULONG_PTR),
                    DWORD_PTR) override;
    STDMETHOD(GetColorSet)(DWORD, LONG, LPVOID, DVTARGETDEVICE*,
                           HDC, LPLOGPALETTE*) override;
    STDMETHOD(Freeze)(DWORD, LONG, LPVOID, LPDWORD) override;
    STDMETHOD(Unfreeze)(DWORD) override;
    STDMETHOD(SetAdvise)(DWORD, DWORD, LPADVISESINK) override;
    STDMETHOD(GetAdvise)(LPDWORD, LPDWORD, LPADVISESINK*) override;

    // IDrawObject methods
    STDMETHOD(GetColor)(LPCOLORREF pColor) override;
    STDMETHOD(HasData)() override;
    STDMETHOD(Randomize)() override;
    STDMETHOD(SetBounds)(LPRECT bounds) override;
    STDMETHOD(SetColor)(COLORREF color) override;
private:
    HRESULT SetData();
    void Draw(HDC hDC);

    // object rendering
    typedef struct tagRendering
    {
        CRect rc{};
        CRect rcBounds{};
        COLORREF color = 0;
        UINT type = 0;
    } RENDERING, *PRENDERING;

    CComPtr<IUnknown> m_pDataObject;
    RENDERING m_rendering;
    BOOL m_fDirty = FALSE;
    BOOL m_hasData = FALSE;
};

OBJECT_ENTRY_AUTO(__uuidof(DrawObject), CDrawObject)
