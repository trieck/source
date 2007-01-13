// PlayerNamesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PlayerNamesDlg.h"
#include "PenteApp.h"
#include "OurConstants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayerNamesDlg dialog


CPlayerNamesDlg::CPlayerNamesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayerNamesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayerNamesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pDoc				= NULL;
	m_lpszComputerName	= NULL;
	m_lpszUserName		= NULL;
	m_pPlayers			= NULL;
}

CPlayerNamesDlg::CPlayerNamesDlg(CPenteDoc* pDoc, CWnd* pParent /*=NULL*/)
	: m_pDoc(pDoc), CDialog(CPlayerNamesDlg::IDD, pParent)
{
	ASSERT_VALID(m_pDoc);

	m_lpszComputerName	= NULL;
	m_lpszUserName		= NULL;
	m_pPlayers			= NULL;
}

CPlayerNamesDlg::~CPlayerNamesDlg()
{
	if (m_lpszComputerName) delete m_lpszComputerName;
	if (m_lpszUserName)		delete m_lpszUserName;
	if (m_pPlayers)			delete m_pPlayers;
}

void CPlayerNamesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayerNamesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayerNamesDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayerNamesDlg)
	ON_COMMAND(IDC_TWOPLAYERGAME, OnTwoPlayerGame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerNamesDlg message handlers

BOOL CPlayerNamesDlg::OnInitDialog() 
{
	DWORD	dwSize = MAX_COMPUTERNAME_LENGTH + 1;
	CString	strPlayers;
	
	CDialog::OnInitDialog();

	ASSERT_VALID(m_pDoc);

	m_pPlayers = new CPlayers;
	ASSERT_VALID(m_pPlayers);

	m_pPlayers->Init();

	// Set the default icon
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ASSERT(hIcon);

	::SetClassLong(GetSafeHwnd(), GCL_HICON, (LONG)hIcon);

	LPDWORD lpdwValue;
	if (CPenteApp::GetRegistryInformation(_T("option"), _T("TwoPlayerGame"), (PPBYTE)&lpdwValue, REG_DWORD))
	{
		GetTwoPlayerGame().SetCheck(*lpdwValue ? 1 : 0);
		delete lpdwValue;
	}

	// Get the Computer Name
	m_lpszComputerName = new TCHAR[dwSize];
	if (!m_lpszComputerName)
	{
		return FALSE;
	}

	::GetComputerName(m_lpszComputerName, &dwSize);

	// Get the User Name
	dwSize = 255;
	m_lpszUserName = new TCHAR[dwSize + 1];
	if (!m_lpszUserName)
	{
		return FALSE;
	}

	::GetUserName(m_lpszUserName, &dwSize);

	GetPlayerOneNameList().AddString(m_lpszUserName);
	
	// Fill the players list
	for (INT i = 0; i < m_pPlayers->GetPlayerCount(); i++)
	{
		CString strPlayer;

		m_pPlayers->GetPlayer(i, strPlayer);
	
		if ((strPlayer != m_lpszUserName) &&
			(strPlayer != m_lpszComputerName))
		{
			if (GetPlayerOneNameList().FindStringExact(-1, strPlayer) == CB_ERR)
			{
				GetPlayerOneNameList().AddString(strPlayer);
			}

			if (GetPlayerTwoNameList().FindStringExact(-1, strPlayer) == CB_ERR)
			{
				GetPlayerTwoNameList().AddString(strPlayer);
			}
		}
	}

	CString strPlayerOne, strPlayerTwo;

	strPlayerOne = m_pDoc->GetPlayerOne();
	strPlayerTwo = m_pDoc->GetPlayerTwo();

	if (!strPlayerOne.IsEmpty())
	{
		GetPlayerOneNameList().SetWindowText(strPlayerOne);
	}
	else
	{
		GetPlayerOneNameList().SetCurSel(0);
	}

	if (!strPlayerTwo.IsEmpty())
	{
		GetPlayerTwoNameList().SetWindowText(strPlayerTwo);
	}

	GetPlayerOneNameList().SetFocus();

	OnTwoPlayerGame();

	return FALSE;  
}

VOID CPlayerNamesDlg::OnTwoPlayerGame()
{
	BOOL fIsChecked = (GetTwoPlayerGame().GetCheck() == 1);

	CString strPlayerTwo;

	GetPlayerTwoNameList().GetWindowText(strPlayerTwo);

	BOOL fError = (strPlayerTwo == m_lpszComputerName);
	if (fIsChecked && fError)
	{
		GetPlayerTwoNameList().SetCurSel(CB_ERR);
	}
	else if (!fIsChecked)
	{
		GetPlayerTwoNameList().SetWindowText(m_lpszComputerName);
	}

	GetPlayerTwoNameList().EnableWindow(fIsChecked);
}

VOID CPlayerNamesDlg::OnOK()
{
	CString strPlayerOneName, strPlayerTwoName;
	
	GetPlayerOneNameList().GetWindowText(strPlayerOneName);
	GetPlayerTwoNameList().GetWindowText(strPlayerTwoName);

	strPlayerOneName.TrimLeft();
	strPlayerOneName.TrimRight();
	strPlayerTwoName.TrimLeft();
	strPlayerTwoName.TrimRight();
		
	if (strPlayerOneName.IsEmpty() || strPlayerTwoName.IsEmpty())
	{
		AfxMessageBox(_T("You must fill in both player names."));
		return;
	}

	if (strPlayerOneName == strPlayerTwoName)
	{
		AfxMessageBox(_T("Player One and Player Two names may not be identical."));
		return;
	}
	
	if (strPlayerOneName != m_lpszUserName && strPlayerOneName != m_lpszComputerName)
	{
		m_pPlayers->AddPlayer(strPlayerOneName);
	}

	if (strPlayerTwoName != m_lpszUserName && strPlayerTwoName != m_lpszComputerName)
	{
		m_pPlayers->AddPlayer(strPlayerTwoName);
	}

	// Set Player Names
	m_pDoc->SetPlayerOneName(strPlayerOneName);
	m_pDoc->SetPlayerTwoName(strPlayerTwoName);

	// Set Play Mode
	DWORD dwValue = GetTwoPlayerGame().GetCheck();
	m_pDoc->SetPlayMode(dwValue == 1 ? PLAYER_VS_PLAYER : PLAYER_VS_COMPUTER);

	CPenteApp::UpdateRegistryInformation(_T("option"), _T("TwoPlayerGame"), (LPBYTE)&dwValue, REG_DWORD);
	
	CDialog::OnOK();
}

