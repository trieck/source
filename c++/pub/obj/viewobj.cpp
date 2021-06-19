/*-----------------------------------------
    Module	:	VIEWOBJ.CPP
    Date	:	08/02/1997
    Purpose	:	IViewObject implementation
------------------------------------------*/

#include "pch.h"
#include "object.h"

CImpIViewObject2::CImpIViewObject2(PCDrawObject pObj) : m_cRef(1), m_pObj(pObj)
{
}

DWORD CImpIViewObject2::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

DWORD CImpIViewObject2::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}

STDMETHODIMP CImpIViewObject2::QueryInterface(REFIID riid, PPVOID ppv)
{
    return m_pObj->QueryInterface(riid, ppv);
}

STDMETHODIMP CImpIViewObject2::Draw(DWORD dwAspect, LONG lindex, LPVOID pvAspect,
                                    DVTARGETDEVICE* ptd, HDC hicTargetDev, HDC hDC,
                                    LPCRECTL prcBounds, LPCRECTL prcWBounds,
                                    BOOL (CALLBACK *pfnContinue)(DWORD), DWORD dwContinue)
{
    INT nSavedDC;

    if (!hDC || !prcBounds)
        return ResultFromScode(E_POINTER);

    nSavedDC = SaveDC(hDC);

    switch (dwAspect) {
    case DVASPECT_CONTENT:
        LPMETAFILEPICT pMF;
        BOOL fRtn;

        pMF = static_cast<LPMETAFILEPICT>(GlobalLock(m_pObj->m_pSTM->hGlobal));
        if (!pMF)
            break;

        fRtn = PlayMetaFile(hDC, pMF->hMF);

        GlobalUnlock(m_pObj->m_pSTM->hGlobal);
        break;
    default:
        return ResultFromScode(E_FAIL);
    }

    RestoreDC(hDC, nSavedDC);

    return NOERROR;
}

STDMETHODIMP CImpIViewObject2::GetColorSet(DWORD dwAspect, LONG lindex, LPVOID pvAspect,
                                           DVTARGETDEVICE* ptd, HDC hicTargetDev,
                                           LPLOGPALETTE* ppColorSet)
{
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CImpIViewObject2::Freeze(DWORD dwAspect, LONG lindex, LPVOID pvAspect,
                                      LPDWORD pdwFreeze)
{
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CImpIViewObject2::Unfreeze(DWORD dwFreeze)
{
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CImpIViewObject2::SetAdvise(DWORD dwAspects, DWORD dwAdvf,
                                         LPADVISESINK pAdvSink)
{
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CImpIViewObject2::GetAdvise(LPDWORD pAspects, LPDWORD pdwAdvf,
                                         LPADVISESINK* ppAdvSink)
{
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP CImpIViewObject2::GetExtent(DWORD dwAspect, LONG lindex, DVTARGETDEVICE* ptd,
                                         LPSIZEL pszl)
{
    return ResultFromScode(E_NOTIMPL);
}

CImpIViewObject2::~CImpIViewObject2()
{
}
