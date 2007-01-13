/*--------------------------------------
	Module:	PREFDLG.H
	Author:	Thomas A. Rieck
	Date:	06/23/97
----------------------------------------*/

#ifndef __PREFDLG_H__
#define __PREFDLG_H__

#include <afxwin.h>
#include "WysApp.h"
#include "resource.h"

class CPrefDlg : public CDialog
{
private:
	CButton*	m_pCheck;
	CEdit*		m_pLogPath;
	CWysApp*	m_pApp;
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnableLogging();
	afx_msg void OnOK();
	enum { IDD = IDD_PREFERENCES };
public:
	CPrefDlg(CWnd* pParentWnd = NULL);
	~CPrefDlg();

	DECLARE_MESSAGE_MAP()
};

#endif // __PREFDLG_H___