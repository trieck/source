// score.h : main header file for the SCORE application
//

#if !defined(AFX_SCORE_H__1FC3C624_FDCF_11D2_822C_00207812120D__INCLUDED_)
#define AFX_SCORE_H__1FC3C624_FDCF_11D2_822C_00207812120D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// ScoreApp:
// See score.cpp for the implementation of this class
//

class ScoreApp : public CWinApp
{
public:
	ScoreApp();
	~ScoreApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScoreApp)
public:
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
protected:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	BOOL Stop() const;
	BOOL PlayStaff(const Staff *);
	BOOL PlayMeasure(const Measure *);
	BOOL PlayNote(const Note *) const;
	BOOL ReleaseNote(const Note *) const;
	void PumpMessages();
	BOOL SetInstrument (BYTE b);
	BYTE GetInstrument() const {		return m_instrument;	}
	BOOL IsPlaying() const;

protected:
	//{{AFX_MSG(ScoreApp)
	afx_msg void OnAppAbout();
	afx_msg void OnSettings();
	afx_msg void OnStop();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	BOOL InitializeStream();
	void LoadSettings();
	void SaveSettings() const;

	MidiStream * m_pStream;     // MIDI output stream
	Sequencer * m_pSequencer;   // MIDI sequencer
	BYTE m_instrument;			// MIDI instrument
};

/////////////////////////////////////////////////////////////////////////////

// Global functions
CString GetRegValue(LPCTSTR, LPCTSTR);
LONG GetRegValue(LPCTSTR, LPCTSTR, LPDWORD);
LONG SetRegValue(LPCTSTR, LPCTSTR, LPCTSTR);
LONG SetRegValue(LPCTSTR, LPCTSTR, DWORD);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCORE_H__1FC3C624_FDCF_11D2_822C_00207812120D__INCLUDED_)

