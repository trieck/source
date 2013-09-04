/////////////////////////////////////////////////////////////////////////////
//
// MATRIX.CPP : Matrix routines
// Copyright(c) 2010 LexisNexis, All Rights Reserved
//

#include "stdafx.h"
#include "Matrix.h"

#define REAL_BLOCK(b) (((LPDWORD)b)-2)

/////////////////////////////////////////////////////////////////////////////
LPBYTE *AllocMatrix(UINT rows, UINT cols)
{
	DWORD size = sizeof(BYTE*) * rows + sizeof(DWORD) * 2;

	LPDWORD pdwBlock = (LPDWORD)GlobalAlloc(GMEM_FIXED, size);

	*pdwBlock++ = rows;
	*pdwBlock++ = cols;

	LPBYTE *block = (LPBYTE*)pdwBlock;

	for (DWORD i = 0; i < rows; i++) {
		block[i] = (LPBYTE)GlobalAlloc(GMEM_FIXED, cols * sizeof(BYTE));
	}

	return block;
}

/////////////////////////////////////////////////////////////////////////////
void FreeMatrix(LPBYTE *m)
{
	LPDWORD pdwBlock = REAL_BLOCK(m);
	DWORD rows = *pdwBlock;

	for (DWORD i = 0; i < rows; i++) {
		GlobalFree(m[i]);
	}

	GlobalFree(pdwBlock);
}

void ClearMatrix(LPBYTE *m)
{
	LPDWORD pdwBlock = REAL_BLOCK(m);
	DWORD rows = *pdwBlock++;
	DWORD cols = *pdwBlock;

	for (DWORD i = 0; i < rows; i++) {
		for (DWORD j = 0; j < cols; j++) {
			m[i][j] = 0;
		}
	}
}
