// PieceBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "PieceBitmap.h"


// PieceBitmap

PieceBitmap::PieceBitmap() : RecolorableBitmap(DEFAULT_COLOR)
{
	Load(IDB_PIECE);
}

PieceBitmap::~PieceBitmap()
{
}

