#if !defined(AFX_OPTDLG_H__CC444281_972F_11D4_89FA_00E098787497__INCLUDED_)
#define AFX_OPTDLG_H__CC444281_972F_11D4_89FA_00E098787497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// optdlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// OptionDlg dialog

class OptionDlg : public CDialog
{
// Construction
public:
	OptionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(OptionDlg)
	enum { IDD = IDD_OPTIONS };
	int		m_TwoPlayerGame;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(OptionDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_OPTDLG_H__CC444281_972F_11D4_89FA_00E098787497__INCLUDED_)
