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
//	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
};


