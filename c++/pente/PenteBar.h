#if !defined(AFX_PENTEBAR_H__AEE839F5_92F3_11D4_9015_00010275679A__INCLUDED_)
#define AFX_PENTEBAR_H__AEE839F5_92F3_11D4_9015_00010275679A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PenteBar.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// PenteBar window

class PenteBar : public CStatusBar
{
// Construction
public:
	PenteBar();
// Attributes
public:
// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PenteBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~PenteBar();
	// Generated message map functions
protected:
	//{{AFX_MSG(PenteBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	CBitmap bmPlayerOne, bmPlayerTwo;
	CImageList imageList;
};
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_PENTEBAR_H__AEE839F5_92F3_11D4_9015_00010275679A__INCLUDED_)
