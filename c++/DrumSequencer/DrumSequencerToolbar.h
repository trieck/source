#pragma once


// DrumSequencerToolbar

class DrumSequencerToolbar : public CMFCToolBar
{
    DECLARE_DYNAMIC(DrumSequencerToolbar)

public:
    DrumSequencerToolbar();
    virtual ~DrumSequencerToolbar();

    void OnAfterFloat() override;
protected:
    DECLARE_MESSAGE_MAP()
    void OnAfterDock(CBasePane* pBar, LPCRECT lpRect, AFX_DOCK_METHOD dockMethod) override;
};


