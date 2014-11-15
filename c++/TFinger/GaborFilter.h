#pragma once

class GaborFilter {
public:
    GaborFilter();
    ~GaborFilter();

    void Apply(CImage &image);
private:
    enum { BLOCK_SIZE = 8 };

};
