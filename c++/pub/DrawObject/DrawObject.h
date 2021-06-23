#pragma once

#include "DataObject.h"
#include "DrawObject_i.h"
#include "ComCreator.h"
#include "resource.h"

class ATL_NO_VTABLE CDrawObject :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CDrawObject, &CLSID_DrawObject>,
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
            COM_INTERFACE_ENTRY(IPersistStream)
            COM_INTERFACE_ENTRY(IDrawObject)
            COM_INTERFACE_ENTRY_AGGREGATE(IID_IDataObject, m_pDataObject)
    END_COM_MAP()

    HRESULT FinalConstruct()
    {
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
    STDMETHODIMP GetClassID(LPCLSID) override;

    // IPersistStream members
    STDMETHODIMP IsDirty() override;
    STDMETHODIMP Load(LPSTREAM) override;
    STDMETHODIMP Save(LPSTREAM, BOOL) override;
    STDMETHODIMP GetSizeMax(ULARGE_INTEGER*) override;

    // IViewObject members
    STDMETHODIMP Draw(DWORD, LONG, LPVOID, DVTARGETDEVICE*,
                      HDC, HDC, LPCRECTL, LPCRECTL, BOOL (CALLBACK*)(DWORD),
                      DWORD) override;
    STDMETHODIMP GetColorSet(DWORD, LONG, LPVOID, DVTARGETDEVICE*,
                             HDC, LPLOGPALETTE*) override;
    STDMETHODIMP Freeze(DWORD, LONG, LPVOID, LPDWORD) override;
    STDMETHODIMP Unfreeze(DWORD) override;
    STDMETHODIMP SetAdvise(DWORD, DWORD, LPADVISESINK) override;
    STDMETHODIMP GetAdvise(LPDWORD, LPDWORD, LPADVISESINK*) override;

    // IDrawObject methods
    STDMETHOD(Load)(BSTR filename) override;
    STDMETHOD(Randomize)() override;
    STDMETHOD(SetBounds)(LPRECT bounds) override;
    STDMETHOD(SetColor)(COLORREF color) override;
    STDMETHOD(GetColor)(LPCOLORREF pColor) override;
private:
    HRESULT SetData();
    void Draw(HDC hDC);

    // object rendering
    typedef struct tagRendering
    {
        RECT rc{};
        RECT rcBounds{};
        COLORREF color = 0;
    } RENDERING, *PRENDERING;

    CComPtr<IUnknown> m_pDataObject;
    RENDERING m_rendering;
    BOOL m_fDirty = FALSE;
};

OBJECT_ENTRY_AUTO(__uuidof(DrawObject), CDrawObject)
