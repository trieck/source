#if !defined(AFX_SCORESDLG_H__6E47350D_94E9_11D1_B85E_0020781268A5__INCLUDED_)
#define AFX_SCORESDLG_H__6E47350D_94E9_11D1_B85E_0020781268A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScoresDlg.h : header file
//
#include "ScoresPreviewFrame.h"
#include "Scores.h"
#include "ResDll\resource.h"
/////////////////////////////////////////////////////////////////////////////
// CScoresDlg dialog

class CScoresDlg : public CDialog
{
// Construction
public:
	CScoresDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScoresDlg();

	static int CALLBACK CompareFunc (LPARAM, LPARAM, LPARAM);

// Dialog Data
	//{{AFX_DATA(CScoresDlg)
	enum { IDD = IDD_SCORES};
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScoresDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	VOID	InsertItems();
	VOID	InsertHeaders();

	inline	CListCtrl& GetListCtrl(){ return * (CListCtrl*) GetDlgItem(IDC_SCORES); }

	CScores *				m_pScores;
	CScoresPreviewFrame *	m_pFrame;
	
	VOID	afx_msg	OnPreview();

	// Generated message map functions
	//{{AFX_MSG(CScoresDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCORESDLG_H__6E47350D_94E9_11D1_B85E_0020781268A5__INCLUDED_)
