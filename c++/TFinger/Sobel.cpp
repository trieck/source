#include "StdAfx.h"
#include "Sobel.h"

namespace Sobel {

/////////////////////////////////////////////////////////////////////////////
// 3x3 GX Sobel mask
static const int GX[3][3] = {
    -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1
};

/////////////////////////////////////////////////////////////////////////////
// 3x3 GY Sobel mask
static const int GY[3][3] = {
    1, 2, 1,
    0, 0, 0,
    -1, -2, -1
};

/////////////////////////////////////////////////////////////////////////////
// X-gradient approximation
int Gx(const CImage &image, int x, int y)
{
    int rows = image.GetHeight();
    int cols = image.GetWidth();
    int pitch = image.GetPitch();

    LPCBYTE pbits = reinterpret_cast<LPCBYTE>(image.GetBits());

    int sumX = 0;

    if (y > 0 && y < rows-1 && x > 0 && x < cols-1) {
        for (int i = -1; i <= 1; i++)  {
            for (int j = -1; j <= 1; j++)  {
                sumX += pbits[(y+i)*pitch+x+j] * GX[i+1][j+1];
            }
        }
    }

    return sumX;
}

/////////////////////////////////////////////////////////////////////////////
// Y-gradient approximation
int Gy(const CImage &image, int x, int y)
{
    int rows = image.GetHeight();
    int cols = image.GetWidth();
    int pitch = image.GetPitch();

    LPCBYTE pbits = reinterpret_cast<LPCBYTE>(image.GetBits());

    int sumY = 0;

    if (y > 0 && y < rows-1 && x > 0 && x < cols-1) {
        for (int i = -1; i <= 1; i++)  {
            for (int j = -1; j <= 1; j++)  {
                sumY += pbits[(y+i)*pitch+x+j] * GY[i+1][j+1];
            }
        }
    }

    return sumY;
}


}	// end namespace