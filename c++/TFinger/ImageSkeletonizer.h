#pragma once

#include "Kernel.h"
#include "MorphologicalOperator.h"

class ImageSkeletonizer : public MorphologicalOperator
{
public:
    ImageSkeletonizer();
    ~ImageSkeletonizer();

    void Skeletonize(CImage &image);

private:
    UINT Neighbors(CImage &image, int x, int y);
    UINT Transitions(CImage &image, int x, int y);
    bool BkgndCond(CImage &image, int x, int y, int sub);
    void ZhangSuen(CImage &image);
    UINT ZhangSuen(CImage &image, int sub);
    bool ZhangSuenCond(CImage &image, int x, int y, int sub);
    void Skeletonize(CImage &image, Kernel *pKernel);

    typedef std::vector<Kernel*> KernelVec;
    KernelVec m_kernels;
};
