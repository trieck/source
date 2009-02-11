// WaitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "WaitDlg.h"

// WaitDlg dialog

IMPLEMENT_DYNAMIC(WaitDlg, CDialog)

WaitDlg::WaitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(WaitDlg::IDD, pParent), nTimer(0), done(false)
{
}

WaitDlg::~WaitDlg()
{
}

void WaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WAIT_PROGRESS, m_progress);
}

BEGIN_MESSAGE_MAP(WaitDlg, CDialog)
	ON_WM_NCDESTROY()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// WaitDlg message handlers

BOOL WaitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_progress.SetBarColor(COLOR_PURPLE);
	CenterWindow();

	nTimer = SetTimer(EVENT_ID, 20, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

WaitDlg *WaitDlg::newInstance(NewVolumeDlg *pParent)
{
	WaitDlg *pDlg = new WaitDlg();
	if (pDlg && pDlg->Create(WaitDlg::IDD, pParent)) {
		pDlg->ShowWindow(SW_SHOW);
	}

	return pDlg;
}

void WaitDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	delete this;
}

void WaitDlg::OnCancel()
{
}

void WaitDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent != EVENT_ID)
		return;

	if (done) {
		DestroyWindow();
		return;
	}
}

void WaitDlg::OnDestroy()
{
	CDialog::OnDestroy();
	KillTimer(nTimer);
}
