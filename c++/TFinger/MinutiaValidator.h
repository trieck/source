/////////////////////////////////////////////////////////////////////////////
//
// MINUTIAVALIDATOR.H
//
// Minutia validator
// based on algorithm by Tico and Kuosmanen, 2000
//
// Copyright(c) 2010 LexisNexis, All Rights Reserved
//

#pragma once

#include "Minutia.h"

class MinutiaValidator
{
public:
    MinutiaValidator();
    ~MinutiaValidator();

    bool IsValid(const CImage &image, const Minutia &minutia);
private:
    bool IsValidEnding(const CImage &image, int x, int y);
    bool IsValidBifurcation(const CImage &image, int x, int y);
    void GetKernel(const CImage &image, int x, int y);
    void LabelRidge(const CImage &image, int x, int y, int m, int n, int label);
    UINT MinutiaValidator::KernelCount() const;
    bool IsVisited(int x, int y) const;
    bool IsBounded(int x, int y) const;
    void Visit(const CImage &image, int x, int y);
    void Label(int x, int y, int label);
    void Clear();
    UINT Transitions(int label) const;

    enum { L_IMAGE_SIZE = 15 };

    BYTE **m_plimage;		// WxW image L
    BYTE **m_pkernel;		// 3x3 neighborhood
    CPointVec m_visited;	// points visited during ridge labeling
};
