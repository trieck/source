/////////////////////////////////////////////////////////////////////////////
//
// ODBMGRDATA.H : Object database manager data
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ODBMGRDATA_H__
#define __ODBMGRDATA_H__

/////////////////////////////////////////////////////////////////////////////
class ODBMgrData : public IComponentData {
// Construction / Destruction
public:
    ODBMgrData(LPUNKNOWN pUnknown);
    virtual ~ODBMgrData();

// Interface

    // IUnknown members
    STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IComponentData members
    STDMETHODIMP Initialize(LPUNKNOWN pUnknown);
    STDMETHODIMP CreateComponent(LPCOMPONENT *ppComponent);
    STDMETHODIMP Notify(LPDATAOBJECT lpDataObject, MMC_NOTIFY_TYPE event,
                        LPARAM arg, LPARAM param);
    STDMETHODIMP Destroy(void);
    STDMETHODIMP QueryDataObject(MMC_COOKIE cookie, DATA_OBJECT_TYPES type,
                                 LPDATAOBJECT *ppDataObject);
    STDMETHODIMP GetDisplayInfo(SCOPEDATAITEM *pScopeDataItem);
    STDMETHODIMP CompareObjects(LPDATAOBJECT lpDataObjectA,
                                LPDATAOBJECT lpDataObjectB);

private:
    LONG m_cRef;								// reference count
    LPUNKNOWN m_pUnknown;						// outer unknown
    IConsoleNameSpace *m_pConsoleNameSpace;		// console namespace
    IConsole *m_pConsole;						// console
};

/////////////////////////////////////////////////////////////////////////////

typedef CComPtr<ODBMgrData> ODBMgrDataPtr;

#endif // __ODBMGRDATA_H__
