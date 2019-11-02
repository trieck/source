#pragma once

#include "RecolorableBitmap.h"

// CaptureBitmap command target

class CaptureBitmap : public RecolorableBitmap
{
public:
    CaptureBitmap();
    virtual ~CaptureBitmap();

private:
    enum { DEFAULT_COLOR = RGB(0x00, 0x80, 0x00) };
};


