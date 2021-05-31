// DrumSequencerMenubar.cpp : implementation file
//

#include "stdafx.h"
#include "DrumSequencerMenubar.h"

IMPLEMENT_DYNAMIC(DrumSequencerMenubar, CMFCMenuBar)

void DrumSequencerMenubar::OnAfterFloat()
{
    auto pWnd = AfxGetMainWnd();
    if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) {
        dynamic_cast<CFrameWnd*>(pWnd)->RecalcLayout();
    }

    CMFCMenuBar::OnAfterFloat();
}

void DrumSequencerMenubar::OnAfterDock(CBasePane* pBar, LPCRECT lpRect, AFX_DOCK_METHOD dockMethod)
{
    auto pWnd = AfxGetMainWnd();
    if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) {
        dynamic_cast<CFrameWnd*>(pWnd)->RecalcLayout();
    }

    CMFCMenuBar::OnAfterDock(pBar, lpRect, dockMethod);
}

BEGIN_MESSAGE_MAP(DrumSequencerMenubar, CMFCMenuBar)
END_MESSAGE_MAP()
