/////////////////////////////////////////////////////////////////////////////
//
// ODBMGRFACTORY.H : Object database manager class factory
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ODBMGRFACTORY_H__
#define __ODBMGRFACTORY_H__

/////////////////////////////////////////////////////////////////////////////
class ODBMgrFactory : public IClassFactory {
// Construction / Destruction
private:
    ODBMgrFactory();	// new creation only
public:
    virtual ~ODBMgrFactory();

// Interface
    static ODBMgrFactory *Create();
    static LONG GetLockCount() {
        return m_cLock;
    }

    // IUnknown members
    STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IClassFactory members
    STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID, LPVOID *);
    STDMETHODIMP         LockServer(BOOL);

// Implementation
private:
    LONG m_cRef;
    static LONG m_cLock;	// total lock count
};

/////////////////////////////////////////////////////////////////////////////

typedef CComPtr<ODBMgrFactory> ODBMgrFactoryPtr;

#endif // __ODBMGRFACTORY_H__
