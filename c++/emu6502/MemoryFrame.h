#pragma once


// MemoryFrame frame

class MemoryFrame : public CMiniFrameWnd {
	DECLARE_DYNCREATE(MemoryFrame)
protected:
	MemoryFrame();           // protected constructor used by dynamic creation
	virtual ~MemoryFrame();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:
	CStatusBar m_wndStatusBar;
};


