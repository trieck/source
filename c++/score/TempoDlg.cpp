// TempoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "baseinc.h"
#include "score.h"
#include "TempoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int minTempo = 10;
static const int maxTempo = 400;

/////////////////////////////////////////////////////////////////////////////
// TempoDlg dialog


TempoDlg::TempoDlg(Measure * pMeasure, CWnd* pParent /*=NULL*/)
	: m_pMeasure(pMeasure),
	  CDialog(TempoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(TempoDlg)
	m_Tempo = DEFAULT_TEMPO;
	m_ApplyForward = FALSE;
	//}}AFX_DATA_INIT

	ASSERT(m_pMeasure != NULL);
}


void TempoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TempoDlg)
	DDX_Control(pDX, IDC_SPINTEMPO, m_TempoSpin);
	DDX_Text(pDX, IDC_TEMPO, m_Tempo);
	DDV_MinMaxUInt(pDX, m_Tempo, minTempo, maxTempo);
	DDX_Check(pDX, IDC_CHKAPPLYMEASURESAHEAD, m_ApplyForward);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TempoDlg, CDialog)
	//{{AFX_MSG_MAP(TempoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TempoDlg message handlers

BOOL TempoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Tempo = m_pMeasure->GetTempo();
	m_TempoSpin.SetRange(minTempo, maxTempo);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//
// OnOK
//
void TempoDlg::OnOK()
{
	CDialog::OnOK();

	m_pMeasure->SetTempo(m_Tempo);

	if (m_ApplyForward)
		ApplyForward();
}

//
// ApplyForward
//
void TempoDlg::ApplyForward() const
{
	const Staff * pStaff = m_pMeasure->GetStaff();
	ASSERT(pStaff != NULL);

	const MEASUREARRAY* pMeasures = pStaff->GetMeasures();
	ASSERT(pMeasures != NULL);

	BOOL ahead = FALSE;

	int Count = pMeasures->GetSize();
	for (int i = 0; i < Count; i++) {
		Measure * pMeasure = pMeasures->GetAt(i);
		ASSERT(pMeasure != NULL);

		if (pMeasure == m_pMeasure)
			ahead = TRUE;
		else if (ahead)
			pMeasure->SetTempo(m_Tempo);
	}

}