// CPAGETWO.H

#ifndef __CPAGETWO_H__
#define __CPAGETWO_H__

#include "stdafx.h"
#include "resource.h"

// CPropertyPage derived class
class CPageTwo : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageTwo);

public:
	CPageTwo();
	~CPageTwo();
protected:
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnInitDialog();
	
	// message handlers
	afx_msg void OnPaint();
private:
	enum {IDD = IDD_PAGETWO};
	
	DECLARE_MESSAGE_MAP();
};

#endif // __CPAGETWO_H__