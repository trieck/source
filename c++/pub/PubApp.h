#pragma once
#include "DrawObject_i.h"

class PubApp : public CAppModule
{
public:
BEGIN_MSG_MAP(PubApp)
    END_MSG_MAP()

    bool Init();
    int Run();

    HRESULT CreateObject(CComPtr<IDrawObject>& pDrawObject);
    CComPtr<IDrawObject> GetDrawObject() const;

    void Release();

private:
    HRESULT Advise();
    HRESULT Unadvise();

    CComPtr<IAdviseSink> m_pAdviseSink;
    CComPtr<IDrawObject> m_pDraw;

    DWORD m_dwConn = 0;
};
