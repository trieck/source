#pragma once

#include "DrawObject_i.h"
#include "resource.h"

class CDrawObjectModule : public CAtlDllModuleT<CDrawObjectModule>
{
public:
    DECLARE_LIBID(LIBID_DrawObjectLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DRAWOBJECT, "{C66AEB85-1E20-41C6-AF31-F1C64D1EE4AB}")
};
