/////////////////////////////////////////////////////////////////////////////
//
// ODBMGRCOMPONENT.H : Object database manager component
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ODBMGRCOMPONENT_H__
#define __ODBMGRCOMPONENT_H__

/////////////////////////////////////////////////////////////////////////////
class ODBMgrComponent : public IComponent
{
// Construction / Destruction
public:
    ODBMgrComponent(LPUNKNOWN pUnknown);
    virtual ~ODBMgrComponent();

// Interface

    // IUnknown members
    STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IComponent members
    STDMETHODIMP Initialize(LPCONSOLE lpConsole);
    STDMETHODIMP Notify(LPDATAOBJECT lpDataObject, MMC_NOTIFY_TYPE event,
                        LPARAM arg, LPARAM param);
    STDMETHODIMP Destroy(MMC_COOKIE cookie);
    STDMETHODIMP QueryDataObject(MMC_COOKIE cookie, DATA_OBJECT_TYPES type,
                                 LPDATAOBJECT *ppDataObject);
    STDMETHODIMP GetResultViewType(MMC_COOKIE cookie, LPOLESTR *ppViewType,
                                   long *pViewOptions);
    STDMETHODIMP GetDisplayInfo(RESULTDATAITEM *pResultDataItem);
    STDMETHODIMP CompareObjects(LPDATAOBJECT lpDataObjectA,
                                LPDATAOBJECT lpDataObjectB);

private:
    LONG m_cRef;			// reference count
    LPUNKNOWN m_pUnknown;	// outer unknown
};

/////////////////////////////////////////////////////////////////////////////

typedef CComPtr<ODBMgrComponent> ODBMgrComponentPtr;

#endif // __ODBMGRCOMPONENT_H__
