#include "StdAfx.h"
#include "MinutiaExtractor.h"
#include "MinutiaValidator.h"
#include "ImageUtil.h"

MinutiaExtractor::MinutiaExtractor()
{
}

MinutiaExtractor::~MinutiaExtractor()
{
}

MinutiaVec MinutiaExtractor::Extract(CImage &image)
{
	MinutiaVec minutiav;

	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());

	UINT cn;
	Minutia minutia;
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			if (pbits[y*pitch+x] == 0xFF)	// background
				continue;

			cn = CrossingNumber(image, x, y);
			if (cn == MT_RIDGE_ENDING || cn == MT_RIDGE_BIFUR) {
				minutia.type = cn;
				minutia.x = x;
				minutia.y = y;
				if (m_validator.IsValid(image, minutia))
					minutiav.push_back(minutia);
			}
		}
	}

	return minutiav;
}

// The crossing number CN(p) of a pixel p is defined
// as half the sum of the differences between pairs
// of adjacent pixels in the 8-neighborhood of p.
UINT MinutiaExtractor::CrossingNumber(CImage &image, int x, int y)
{
	UINT cn = 0;

	CPoint pt1, pt2;
	BYTE p1, p2;
	for (int i = 0; i < 8; i++) {
		pt1 = Neighbor(x, y, i);
		pt2 = Neighbor(x, y, i+1);

		p1 = PixelDigit(image, pt1);
		p2 = PixelDigit(image, pt2);

		cn += abs(p1 - p2);
	}

	cn /= 2;

	return cn;
}


