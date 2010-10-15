
#include "stdafx.h"
#include "ImageUtil.h"

// clockwise neighbors defining the 8-neighborhood
static const POINT neighbors[8] = {
	{ 0, -1 }, { 1, -1 }, 
	{ 1, 0 }, { 1, 1 }, 
	{ 0, 1 }, { -1 , 1 },
	{ -1, 0 }, { -1, -1 }
};

bool IsValidPoint(const CImage &image, const CPoint &pt)
{
	return IsValidPoint(image, pt.x, pt.y);
}

bool IsValidPoint(const CImage &image, int x, int y)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();

	if (x < 0 || x >= cols || y < 0 || y >= rows)
		return false;

	return true;
}

// Find the k-th neighbor in the 8-neighborhood of pixel x, y
CPoint Neighbor(int x, int y, int k)
{
	CPoint pt;

	pt = neighbors[k % 8];

	pt.x = x + pt.x;
	pt.y = y + pt.y;

	return pt;
}

BYTE PixelDigit(const CImage &image, int x, int y)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPCBYTE pbits = reinterpret_cast<LPCBYTE>(image.GetBits());	

	if (!IsValidPoint(image, x, y))
		return 1;	// background

	if (pbits[y*pitch+x] == 0x00)
		return 0;	// foreground

	return 1;		// background
}

BYTE PixelDigit(const CImage &image, const CPoint &pt)
{
	return PixelDigit(image, pt.x, pt.y);
}

