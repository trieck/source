/*---------------------------------------------
	Module Name	:	MiscPage.cpp	
	Author		:	Thomas A. Rieck 
	Purpose		:	Miscellaneous Preference
					Property Page
					implementation
	Date		:	01/18/1997
----------------------------------------------*/

#include "stdafx.h"
#include "PenteApp.h"
#include "MiscPage.h"
#include "Scores.h"
#include "Players.h"
#include "OurConstants.h"

IMPLEMENT_DYNCREATE(CMiscPage, CPropertyPage)

BEGIN_MESSAGE_MAP(CMiscPage, CPropertyPage)
	ON_COMMAND(IDC_DEBUGOPTIONS, OnEnableDebug)
	ON_COMMAND(IDC_FLUSHPLAYERS, OnFlushPlayers)
	ON_COMMAND(IDC_FLUSHSCORES, OnFlushScores)
END_MESSAGE_MAP()

CMiscPage::CMiscPage() : CPropertyPage(CMiscPage::IDD)
{
}

BOOL CMiscPage::OnInitDialog()
{
	CPenteApp * pApp = (CPenteApp*)AfxGetApp();
	ASSERT_VALID(pApp);

#ifdef _DEBUG
	INT nEnabled = pApp->m_fEnableDebug ? 1 : 0;

	GetCheckBox().SetCheck(nEnabled);
#else
	LONG lStyle = ::GetWindowLong(GetCheckBox().GetSafeHwnd(), GWL_STYLE);
	::SetWindowLong(GetCheckBox().GetSafeHwnd(), GWL_STYLE, lStyle &~ WS_VISIBLE);
#endif // _DEBUG

	return CPropertyPage::OnInitDialog();
}

VOID CMiscPage::OnEnableDebug()
{
	SetModified();
}

VOID CMiscPage::OnFlushPlayers()
{
	INT nRtn = AfxMessageBox(IDS_CLEARALLPLAYERS, MB_YESNO);
	if (nRtn == IDYES)
	{
		CPlayers players;

		players.Init();

		if (players.FlushPlayers())
		{
			GetDlgItem(IDC_FLUSHPLAYERS)->EnableWindow(FALSE);
		}
	}
}

VOID CMiscPage::OnFlushScores()
{
	INT nRtn = AfxMessageBox(IDS_CLEARALLSCORES, MB_YESNO);
	if (nRtn == IDYES)
	{
		CScores scores;

		scores.Init();

		if (scores.FlushScores())
		{
			GetDlgItem(IDC_FLUSHSCORES)->EnableWindow(FALSE);
		}
	}
}

VOID CMiscPage::OnOK()
{
	CPenteApp * pApp = (CPenteApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->m_fEnableDebug = GetCheckBox().GetCheck() == 1 ? TRUE : FALSE;

	DWORD dwValue = pApp->m_fEnableDebug ? 1 : 0;

	CPenteApp::UpdateRegistryInformation(_T("Option"), _T("EnableDebug"),
		(LPBYTE)&dwValue, REG_DWORD);
}

BOOL CMiscPage::OnApply()
{
	return CPropertyPage::OnApply();
}

VOID CMiscPage::OnPaint()
{
	CPropertyPage::OnPaint();
}

CMiscPage::~CMiscPage()
{
}