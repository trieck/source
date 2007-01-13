/*---------------------------------------
	Module	:	PLAYDLG.CPP
	Purpose	:	Player Dialog 
				Implementations
	Date	:	12/01/1997
---------------------------------------*/

#include "PlayDlg.h"
#include "MainFrame.h"

// Initialize static data members
const UINT CPlayDlg::sm_nCtrlIDs[] = {IDC_BACKFRAME1, IDC_BACKFRAME2, IDC_BACKFRAME3,
									IDC_BACKFRAME4, IDC_BACKFRAME5, IDC_BACKFRAME6};
const RECT CPlayDlg::sm_rcDigitSizes[] = {{67, 7, 79, 25},
										{55, 7, 67, 25},
										{43, 7, 55, 25},
										{31, 7, 43, 25},
										{19, 7, 31, 25},
										{7, 7, 19, 25}};

IMPLEMENT_DYNCREATE (CPlayDlg, CDialog)

BEGIN_MESSAGE_MAP(CPlayDlg, CDialog)
	ON_COMMAND(IDC_STOP, OnStopWave)
	ON_COMMAND(IDC_PLAY, OnPlayWave)
	ON_COMMAND(IDC_PAUSE, OnPauseWave)
	ON_WM_TIMER()
END_MESSAGE_MAP()

CPlayDlg :: CPlayDlg(CWnd* pParent)
{
	m_pDoc			= NULL;
	m_pDigitCtrlMgr	= NULL;
	m_pLeftChannel	= NULL;
	m_pRightChannel	= NULL;
	m_fPaused		= FALSE;
}

CPlayDlg :: ~CPlayDlg()
{
	if (m_pDigitCtrlMgr)	delete m_pDigitCtrlMgr;
	if (m_pLeftChannel)		delete m_pLeftChannel;
	if (m_pRightChannel)	delete m_pRightChannel;
}

VOID CPlayDlg :: OnCancel()
{
	DestroyWindow();
}

VOID CPlayDlg :: PostNcDestroy()
{
	delete this;
}

BOOL CPlayDlg :: OnInitDialog()
{
	// Call the base class handler
	CDialog :: OnInitDialog();

	UINT nIcons[] = {IDI_STOPBTN, IDI_PLAYBTN, IDI_PAUSEBTN};
	UINT nCtrls[] = {IDC_STOP, IDC_PLAY, IDC_PAUSE};

	UINT nCount = sizeof(nIcons) / sizeof(UINT);

	for (UINT i = 0; i < nCount; i++)
	{
		// Set the Button Icons
		HICON hIcon = (HICON)::LoadImage(AfxGetInstanceHandle(),
										MAKEINTRESOURCE(nIcons[i]),
										IMAGE_ICON, 15, 15, LR_LOADMAP3DCOLORS);
		SendDlgItemMessage(nCtrls[i], BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
	}

	// Create the CDigitCtrlMgr

	nCount = sizeof(CPlayDlg::sm_nCtrlIDs) / sizeof(UINT);

	m_pDigitCtrlMgr = new CDigitCtrlMgr(this, CPlayDlg::sm_nCtrlIDs, 
						CPlayDlg::sm_rcDigitSizes, nCount);

	ASSERT_VALID(m_pDigitCtrlMgr);

	// Create the LEDMeter objects
	m_pLeftChannel = new CLEDMeter();
	ASSERT_VALID(m_pLeftChannel);

	CRect rcLeft(7, 50, 79, 57);
	CRect rcRight(7, 59, 79, 66);
	// Convert the dialog coordinates
	MapDialogRect(&rcLeft);
	MapDialogRect(&rcRight);

	m_pLeftChannel->Create(WS_VISIBLE | WS_CHILD, rcLeft, this, IDC_LEFTCHANNEL);

	m_pRightChannel = new CLEDMeter();
	ASSERT_VALID(m_pRightChannel);

	m_pRightChannel->Create(WS_VISIBLE | WS_CHILD, rcRight,
				this, IDC_RIGHTCHANNEL);

	m_pLeftChannel->SetPos(50);
	m_pRightChannel->SetPos(85);

	// Set the custom icon
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	::SetClassLong(GetSafeHwnd(), GCL_HICON, (LONG)hIcon);

	return TRUE;
}

VOID CPlayDlg :: OnStopWave()
{
	if (m_pDoc)
	{
		if (m_pDoc->Stop())
		{
			KillTimer(1);
				
			CString strValue = _T("000000");
			m_pDigitCtrlMgr->SetValue(strValue);

			GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
			GetDlgItem(IDC_PLAY)->EnableWindow(TRUE);
			GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);

			m_fPaused = FALSE;
		}
	}

}

VOID CPlayDlg :: OnPlayWave()
{
	if (!m_fPaused)
	{	// Play current document file
		m_pDoc = GetActiveDocument();
		if (m_pDoc)
		{
			if (m_pDoc->Play())
			{
				SetTimer(1, 1, NULL);
				GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
				GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
				GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
			}
		}
	}
	else // Restart a paused document
	{
		if (m_pDoc)
		{
			if (m_pDoc->Restart())
			{
				SetTimer(1, 1, NULL);
				GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
				GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
				GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
				m_fPaused = FALSE;
			}
		}
	}
}

VOID CPlayDlg :: OnPauseWave()
{
	if (m_pDoc)
	{
		if (m_pDoc->Pause())
		{
			KillTimer(1);
			GetDlgItem(IDC_PLAY)->EnableWindow(TRUE);
			GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
			m_fPaused = TRUE;
		}
	}
}

void CPlayDlg :: OnTimer(UINT nIDEvent)
{
	DWORD dwPlayPosition, dwWritePosition, dwBytesPerMs;

	if (m_pDoc)
	{
		// If we are not playing anymore kill the timer.
		if (!m_pDoc->IsPlaying())
		{
			OnStopWave();
			return;
		}

		// Get Current play rate and convert to BytesPerMillisecond.
		dwBytesPerMs = m_pDoc->GetRate() / 1000;
		
		// Get Current Play Position
		m_pDoc->GetCurrentPosition(&dwPlayPosition, &dwWritePosition);
		
		dwPlayPosition /= dwBytesPerMs;

		// Update the display with current value.
		m_pDigitCtrlMgr->SetValue(TranslatePlayPosition(dwPlayPosition));
	}
}

CWaveDoc* CPlayDlg :: GetActiveDocument()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT_VALID(pFrame);

	CMDIChildWnd* pChild = pFrame->MDIGetActive();
	if (!pChild)	// No Child Windows
		return NULL;

	return (CWaveDoc*)pChild->GetActiveDocument();
}

CString CPlayDlg :: TranslatePlayPosition(DWORD dwPosition)
{
	int		nLength;
	int		nCount;
	CString strPosition;
	
	nCount = sizeof(CPlayDlg::sm_nCtrlIDs) / sizeof(UINT);
	
	strPosition.Format(_T("%ld"), dwPosition);
	if ((nLength = strPosition.GetLength()) < nCount)
	{
		CString strTemp;
		int nDiff = nCount - nLength;
		for (int i = nDiff; i > 0; i--)
			strTemp += _T("0");
		strPosition = strTemp + strPosition;
	}

	return strPosition;
}


