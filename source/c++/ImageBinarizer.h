#pragma once

#include <atlimage.h>

class ImageBinarizer
{
public:
	ImageBinarizer();
	~ImageBinarizer();

	void Binarize(CImage &image);
private:
	ULONG OtsusMethod(CImage &image);
	void Histogram(CImage &image);
	void Reset();

	ULONG m_histogram[256];
};
