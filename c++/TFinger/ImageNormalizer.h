#pragma once

class ImageNormalizer {
public:
    ImageNormalizer();
    ~ImageNormalizer();

    void Normalize(CImage &image);
private:
    enum { M0 = 220 };	// desired mean
    enum { V0 = 220 };	// desired variance
};
