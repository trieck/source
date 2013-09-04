#include "StdAfx.h"
#include "ImageNormalizer.h"
#include "ImageUtil.h"
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
ImageNormalizer::ImageNormalizer()
{
}

/////////////////////////////////////////////////////////////////////////////
ImageNormalizer::~ImageNormalizer()
{
}

/////////////////////////////////////////////////////////////////////////////
// Hong, Wan, Jain 1998
void ImageNormalizer::Normalize(CImage &image)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());

	int M = ImageMean(image);
	int V = ImageVariance(image);

	if (V == 0)
		return;

	int N, I;
	BYTE v;
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			I = pbits[y*pitch+x];
			N = (int)sqrt(((float)V0/V) * (I-M) * (I-M));
			if (I > M) {
				v = M0 + N;
			} else {
				v = M0 - N;
			}
			pbits[y*pitch+x] = v;
		}
	}
}
