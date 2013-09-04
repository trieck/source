#include "StdAfx.h"
#include "GaborFilter.h"
#include "Sobel.h"
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
GaborFilter::GaborFilter()
{
}

/////////////////////////////////////////////////////////////////////////////
GaborFilter::~GaborFilter()
{
}

/////////////////////////////////////////////////////////////////////////////
void GaborFilter::Apply(CImage &image)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());

	int gx, gy;
	int Vx, Vy;

	float theta;
	float Px, Py;

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			Vx = 0;
			Vy = 0;

			// estimate the local orientation of block centered at (x, y)
			for (int j = y - BLOCK_SIZE/2; j <= y + BLOCK_SIZE/2; j++) {
				for (int i = x - BLOCK_SIZE/2; i <= x + BLOCK_SIZE/2; i++) {
					gx = Sobel::Gx(image, i, j);
					gy = Sobel::Gy(image, i, j);

					Vx = Vx + 2 * gx * gy;
					Vy = Vy + (gx * gx) - (gy * gy);
				}
			}

			theta = atan((float)Vy/Vx) / 2;

			// convert the orientation image into a continuous vector field
			Px = cos(2 * theta);
			Py = sin(2 * theta);

			// perform gaussian smoothing

		}
	}

}
