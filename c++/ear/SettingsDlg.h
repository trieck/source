#if !defined(AFX_SETTINGSDLG_H__D3D47E91_F6F8_11D3_8960_000000000000__INCLUDED_)
#define AFX_SETTINGSDLG_H__D3D47E91_F6F8_11D3_8960_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SettingsDlg dialog

class SettingsDlg : public CDialog {
// Construction
public:
	SettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SettingsDlg)
	enum { IDD = IDD_SETTINGS };
	BOOL	m_Fifths;
	BOOL	m_Fourths;
	BOOL	m_Octaves;
	BOOL	m_Seconds;
	BOOL	m_Sevenths;
	BOOL	m_Sixths;
	BOOL	m_Thirds;
	int		m_instrument;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SettingsDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void BuildInstruments();
	void SetIntervals();

	// Generated message map functions
	//{{AFX_MSG(SettingsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__D3D47E91_F6F8_11D3_8960_000000000000__INCLUDED_)

