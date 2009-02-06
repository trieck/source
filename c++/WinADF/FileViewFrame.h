#pragma once


// FileViewFrame frame

class FileViewFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(FileViewFrame)
protected:
	FileViewFrame();           // protected constructor used by dynamic creation
	virtual ~FileViewFrame();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	CStatusBar  m_wndStatusBar;
public:
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
protected:
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
};


