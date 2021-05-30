#pragma once


// DrumSequencerMenubar

class DrumSequencerMenubar : public CMFCMenuBar
{
    DECLARE_DYNAMIC(DrumSequencerMenubar)

public:
    DrumSequencerMenubar();
    virtual ~DrumSequencerMenubar();
    void OnAfterFloat() override;
protected:
    DECLARE_MESSAGE_MAP()
    void OnAfterDock(CBasePane* pBar, LPCRECT lpRect, AFX_DOCK_METHOD dockMethod) override;
};


