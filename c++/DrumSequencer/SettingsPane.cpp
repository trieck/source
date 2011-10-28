// SettingsPane.cpp : implementation file
//

#include "stdafx.h"
#include "DrumSequencer.h"
#include "SettingsPane.h"

// SettingsPane

IMPLEMENT_DYNAMIC(SettingsPane, CDockablePane)

SettingsPane::SettingsPane()
{

}

SettingsPane::~SettingsPane()
{
}
BEGIN_MESSAGE_MAP(SettingsPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int SettingsPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_bar.Create(this, IDD_SETTINGS, WS_CHILD | WS_VISIBLE, ID_SETTINGS_BAR)) {
		TRACE0("Unable to create settings bar.\n");
		return -1;
	}

	SetPaneStyle(0);

	return 0;
}

void SettingsPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_bar.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL SettingsPane::OnBeforeFloat(CRect& rectFloat, AFX_DOCK_METHOD dockMethod)
{
	return FALSE;
}