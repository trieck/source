
#include <string.h>
#include "matrix.h"
#include "NoSuchElement.h"

/////////////////////////////////////////////////////////////////////////////
Matrix::Matrix(int m, int n) : M(m), N(n)
{
	A = new float[m * n];
	memset(A, 0, sizeof(float) * m * n);
}

/////////////////////////////////////////////////////////////////////////////
Matrix::Matrix(const Matrix &rhs) : M(0), N(0), A(0)
{
	*this = rhs;
}

/////////////////////////////////////////////////////////////////////////////
Matrix::~Matrix()
{
	delete []A;
}

/////////////////////////////////////////////////////////////////////////////
Matrix & Matrix::operator = (const Matrix &rhs)
{
	if (this != &rhs) {
		delete []A;
		M = rhs.M;
		N = rhs.N;
		memcpy(A, rhs.A, sizeof(float) * M * N);
	}

	return *this;
}
/////////////////////////////////////////////////////////////////////////////
void Matrix::setElement(int i, int j, float f)
{
	if (i >= M || j >= N)
		throw NoSuchElementException();

	A[i*j] = f;
}

/////////////////////////////////////////////////////////////////////////////
float Matrix::getElement(int i, int j) const
{
	if (i >= M || j >= N)
		throw NoSuchElementException();

	return A[i*j];
}
