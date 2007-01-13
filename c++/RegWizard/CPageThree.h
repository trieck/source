// CPAGETHREE.H

#ifndef __CPageThree_H__
#define __CPageThree_H__

#include "stdafx.h"
#include "resource.h"

// CPropertyPage derived class
class CPageThree : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageThree);

public:
	CPageThree();
	~CPageThree();
	CProgressCtrl* m_pProgress;
protected:
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
	virtual BOOL OnInitDialog();
	// message handlers
	afx_msg void OnPaint();
private:
	enum {IDD = IDD_PAGETHREE};
		
	DECLARE_MESSAGE_MAP();
};

#endif // __CPAGETHREE_H__