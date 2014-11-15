// keysigdg.cpp : implementation file
//

#include "stdafx.h"
#include "baseinc.h"
#include "score.h"
#include "keysigdg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// KeySignatureDlg dialog


KeySignatureDlg::KeySignatureDlg(Measure * pMeasure, CWnd* pParent /*=NULL*/)
    : m_pMeasure(pMeasure),
      CDialog(KeySignatureDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(KeySignatureDlg)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    ASSERT_VALID(m_pMeasure);
}


void KeySignatureDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(KeySignatureDlg)
    DDX_Control(pDX, IDC_KEYSIGNATURE, m_KeySignature);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(KeySignatureDlg, CDialog)
    //{{AFX_MSG_MAP(KeySignatureDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// KeySignatureDlg message handlers

BOOL KeySignatureDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetActiveKeySignature();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

//
// SetActiveKeySignature
//
void KeySignatureDlg::SetActiveKeySignature()
{
    const KeySignature & ks = m_pMeasure->GetKeySignature();
    int index = ks.GetIndex();

    m_KeySignature.SetCurSel(index);
}

//
// OnOK
//
void KeySignatureDlg::OnOK()
{
    CDialog::OnOK();

    int index = m_KeySignature.GetCurSel();
    if (index != CB_ERR) {
        m_pMeasure->SetKeySignature(index);
    }
}

