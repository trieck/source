#pragma once


// DrumSequencerMenubar

class DrumSequencerMenubar : public CMFCMenuBar
{
    DECLARE_DYNAMIC(DrumSequencerMenubar)

public:
    DrumSequencerMenubar();
    virtual ~DrumSequencerMenubar();
    virtual void OnAfterFloat();
protected:
    DECLARE_MESSAGE_MAP()
    virtual void OnAfterDock(CBasePane* pBar, LPCRECT lpRect, AFX_DOCK_METHOD dockMethod);
};


