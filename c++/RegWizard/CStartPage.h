// CSTARTPAGE.H

#ifndef __CSTARTPAGE_H__
#define __CSTARTPAGE_H__

#include "stdafx.h"
#include "resource.h"

// CPropertyPage derived class
class CStartPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CStartPage);

public:
	CStartPage();
	~CStartPage();
protected:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnInitDialog();
	// message handlers
	afx_msg void OnPaint();
private:
	CFont m_fntTitle;
	enum {IDD = IDD_STARTPAGE};
	DECLARE_MESSAGE_MAP();
};

#endif // __CSTARTPAGE_H__