// ColorChooserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "torrentexplorer.h"
#include "ColorChooserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ColorChooserDlg dialog


ColorChooserDlg::ColorChooserDlg(CWnd* pParent /*=NULL*/)
		: CDialog(ColorChooserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ColorChooserDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ColorChooserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ColorChooserDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ColorChooserDlg, CDialog)
	//{{AFX_MSG_MAP(ColorChooserDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColorChooserDlg message handlers

BOOL ColorChooserDlg::OnInitDialog()
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

void ColorChooserDlg::OnOK()
{
	CDialog::OnOK();
}

void ColorChooserDlg::OnCancel()
{
	CDialog::OnCancel();
}

COLORREF ColorChooserDlg::GetSelectedColor() const
{
	return m_ColorsWnd.GetSelectedColor();
}
