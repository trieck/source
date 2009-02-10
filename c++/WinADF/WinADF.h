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
	afx_msg void OnFileNew();

	DECLARE_MESSAGE_MAP()
	virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);

protected:
	CMultiDocTemplate *m_pTextFileViewTemplate;
	CMultiDocTemplate *m_pBinaryFileViewTemplate;
public:
	void ShowTextFileView(CDocument *pDoc);
	void ShowBinaryFileView(CDocument *pDoc);
};

extern WinADFApp theApp;

// utility functions
string comma(uint64_t i);
CString LastError();
CDocument *MDIGetActiveDoc();