#pragma once

#include "MorphologicalOperator.h"

class ImageDilater : public MorphologicalOperator {
public:
    ImageDilater();
    ~ImageDilater();

    void Dilate(CImage &image);
private:
    void Dilate(CImage &image, Kernel *pKernel);
    void Dilate(CImage &image, Kernel *pKernel, int x, int y);

    typedef std::vector<Kernel*> KernelVec;
    KernelVec m_kernels;
};
