/////////////////////////////////////////////////////////////////////////////
//
// ODBMANAGER.H : Object database manager
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ODBMANAGER_H__
#define __ODBMANAGER_H__

/////////////////////////////////////////////////////////////////////////////
class ODBManager : public IUnknown
{
// Construction / Destruction
public:
	ODBManager();	
	virtual ~ODBManager();
    
// Interface
	static LONG GetObjectCount() { return m_cCount; }

    // IUnknown members
    STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

private:
	IComponentData *m_pData;	// component data
	static LONG m_cCount;		// object count
	LONG m_cRef;				// reference count
};

/////////////////////////////////////////////////////////////////////////////

typedef CComPtr<ODBManager> ODBManagerPtr;

#endif // __ODBMANAGER_H__
