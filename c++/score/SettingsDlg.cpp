// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "baseinc.h"
#include "score.h"
#include "SettingsDlg.h"
#include "OutputDevs.h"
#include "OutputDev.h"
#include "InputDevs.h"
#include "InputDev.h"

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
	//}}AFX_DATA_INIT
}


void SettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingsDlg)
	DDX_Control(pDX, IDC_CB_OUTPUTDEVICES, m_OutputDevices);
	DDX_Control(pDX, IDC_CB_INPUTDEVICES, m_InputDevices);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SettingsDlg, CDialog)
	//{{AFX_MSG_MAP(SettingsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingsDlg message handlers

//
// OnInitDialog
//
BOOL SettingsDlg :: OnInitDialog() 
{
    CDialog :: OnInitDialog();
	
	BuildDevices();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//
// BuildDevices
//
void SettingsDlg :: BuildDevices()
{
    // Insert output devices
    OutputDevices outputDevs;
    int count = outputDevs.Count();
    for (int i = 0; i < count; i++) {
        OutputDevice * pDevice = (OutputDevice *)outputDevs.GetDevice(i);
        m_OutputDevices.AddString(pDevice->GetProduct());
        delete pDevice;
    }

    // Insert input devices
    InputDevices inputDevs;
    count = inputDevs.Count();
    for (i = 0; i < count; i++) {
        InputDevice * pDevice = (InputDevice *)inputDevs.GetDevice(i);
        m_InputDevices.AddString(pDevice->GetProduct());
        delete pDevice;
    }

    if (m_OutputDevices.GetCount() > 0)
        m_OutputDevices.SetCurSel(0);

    if (m_InputDevices.GetCount() > 0)
        m_InputDevices.SetCurSel(0);
}



void SettingsDlg::OnOK() 
{
    ScoreApp * pApp = (ScoreApp *)AfxGetApp();
    ASSERT_VALID(pApp);

	CDialog::OnOK();
}
