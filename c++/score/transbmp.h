///////////////////////////////////////////////////////////////////////
//
//	TRANSBMP.H : transparent bitmap
//
//	Copyright © 1999 Rieck Enterprises
//

#ifndef __TRANSBMP_H__
#define __TRANSBMP_H__

///////////////////////////////////////////////////////////////////////
class TransparentBitmap : public CBitmap
{
public:
	// Construction / Destruction
	TransparentBitmap(UINT, COLORREF);
	virtual ~TransparentBitmap();

	// Interface
	BOOL Initialize(CDC *);
	BOOL Render(CDC * pDC, int x, int y);

	// Implementation
protected:
	CDC m_MemDC;
	CDC m_AndDC;
	CDC m_XOrDC;
	CBitmap * m_pOldBitmapMem;
	CBitmap * m_pOldBitmapXor;
	CBitmap * m_pOldBitmapAnd;
	BOOL m_fInitialized;
	COLORREF m_transparent;
};

///////////////////////////////////////////////////////////////////////


#endif // __TRANSBMP_H__