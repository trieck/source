#if !defined(AFX_COLORCHOOSERWND_H__D4BEA107_CC0D_411C_B4F2_3FD1E5E36997__INCLUDED_)
#define AFX_COLORCHOOSERWND_H__D4BEA107_CC0D_411C_B4F2_3FD1E5E36997__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorChooserWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ColorChooserWnd window

class ColorChooserWnd : public CWnd
{
// Construction
public:
	ColorChooserWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColorChooserWnd)
	public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF GetSelectedColor() const;
	virtual ~ColorChooserWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(ColorChooserWnd)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PaintBitmap();

	CRgn m_Region;
	CDC m_MemDC;
	CBitmap m_Bitmap;
	COLORREF m_Shadow, m_Hilight, m_BtnFace;
	CPoint m_ptSelected;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCHOOSERWND_H__D4BEA107_CC0D_411C_B4F2_3FD1E5E36997__INCLUDED_)
