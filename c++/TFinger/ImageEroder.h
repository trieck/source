#pragma once

#include "Kernel.h"
#include "MorphologicalOperator.h"

class ImageEroder : public MorphologicalOperator {
public:
	ImageEroder();
	~ImageEroder();

	void Erode(CImage &image);
private:
	void Erode(CImage &image, Kernel *pKernel);
	void Erode(CImage &image, Kernel *pKernel, int x, int y);

	typedef std::vector<Kernel*> KernelVec;
	KernelVec m_kernels;
};
