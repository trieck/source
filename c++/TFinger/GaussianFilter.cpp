#include "StdAfx.h"
#include "GaussianFilter.h"
#include "ImageUtil.h"

// base filter kernel
static FLOAT BASE_KERNEL[5][5] = {
    1,  4,  7,  4, 1,
    4, 16, 26, 16, 4,
    7, 26, 41, 26, 7,
    4, 16, 26, 16, 4,
    1,  4,  7,  4, 1
};

static const float SCALE_FACTOR = 1/273.00f;

/////////////////////////////////////////////////////////////////////////////
GaussianFilter::GaussianFilter()
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            m_kernel[i][j] = BASE_KERNEL[i][j] * SCALE_FACTOR;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
GaussianFilter::~GaussianFilter()
{
}

/////////////////////////////////////////////////////////////////////////////
void GaussianFilter::Filter(CImage &image)
{
    Convolve(image, &m_kernel[0][0], 5);
}

