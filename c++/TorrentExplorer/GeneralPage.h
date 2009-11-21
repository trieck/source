#if !defined(AFX_GENERALPAGE_H__2B2AD725_5C99_4DED_8AD2_337FCEA94019__INCLUDED_)
#define AFX_GENERALPAGE_H__2B2AD725_5C99_4DED_8AD2_337FCEA94019__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GeneralPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GeneralPage dialog

class GeneralPage : public CPropertyPage {
	DECLARE_DYNCREATE(GeneralPage)

// Construction
public:
	GeneralPage();
	~GeneralPage();

// Dialog Data
	//{{AFX_DATA(GeneralPage)
	enum { IDD = IDD_GENERAL_PAGE };
	BOOL	m_SaveWin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(GeneralPage)
public:
	virtual void OnOK();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(GeneralPage)
	afx_msg void OnSaveWin();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	BOOL m_Dirty;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERALPAGE_H__2B2AD725_5C99_4DED_8AD2_337FCEA94019__INCLUDED_)
