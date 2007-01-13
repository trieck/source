/*------------------------------------------------
	Module	:	IADVSINK.CPP
	Date	: 	07/19/1997
	Purpose	:	IAdviseSink class implementation
-------------------------------------------------*/

#include "capp.h"

CAdviseSink :: CAdviseSink(PAPP pApp)
{
    m_cRef = 0;
    m_pApp = pApp;
}

CAdviseSink :: ~CAdviseSink()
{
}

STDMETHODIMP CAdviseSink :: QueryInterface(REFIID riid, PPVOID ppv)
{
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IAdviseSink==riid)
        *ppv = this;

    if (*ppv)
    {
		((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
	}

    return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CAdviseSink :: AddRef()
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) CAdviseSink :: Release()
{
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
}

STDMETHODIMP_(VOID) CAdviseSink :: OnDataChange(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
{
	HDC		hDC;
	RECT	aRect;

	if (pFE->dwAspect != DVASPECT_CONTENT || pFE->cfFormat != CF_METAFILEPICT)
		return;
	
	hDC = GetDC(m_pApp->m_hWndClient);

	GetClientRect(m_pApp->m_hWndClient, &aRect);
	
	// Redraw object
	OleDraw(m_pApp->m_pIUnknown, 
			DVASPECT_CONTENT, 
			hDC, 
			&aRect);

	ReleaseDC(m_pApp->m_hWndClient, hDC);

	m_pApp->UpdateControls();
}

STDMETHODIMP_(VOID) CAdviseSink :: OnViewChange(DWORD dwAspect
    , LONG lindex)
{
}

STDMETHODIMP_(VOID) CAdviseSink :: OnRename(LPMONIKER pmk)
{
}

STDMETHODIMP_(VOID) CAdviseSink :: OnSave()
{
}

STDMETHODIMP_(VOID) CAdviseSink :: OnClose()
{
}
