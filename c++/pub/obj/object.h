/*-----------------------------------
    Module	:	OBJECT.H
    Date	:	07/19/1997
    Purpose	:	Implementation of the
                IDrawObject interface
------------------------------------*/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <windows.h>
#include <TCHAR.H>
#include "../olemac.h"
#include "../interfac.h"

// object rendering
typedef struct tagRendering {
    RECT		aRect;
    RECT		aBoundsRect;
    COLORREF	aColor;
} RENDERING, *PRENDERING;

// function for destroying object
typedef void (*PFNDESTROYED)(void);

BOOL SetKeyAndValue(LPCTSTR pszKey, LPCTSTR pszSubkey, LPCTSTR pszValue);

// forward declarations
class CImpIPersistStream;
class CImpIDataObject;
class CImpIViewObject2;

typedef CImpIPersistStream	*PCImpIPersistStream;
typedef CImpIDataObject		*PCImpIDataObject;
typedef CImpIViewObject2	*PCImpIViewObject2;

class CDrawObject : public IDrawObject
{
    friend CImpIPersistStream;
    friend CImpIDataObject;
    friend CImpIViewObject2;

protected:
    DWORD				m_cRef;					// Object reference count
    LPUNKNOWN			m_pUnkOuter;			// Controlling unknown
    PFNDESTROYED		m_pfnDestroy;			// To call on closure
    PCImpIPersistStream	m_pImpIPersistStream;	// Persistant stream pointer
    PCImpIDataObject	m_pImpIDataObject;		// Data Object pointer
    PCImpIViewObject2	m_pImpIViewObject2;		// View Object pointer
    LPDATAADVISEHOLDER	m_pIDataAdviseHolder;	// Data Advise Holder pointer
    CLSID				m_clsID{};
    BOOL				m_fDirty;
    PRENDERING			m_pRender;				// Object rendering pointer
    LPSTGMEDIUM			m_pSTM;
public:
    CDrawObject(LPUNKNOWN, PFNDESTROYED);
    virtual ~CDrawObject();
    BOOL		Init();

protected:
    HRESULT		RenderData();
    BOOL		RenderMetafile();
    VOID		Draw(HDC);

public:
    // IUnknown members
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(DWORD) AddRef();
    STDMETHODIMP_(DWORD) Release();

    // IDrawObject members
    STDMETHODIMP		Randomize();
    STDMETHODIMP		SetBounds(LPRECT);
    STDMETHODIMP		GetColor(LPCOLORREF);
    STDMETHODIMP		SetColor(COLORREF);
};

typedef CDrawObject *PCDrawObject;

class CImpIPersistStream : public IPersistStream
{
protected:
    DWORD			m_cRef = 0;
    PCDrawObject	m_pObj;
public:
    CImpIPersistStream(PCDrawObject);
    virtual ~CImpIPersistStream();

    // IUnknown members
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(DWORD) AddRef();
    STDMETHODIMP_(DWORD) Release();

    // IPersist members
    STDMETHODIMP GetClassID(LPCLSID);

    // IPersistStream members
    STDMETHODIMP IsDirty();
    STDMETHODIMP Load(LPSTREAM);
    STDMETHODIMP Save(LPSTREAM, BOOL);
    STDMETHODIMP GetSizeMax(ULARGE_INTEGER*);
};

class CImpIDataObject : public IDataObject
{
protected:
    DWORD			m_cRef = 0;
    PCDrawObject	m_pObj;			// back pointer to main object
public:
    CImpIDataObject(PCDrawObject);
    virtual ~CImpIDataObject();

    // IUnknown members
    STDMETHODIMP			QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(DWORD)	AddRef();
    STDMETHODIMP_(DWORD)	Release();

    // IDataObject members
    STDMETHODIMP			GetData(LPFORMATETC, LPSTGMEDIUM);
    STDMETHODIMP			GetDataHere(LPFORMATETC, LPSTGMEDIUM);
    STDMETHODIMP			QueryGetData(LPFORMATETC);
    STDMETHODIMP			GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC);
    STDMETHODIMP			SetData(LPFORMATETC, LPSTGMEDIUM, BOOL);
    STDMETHODIMP			EnumFormatEtc(DWORD, LPENUMFORMATETC*);
    STDMETHODIMP			DAdvise(LPFORMATETC, DWORD, LPADVISESINK, LPDWORD);
    STDMETHODIMP			DUnadvise(DWORD);
    STDMETHODIMP			EnumDAdvise(LPENUMSTATDATA*);
};

class CImpIViewObject2 : public IViewObject
{
protected:
    ULONG			m_cRef = 0;
    PCDrawObject	m_pObj;		// back pointer to main object
public:
    CImpIViewObject2(PCDrawObject);
    virtual ~CImpIViewObject2();

    // IUnknown members
    STDMETHODIMP			QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(DWORD)	AddRef();
    STDMETHODIMP_(DWORD)	Release();

    // IViewObject members
    STDMETHODIMP Draw (DWORD, LONG, LPVOID, DVTARGETDEVICE*,
                       HDC, HDC, LPCRECTL, LPCRECTL, BOOL (CALLBACK*)(DWORD),
                       DWORD);
    STDMETHODIMP GetColorSet(DWORD, LONG, LPVOID, DVTARGETDEVICE*,
                             HDC, LPLOGPALETTE*);
    STDMETHODIMP Freeze(DWORD, LONG, LPVOID, LPDWORD);
    STDMETHODIMP Unfreeze(DWORD);
    STDMETHODIMP SetAdvise(DWORD, DWORD, LPADVISESINK);
    STDMETHODIMP GetAdvise(LPDWORD, LPDWORD, LPADVISESINK*);

    // IViewObject2 members
    STDMETHODIMP GetExtent(DWORD, LONG, DVTARGETDEVICE*, LPSIZEL);
};

class CDrawClassFactory : public IClassFactory
{
protected:
    ULONG           m_cRef =0;

public:
    CDrawClassFactory();
    virtual ~CDrawClassFactory() = default;

    // IUnknown members
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IClassFactory members
    STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                        , PPVOID);
    STDMETHODIMP         LockServer(BOOL);
};

typedef CDrawClassFactory *PCDrawClassFactory;

#endif // _OBJECT_H_

