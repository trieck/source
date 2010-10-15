#include "StdAfx.h"
#include "MorphologicalOperator.h"

MorphologicalOperator::MorphologicalOperator()
{
}

MorphologicalOperator::~MorphologicalOperator()
{
}

bool MorphologicalOperator::Match(CImage &image, Kernel *pKernel, 
	int x, int y)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	int blocksize = pKernel->GetBlockSize();	
	int cx = x - ((blocksize-1) / 2);
	int cy = y - ((blocksize-1) / 2);

	LPBYTE pbits = reinterpret_cast<LPBYTE>(image.GetBits());	

	BYTE a, b;
	for (int j = cy, l = 0; j < cy + blocksize; j++, l++) {
		for (int i = cx, k = 0; i < cx + blocksize; i++, k++) {
			a = (j < 0 || i < 0 || j >= rows || i >= cols) ? 0xFF
				: pbits[j*pitch+i];
					
			b = pKernel->GetPixel(k, l);
			if (a != b)
				return false;
		}
	}

	return true;
}

