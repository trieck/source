// AddEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "music.h"
#include "AddEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddEditDlg dialog

AddEditDlg::AddEditDlg(Mode M, LPRECORD rec, CWnd* pParent /*=NULL*/)
    : CDialog(AddEditDlg::IDD, pParent),
      _mode(M),
      _rec(rec)
{
    //{{AFX_DATA_INIT(AddEditDlg)
    m_Album = _T("");
    m_Artist = _T("");
    m_Label = _T("");
    m_Year = 0;
    //}}AFX_DATA_INIT
    ASSERT(_rec != NULL);
}

void AddEditDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(AddEditDlg)
    DDX_Text(pDX, IDC_ALBUMTITLE, m_Album);
    DDX_CBString(pDX, IDC_ARTIST, m_Artist);
    DDX_Text(pDX, IDC_LABEL, m_Label);
    DDX_Text(pDX, IDC_YEAR, m_Year);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(AddEditDlg, CDialog)
    //{{AFX_MSG_MAP(AddEditDlg)
    ON_BN_CLICKED(IDC_NEWARTIST, OnNewArtist)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddEditDlg message handlers

BOOL AddEditDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (_mode == addMode) {
        SetWindowText(LoadString(IDS_ADDMODE));
    } else {
        m_Artist = _rec->Artist;
        m_Album = _rec->Album;
        m_Label = _rec->Label;
        m_Year = _rec->year;
        SetWindowText(LoadString(IDS_EDITMODE));
        UpdateData(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void AddEditDlg::OnNewArtist()
{
}

void AddEditDlg::OnOK()
{
    CDialog::OnOK();
}
