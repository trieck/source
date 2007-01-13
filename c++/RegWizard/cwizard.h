// CWIZARD.H

#ifndef __CWIZARD_H__
#define __CWIZARD_H__

#include "stdafx.h"

// structure for holding data
typedef struct tagREGINFO
{
   CString  sServerName;
   CString  sDatabaseName;
   CString  sReportPath;
}
REGINFO;

class CWizard : public CPropertySheet
{
public:
	REGINFO m_rgi;
	// Construction
	CWizard(UINT nIDCaption, CWnd* pParentWnd = NULL, 
      UINT iSelectPage = 0);
	CWizard(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, 
      UINT iSelectPage = 0);
	virtual ~CWizard();
	int GetRegInfo();
	int SetRegInfo();
protected:
	// message handlers
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP();
};

#endif // __CWIZARD_H__