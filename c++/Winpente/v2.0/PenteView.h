/*---------------------------------------
	Module Name	:	PenteView.h
	Author		:	Thomas A. Rieck 
	Purpose		:	Pente View
					declarations
	Date		:	08/21/1997
---------------------------------------*/

#ifndef __PENTEVIEW_H__
#define __PENTEVIEW_H__

#include "MainFrame.h"
#include "PenteDoc.h"
#include "CustBmp.h"

///////////////////////////////////////////////////////////////////
// The CPenteView view class

// forward declarations

class CPenteView : public CView
{
protected:
	CPenteView();
	DECLARE_DYNCREATE(CPenteView)

// Attributes
public:
	CPenteDoc* GetDocument();

	inline	INT		GetBackgroundRes(){return m_nBackground;}
	VOID			SetBackgroundBitmap(INT);
protected:
	VOID 			DrawGrid(CPenteDoc*, CDC*);   
// Overrides
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT&);
// Implementation
protected:
	CMainFrame*		m_pMainFrame;
	CCustomBitmap*	m_pCustomBitmap;
	INT				m_nBackground;
	HBITMAP			m_hBitmap;
	HPALETTE		m_hPalette;
public:
	virtual ~CPenteView();

protected:
	// message map entries
	afx_msg	INT		OnCreate(LPCREATESTRUCT);
	afx_msg VOID	OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL	OnQueryNewPalette();
	afx_msg VOID	OnPaletteChanged(CWnd* pFocusWnd);
	DECLARE_MESSAGE_MAP()
};       

inline CPenteDoc* CPenteView::GetDocument()
{ 
   return (CPenteDoc*)m_pDocument; 
}

///////////////////////////////////////////////////////////////////
  
#endif	// __PENTEVIEW_H__