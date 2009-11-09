// CaptureBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "CaptureBitmap.h"


// CaptureBitmap

CaptureBitmap::CaptureBitmap() : RecolorableBitmap(DEFAULT_COLOR)
{
	Load(IDB_CAPTURE);
}

CaptureBitmap::~CaptureBitmap()
{
}


// CaptureBitmap member functions
