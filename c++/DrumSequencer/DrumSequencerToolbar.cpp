// DrumSequencerToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "DrumSequencerToolbar.h"

IMPLEMENT_DYNAMIC(DrumSequencerToolbar, CMFCToolBar)

DrumSequencerToolbar::DrumSequencerToolbar()
{
}

DrumSequencerToolbar::~DrumSequencerToolbar()
{
}

void DrumSequencerToolbar::OnAfterFloat()
{
    auto pWnd = AfxGetMainWnd();
    if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) {
        dynamic_cast<CFrameWnd*>(pWnd)->RecalcLayout();
    }

    CMFCToolBar::OnAfterFloat();
}

void DrumSequencerToolbar::OnAfterDock(CBasePane* pBar, LPCRECT lpRect, AFX_DOCK_METHOD dockMethod)
{
    auto pWnd = AfxGetMainWnd();
    if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) {
        dynamic_cast<CFrameWnd*>(pWnd)->RecalcLayout();
    }

    CMFCToolBar::OnAfterDock(pBar, lpRect, dockMethod);
}

BEGIN_MESSAGE_MAP(DrumSequencerToolbar, CMFCToolBar)
END_MESSAGE_MAP()
