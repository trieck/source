#if !defined(AFX_BACKENDSVIEW_H__C69581FF_2545_4055_9079_D5F1A922C56F__INCLUDED_)
#define AFX_BACKENDSVIEW_H__C69581FF_2545_4055_9079_D5F1A922C56F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackendsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BackendsView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class BackendsView : public CFormView
{
protected:
	BackendsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(BackendsView)

// Form Data
public:
	//{{AFX_DATA(BackendsView)
	enum { IDD = IDD_CONFIG_VIEW };
	CListCtrl	m_ProductList;
	CString	m_osversion;
	CString	m_reposCount;
	CString	m_FileCache;
	CString	m_CompilerVersion;
	CString	m_rawCount;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BackendsView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~BackendsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(BackendsView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InsertHeaders();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKENDSVIEW_H__C69581FF_2545_4055_9079_D5F1A922C56F__INCLUDED_)
