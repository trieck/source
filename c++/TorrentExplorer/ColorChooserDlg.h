#if !defined(AFX_COLORCHOOSERDLG_H__D36C571E_E7DC_401A_8F0F_79EC8FE773A3__INCLUDED_)
#define AFX_COLORCHOOSERDLG_H__D36C571E_E7DC_401A_8F0F_79EC8FE773A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorChooserDlg.h : header file
//

#include "ColorChooserWnd.h"

/////////////////////////////////////////////////////////////////////////////
// ColorChooserDlg dialog

class ColorChooserDlg : public CDialog {
// Construction
public:
	COLORREF GetSelectedColor() const;
	ColorChooserDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ColorChooserDlg)
	enum { IDD = IDD_COLOR_CHOOSER };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColorChooserDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ColorChooserDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ColorChooserWnd m_ColorsWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCHOOSERDLG_H__D36C571E_E7DC_401A_8F0F_79EC8FE773A3__INCLUDED_)
