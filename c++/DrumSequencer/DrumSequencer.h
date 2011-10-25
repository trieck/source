
// DrumSequencer.h : main header file for the DrumSequencer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "midistream.h"

// CDrumSequencerApp:
// See DrumSequencer.cpp for the implementation of this class
//

class CDrumSequencerApp : public CWinAppEx
{
public:
	CDrumSequencerApp();
	virtual ~CDrumSequencerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
private:
	MidiStream *m_pStream;
public:
	virtual int ExitInstance();
	BOOL InitializeStream(void);
	afx_msg void OnSequencerPlay();
	afx_msg void OnSequencerStop();
};

extern CDrumSequencerApp theApp;
