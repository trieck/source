// DrumSequencerMenubar.cpp : implementation file
//

#include "stdafx.h"
#include "DrumSequencerMenubar.h"


// DrumSequencerMenubar

IMPLEMENT_DYNAMIC(DrumSequencerMenubar, CMFCMenuBar)

DrumSequencerMenubar::DrumSequencerMenubar()
{

}

DrumSequencerMenubar::~DrumSequencerMenubar()
{
}

void DrumSequencerMenubar::OnAfterFloat()
{
    CWnd *pWnd = AfxGetMainWnd();
    if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) {
        ((CFrameWnd*)pWnd)->RecalcLayout();
    }

    CMFCMenuBar::OnAfterFloat();
}

void DrumSequencerMenubar::OnAfterDock(CBasePane* pBar, LPCRECT lpRect, AFX_DOCK_METHOD dockMethod)
{
    CWnd *pWnd = AfxGetMainWnd();
    if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) {
        ((CFrameWnd*)pWnd)->RecalcLayout();
    }

    CMFCMenuBar::OnAfterDock(pBar, lpRect, dockMethod);
}

BEGIN_MESSAGE_MAP(DrumSequencerMenubar, CMFCMenuBar)
END_MESSAGE_MAP()



// DrumSequencerMenubar message handlers


