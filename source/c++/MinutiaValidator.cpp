/////////////////////////////////////////////////////////////////////////////
//
// MINUTIAVALIDATOR.CPP
//
// Minutia validator
// based on algorithm by Tico and Kuosmanen, 2000
//
// Copyright(c) 2010 LexisNexis, All Rights Reserved
//

#include "StdAfx.h"
#include "MinutiaValidator.h"
#include "ImageUtil.h"

static LPBYTE* AllocBlock(UINT size);
static void FreeBlock(LPBYTE *block);
static void ClearBlock(LPBYTE *block);

#define REAL_BLOCK(b)	((LPDWORD)((LPBYTE*)b-1))
#define BLOCK_SIZE(b)	(*REAL_BLOCK(b))

struct RidgeOrigin {
	POINT ptKernel;	// kernel origin
	POINT ptLImage;	// L-image origin
};

typedef std::vector<RidgeOrigin> RidgeOriginVec;

/////////////////////////////////////////////////////////////////////////////
MinutiaValidator::MinutiaValidator()
{
	m_plimage = AllocBlock(L_IMAGE_SIZE);
	m_pkernel = AllocBlock(3);
	Clear();
}

/////////////////////////////////////////////////////////////////////////////
MinutiaValidator::~MinutiaValidator()
{
	FreeBlock(m_plimage);
	FreeBlock(m_pkernel);
}

/////////////////////////////////////////////////////////////////////////////
void MinutiaValidator::Clear()
{
	ClearBlock(m_plimage);
	ClearBlock(m_pkernel);
	m_visited.clear();
	m_plimage[L_IMAGE_SIZE/2][L_IMAGE_SIZE/2] = -1;	// minutia point
}

/////////////////////////////////////////////////////////////////////////////
bool MinutiaValidator::IsValid(const CImage &image, const Minutia &minutia)
{
	if (minutia.type == MT_RIDGE_ENDING) {
		return IsValidEnding(image, minutia.x, minutia.y);
	} else if (minutia.type == MT_RIDGE_BIFUR) {
		return IsValidBifurcation(image, minutia.x, minutia.y);
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
bool MinutiaValidator::IsValidEnding(const CImage &image, int x, int y)
{
	Clear();

	LabelRidge(image, x, y, L_IMAGE_SIZE / 2, L_IMAGE_SIZE / 2, 1);

	if (Transitions(1) != 1)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool MinutiaValidator::IsValidBifurcation(const CImage &image, int x, int y)
{
	Clear();

	GetKernel(image, x, y);
	if (KernelCount() != 3)
		return false;	// not a bi-furcation

	Visit(image, x, y);

	RidgeOrigin origin;
	RidgeOriginVec v;

	int m = L_IMAGE_SIZE/2;
	int n = L_IMAGE_SIZE/2;

	if (m_pkernel[0][0] == 0) {
		origin.ptKernel.x = x-1;
		origin.ptKernel.y = y-1;
		origin.ptLImage.x = m-1;
		origin.ptLImage.y = n-1;
		v.push_back(origin);
	} 
	
	if (m_pkernel[0][1] == 0) {
		origin.ptKernel.x = x;
		origin.ptKernel.y = y-1;
		origin.ptLImage.x = m;
		origin.ptLImage.y = n-1;
		v.push_back(origin);
	} 
	
	if (m_pkernel[0][2] == 0) {
		origin.ptKernel.x = x+1;
		origin.ptKernel.y = y-1;
		origin.ptLImage.x = m+1;
		origin.ptLImage.y = n-1;
		v.push_back(origin);
	} 
	
	if (m_pkernel[1][2] == 0) {
		origin.ptKernel.x = x+1;
		origin.ptKernel.y = y;
		origin.ptLImage.x = m+1;
		origin.ptLImage.y = n;
		v.push_back(origin);
	} 
	
	if (m_pkernel[2][2] == 0) {
		origin.ptKernel.x = x+1;
		origin.ptKernel.y = y+1;
		origin.ptLImage.x = m+1;
		origin.ptLImage.y = n+1;
		v.push_back(origin);
	} 
	
	if (m_pkernel[2][1] == 0) {
		origin.ptKernel.x = x;
		origin.ptKernel.y = y+1;
		origin.ptLImage.x = m;
		origin.ptLImage.y = n+1;
		v.push_back(origin);
	} 
	
	if (m_pkernel[2][0] == 0) {
		origin.ptKernel.x = x-1;
		origin.ptKernel.y = y+1;
		origin.ptLImage.x = m-1;
		origin.ptLImage.y = n+1;
		v.push_back(origin);
	} 
	
	if (m_pkernel[1][0] == 0) {
		origin.ptKernel.x = x-1;
		origin.ptKernel.y = y;
		origin.ptLImage.x = m-1;
		origin.ptLImage.y = n;
		v.push_back(origin);
	}

	RidgeOriginVec::const_iterator it = v.begin();
	for (int label = 1; it != v.end(); it++, label++) {
		const RidgeOrigin &origin = *it;
		Label(origin.ptLImage.x, origin.ptLImage.y, label);	
		LabelRidge(image, origin.ptKernel.x, origin.ptKernel.y, 
			origin.ptLImage.x, origin.ptLImage.y, label);
	}

	if (Transitions(1) != 1)
		return false;

	if (Transitions(2) != 1)
		return false;

	if (Transitions(3) != 1)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
void MinutiaValidator::GetKernel(const CImage &image, int x, int y)
{
	int rows = image.GetHeight();
	int cols = image.GetWidth();
	int pitch = image.GetPitch();

	LPCBYTE pbits = reinterpret_cast<LPCBYTE>(image.GetBits());

	for (int i = 0, k = y-1; i < 3; i++, k++) {
		for (int j = 0, l = x-1; j < 3; j++, l++) {
			if (IsVisited(l, k))
				m_pkernel[i][j] = 1;
			else 
				m_pkernel[i][j] = PixelDigit(image, l, k);
		}
	}	
}

/////////////////////////////////////////////////////////////////////////////
void MinutiaValidator::LabelRidge(const CImage &image, int x, int y, int m, 
	int n, int label)
{
	GetKernel(image, x, y);

	// There must be exactly one black pixel
	// in the 8-neighborhood defined by the kernel
	// in order to determine a valid ridge direction.
	while (IsBounded(m, n) && (KernelCount() == 1)) {
		Visit(image, x, y);

		if (m_pkernel[0][0] == 0) {
			--x, --y, --m, --n;
		} else if (m_pkernel[0][1] == 0) {
			--y, --n;
		} else if (m_pkernel[0][2] == 0) {
			++x, --y, ++m, --n;
		} else if (m_pkernel[1][2] == 0) {
			++x, ++m;
		} else if (m_pkernel[2][2] == 0) {
			++x, ++y, ++m, ++n;
		} else if (m_pkernel[2][1] == 0) {
			++y, ++n;
		} else if (m_pkernel[2][0] == 0) {
			--x, ++y, --m, ++n;
		} else if (m_pkernel[1][0] == 0) {
			--x, --m;
		}

		Label(m, n, label);
		GetKernel(image, x, y);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Count the number of transitions from 0 => label
// when making a full clockwise trip along the border of L
UINT MinutiaValidator::Transitions(int label) const
{
	UINT t = 0;

	int i, j;

	for (i = 0, j = 0; j < L_IMAGE_SIZE-1; j++) {
		if (m_plimage[i][j] == 0 && m_plimage[i][j+1] == label)
			t++;
	}

	for (i = 0, j = L_IMAGE_SIZE-1; i < L_IMAGE_SIZE-1; i++) {
		if (m_plimage[i][j] == 0 && m_plimage[i+1][j] == label)
			t++;
	}

	for (i = L_IMAGE_SIZE-1, j = L_IMAGE_SIZE-1; j >= 1; j--) {
		if (m_plimage[i][j] == 0 && m_plimage[i][j-1] == label)
			t++;
	}

	for (i = L_IMAGE_SIZE-1, j = 0; i >= 1; i--) {
		if (m_plimage[i][j] == 0 && m_plimage[i-1][j] == label)
			t++;
	}

	return t;
}

/////////////////////////////////////////////////////////////////////////////
bool MinutiaValidator::IsBounded(int x, int y) const
{
	if (x < 0 || x >= L_IMAGE_SIZE || y < 0 || y >= L_IMAGE_SIZE)
		return false;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
void MinutiaValidator::Label(int x, int y, int label)
{
	if (IsBounded(x, y)) {
		m_plimage[y][x] = label;
	}
}

/////////////////////////////////////////////////////////////////////////////
UINT MinutiaValidator::KernelCount() const
{
	UINT count = 0;

	// count black pixels clockwise in 8-neighborhood
	if (m_pkernel[0][0] == 0) count++;
    if (m_pkernel[0][1] == 0) count++;
    if (m_pkernel[0][2] == 0) count++;
    if (m_pkernel[1][2] == 0) count++;
    if (m_pkernel[2][2] == 0) count++;
    if (m_pkernel[2][1] == 0) count++;
    if (m_pkernel[2][0] == 0) count++;
    if (m_pkernel[1][0] == 0) count++;

	return count;
}

/////////////////////////////////////////////////////////////////////////////
bool MinutiaValidator::IsVisited(int x, int y) const
{
	CPoint pt(x, y);

	if (std::find(m_visited.begin(), m_visited.end(), pt) 
		!= m_visited.end()) {
		return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
void MinutiaValidator::Visit(const CImage &image, int x, int y)
{
	if (!IsValidPoint(image, x, y))
		return;

	CPoint pt(x, y);
	m_visited.push_back(pt);
}

// Helper functions

/////////////////////////////////////////////////////////////////////////////
LPBYTE *AllocBlock(UINT size)
{
	DWORD allocSize = sizeof(BYTE*) * size + sizeof(DWORD);

	LPDWORD pdwBlock = (LPDWORD)GlobalAlloc(GMEM_FIXED, allocSize);

	*pdwBlock = size;	// store the block size

	LPBYTE *block = (LPBYTE*)++pdwBlock;

	for (UINT i = 0; i < size; i++) {
		block[i] = (LPBYTE)GlobalAlloc(GMEM_FIXED, size * sizeof(BYTE));
	}	

	return block;	
}

/////////////////////////////////////////////////////////////////////////////
void FreeBlock(LPBYTE *block)
{
	LPDWORD pdwBlock = REAL_BLOCK(block);
	DWORD size = *pdwBlock;
	
	for (UINT i = 0; i < size; i++) {
		GlobalFree(block[i]);
	}

	GlobalFree(pdwBlock);
}

void ClearBlock(LPBYTE *block)
{
	DWORD size = BLOCK_SIZE(block);

	for (UINT i = 0; i < size; i++) {
		for (UINT j = 0; j < size; j++) {
			block[i][j] = 0;
		}
	}
}
