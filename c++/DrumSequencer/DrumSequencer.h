
// DrumSequencer.h : main header file for the DrumSequencer application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "sequencer.h"

// CDrumSequencerApp:
// See DrumSequencer.cpp for the implementation of this class
//

class CDrumSequencerApp : public CWinAppEx {
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
	Sequencer m_sequencer;
public:
	virtual int ExitInstance();
	afx_msg void OnSequencerStop();
	BOOL Play(const Sequence & sequence);
	afx_msg void OnUpdateSequencerPlay(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSequencerStop(CCmdUI *pCmdUI);
};

extern CDrumSequencerApp theApp;
