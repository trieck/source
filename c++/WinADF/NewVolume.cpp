// NewVolume.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "NewVolume.h"
#include "WaitDlg.h"

// NewVolumeDlg dialog

IMPLEMENT_DYNAMIC(NewVolumeDlg, CDialog)

NewVolumeDlg::NewVolumeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(NewVolumeDlg::IDD, pParent)
{

}

NewVolumeDlg::~NewVolumeDlg()
{
}

void NewVolumeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TYPE_ADF, m_DiskType);
	DDX_Control(pDX, IDC_CHK_HIGHDENSITY, m_HighDensity);
	DDX_Control(pDX, IDC_RD_PRESET, m_PresetSize);
	DDX_Control(pDX, IDC_RD_CUSTOM, m_CustomSize);
	DDX_Control(pDX, IDC_SL_PRESET, m_HDFSizeSlider);
	DDX_Control(pDX, IDC_E_CUSTOM, m_CustomSizeEdit);
	DDX_Control(pDX, IDC_CHK_FFS, m_FFS);
	DDX_Control(pDX, IDC_CHK_INTL, m_Intl);
	DDX_Control(pDX, IDC_CHK_DIRCACHE, m_dircache);
	DDX_Control(pDX, IDC_CHK_BOOT, m_boot);
	DDX_Control(pDX, IDC_E_PATH, m_path);
	DDX_Control(pDX, IDC_ST_PRESET, m_PresetText);
	DDX_Control(pDX, IDC_E_LABEL, m_label);
}

BEGIN_MESSAGE_MAP(NewVolumeDlg, CDialog)
	ON_BN_CLICKED(IDC_BROWSE, &NewVolumeDlg::OnBrowse)
	ON_BN_CLICKED(IDC_TYPE_ADF, &NewVolumeDlg::OnTypeADF)
	ON_BN_CLICKED(IDC_TYPE_HDF, &NewVolumeDlg::OnTypeHDF)
	ON_BN_CLICKED(IDOK, &NewVolumeDlg::OnOK)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RD_CUSTOM, &NewVolumeDlg::OnCustomSize)
	ON_BN_CLICKED(IDC_RD_PRESET, &NewVolumeDlg::OnPresetSize)
	ON_BN_CLICKED(IDC_CHK_DIRCACHE, &NewVolumeDlg::OnDirCache)
END_MESSAGE_MAP()

void NewVolumeDlg::OnBrowse()
{
	static TCHAR BASED_CODE szFilter[] =
	    _T("All Supported Types|*.adf;*.hdf|")
	    _T("Amiga Disk Files (*.adf)|*.adf|")
	    _T("Hard Disk Files (*.hdf)|*.hdf|")
	    _T("All Files (*.*)|*.*||");

	CFileDialog dlg(FALSE, _T("*.adf"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	                szFilter, this);

	int result = dlg.DoModal();
	if (result == IDOK) {
		CString pathName = dlg.GetPathName();
		m_path.SetWindowText(pathName);
	}
}

BOOL NewVolumeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CheckRadioButton(IDC_TYPE_ADF, IDC_TYPE_HDF, IDC_TYPE_ADF);
	CheckRadioButton(IDC_RD_PRESET, IDC_RD_CUSTOM, IDC_RD_PRESET);
	OnTypeADF();

	m_HDFSizeSlider.SetRange(1, 9, TRUE);

	SendMessage(WM_HSCROLL, 0, (LPARAM)m_HDFSizeSlider.m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void NewVolumeDlg::OnTypeADF()
{
	m_PresetSize.EnableWindow(FALSE);
	m_CustomSize.EnableWindow(FALSE);
	m_CustomSizeEdit.EnableWindow(FALSE);
	m_HDFSizeSlider.EnableWindow(FALSE);
	m_HighDensity.EnableWindow(TRUE);
	m_boot.EnableWindow(TRUE);
}

void NewVolumeDlg::OnTypeHDF()
{
	m_PresetSize.EnableWindow(TRUE);
	m_CustomSize.EnableWindow(TRUE);
	m_CustomSizeEdit.EnableWindow(TRUE);
	m_HDFSizeSlider.EnableWindow(TRUE);
	m_HighDensity.EnableWindow(FALSE);
	m_boot.SetCheck(BST_UNCHECKED);
	m_boot.EnableWindow(FALSE);
}

void NewVolumeDlg::OnOK()
{
	m_path.GetWindowText(m_strPath);
	m_strPath.Trim();

	if (m_strPath.GetLength() == 0) {
		AfxMessageBox(IDS_NOPATH);
		return;
	}

	CString label;
	m_label.GetWindowText(label);
	label.Trim();

	uint32_t size;
	int type = GetCheckedRadioButton(IDC_TYPE_ADF, IDC_TYPE_HDF);
	if (type == IDC_TYPE_ADF) {	// adf
		size = m_HighDensity.GetCheck() == BST_CHECKED ? FLOPHD_SIZE : FLOPDD_SIZE;
	} else {	// hdf
		type = GetCheckedRadioButton(IDC_RD_PRESET, IDC_RD_CUSTOM);
		if (type == IDC_RD_PRESET) {
			size = (2 << m_HDFSizeSlider.GetPos()) * 1024;
		} else {
			CString strSize;
			m_CustomSizeEdit.GetWindowText(strSize);
			size = atoi(strSize) << 1;
		}
	}

	if (size == 0) {
		AfxMessageBox(IDS_BADSIZE);
		return;
	}


	bool bootable = (m_boot.GetCheck() == BST_CHECKED);

	uint32_t flags = 0;
	if (m_dircache.GetCheck() == BST_CHECKED) {
		flags |= FSTYPE_DIRCACHE;
	}
	if (m_FFS.GetCheck() == BST_CHECKED) {
		flags |= FSTYPE_FFS;
	}
	if (m_Intl.GetCheck() == BST_CHECKED) {
		flags |= FSTYPE_INTL;
	}

	WaitDlg dlg(this);
	dlg.SetCreateParams(size, m_strPath, label, flags, bootable);

	if (dlg.DoModal() == IDOK)
		CDialog::OnOK();
}

void NewVolumeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar->m_hWnd == m_HDFSizeSlider) {
		int pos = m_HDFSizeSlider.GetPos();
		CString size;
		size.Format("%u MB", (1 << pos));
		m_PresetText.SetWindowText(size);
	} else {
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void NewVolumeDlg::OnCustomSize()
{
	m_HDFSizeSlider.EnableWindow(FALSE);
}

void NewVolumeDlg::OnPresetSize()
{
	m_HDFSizeSlider.EnableWindow(TRUE);
}

void NewVolumeDlg::OnDirCache()
{
	if (m_dircache.GetCheck() == BST_CHECKED) {
		m_Intl.SetCheck(BST_CHECKED);
		m_Intl.EnableWindow(FALSE);
	} else if (m_dircache.GetCheck() == BST_UNCHECKED) {
		m_Intl.EnableWindow(TRUE);
	}
}

