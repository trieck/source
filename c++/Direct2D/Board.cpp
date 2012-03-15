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
void Board::Render(ID2D1RenderTarget *pTarget)
{
	pTarget->DrawBitmap(m_bitmap, D2D1::RectF(0, 0, 10, 10), 1.0);
}

/////////////////////////////////////////////////////////////////////////////
HRESULT Board::Create(ID2D1RenderTarget *pTarget)
{
	Destroy();

	CSize dims = GetDimensions();

	D2D1_SIZE_U size;
	size.width = dims.cx;
	size.height = dims.cy;

	// Create a compatible render target
	CComPtr<ID2D1BitmapRenderTarget> pbmTarget;
	HRESULT hr = pTarget->CreateCompatibleRenderTarget(
		D2D1::SizeF(10.0f, 10.0f), 
		&pbmTarget);
	if (FAILED(hr))
		return hr;

	// Draw a pattern
	CComPtr<ID2D1SolidColorBrush> pGridBrush;
	hr = pbmTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(0.93f, 0.94f, 0.96f, 1.0f)),
        &pGridBrush);
	if (FAILED(hr))
		return hr;

    pbmTarget->BeginDraw();
	pbmTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f, 10.0f, 1.0f), pGridBrush);
    pbmTarget->FillRectangle(D2D1::RectF(0.0f, 0.1f, 1.0f, 10.0f), pGridBrush);
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