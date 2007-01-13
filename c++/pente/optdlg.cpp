// optdlg.cpp : implementation file
//
#include "stdafx.h"
#include "pente.h"
#include "optdlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OptionDlg dialog


OptionDlg::OptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(OptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(OptionDlg)
	m_TwoPlayerGame = -1;
	//}}AFX_DATA_INIT
}

void OptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OptionDlg)
	DDX_Radio(pDX, IDC_PLAYERVSPLAYER, m_TwoPlayerGame);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(OptionDlg, CDialog)
	//{{AFX_MSG_MAP(OptionDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// OptionDlg message handlers
