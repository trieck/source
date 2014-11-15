#include "StdAfx.h"
#include "MeanFilter.h"
#include "ImageUtil.h"

// mean filter kernel
static const FLOAT KERNEL[3][3] = {
    0.11f, 0.11f, 0.11f,
    0.11f, 0.11f, 0.11f,
    0.11f, 0.11f, 0.11f
};

/////////////////////////////////////////////////////////////////////////////
MeanFilter::MeanFilter()
{
}

/////////////////////////////////////////////////////////////////////////////
MeanFilter::~MeanFilter()
{
}

/////////////////////////////////////////////////////////////////////////////
void MeanFilter::Filter(CImage &image)
{
    Convolve(image, &KERNEL[0][0], 3);
}
