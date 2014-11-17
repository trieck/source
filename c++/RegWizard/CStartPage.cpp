// CSTARTPAGE.CPP

#include "cstartpage.h"
#include "cwizard.h"

IMPLEMENT_DYNCREATE(CStartPage, CPropertyPage)

CStartPage::CStartPage() :CPropertyPage(CStartPage::IDD)
{
}

// Message Map for CStartPage
BEGIN_MESSAGE_MAP(CStartPage, CPropertyPage)
    ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CStartPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // set wizard buttons
    CWizard* pWizard = (CWizard*)GetParent();
    ASSERT_VALID (pWizard);
    pWizard->SetWizardButtons(PSWIZB_NEXT);

    // set font for title
    m_fntTitle.CreateFont(28, 0, 0, 0, FW_BOLD, TRUE, FALSE,
                          0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                          DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Times New Roman"));
    return (TRUE);
}

void CStartPage::OnPaint()
{
    CPaintDC dc(this);

    // set captions
    CString str;
    str.LoadString(IDS_WELCOME);
    SetDlgItemText(IDC_TITLE, (LPCTSTR)str);

    str.LoadString(IDS_STARTPAGE);
    SetDlgItemText(IDC_START, (LPCTSTR)str);

    // change the font for the title caption
    CStatic* pTitle = (CStatic*)GetDlgItem(IDC_TITLE);
    ASSERT_VALID(pTitle);

    pTitle->SetFont(&m_fntTitle);
}

LRESULT CStartPage::OnWizardNext()
{
    // set wizard buttons
    CWizard* pWizard = (CWizard*)GetParent();
    ASSERT_VALID (pWizard);

    pWizard->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

    return (CPropertyPage::OnWizardNext());
}

CStartPage::~CStartPage()
{
}


