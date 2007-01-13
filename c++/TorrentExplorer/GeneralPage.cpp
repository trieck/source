// GeneralPage.cpp : implementation file
//

#include "stdafx.h"
#include "torrentexplorer.h"
#include "GeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GeneralPage property page

IMPLEMENT_DYNCREATE(GeneralPage, CPropertyPage)

GeneralPage::GeneralPage() 
 : CPropertyPage(GeneralPage::IDD), m_Dirty(FALSE)
{
	//{{AFX_DATA_INIT(GeneralPage)
	m_SaveWin = FALSE;
	//}}AFX_DATA_INIT
}

GeneralPage::~GeneralPage()
{
}

void GeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GeneralPage)
	DDX_Check(pDX, IDC_SAVEWIN, m_SaveWin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(GeneralPage)
	ON_BN_CLICKED(IDC_SAVEWIN, OnSaveWin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GeneralPage message handlers

void GeneralPage::OnSaveWin() 
{
	m_Dirty = TRUE;
	SetModified();	
}

void GeneralPage::OnOK() 
{
	TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
	if (m_Dirty) {
		pApp->PutSetting("ui_save_win", m_SaveWin);
	}
	m_Dirty = FALSE;
}

BOOL GeneralPage::OnInitDialog() 
{
	TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
	m_SaveWin = pApp->GetBOOLSetting("ui_save_win");

	CPropertyPage::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
