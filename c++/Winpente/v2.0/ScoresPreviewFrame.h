#if !defined(AFX_SCORESPREVIEWFRAME_H__6C091319_9B34_11D1_B85F_0020781268A5__INCLUDED_)
#define AFX_SCORESPREVIEWFRAME_H__6C091319_9B34_11D1_B85F_0020781268A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScoresPreviewFrame.h : header file
//

#include "ScoresPreviewWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CScoresPreviewFrame frame

class CScoresPreviewFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CScoresPreviewFrame)
public:
	CScoresPreviewFrame();         
	virtual ~CScoresPreviewFrame();

// Attributes
public:

// Operations
public:
	CStatusBar * GetStatusBar();
	inline CDC* GetPrinterDC() { return m_pPrinterDC; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScoresPreviewFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStatusBar			m_StatusBar;
	CScoresPreviewWnd * m_pClientWnd;
	CButton *			m_pPrintButton;
	CDC	*				m_pPrinterDC;

	// Generated message map functions
	//{{AFX_MSG(CScoresPreviewFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCORESPREVIEWFRAME_H__6C091319_9B34_11D1_B85F_0020781268A5__INCLUDED_)
