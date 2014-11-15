// REGWIZARD.CPP

#include "regwizard.h"

CRegWizApp::CRegWizApp(LPCTSTR lpszAppName)
{
    // initialize member variables
    m_pWizard = NULL;
    m_pStartPage = NULL;
    m_pPageTwo = NULL;
    m_pPageThree = NULL;
}

BOOL CRegWizApp::InitInstance()
{
    // create the wizard
    m_pWizard = new CWizard("Registry Wizard");
    ASSERT_VALID (m_pWizard);

    this->CreateWizard();

    m_pMainWnd = m_pWizard;

    // Display the Wizard
    m_pWizard->DoModal();

    return(FALSE);
}

CRegWizApp::~CRegWizApp()
{
    // release allocated memory
    if (m_pWizard) delete m_pWizard;
    if (m_pStartPage) delete m_pStartPage;
    if (m_pPageTwo) delete m_pPageTwo;
    if (m_pPageThree) delete m_pPageThree;
}
CRegWizApp TheApp;

void CRegWizApp::CreateWizard()
{
    // ensure a valid wizard pointer
    if (!m_pWizard)
        return;

    // Construct the property pages
    m_pStartPage = new CStartPage;
    ASSERT_VALID(m_pStartPage);
    m_pStartPage->Construct(IDD_STARTPAGE, 0);

    m_pPageTwo = new CPageTwo;
    ASSERT_VALID(m_pPageTwo);
    m_pPageTwo->Construct(IDD_PAGETWO, 0);

    m_pPageThree = new CPageThree;
    ASSERT_VALID(m_pPageThree);
    m_pPageThree->Construct(IDD_PAGETHREE, 0);

    // Add the property pages to the property sheet
    m_pWizard->AddPage(m_pStartPage);
    m_pWizard->AddPage(m_pPageTwo);
    m_pWizard->AddPage(m_pPageThree);

    // Make the property sheet a wizard
    m_pWizard->SetWizardMode();
}
