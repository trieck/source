#pragma once

#include "Sequence.h"

class BeatGrid {
public:
	BeatGrid(void);
	~BeatGrid(void);
	void Draw(CDC* pDC);

	enum { CX_SUB = 30 };		// width of each subdivision
	enum { CY_SUB = 20 };		// height of subdivision
	enum { CX_OFFSET = 80 };	// horz. border
	enum { CY_OFFSET = 20 };	// vert. border

	enum { CX_GRID = CX_SUB * Sequence::NSUBS };	// width of grid
	enum { CY_GRID = CY_SUB * Sequence::NINSTRUMENTS };	// height of grid

private:

	CPen m_thinPen, m_thickPen;
	CBrush m_bkgBrush;
	CRgn m_Region;
	CDC m_MemDC;
	CBitmap m_Bitmap;

public:
	void CreateBitmap(void);
	void PaintBitmap(void);
	static void GetBoundingRect(CRect & rc);
	static void GetDimensions(CRect &rc);
	static COLORREF GetInstColor(int i);
	BOOL PointOnGrid(const CPoint &pt);
	CPoint GetSubdivision(const CPoint& pt);
	void GetBeatRect(int x, int y, CRect& rc);
};

