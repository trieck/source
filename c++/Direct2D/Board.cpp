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
	CSize dims = GetDimensions();

	D2D1_RECT_F aRect;
	aRect.left = rc.left + CX_BORDER;
	aRect.top = rc.top + CY_BORDER;
	aRect.right = aRect.left + dims.cx;
	aRect.bottom = aRect.top + dims.cy;

	pTarget->DrawBitmap(m_bitmap, aRect);
}

/////////////////////////////////////////////////////////////////////////////
HRESULT Board::Create(ID2D1RenderTarget *pTarget)
{
	Destroy();

	CSize dims = GetDimensions();

	// Create a compatible render target
	CComPtr<ID2D1BitmapRenderTarget> pbmTarget;
	HRESULT hr = pTarget->CreateCompatibleRenderTarget(
		D2D1::SizeF(dims.cx, dims.cy), 
		&pbmTarget);
	if (FAILED(hr))
		return hr;

	// Draw a pattern
	CComPtr<ID2D1SolidColorBrush> pGridBrush;
	hr = pbmTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::ForestGreen),
        &pGridBrush);
	if (FAILED(hr))
		return hr;

    pbmTarget->BeginDraw();
	pbmTarget->FillRectangle(D2D1::RectF(0, 0, dims.cx, dims.cy), pGridBrush);
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