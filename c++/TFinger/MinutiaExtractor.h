#pragma once

#include "MinutiaValidator.h"

typedef std::vector<Minutia> MinutiaVec;

class MinutiaExtractor
{
public:
    MinutiaExtractor();
    ~MinutiaExtractor();

    MinutiaVec Extract(CImage &image);
private:
    UINT CrossingNumber(CImage &image, int x, int y);
    MinutiaValidator m_validator;
};
