// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "baseinc.h"
#include "ear.h"
#include "SettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingsDlg dialog


SettingsDlg::SettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingsDlg)
	m_Fifths = FALSE;
	m_Fourths = FALSE;
	m_Octaves = FALSE;
	m_Seconds = FALSE;
	m_Sevenths = FALSE;
	m_Sixths = FALSE;
	m_Thirds = FALSE;
	m_instrument = -1;
	//}}AFX_DATA_INIT
}


void SettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingsDlg)
	DDX_Check(pDX, IDC_CHKFIFTHS, m_Fifths);
	DDX_Check(pDX, IDC_CHKFOURTHS, m_Fourths);
	DDX_Check(pDX, IDC_CHKOCTAVES, m_Octaves);
	DDX_Check(pDX, IDC_CHKSECONDS, m_Seconds);
	DDX_Check(pDX, IDC_CHKSEVENTHS, m_Sevenths);
	DDX_Check(pDX, IDC_CHKSIXTHS, m_Sixths);
	DDX_Check(pDX, IDC_CHKTHIRDS, m_Thirds);
	DDX_CBIndex(pDX, IDC_INSTRUMENTS, m_instrument);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SettingsDlg, CDialog)
	//{{AFX_MSG_MAP(SettingsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingsDlg message handlers

BOOL SettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIntervals();
	BuildInstruments();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void SettingsDlg::BuildInstruments()
{
	EarApp *pApp = (EarApp *)AfxGetApp();
	ASSERT_VALID(pApp);

	CComboBox * pInstruments =
	    (CComboBox *)GetDlgItem(IDC_INSTRUMENTS);
	ASSERT_VALID(pInstruments);

	HRSRC hResource = ::FindResource(AfxGetResourceHandle(),
	                                 MAKEINTRESOURCE(IDR_INSTRUMENTS),
	                                 "TEXT");
	ASSERT(hResource != NULL);

	HGLOBAL hGlobal = ::LoadResource(AfxGetResourceHandle(), hResource);
	ASSERT(hGlobal != NULL);

	LPCSTR pResource = (LPCSTR)::LockResource(hGlobal);
	ASSERT(pResource != NULL);
	LPSTR pdata = strdup(pResource);

	LPCSTR ptok = strtok(pdata, "\r\n");
	while (ptok != NULL) {
		pInstruments->AddString(ptok);
		ptok = strtok(NULL, "\r\n");
	}

	if (pdata != NULL) delete [] pdata;

	if (pInstruments->GetCount() > 0) {
		m_instrument = pApp->GetInstrument();
		UpdateData(FALSE);
	}
}

void SettingsDlg::SetIntervals()
{
	EarApp *pApp = (EarApp *)AfxGetApp();
	ASSERT_VALID(pApp);

	int intervals = pApp->GetIntervals();

	m_Seconds = (intervals & INTERVAL_SECONDS) != 0;
	m_Thirds = (intervals & INTERVAL_THIRDS) != 0;
	m_Fourths = (intervals & INTERVAL_FOURTHS) != 0;
	m_Fifths = (intervals & INTERVAL_FIFTHS) != 0;
	m_Sixths = (intervals & INTERVAL_SIXTHS) != 0;
	m_Sevenths = (intervals & INTERVAL_SEVENTHS) != 0;
	m_Octaves = (intervals & INTERVAL_OCTAVES) != 0;

	UpdateData(FALSE);
}
void SettingsDlg::OnOK()
{
	int intervals = 0;

	UpdateData(TRUE);

	if (m_Seconds) intervals |= INTERVAL_SECONDS;
	if (m_Thirds) intervals |= INTERVAL_THIRDS;
	if (m_Fourths) intervals |= INTERVAL_FOURTHS;
	if (m_Fifths) intervals |= INTERVAL_FIFTHS;
	if (m_Sixths) intervals |= INTERVAL_SIXTHS;
	if (m_Sevenths) intervals |= INTERVAL_SEVENTHS;
	if (m_Octaves) intervals |= INTERVAL_OCTAVES;

	EarApp *pApp = (EarApp *)AfxGetApp();
	ASSERT_VALID(pApp);

	pApp->SetIntervals(intervals);
	pApp->SetInstrument(m_instrument);

	CDialog::OnOK();
}

