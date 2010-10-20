
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

/////////////////////////////////////////////////////////////////////////////
// Calculate the mean value of a block 
UINT MeanBlock(const CImage &image, int x, int y, int blocksize)
{
	UINT mean = 0;

	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPCBYTE pbits = reinterpret_cast<LPCBYTE>(image.GetBits());	

	for (int j = y; j < y + blocksize && j < rows; j++) {
		for (int i = x; i < x + blocksize && i < cols; i++) {
			mean += pbits[j*pitch+i];
		}
	}
	
	mean /= (blocksize * blocksize);

	return mean;
}

/////////////////////////////////////////////////////////////////////////////
// Calculate the variance of a block
UINT VarianceBlock(CImage &image, int x, int y, int blocksize)
{
	UINT variance = 0;
	
	UINT mean = MeanBlock(image, x, y, blocksize);

	int diff;
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPCBYTE pbits = reinterpret_cast<LPCBYTE>(image.GetBits());	

	for (int j = y; j < y + blocksize && j < rows; j++) {
		for (int i = x; i < x + blocksize && i < cols; i++) {
			diff = pbits[j*pitch+i] - mean;
			variance += (diff * diff);
		}
	}
	
	variance /= (blocksize * blocksize);

	return variance;
}

/////////////////////////////////////////////////////////////////////////////
// Calculate the mean of a block
UINT ImageMean(const CImage &image)
{
	UINT mean = 0;

	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPCBYTE pbits = reinterpret_cast<LPCBYTE>(image.GetBits());	

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			mean += pbits[y*pitch+x];
		}
	}
	
	mean /= rows * cols;

	return mean;
}

/////////////////////////////////////////////////////////////////////////////
// Calculate the variance of an image
UINT ImageVariance(const CImage &image)
{
	UINT variance = 0;
	
	UINT mean = ImageMean(image);

	int diff;
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPCBYTE pbits = reinterpret_cast<LPCBYTE>(image.GetBits());	

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			diff = pbits[y*pitch+x] - mean;
			variance += (diff * diff);
		}
	}
	
	variance /= rows * cols;

	return variance;
}
