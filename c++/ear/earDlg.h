// earDlg.h : header file
//

#if !defined(AFX_EARDLG_H__5C739467_F614_11D3_895D_000000000000__INCLUDED_)
#define AFX_EARDLG_H__5C739467_F614_11D3_895D_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "interval.h"

/////////////////////////////////////////////////////////////////////////////
// EarDlg dialog

class EarDlg : public CDialog
{
// Construction
public:
	EarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(EarDlg)
	enum { IDD = IDD_EAR_DIALOG };
	int		m_Interval;
	CString	m_Output;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CreateInterval();

	// Generated message map functions
	//{{AFX_MSG(EarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSettings();
	afx_msg void OnListen();
	virtual void OnCancel();
	afx_msg void OnEnter();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	HICON m_hIcon;
	MidiBuffer m_buffer;
	Interval m_MidiInterval;
	int m_correct;
	int m_incorrect;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EARDLG_H__5C739467_F614_11D3_895D_000000000000__INCLUDED_)

