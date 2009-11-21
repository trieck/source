// REGWIZARD.H

#ifndef __REGWIZARD_H__
#define __REGWIZARD_H__

#include "stdafx.h"
#include "resource.h"
#include "cwizard.h"
#include "cstartpage.h"
#include "cpagetwo.h"
#include "cpagethree.h"

// CWinApp derived class
class CRegWizApp : public CWinApp {
public:
	virtual BOOL InitInstance();
	CRegWizApp(LPCTSTR lpszAppName = NULL);
	~CRegWizApp();
private:
	void CreateWizard();
	CWizard* m_pWizard;
	CStartPage* m_pStartPage;
	CPageTwo* m_pPageTwo;
	CPageThree* m_pPageThree;
};

#endif // __REGWIZARD_H__