#include "StdAfx.h"
#include "ImageBinarizer.h"

ImageBinarizer::ImageBinarizer()
{
	Reset();
}

ImageBinarizer::~ImageBinarizer()
{
}

void ImageBinarizer::Reset()
{
	memset(m_histogram, 0, 256 * sizeof(ULONG));
}

void ImageBinarizer::Binarize(CImage &image)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	ULONG threshold = OtsusMethod(image);

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			BYTE &p = pbits[y*pitch+x];
			if (p < threshold) {
				p = 0x00;	// black
			} else {
				p = 0xFF;	// white
			}
		}
	}
}

ULONG ImageBinarizer::OtsusMethod(CImage &image)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	Histogram(image);

	// total number of pixels
	int total = rows * cols;

	float sum = 0, sumB = 0;
	for (int t = 0; t < 256; t++) {
		sum += t * m_histogram[t];
	}

	ULONG wB = 0, wF = 0;
	float mB, mF;
	float varMax = 0, varBetween;
	
	ULONG threshold = 0;
	
	for (int t = 0; t < 256; t++) {
		wB += m_histogram[t];	// weight background
		if (wB == 0) continue;

		wF = total - wB;		// weight foreground
		if (wF == 0) break;

		sumB += t * m_histogram[t];

		mB = sumB / wB;			// mean background
		mF = (sum - sumB) / wF;	// mean foreground

		// compute between class variance
		varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);	

		// check if new maximum found
		if (varBetween > varMax) {
			varMax = varBetween;
			threshold = t;
		}
	}

	return threshold;
}

void ImageBinarizer::Histogram(CImage &image)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	ULONG maxlevel = 0;

	Reset();

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	BYTE h;
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			h = pbits[y*pitch+x];
			m_histogram[h]++;
			if (m_histogram[h] > maxlevel)  {
				maxlevel = m_histogram[h];
			}
		}
	}	
}
