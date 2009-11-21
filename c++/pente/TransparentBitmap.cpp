// TransparentBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "TransparentBitmap.h"


// TransparentBitmap

TransparentBitmap::TransparentBitmap(COLORREF transparent)
		: m_Transparent(transparent), m_pOldBitmapAnd(NULL), m_pOldBitmapXor(NULL),
		m_pOldBitmapMem(NULL)
{
}

TransparentBitmap::~TransparentBitmap()
{
	Cleanup();
}

// TransparentBitmap member functions

void TransparentBitmap::Repaint()
{
	Cleanup();

	BITMAP bm;
	GetObject(sizeof(BITMAP), &bm);

	CPoint size(bm.bmWidth, bm.bmHeight);
	CPoint org(0, 0);

	CDC dc;
	dc.Attach(GetDC(NULL));

	CDC dcImage;
	dcImage.CreateCompatibleDC(&dc);
	CBitmap *pOldBitmapImage = dcImage.SelectObject(this);
	dcImage.SetMapMode(dc.GetMapMode());


	m_AndDC.CreateCompatibleDC(&dc);
	m_AndDC.SetMapMode(dc.GetMapMode());

	CBitmap bitmapAnd;
	bitmapAnd.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	m_pOldBitmapAnd = m_AndDC.SelectObject(&bitmapAnd);

	dcImage.SetBkColor(m_Transparent);

	m_AndDC.BitBlt(org.x, org.y, size.x, size.y, &dcImage, org.x, org.y, SRCCOPY);

	m_XorDC.CreateCompatibleDC(&dc);
	m_XorDC.SetMapMode(dc.GetMapMode());

	CBitmap bitmapXor;
	bitmapXor.CreateCompatibleBitmap(&dcImage, bm.bmWidth, bm.bmHeight);

	m_pOldBitmapXor = m_XorDC.SelectObject(&bitmapXor);

	m_XorDC.BitBlt(org.x, org.y, size.x, size.y, &dcImage, org.x, org.y, SRCCOPY);
	m_XorDC.BitBlt(org.x, org.y, size.x, size.y, &m_AndDC, org.x, org.y, 0x220326);

	m_MemDC.CreateCompatibleDC(&dc);
	m_MemDC.SetMapMode(dc.GetMapMode());

	CBitmap bitmapMem;
	bitmapMem.CreateCompatibleBitmap(&dcImage, bm.bmWidth, bm.bmHeight);

	m_pOldBitmapMem = m_MemDC.SelectObject(&bitmapMem);

	dcImage.SelectObject(pOldBitmapImage);
}

void TransparentBitmap::Draw(CDC *pDC, int x, int y)
{
	BITMAP bm;
	GetObject(sizeof(BITMAP), &bm);

	CPoint size(bm.bmWidth, bm.bmHeight);
	CPoint org(0, 0);

	m_MemDC.BitBlt(org.x, org.y, size.x, size.y, pDC, x, y, SRCCOPY);
	m_MemDC.BitBlt(org.x, org.y, size.x, size.y, &m_AndDC, org.x, org.y, SRCAND);
	m_MemDC.BitBlt(org.x, org.y, size.x, size.y, &m_XorDC, org.x, org.y, SRCINVERT);

	pDC->BitBlt(x, y, size.x, size.y, &m_MemDC, org.x, org.y, SRCCOPY);
}

void TransparentBitmap::Cleanup()
{
	if (m_pOldBitmapXor != NULL) {
		m_XorDC.SelectObject(m_pOldBitmapXor);
		m_pOldBitmapXor = NULL;
	}
	m_XorDC.DeleteDC();

	if (m_pOldBitmapAnd != NULL) {
		m_AndDC.SelectObject(m_pOldBitmapAnd);
		m_pOldBitmapAnd = NULL;
	}
	m_AndDC.DeleteDC();

	if (m_pOldBitmapMem != NULL) {
		m_MemDC.SelectObject(m_pOldBitmapMem);
		m_pOldBitmapMem = NULL;
	}
	m_MemDC.DeleteDC();
}
