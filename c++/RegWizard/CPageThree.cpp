// CPAGETHREE.CPP

#include "cpagethree.h"
#include "cwizard.h"

IMPLEMENT_DYNCREATE(CPageThree, CPropertyPage)

CPageThree::CPageThree() :CPropertyPage(CPageThree::IDD)
{
}

// Message Map for CPageThree
BEGIN_MESSAGE_MAP(CPageThree, CPropertyPage)
    ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CPageThree::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // set progress control ranges
    m_pProgress = (CProgressCtrl*)GetDlgItem(IDC_REGPROGRESS);
    ASSERT_VALID(m_pProgress);

    m_pProgress->SetRange(0, 70);

    return (TRUE);
}

void CPageThree::OnPaint()
{
    CPaintDC dc(this);

    // set captions
    CString str;
    str.LoadString(IDS_PAGETHREEREVIEW);
    SetDlgItemText(IDC_PAGETHREE, (LPCTSTR)str);

    CWizard* pWizard = (CWizard*)GetParent();
    ASSERT_VALID(pWizard);

    SetDlgItemText(IDC_PAGETHREESERVER, (LPCTSTR)pWizard->m_rgi.sServerName);
    SetDlgItemText(IDC_PAGETHREEDBNAME, (LPCTSTR)pWizard->m_rgi.sDatabaseName);
    SetDlgItemText(IDC_PAGETHREEREPORTPATH, (LPCTSTR)pWizard->m_rgi.sReportPath);
}

LRESULT CPageThree::OnWizardBack()
{
    // set wizard buttons
    CWizard* pWizard = (CWizard*)GetParent();
    ASSERT_VALID(pWizard);

    pWizard->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);

    return (CPropertyPage::OnWizardBack());
}

BOOL CPageThree::OnWizardFinish()
{
    CWizard* pWizard = (CWizard*)GetParent();
    ASSERT_VALID(pWizard);

    // set wizard buttons
    pWizard->SetWizardButtons(PSWIZB_DISABLEDFINISH);

    if (pWizard->SetRegInfo() == -1) {
        CString str;
        str.LoadString(IDS_REGERROR);
        AfxMessageBox (str, MB_OK | MB_ICONINFORMATION);
    } else {
        CString str;
        str.LoadString(IDS_REGSUCCESS);
        AfxMessageBox(str, MB_OK | MB_ICONINFORMATION);
    }
    return (CPropertyPage::OnWizardFinish());
}

CPageThree::~CPageThree()
{
}


