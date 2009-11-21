#if !defined(AFX_TEMPODLG_H__12A6C663_1546_11D3_823A_00207812120D__INCLUDED_)
#define AFX_TEMPODLG_H__12A6C663_1546_11D3_823A_00207812120D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TempoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TempoDlg dialog

class TempoDlg : public CDialog
{
// Construction
public:
	TempoDlg(Measure * pMeasure, CWnd* pParent = NULL);

protected:
// Dialog Data
	//{{AFX_DATA(TempoDlg)
	enum { IDD = IDD_TEMPO };
	CSpinButtonCtrl	m_TempoSpin;
	UINT m_Tempo;
	BOOL	m_ApplyForward;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TempoDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	Measure * m_pMeasure;
	void ApplyForward() const;

	// Generated message map functions
	//{{AFX_MSG(TempoDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPODLG_H__12A6C663_1546_11D3_823A_00207812120D__INCLUDED_)

