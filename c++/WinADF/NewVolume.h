#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// NewVolume dialog

class NewVolumeDlg : public CDialog
{
	DECLARE_DYNAMIC(NewVolumeDlg)

public:
	NewVolumeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~NewVolumeDlg();

// Dialog Data
	enum { IDD = IDD_NEW_VOLUME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnTypeADF();
	afx_msg void OnTypeHDF();
	afx_msg void OnOK();
	CStatic m_PresetText;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCustomSize();
	afx_msg void OnPresetSize();
	afx_msg void OnDirCache();
public:
	CEdit m_label;
	CButton m_DiskType;
	CButton m_HighDensity;
	CSliderCtrl m_HDFSizeSlider;

	CButton m_PresetSize;
	CButton m_CustomSize;
	CEdit m_CustomSizeEdit;

	CButton m_FFS;
	CButton m_Intl;
	CButton m_dircache;
	CButton m_boot;
	CEdit m_path;
protected:
};
