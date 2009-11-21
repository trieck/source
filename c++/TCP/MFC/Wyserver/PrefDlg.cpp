/*--------------------------------------
	Module:	PREFDLG.CPP
	Author:	Thomas A. Rieck
	Date:	06/23/97
----------------------------------------*/

#include "PrefDlg.h"

BEGIN_MESSAGE_MAP(CPrefDlg, CDialog)
	ON_COMMAND(IDC_LOGGING, OnEnableLogging)
	ON_COMMAND(IDOK, OnOK)
END_MESSAGE_MAP()

CPrefDlg :: CPrefDlg(CWnd* pParentWnd) :
		CDialog(CPrefDlg::IDD, pParentWnd)
{
	m_pApp		= NULL;
	m_pCheck	= NULL;
	m_pLogPath	= NULL;
}

CPrefDlg :: ~CPrefDlg()
{
}

BOOL CPrefDlg :: OnInitDialog()
{
	// set app data member
	m_pApp = (CWysApp*)AfxGetApp();
	ASSERT_VALID(m_pApp);

	// set check button data member
	m_pCheck = (CButton*)GetDlgItem(IDC_LOGGING);
	ASSERT_VALID(m_pCheck);

	// set edit control data member
	m_pLogPath = (CEdit*)GetDlgItem(IDC_LOGPATH);
	ASSERT_VALID(m_pLogPath);

	// check for logging
	if (m_pApp->IsLogging() ) {
		CString szLogPath;

		// set button check
		m_pCheck->SetCheck(1);

		m_pApp->GetLoggingPath(szLogPath);

		// enable logging path and set it
		m_pLogPath->EnableWindow(TRUE);
		m_pLogPath->SetWindowText(szLogPath);
	}

	// center the dialog
	this->CenterWindow();

	return (CDialog :: OnInitDialog());
}

void CPrefDlg :: OnEnableLogging()
{
	// enable/disable logging path
	m_pLogPath->EnableWindow(!m_pLogPath->IsWindowEnabled());

	if (m_pLogPath->IsWindowEnabled())
		m_pLogPath->SetFocus();
}

void CPrefDlg :: OnOK()
{
	CString szLogPath;

	if (m_pLogPath->IsWindowEnabled() ) {
		m_pLogPath->GetWindowText(szLogPath);

		szLogPath.TrimLeft();
		szLogPath.TrimRight();

		if (szLogPath.IsEmpty()) {
			CString szTemp;
			szTemp.LoadString(IDS_EMPTYSTRING);
			MessageBox(szTemp, NULL, MB_ICONINFORMATION);
			m_pLogPath->SetFocus();
			return;
		}
		m_pApp->SetLogging(TRUE);
		m_pApp->SetLoggingPath(szLogPath);
	} else
		m_pApp->SetLogging(FALSE);

	CDialog :: OnOK();
}