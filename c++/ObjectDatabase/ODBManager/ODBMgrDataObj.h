/////////////////////////////////////////////////////////////////////////////
//
// ODBMGRDATAOBJ.H : Object database manager data object
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ODBMGRDATAOBJ_H__
#define __ODBMGRDATAOBJ_H__

/////////////////////////////////////////////////////////////////////////////
class ODBMgrDataObj : public IDataObject {
// Construction / Destruction
public:
    ODBMgrDataObj(LPUNKNOWN pUnknown);
    virtual ~ODBMgrDataObj();

// Interface

    // IUnknown members
    STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IDataObject members
    STDMETHODIMP GetData(LPFORMATETC, LPSTGMEDIUM);
    STDMETHODIMP GetDataHere(LPFORMATETC, LPSTGMEDIUM);
    STDMETHODIMP QueryGetData(LPFORMATETC);
    STDMETHODIMP GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC);
    STDMETHODIMP SetData(LPFORMATETC, LPSTGMEDIUM, BOOL);
    STDMETHODIMP EnumFormatEtc(DWORD, LPENUMFORMATETC*);
    STDMETHODIMP DAdvise(LPFORMATETC, DWORD, LPADVISESINK, LPDWORD);
    STDMETHODIMP DUnadvise(DWORD);
    STDMETHODIMP EnumDAdvise(LPENUMSTATDATA*);

private:
    LONG m_cRef;			// reference count
    LPUNKNOWN m_pUnknown;	// outer unknown
};

/////////////////////////////////////////////////////////////////////////////

typedef CComPtr<ODBMgrDataObj> ODBMgrDataObjPtr;

#endif // __ODBMGRDATAOBJ_H__
