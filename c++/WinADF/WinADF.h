// WinADF.h : main header file for the WinADF application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// WinADFApp:
// See WinADF.cpp for the implementation of this class
//

class WinADFApp : public CWinApp
{
public:
	WinADFApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);

protected:
	CMultiDocTemplate *m_pFileViewTemplate;
public:
	void ShowFileView(CDocument *pDoc);
};

extern WinADFApp theApp;