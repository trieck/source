// DrumSequencer.h : main header file for the DrumSequencer application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "sequencer.h"

// CDrumSequencerApp:
// See DrumSequencer.cpp for the implementation of this class
//

class CDrumSequencerApp : public CWinAppEx
{
public:
    CDrumSequencerApp();
    virtual ~CDrumSequencerApp() = default;

    // Overrides
    BOOL InitInstance() override;
    void SetTempo(short bpm);
    short Tempo() const;

    // Implementation
    UINT m_nAppLook{};
    BOOL m_bHiColorIcons{};

    void PreLoadState() override;
    void LoadCustomState() override;
    void SaveCustomState() override;

    afx_msg void OnAppAbout();
DECLARE_MESSAGE_MAP()
private:
    Sequencer m_sequencer;
public:
    int ExitInstance() override;
    BOOL Play(const Sequence& sequence);
    BOOL Stop();

    afx_msg void OnSequencerStop();
    afx_msg void OnUpdateSequencerPlay(CCmdUI* pCmdUI);
    afx_msg void OnUpdateSequencerStop(CCmdUI* pCmdUI);
};

extern CDrumSequencerApp theApp;
