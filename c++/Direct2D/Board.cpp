/////////////////////////////////////////////////////////////////////////////
//
// BOARD.CPP
//

#include "stdafx.h"
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
void Board::Render(ID2D1RenderTarget *pTarget, const CRect &rc)
{
	D2D1_SIZE_F size = m_bitmap->GetSize();

	D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(
		(FLOAT)-rc.left + CX_BORDER,
		(FLOAT)-rc.top + CY_BORDER);

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
HRESULT Board::Create(ID2D1RenderTarget *pTarget)
{
	Destroy();

	CSize dims = GetDimensions();

	// Create a compatible render target
	CComPtr<ID2D1BitmapRenderTarget> pbmTarget;
	HRESULT hr = pTarget->CreateCompatibleRenderTarget(
		D2D1::SizeF((FLOAT)dims.cx, (FLOAT)dims.cy), 
		&pbmTarget);
	if (FAILED(hr))
		return hr;

	// Draw a pattern
	CComPtr<ID2D1SolidColorBrush> pGridBrush;
	hr = pbmTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
        &pGridBrush);
	if (FAILED(hr))
		return hr;

    pbmTarget->BeginDraw();
	pbmTarget->FillRectangle(D2D1::RectF(0, 0, (FLOAT)dims.cx, (FLOAT)dims.cy), pGridBrush);
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

	CSize sz = Board::GetDimensions();

	rc.right = sz.cx + (CX_BORDER * 2);
	rc.bottom = sz.cy + (CY_BORDER * 2);

	return rc;
}