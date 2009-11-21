/*--------------------------------------
	Module:	CONNDLG.H
	Author:	Thomas A. Rieck
	Date:	06/22/97
----------------------------------------*/

#ifndef __CONNDLG_H__
#define __CONNDLG_H__

#include <afxwin.h>
#include "resource.h"

class CConnDlg : public CDialog {
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnRefresh();
	afx_msg void OnKillSocket();
	enum { IDD = IDD_ACTIVECONN };
public:
	CConnDlg(CWnd* pParentWnd = NULL);
	~CConnDlg();

	DECLARE_MESSAGE_MAP()
};
#endif // __CONNDLG_H__