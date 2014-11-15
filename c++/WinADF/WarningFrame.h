#pragma once

#include "adfwarn.h"

// WarningFrame frame

class WarningFrame : public CMDIChildWnd, public IADFWarningHandler {
    DECLARE_DYNCREATE(WarningFrame)
protected:
    WarningFrame();           // protected constructor used by dynamic creation
    virtual ~WarningFrame();

// Interface
public:

protected:
    DECLARE_MESSAGE_MAP()

// Overrides
    virtual void PostNcDestroy();
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    // IADFHandler methods
    virtual void handle(const string &s) const;

// Generated message map functions

    afx_msg void OnNcDestroy();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnClose();
    afx_msg void OnDestroy();
private:
    CListView *view;
};


