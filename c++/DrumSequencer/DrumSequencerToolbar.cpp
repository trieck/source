// DrumSequencerToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "DrumSequencer.h"
#include "DrumSequencerToolbar.h"


// DrumSequencerToolbar

IMPLEMENT_DYNAMIC(DrumSequencerToolbar, CMFCToolBar)

DrumSequencerToolbar::DrumSequencerToolbar()
{

}

DrumSequencerToolbar::~DrumSequencerToolbar()
{
}

void DrumSequencerToolbar::OnAfterFloat()
{
	CWnd *pWnd = AfxGetMainWnd();
	if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) {
		((CFrameWnd*)pWnd)->RecalcLayout();
	}

	CMFCToolBar::OnAfterFloat();
}

void DrumSequencerToolbar::OnAfterDock(CBasePane* pBar, LPCRECT lpRect, AFX_DOCK_METHOD dockMethod)
{
	CWnd *pWnd = AfxGetMainWnd();
	if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) {
		((CFrameWnd*)pWnd)->RecalcLayout();
	}

	CMFCToolBar::OnAfterDock(pBar, lpRect, dockMethod);
}

BEGIN_MESSAGE_MAP(DrumSequencerToolbar, CMFCToolBar)
END_MESSAGE_MAP()



// DrumSequencerToolbar message handlers


