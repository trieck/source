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
    CComPtr<IDrawObject> m_pDraw;
};

extern PubApp theApp;
