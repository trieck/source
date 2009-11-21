#if !defined(AFX_SETTINGSDLG_H__AD0F41F3_FDD2_11D2_822C_00207812120D__INCLUDED_)
#define AFX_SETTINGSDLG_H__AD0F41F3_FDD2_11D2_822C_00207812120D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SettingsDlg dialog

class SettingsDlg : public CDialog
{
// Construction
public:
	SettingsDlg(CWnd* pParent = NULL);   // standard constructor

protected:
// Dialog Data
	//{{AFX_DATA(SettingsDlg)
	enum { IDD = IDD_SETTINGS };
	CComboBox	m_OutputDevices;
	CComboBox	m_InputDevices;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SettingsDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void BuildDevices();

	// Generated message map functions
	//{{AFX_MSG(SettingsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__AD0F41F3_FDD2_11D2_822C_00207812120D__INCLUDED_)

