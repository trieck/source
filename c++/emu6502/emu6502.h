// emu6502.h : main header file for the EMU6502 application
//

#if !defined(AFX_EMU6502_H__70EF8546_8FB7_452B_82BA_F4FC0EF5F5F9__INCLUDED_)
#define AFX_EMU6502_H__70EF8546_8FB7_452B_82BA_F4FC0EF5F5F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Emu6502App:
// See emu6502.cpp for the implementation of this class
//

class Emu6502App : public CWinApp
{
public:
	Emu6502App();

// Interface
	void RegisterConstruct(int id, CWnd *pWnd);
	void RegisterDestruct(int id);
	CWnd *GetState(int id);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Emu6502App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(Emu6502App)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMap<int, int, CWnd*, CWnd*> states;
};


/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Global Helper Functions
BOOL IsHexChar(char c);
CString ByteToHex(BYTE b);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMU6502_H__70EF8546_8FB7_452B_82BA_F4FC0EF5F5F9__INCLUDED_)
