#pragma once

class ImageNormalizer
{
public:
	ImageNormalizer();
	~ImageNormalizer();

	void Normalize(CImage &image);
private:
	enum { M0 = 215 };	// desired mean
	enum { V0 = 2200 };	// desired variance
};
