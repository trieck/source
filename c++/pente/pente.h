// pente.h : main header file for the PENTE application
//
#if !defined(AFX_PENTE_H__84460ED6_8E6D_11D4_9013_00010275679A__INCLUDED_)
#define AFX_PENTE_H__84460ED6_8E6D_11D4_9013_00010275679A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "LogWnd.h"
/////////////////////////////////////////////////////////////////////////////
// PenteApp:
// See pente.cpp for the implementation of this class
//

class PenteApp : public CWinApp
{
public:
	PenteApp();
	virtual ~PenteApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PenteApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	LogWnd *getLogWindow();
	bool isTwoPlayerGame() const;
	void setTwoPlayerGame(bool bTwoPlayerGame);
// Implementation
	//{{AFX_MSG(PenteApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnShowlog();
	afx_msg void OnOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void createLogWnd();
	LogWnd *logWnd;
	bool twoPlayerGame;
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
inline LogWnd *PenteApp::getLogWindow() {
	return logWnd;
}
/////////////////////////////////////////////////////////////////////////////
inline bool PenteApp::isTwoPlayerGame() const {
	return twoPlayerGame;
}
/////////////////////////////////////////////////////////////////////////////
inline void PenteApp::setTwoPlayerGame(bool bTwoPlayerGame) {
	twoPlayerGame = bTwoPlayerGame;
}
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_PENTE_H__84460ED6_8E6D_11D4_9013_00010275679A__INCLUDED_)
