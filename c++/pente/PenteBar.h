#pragma once

#include "CaptureBitmap.h"

/////////////////////////////////////////////////////////////////////////////
// PenteBar window

class PenteBar : public CStatusBar
{
// Construction
public:
    PenteBar();
// Attributes
public:
// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(PenteBar)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~PenteBar();
    // Generated message map functions
protected:
    //{{AFX_MSG(PenteBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnAppSettingChange(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
private:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    CaptureBitmap bmPlayerOne, bmPlayerTwo;
};

