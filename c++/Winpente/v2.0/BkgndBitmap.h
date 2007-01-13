// BkgndBitmap.h: interface for the CBkgndBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BKGNDBITMAP_H__C3AE75C2_90D8_11D1_B85E_0020781268A5__INCLUDED_)
#define AFX_BKGNDBITMAP_H__C3AE75C2_90D8_11D1_B85E_0020781268A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "stdafx.h"
#include "CustBmp.h"

class CBkgndBitmap : public CWnd  
{
public:
	CBkgndBitmap(HBITMAP, HPALETTE, UINT);
	virtual ~CBkgndBitmap();

	inline VOID Frame(BOOL fFrameBitmap) { m_fFrameBitmap = fFrameBitmap; }
	inline UINT	GetResID() { return m_ResID; }
protected:
	// Message Handlers
	afx_msg VOID	OnPaint();
	afx_msg INT		OnCreate(LPCREATESTRUCT);
	afx_msg	VOID	OnLButtonDown(UINT nFlags, CPoint point);

	CCustomBitmap * m_pCustomBitmap;

	BOOL		m_fFrameBitmap;
	HBITMAP		m_hBitmap;
	HPALETTE	m_hPalette;
	UINT		m_ResID;

	VOID FrameBitmap(CDC*);

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_BKGNDBITMAP_H__C3AE75C2_90D8_11D1_B85E_0020781268A5__INCLUDED_)
