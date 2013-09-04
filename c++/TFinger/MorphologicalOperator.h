#pragma once

#include "Kernel.h"

class MorphologicalOperator {
public:
	MorphologicalOperator();
	virtual ~MorphologicalOperator();
protected:
	virtual bool Match(CImage &image, Kernel *pKernel, int x, int y);
};
