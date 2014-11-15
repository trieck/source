#pragma once


// DisassemFrame frame

class DisassemFrame : public CMiniFrameWnd {
    DECLARE_DYNCREATE(DisassemFrame)
protected:
    DisassemFrame();           // protected constructor used by dynamic creation
    virtual ~DisassemFrame();

protected:
    DECLARE_MESSAGE_MAP()
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
    CStatusBar m_wndStatusBar;
};


