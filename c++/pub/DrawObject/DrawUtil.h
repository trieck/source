#pragma once

inline void PixelToHimetric(CRect& rc)
{
    // Convert pixel coordinates to twips (.01-mm).
    auto hDC = GetDC(nullptr);

    auto horzTwip = GetDeviceCaps(hDC, HORZSIZE) * 100; // Horizontal size in hundredths of millimeters
    auto vertTwip = GetDeviceCaps(hDC, VERTSIZE) * 100; // Vertical size in hundredths of millimeters
    auto horzPels = GetDeviceCaps(hDC, HORZRES);        // Horizontal width in pixels
    auto vertPels = GetDeviceCaps(hDC, VERTRES);        // Vertical height in pixels

    rc.left = (rc.left * horzTwip) / horzPels;
    rc.top = (rc.top * vertTwip) / vertPels;
    rc.right = (rc.right * horzTwip) / horzPels;
    rc.bottom = (rc.bottom * vertTwip) / vertPels;

    ReleaseDC(nullptr, hDC);
}

inline void HimetricToPixel(CRect& rc)
{
    // Convert twips (.01 mm) to pixels
    auto hDC = GetDC(nullptr);

    auto horzTwip = GetDeviceCaps(hDC, HORZSIZE) * 100; // Horizontal size in hundredths of millimeters
    auto vertTwip = GetDeviceCaps(hDC, VERTSIZE) * 100; // Vertical size in hundredths of millimeters
    auto horzPels = GetDeviceCaps(hDC, HORZRES);        // Horizontal width in pixels
    auto vertPels = GetDeviceCaps(hDC, VERTRES);        // Vertical height in pixels

    rc.left = (rc.left * horzPels) / horzTwip;
    rc.top = (rc.top * vertPels) / vertTwip;
    rc.right = (rc.right * horzPels) / horzTwip;
    rc.bottom = (rc.bottom * vertPels) / vertTwip;

    ReleaseDC(nullptr, hDC);
}

struct AutoStgMedium : STGMEDIUM
{
    AutoStgMedium() : STGMEDIUM{}
    {
    }

    ~AutoStgMedium()
    {
        Release();
    }

    void Release()
    {
        ReleaseStgMedium(this);
    }
};
