#pragma once

#include "SettingsBar.h"

// SettingsPane

class SettingsPane : public CDockablePane {
    DECLARE_DYNAMIC(SettingsPane)

public:
    SettingsPane();
    virtual ~SettingsPane();

protected:
    SettingsBar m_bar;
public:
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
    virtual BOOL OnBeforeFloat(CRect& rectFloat, AFX_DOCK_METHOD dockMethod);
};


