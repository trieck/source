#pragma once

namespace ComCreator {

/////////////////////////////////////////////////////////////////////////////
template <typename Base, typename Interface>
HRESULT Create(CComPtr<Interface>& p)
{
    CComObject<Base>* pObject = nullptr;
    auto hr = CComObject<Base>::CreateInstance(&pObject);
    if (FAILED(hr)) {
        return hr;
    }

    hr = pObject->QueryInterface(__uuidof(Interface), reinterpret_cast<void**>(&p));

    return hr;
}

/////////////////////////////////////////////////////////////////////////////
template <typename Base>
HRESULT CreateAgg(LPUNKNOWN pUnkOuter, CComPtr<IUnknown>& p)
{
    CComAggObject<Base>* pObject = nullptr;

    auto hr = CComAggObject<Base>::CreateInstance(pUnkOuter, &pObject);
    if (FAILED(hr)) {
        return hr;
    }

    ATLASSERT(pObject);

    hr = pObject->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(&p));

    return hr;
}

}
