#if !defined(AFX_TOOLBOXDLG_H__ED618293_00F0_11D3_822F_00207812120D__INCLUDED_)
#define AFX_TOOLBOXDLG_H__ED618293_00F0_11D3_822F_00207812120D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolboxDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ToolboxDlg dialog

class ToolboxDlg : public CDialog
{
// Construction
public:
	ToolboxDlg(CWnd * pParent = NULL);   // standard constructor
	~ToolboxDlg();

// Dialog Data
	//{{AFX_DATA(ToolboxDlg)
	enum { IDD = IDD_TOOLBOX };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ToolboxDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void LoadImages();
	void SetActiveButton();
	void SetTool(UINT);

	// Generated message map functions
	//{{AFX_MSG(ToolboxDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnQuarterNote();
	afx_msg void OnEigthNote();
	afx_msg void OnSixteenthNote();
	afx_msg void OnThirtysecondNote();
	afx_msg void OnHalfNote();
	afx_msg void OnWholeNote();
	afx_msg void OnSharpen();
	afx_msg void OnFlatten();
	afx_msg void OnNaturalize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBOXDLG_H__ED618293_00F0_11D3_822F_00207812120D__INCLUDED_)

