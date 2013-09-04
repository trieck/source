// ScoresDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScoresDlg.h"
#include "PenteApp.h"
#include "OurConstants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoresDlg dialog

CScoresDlg::CScoresDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScoresDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScoresDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pScores	= NULL;
	m_pFrame	= NULL;
}

CScoresDlg::~CScoresDlg()
{
	if (m_pScores) delete m_pScores;
	if (m_pFrame) {
		if (::IsWindow(m_pFrame->GetSafeHwnd())) {
			m_pFrame->DestroyWindow();
		}
	}
}

void CScoresDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScoresDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScoresDlg, CDialog)
	//{{AFX_MSG_MAP(CScoresDlg)
	ON_COMMAND(IDC_PRINTPREVIEW, OnPreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScoresDlg message handlers

VOID CScoresDlg::InsertHeaders()
{
	LPCTSTR lpszHeaders[] = {
		_T("Player One"),
		_T("Player Two"),
		_T("Winner"),
		_T("Date / Time")
	};

	UINT nCount = sizeof (lpszHeaders) / sizeof (LPCTSTR);

	LV_COLUMN	lvc;
	CRect		rc;

	GetListCtrl().GetClientRect(&rc);

	for (UINT i = 0; i < nCount; i++) {
		lvc.mask		= LVCF_TEXT | LVCF_WIDTH;
		lvc.cx			= rc.Width() / nCount;
		lvc.pszText		= (LPTSTR)lpszHeaders[i];
		lvc.cchTextMax	= lstrlen(lpszHeaders[i]);

		GetListCtrl().InsertColumn(i, &lvc);
	}
}

VOID CScoresDlg::InsertItems()
{
	ASSERT_VALID(m_pScores);

	for (int i = 0; i < m_pScores->GetScoreCount(); i++) {
		CString strItems[4];

		for (int j = 0; j < 4; j++) {
			m_pScores->GetScoreItem(i, j, strItems[j]);
		}

		LV_ITEM lvi;

		lvi.mask		= LVIF_TEXT;
		lvi.iItem		= i;
		lvi.iSubItem	= 0;
		lvi.pszText		= strItems[0].GetBuffer(0);
		lvi.cchTextMax	= strItems[0].GetLength();

		GetListCtrl().InsertItem(&lvi);
		GetListCtrl().SetItemText(i, 1, strItems[1]);
		GetListCtrl().SetItemText(i, 2, strItems[2]);
		GetListCtrl().SetItemText(i, 3, strItems[3]);
	}
}

BOOL CScoresDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pScores = new CScores;
	ASSERT_VALID(m_pScores);

	// Initialize the Scores object
	m_pScores->Init();

	// Set the sort function
	GetListCtrl().SortItems(&CompareFunc, 0L);

	// Insert Headers
	InsertHeaders();

	// Insert Items
	InsertItems();

	return TRUE;
}

VOID CScoresDlg::OnPreview()
{
	BeginWaitCursor();

	CString	strTitle;
	strTitle.LoadString(IDS_SCORESPREVIEWTITLE);

	// Allow only one instance
	if (m_pFrame) {
		if (::IsWindow(m_pFrame->GetSafeHwnd())) {
			m_pFrame->ShowWindow(SW_RESTORE);
			return;
		}
	}

	m_pFrame = new CScoresPreviewFrame();
	ASSERT_VALID(m_pFrame);

	if (m_pFrame->Create(NULL, strTitle, WS_OVERLAPPEDWINDOW,
	                     CRect(100, 100, 600, 500), GetParentFrame(), NULL, WS_EX_OVERLAPPEDWINDOW, NULL)) {
		m_pFrame->CenterWindow();
		m_pFrame->ShowWindow(SW_SHOW);
		m_pFrame->UpdateWindow();
	}

	EndWaitCursor();
}

int CScoresDlg::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return -1;
}

