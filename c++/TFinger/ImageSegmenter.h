#pragma once

#include <atlimage.h>

// ImageSegmenter

class ImageSegmenter {
public:
	ImageSegmenter();
	virtual ~ImageSegmenter();

	void Segment(CImage &image);
private:
	void VarianceThreshold(CImage &image, int x, int y);

	enum { BLOCK_SIZE = 8 };
	enum { VARIANCE_THRESHOLD = 49 };
};


