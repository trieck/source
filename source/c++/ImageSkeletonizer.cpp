#include "StdAfx.h"
#include "ImageSkeletonizer.h"
#include "ImageUtil.h"

// "structuring elements" used in the skeletonization process
static const BYTE ELEM0[3][3] = {
	0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0x00
};

static const BYTE ELEM1[3][3] = {
	0xFF, 0x00, 0xFF,
	0x00, 0x00, 0xFF,
	0x00, 0xFF, 0xFF
};

static const BYTE ELEM2[3][3] = {
	0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,
	0x00, 0x00, 0xFF
};

static const BYTE ELEM3[3][3] = {
	0x00, 0x00, 0xFF,
	0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0xFF
};

static const BYTE ELEM4[3][3] = {
	0x00, 0xFF, 0xFF,
	0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF
};

static const BYTE ELEM5[3][3] = {
	0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0x00,
	0xFF, 0x00, 0xFF
};

static const BYTE ELEM6[3][3] = {
	0xFF, 0x00, 0x00,
	0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0xFF
};

static const BYTE ELEM7[3][3] = {
	0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0xFF,
	0xFF, 0x00, 0x00
};

static const BYTE ELEM8[3][3] = {
	0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0xFF
};

static const BYTE ELEM9[3][3] = {
	0xFF, 0x00, 0xFF,
	0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0xFF
};

static const BYTE ELEM10[3][3] = {
	0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,
	0xFF, 0x00, 0xFF
};

static const BYTE ELEM11[3][3] = {
	0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF
};

static const BYTE ELEM12[3][3] = {
	0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF
};

static const BYTE ELEM13[3][3] = {
	0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0x00,
	0xFF, 0x00, 0xFF
};

static const BYTE ELEM14[3][3] = {
	0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0x00,
	0xFF, 0x00, 0xFF
};

static const BYTE ELEM15[3][3] = {
	0xFF, 0x00, 0xFF,
	0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF
};

ImageSkeletonizer::ImageSkeletonizer()
{
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM0[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM1[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM2[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM3[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM4[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM5[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM6[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM7[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM8[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM9[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM10[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM11[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM12[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM13[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM14[0][0]));
	m_kernels.push_back(Kernel::MakeKernel(3, &ELEM15[0][0]));
}

ImageSkeletonizer::~ImageSkeletonizer()
{
	KernelVec::iterator it = m_kernels.begin();
	for ( ; it != m_kernels.end(); it++) {
		delete (*it);
	}

	m_kernels.clear();
}

void ImageSkeletonizer::Skeletonize(CImage &image)
{
	ZhangSuen(image);

	CPointVec v;
	KernelVec::iterator it = m_kernels.begin();
	for ( ; it != m_kernels.end(); it++) {
		Skeletonize(image, *it);
	}
}

void ImageSkeletonizer::Skeletonize(CImage &image, Kernel *pKernel)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			BYTE &p = pbits[y*pitch+x];
			
			if (p == 0x00) {	// foreground
				if (Match(image, pKernel, x, y)) {
					p = 0xFF;	// background
				}
			}
		}
	}
}

// Zhang and Suen algorithm
// Communications of the ACM, March 1984
void ImageSkeletonizer::ZhangSuen(CImage &image)
{
	UINT c;

	do { 
		if ((c = ZhangSuen(image, 1)) == 0)
			break;
		c = ZhangSuen(image, 2);
	} while (c > 0);
}

UINT ImageSkeletonizer::ZhangSuen(CImage &image, int sub)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	CPointVec points;
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			BYTE &p = pbits[y*pitch+x];
				
			if (p == 0x00) {	// foreground
				if (ZhangSuenCond(image, x, y, sub)) {	
					points.push_back(CPoint(x, y));
				}
			}
		}
	}

	CPointVec::const_iterator it = points.begin();
	for ( ; it != points.end(); it++) {
		const CPoint &pt = *it;
		pbits[pt.y*pitch+pt.x] = 0xFF;	// background
	}

	return points.size();
}

bool ImageSkeletonizer::ZhangSuenCond(CImage &image, int x, int y, int sub)
{
	UINT n = Neighbors(image, x, y);	// number of foreground neighbors
	if (n < 2 || n > 6)
		return false;

	n = Transitions(image, x, y);	// number of 1-0 transitions
	if (n > 1)
		return false;

	// background condition for sub-iteration
	return BkgndCond(image, x, y, sub);
}

UINT ImageSkeletonizer::Neighbors(CImage &image, int x, int y)
{
	UINT neighbors = 0;

	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	CPoint pt;
	for (int i = 0; i < 8; i++) {
		pt = Neighbor(x, y, i);
		if (!IsValidPoint(image, pt))
			continue;

		if (pbits[pt.y*pitch+pt.x] == 0x00) {	// foreground
			neighbors++;
		}
	}

	return neighbors;
}

// number of 1-0 transitions in the neighborhood of P(x,y)
UINT ImageSkeletonizer::Transitions(CImage &image, int x, int y)
{
	UINT transitions = 0;
	
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();
	int intrans = 0;

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	CPoint pt;
	for (int i = 0; i < 8; i++) {
		pt = Neighbor(x, y, i);
		if (!IsValidPoint(image, pt)) {
			intrans = 0;
			continue;
		}

		if (pbits[pt.y*pitch+pt.x] == 0xFF) {
			intrans = 1;
		} else if (intrans) {
			transitions++;
			intrans = 0;
		}
	}

	return transitions;
}

bool ImageSkeletonizer::BkgndCond(CImage &image, int x, int y, int sub)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	CPoint pt1 = Neighbor(x, y, 0);
	CPoint pt3 = Neighbor(x, y, 2);
	CPoint pt5 = Neighbor(x, y, 4);
	CPoint pt7 = Neighbor(x, y, 6);

	BYTE p1 = IsValidPoint(image, pt1) ? pbits[pt1.y*pitch+pt1.x] : 0x00;
	BYTE p3 = IsValidPoint(image, pt3) ? pbits[pt3.y*pitch+pt3.x] : 0x00;
	BYTE p5 = IsValidPoint(image, pt5) ? pbits[pt5.y*pitch+pt5.x] : 0x00;
	BYTE p7 = IsValidPoint(image, pt7) ? pbits[pt7.y*pitch+pt7.x] : 0x00;

	// sub-iteration condition 1
	if (sub == 1 && (p3 || p5 || (p1 && p7)))
		return true;

	// sub-iteration condition 2
	else if (sub == 2 && (p1 || p7 || (p3 && p5)))
		return true;

	return false;
}

