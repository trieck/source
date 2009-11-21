// earDlg.cpp : implementation file
//
#include "stdafx.h"
#include "baseinc.h"
#include "ear.h"
#include "earDlg.h"
#include "SettingsDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int loNote;
extern int hiNote;
static int random(int lo, int hi);
static CString IntervalToString(Interval i);
/////////////////////////////////////////////////////////////////////////////
// AboutDlg dialog used for App About
class AboutDlg : public CDialog {
public:
	AboutDlg();
// Dialog Data
	//{{AFX_DATA(AboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	//{{AFX_MSG(AboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
AboutDlg::AboutDlg() : CDialog(AboutDlg::IDD)
{
	//{{AFX_DATA_INIT(AboutDlg)
	//}}AFX_DATA_INIT
}
void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AboutDlg)
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(AboutDlg, CDialog)
	//{{AFX_MSG_MAP(AboutDlg)
	// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// EarDlg dialog
EarDlg::EarDlg(CWnd* pParent /*=NULL*/)
		: CDialog(EarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(EarDlg)
	m_Interval = 0;
	m_Output = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_MidiInterval = Unison;
	m_correct = 0;
	m_incorrect = 0;
}
void EarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EarDlg)
	DDX_Radio(pDX, IDC_RDINTERVALMIN2ND, m_Interval);
	DDX_Text(pDX, IDC_OUTPUT, m_Output);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(EarDlg, CDialog)
	//{{AFX_MSG_MAP(EarDlg)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDSETTINGS, OnSettings)
	ON_BN_CLICKED(IDLISTEN, OnListen)
	ON_BN_CLICKED(IDENTER, OnEnter)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// EarDlg message handlers
BOOL EarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CreateInterval();
	OnListen();
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void EarDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		AboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else CDialog::OnSysCommand(nID, lParam);
}
void EarDlg::OnSettings()
{
	SettingsDlg().DoModal();
}
void EarDlg::OnListen()
{
	EarApp *pApp = (EarApp *)AfxGetApp();
	ASSERT_VALID(pApp);
	pApp->Play(&m_buffer);
}
void EarDlg::OnCancel()
{
	EarApp *pApp = (EarApp *)AfxGetApp();
	ASSERT_VALID(pApp);
	pApp->Stop();
	CDialog::OnCancel();
}
void EarDlg::CreateInterval()
{
	int first, second;
	first = random(loNote, hiNote);
	while ((second = random(loNote, hiNote)) == first)
		;

	m_MidiInterval = Interval(abs(second - first));
	m_buffer.Transform(first, second);
}
// Helper functions
int random(int lo, int hi)
{
	return lo + int(rand() * double(hi - lo) / RAND_MAX);
}

void EarDlg::OnEnter()
{
	CString message;
	UpdateData(TRUE);
	Interval i = Interval(m_Interval + 1);
	if (i == m_MidiInterval) {
		message.LoadString(IDS_CORRECT);
		CString correct;
		correct.Format("%d", ++m_correct);
		GetDlgItem(IDC_CORRECT)->SetWindowText(correct);
	} else {
		message.Format(IDS_INCORRECT, IntervalToString(m_MidiInterval));
		CString incorrect;
		incorrect.Format("%d", ++m_incorrect);
		GetDlgItem(IDC_INCORRECT)->SetWindowText(incorrect);
	}
	float total = 100 * m_correct / (float)(m_correct + m_incorrect);
	CString T;
	T.Format("%.2f%%", total);
	GetDlgItem(IDC_TOTAL)->SetWindowText(T);
	m_Output = message;
	UpdateData(FALSE);
	CreateInterval();
	OnListen();
}
CString IntervalToString(Interval i)
{
	CString output;
	switch (i) {
	case Unison:
		output = "Unison";
		break;
	case MinorSecond:
		output = "Minor Second";
		break;
	case MajorSecond:
		output = "Major Second";
		break;
	case MinorThird:
		output = "Minor Third";
		break;
	case MajorThird:
		output = "Major Third";
		break;
	case PerfectFourth:
		output = "Perfect Fourth";
		break;
	case DiminishedFifth:
		output = "Diminished Fifth";
		break;
	case PerfectFifth:
		output = "Perfect Fifth";
		break;
	case MinorSixth:
		output = "Minor Sixth";
		break;
	case MajorSixth:
		output = "Major Sixth";
		break;
	case MinorSeventh:
		output = "Minor Seventh";
		break;
	case MajorSeventh:
		output = "Major Seventh";
		break;
	case Octave:
		output = "Octave";
		break;
	}
	return output;
}
HBRUSH EarDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	HWND correct = GetDlgItem(IDC_CORRECT)->GetSafeHwnd();
	HWND incorrect = GetDlgItem(IDC_INCORRECT)->GetSafeHwnd();
	HWND total = GetDlgItem(IDC_TOTAL)->GetSafeHwnd();
	if (pWnd->GetSafeHwnd() == correct ||
	        pWnd->GetSafeHwnd() == incorrect ||
	        pWnd->GetSafeHwnd() == total) {
		pDC->SetTextColor(RGB(128, 0, 0));
	}
	return hbr;
}
