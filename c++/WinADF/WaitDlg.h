#pragma once
#include "afxcmn.h"
#include "NewVolume.h"

// WaitDlg dialog

class WaitDlg : public CDialog
{
	DECLARE_DYNAMIC(WaitDlg)
private:
	WaitDlg(CWnd* pParent = NULL);   // standard constructor
public:
	virtual ~WaitDlg();

// Dialog Data
	enum { IDD = IDD_WAIT };

	static WaitDlg *newInstance(NewVolumeDlg *pParent);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CProgressCtrl m_progress;
protected:	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNcDestroy();
protected:
	virtual void OnCancel();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	UINT nTimer;
	bool done;

	enum { EVENT_ID = 0xFFFFFFFF };
};
