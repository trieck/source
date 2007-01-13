#if !defined(AFX_LOGWND_H__D053A9C1_93FB_11D4_89F3_00E098787497__INCLUDED_)
#define AFX_LOGWND_H__D053A9C1_93FB_11D4_89F3_00E098787497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogWnd.h : header file
//
#include <afxcview.h>
/////////////////////////////////////////////////////////////////////////////
// LogWnd frame

class LogWnd : public CMiniFrameWnd
{
	DECLARE_DYNCREATE(LogWnd)
public:
	LogWnd();         
// Attributes
public:
// Operations
public:
	void logMessage(LPCTSTR message);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LogWnd)
	protected:
	virtual void PostNcDestroy();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~LogWnd();
	// Generated message map functions
	//{{AFX_MSG(LogWnd)
	afx_msg void OnNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CListView *view;
};
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_LOGWND_H__D053A9C1_93FB_11D4_89F3_00E098787497__INCLUDED_)
