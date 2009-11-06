// PieceIcon.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "PieceIcon.h"
#include "resource.h"

// PieceIcon
PieceIcon::PieceIcon() : hIcon(NULL), color(DEFAULT_COLOR)
{
	load();
	recreateIcon();
}

PieceIcon::~PieceIcon()
{
	DestroyIcon(hIcon);	
}

void PieceIcon::load(void)
{
	HICON hIcon = (HICON)LoadImage(AfxGetResourceHandle(),
		MAKEINTRESOURCE(IDI_PIECE),
		IMAGE_ICON,
		0, 0, LR_SHARED);
	ASSERT(hIcon != NULL);

	ICONINFO info;
	GetIconInfo(hIcon, &info);

	createBitmap(info.hbmMask, bmMask);
	createBitmap(info.hbmColor, bmColor);

	DeleteObject(info.hbmMask);
	DeleteObject(info.hbmColor);

	DestroyIcon(hIcon);
}

void PieceIcon::createBitmap(HBITMAP hBitmap, CBitmap &bitmap)
{
	BITMAP bm;
	if (!GetObject(hBitmap, sizeof(BITMAP), &bm))
		AfxThrowResourceException();

	bitmap.DeleteObject();
	if (!bitmap.CreateBitmapIndirect(&bm))
		AfxThrowResourceException();

	DWORD dwBmpSize = ((bm.bmWidth * bm.bmBitsPixel + 31) / 32) * 4 * bm.bmHeight;
	
	BYTE *bits = new BYTE[dwBmpSize];

	GetBitmapBits(hBitmap, dwBmpSize, bits);
	bitmap.SetBitmapBits(dwBmpSize, bits);

	delete [] bits;
}

void PieceIcon::recreateIcon()
{
	BITMAP bm;
	bmColor.GetBitmap(&bm);

	ICONINFO info;
	info.fIcon = TRUE;
	info.xHotspot = bm.bmWidth / 2;
	info.yHotspot = bm.bmHeight / 2;
	info.hbmMask = bmMask;
	info.hbmColor = bmColor;
	
	if ((hIcon = CreateIconIndirect(&info)) == NULL)
		AfxThrowResourceException();
}

void PieceIcon::setColor(COLORREF nColor)
{
	BITMAP bm;
	bmColor.GetBitmap(&bm);

	DWORD dwBmpSize = ((bm.bmWidth * bm.bmBitsPixel + 31) / 32) * 4 * bm.bmHeight;

	BYTE *bits = new BYTE[dwBmpSize];

	bmColor.GetBitmapBits(dwBmpSize, bits);

	for (uint32_t i = 0; i < dwBmpSize; i++) {
		BYTE &b = bits[i++];
		BYTE &g = bits[i++];
		BYTE &r = bits[i++];
		BYTE z = bits[i];

		COLORREF dwColor = RGB(r, g, b);
		if (dwColor == color) {
			r = GetRValue(nColor);
			g = GetGValue(nColor);
			b = GetBValue(nColor);
		}
	}

	bmColor.SetBitmapBits(dwBmpSize, bits);

	delete [] bits;

	recreateIcon();

	color = nColor;
}