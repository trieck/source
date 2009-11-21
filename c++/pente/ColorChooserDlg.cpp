// ColorChooserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "ColorChooserDlg.h"


// CColorChooserDlg dialog

IMPLEMENT_DYNAMIC(CColorChooserDlg, CDialog)

CColorChooserDlg::CColorChooserDlg(CWnd* pParent /*=NULL*/)
		: CDialog(CColorChooserDlg::IDD, pParent)
{

}

CColorChooserDlg::~CColorChooserDlg()
{
}

void CColorChooserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CColorChooserDlg, CDialog)
END_MESSAGE_MAP()


// CColorChooserDlg message handlers

BOOL CColorChooserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rectDefault(CW_USEDEFAULT, CW_USEDEFAULT,
	                  CW_USEDEFAULT, CW_USEDEFAULT);

	if (!m_ColorsWnd.Create(
	            NULL,
	            "",
	            WS_CHILD | WS_VISIBLE,
	            rectDefault,
	            this,
	            IDC_COLOR_CHOOSER))
		return FALSE;

	CRect rc, rcParent;
	m_ColorsWnd.GetWindowRect(rc);
	m_pParentWnd->GetWindowRect(rcParent);

	AdjustWindowRectEx(&rc, GetStyle(), FALSE, GetExStyle());
	SetWindowPos(NULL, rcParent.left, rcParent.bottom,
	             rc.Width(), rc.Height(), 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


COLORREF CColorChooserDlg::GetSelectedColor() const
{
	return m_ColorsWnd.GetSelectedColor();
}
