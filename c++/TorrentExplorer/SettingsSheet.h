#if !defined(AFX_SETTINGSSHEET_H__9D82D08B_33EC_46CB_BBDA_07551BBEA66D__INCLUDED_)
#define AFX_SETTINGSSHEET_H__9D82D08B_33EC_46CB_BBDA_07551BBEA66D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsSheet.h : header file
//

#include "GeneralPage.h"
#include "ColorsPage.h"

/////////////////////////////////////////////////////////////////////////////
// SettingsSheet

class SettingsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(SettingsSheet)

// Construction
public:
	SettingsSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	SettingsSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SettingsSheet)
	virtual void BuildPropPageArray();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~SettingsSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(SettingsSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ColorsPage * m_pColorsPage;
	GeneralPage *m_pGeneralPage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSSHEET_H__9D82D08B_33EC_46CB_BBDA_07551BBEA66D__INCLUDED_)
