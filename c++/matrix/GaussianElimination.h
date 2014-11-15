#ifndef __GAUSSIANELIMINATION_H__
#define __GAUSSIANELIMINATION_H__

#include "matrix.h"

/////////////////////////////////////////////////////////////////////////////
class GaussianElimination {
// Construction / Destuction
private:
    GaussianElimination();
    ~GaussianElimination();

// Interface
public:
    static Matrix solve(const Matrix &A);

// Implementation
private:
};

#endif // __GAUSSIANELIMINATION_H__