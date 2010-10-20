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

	UINT M = ImageMean(image);
	UINT V = ImageVariance(image);

	if (V == 0)
		return;

	int N;
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			BYTE &I = pbits[y*pitch+x];
			N = (int)sqrt((float)(I-M) * (I-M) * ((float)V0/V));
			if (I > M) {
				I = M0 + N;
			} else {
				I = M0 - N;
			}
		}
	}
}
