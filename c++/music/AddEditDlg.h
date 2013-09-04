#if !defined(AFX_ADDEDITDLG_H__B9EA57E3_5994_11D4_89F0_00E098787497__INCLUDED_)

#define AFX_ADDEDITDLG_H__B9EA57E3_5994_11D4_89F0_00E098787497__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000

// AddEditDlg.h : header file

//



#include "musicDoc.h"

#include "musicView.h"



/////////////////////////////////////////////////////////////////////////////

// AddEditDlg dialog



class AddEditDlg : public CDialog

{

public:

	enum Mode {

	    addMode,

	    editMode

	};

// Construction

	AddEditDlg(Mode M, LPRECORD rec, CWnd* pParent = NULL);   // standard constructor



// Dialog Data

	//{{AFX_DATA(AddEditDlg)

	enum { IDD = IDD_ADDEDITRECORD };

	CString	m_Album;

	CString	m_Artist;

	CString	m_Label;

	UINT	m_Year;

	//}}AFX_DATA





// Overrides

	// ClassWizard generated virtual function overrides

	//{{AFX_VIRTUAL(AddEditDlg)

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//}}AFX_VIRTUAL



// Implementation

protected:



	// Generated message map functions

	//{{AFX_MSG(AddEditDlg)

	virtual BOOL OnInitDialog();

	afx_msg void OnNewArtist();

	virtual void OnOK();

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:

	Mode _mode;

	LPRECORD _rec;

};



//{{AFX_INSERT_LOCATION}}

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



#endif // !defined(AFX_ADDEDITDLG_H__B9EA57E3_5994_11D4_89F0_00E098787497__INCLUDED_)

