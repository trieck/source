#pragma once

#include <atlimage.h>

// ImageSegmenter

class ImageSegmenter
{
public:
	ImageSegmenter();
	virtual ~ImageSegmenter();

	void Segment(CImage &image);
private:
	static ULONG MeanBlock(CImage &image, int x, int y);
	static ULONG VarianceBlock(CImage &image, int x, int y);
	static void VarianceThreshold(CImage &image, int x, int y);
};


