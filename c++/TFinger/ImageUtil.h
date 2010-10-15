
#pragma once

BYTE PixelDigit(const CImage &image, const CPoint &pt);
BYTE PixelDigit(const CImage &image, int x, int y);
bool IsValidPoint(const CImage &image, const CPoint &pt);
bool IsValidPoint(const CImage &image, int x, int y);
CPoint Neighbor(int x, int y, int k);
