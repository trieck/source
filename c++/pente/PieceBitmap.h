#pragma once

#include "RecolorableBitmap.h"

class PieceBitmap : public RecolorableBitmap {
public:
	PieceBitmap();
	virtual ~PieceBitmap();

private:
	enum { DEFAULT_COLOR = RGB(0x00, 0x80, 0x00) };
};


