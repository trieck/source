/////////////////////////////////////////////////////////////////////////////
//
// MATRIX.H : Matrix routines
// Copyright(c) 2010 LexisNexis, All Rights Reserved
//

#pragma once

#define REAL_BLOCK(b) (((LPDWORD)b)-2)

/////////////////////////////////////////////////////////////////////////////
template <typename T>
T** MatrixAlloc(UINT rows, UINT cols)
{
    DWORD size = sizeof(T*) * rows + sizeof(DWORD) * 2;

    LPDWORD pdwBlock = (LPDWORD)GlobalAlloc(GMEM_FIXED, size);

    *pdwBlock++ = rows;
    *pdwBlock++ = cols;

    T** block = (T**)pdwBlock;

    for (DWORD i = 0; i < rows; i++) {
        block[i] = (T*)GlobalAlloc(GMEM_FIXED, cols * sizeof(T));
    }

    return block;
}

/////////////////////////////////////////////////////////////////////////////
template <typename T>
void MatrixFree(T **m)
{
    LPDWORD pdwBlock = REAL_BLOCK(m);
    DWORD rows = *pdwBlock;

    for (DWORD i = 0; i < rows; i++) {
        GlobalFree(m[i]);
    }

    GlobalFree(pdwBlock);
}

/////////////////////////////////////////////////////////////////////////////
template <typename T>
void MatrixClear(T **m)
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
