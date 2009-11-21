#ifndef __MATRIX_H__
#define __MATRIX_H__

/////////////////////////////////////////////////////////////////////////////
class Matrix {
public:
// Construction / Destruction
	Matrix(int m, int n);
	Matrix(const Matrix &rhs);
	~Matrix();

// Interface
	Matrix& operator = (const Matrix &rhs);
	void setElement(int i, int j, float f);
	float Matrix::getElement(int i, int j) const;

// Implementation
private:
	int M, N;
	float *A;
};


#endif // __MATRIX_H__
