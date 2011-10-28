#pragma once


// DrumSequencerToolbar

class DrumSequencerToolbar : public CMFCToolBar
{
	DECLARE_DYNAMIC(DrumSequencerToolbar)

public:
	DrumSequencerToolbar();
	virtual ~DrumSequencerToolbar();

	virtual void OnAfterFloat();
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnAfterDock(CBasePane* pBar, LPCRECT lpRect, AFX_DOCK_METHOD dockMethod);
};


