#if !defined(AFX_SETTINGSDLG_H__AC1FFC61_9A43_11D1_B85E_0020781268A5__INCLUDED_)
#define AFX_SETTINGSDLG_H__AC1FFC61_9A43_11D1_B85E_0020781268A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SettingsDlg.h : header file
//

#include "MiscPage.h"
/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg

class CSettingsDlg : public CPropertySheet {
	DECLARE_DYNAMIC(CSettingsDlg)

// Construction
public:
	CSettingsDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSettingsDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDlg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSettingsDlg();

	VOID Init();
	// Generated message map functions
protected:
	VOID BuildPages();
	//{{AFX_MSG(CSettingsDlg)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	CMiscPage * m_pMiscPage;
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__AC1FFC61_9A43_11D1_B85E_0020781268A5__INCLUDED_)
