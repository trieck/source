/////////////////////////////////////////////////////////////////////////////
//
// BOARD.CPP
//

#include "StdAfx.h"
#include "Board.h"

/////////////////////////////////////////////////////////////////////////////
Board::Board()
{
}

/////////////////////////////////////////////////////////////////////////////
Board::~Board()
{
    Destroy();
}

/////////////////////////////////////////////////////////////////////////////
void Board::Render(ID2D1RenderTarget* pTarget, const CRect& rc)
{
    const auto size = m_bitmap->GetSize();

    const auto upperLeftCorner = D2D1::Point2F(
        static_cast<FLOAT>(-rc.left) + CX_BORDER,
        static_cast<FLOAT>(-rc.top) + CY_BORDER);

    pTarget->DrawBitmap(
        m_bitmap,
        D2D1::RectF(
            upperLeftCorner.x,
            upperLeftCorner.y,
            upperLeftCorner.x + size.width,
            upperLeftCorner.y + size.height)
    );
}

/////////////////////////////////////////////////////////////////////////////
HRESULT Board::Create(ID2D1RenderTarget* pTarget)
{
    Destroy();

    const auto dims = GetDimensions();

    // Create a compatible render target
    CComPtr<ID2D1BitmapRenderTarget> pbmTarget;
    auto hr = pTarget->CreateCompatibleRenderTarget(
        D2D1::SizeF(static_cast<FLOAT>(dims.cx), static_cast<FLOAT>(dims.cy)),
        &pbmTarget);
    if (FAILED(hr))
        return hr;

    CComPtr<ID2D1SolidColorBrush> pBgBrush;
    hr = pbmTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::LightSteelBlue),
        &pBgBrush);
    if (FAILED(hr))
        return hr;

    CComPtr<ID2D1SolidColorBrush> pGridBrush;
    hr = pbmTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::DarkSlateGray),
        &pGridBrush);
    if (FAILED(hr))
        return hr;

    const auto rc = D2D1::RectF(0, 0, static_cast<FLOAT>(dims.cx), static_cast<FLOAT>(dims.cy));
    const auto cx = FLOAT(dims.cx) / CX_SQUARES;
    const auto cy = FLOAT(dims.cy) / CY_SQUARES;

    auto ptStart = D2D1::Point2F(cx, 0);
    D2D1_POINT_2F ptEnd;

    pbmTarget->BeginDraw();
    pbmTarget->FillRectangle(rc, pBgBrush);

    // Draw vertical lines
    while (ptStart.x < rc.right) {
        ptEnd = D2D1::Point2F(ptStart.x, FLOAT(dims.cy));
        pbmTarget->DrawLine(ptStart, ptEnd, pGridBrush, 0.2f);
        ptStart.x += cx;
    }

    // Draw horizontal lines
    ptStart = D2D1::Point2F(0, cy);
    while (ptStart.y < rc.bottom) {
        ptEnd = D2D1::Point2F(FLOAT(dims.cx), ptStart.y);
        pbmTarget->DrawLine(ptStart, ptEnd, pGridBrush, 0.2f);
        ptStart.y += cy;
    }

    pbmTarget->EndDraw();

    // Retrieve the bitmap from the render target
    hr = pbmTarget->GetBitmap(&m_bitmap);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
void Board::Destroy()
{
    m_bitmap.Release();
}

/////////////////////////////////////////////////////////////////////////////
CSize Board::GetDimensions()
{
    CSize sz;

    sz.cx = SQUARE_SIZE * CX_SQUARES;
    sz.cy = SQUARE_SIZE * CY_SQUARES;

    return sz;
}

/////////////////////////////////////////////////////////////////////////////
CRect Board::GetBoundingRect()
{
    CRect rc;

    const auto sz = GetDimensions();

    rc.right = sz.cx + (CX_BORDER * 2);
    rc.bottom = sz.cy + (CY_BORDER * 2);

    return rc;
}
