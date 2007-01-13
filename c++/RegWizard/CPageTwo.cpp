// CPAGETWO.CPP

#include "cpagetwo.h"
#include "cwizard.h"

IMPLEMENT_DYNCREATE(CPageTwo, CPropertyPage)

CPageTwo::CPageTwo() :CPropertyPage(CPageTwo::IDD)
{
}

// Message Map for CPageTwo
BEGIN_MESSAGE_MAP(CPageTwo, CPropertyPage)
    ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CPageTwo::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CWizard* pWizard = (CWizard*)GetParent();
	ASSERT_VALID(pWizard);

	if (pWizard->GetRegInfo()==0)
	{
		// set edit controls
		SetDlgItemText(IDC_SERVER, pWizard->m_rgi.sServerName);
		SetDlgItemText(IDC_DATABASE, pWizard->m_rgi.sDatabaseName);
		SetDlgItemText(IDC_REPORTPATH, pWizard->m_rgi.sReportPath);
	}
	
	return (TRUE);
}

void CPageTwo::OnPaint()
{
	CPaintDC dc(this);
	
	// set captions
	CString str;
	str.LoadString(IDS_PAGETWO);
	SetDlgItemText(IDC_PAGETWO, (LPCTSTR)str);
}

LRESULT CPageTwo::OnWizardBack()
{
	// set wizard buttons
	CWizard* pWizard = (CWizard*)GetParent();
	ASSERT_VALID(pWizard);

	pWizard->SetWizardButtons(PSWIZB_NEXT);

	return (CPropertyPage::OnWizardBack());
}

LRESULT CPageTwo::OnWizardNext() 
{
	CString sServer, sDatabase, sReportPath;
	
	GetDlgItemText(IDC_SERVER, sServer);
	GetDlgItemText(IDC_DATABASE, sDatabase);
	GetDlgItemText(IDC_REPORTPATH, sReportPath);
		
   // Check to see that text exists in  edit controls	
   if (sServer.GetLength() == 0)
   {
      AfxMessageBox("You must enter a server name.",
         MB_OK | MB_ICONINFORMATION);
	  
	  // set focus
	  CEdit* pEdit = (CEdit*)GetDlgItem(IDC_SERVER);
	  ASSERT_VALID(pEdit);
	  pEdit->SetFocus();
      
	  // Prevent the page from turning
      return -1;
   }

   if (sDatabase.GetLength() == 0)
   {
      AfxMessageBox("You must enter a database name.",
         MB_OK | MB_ICONINFORMATION);

	  // set focus
	  CEdit* pEdit = (CEdit*)GetDlgItem(IDC_DATABASE);
	  ASSERT_VALID(pEdit);
	  pEdit->SetFocus();
	
      // Prevent the page from turning
      return -1;
   }

   if (sReportPath.GetLength() == 0)
   {
	   AfxMessageBox("You must enter a report path.",
		 MB_OK | MB_ICONINFORMATION);

	   // set focus
	   CEdit* pEdit = (CEdit*)GetDlgItem(IDC_REPORTPATH);
	   ASSERT_VALID(pEdit);
	   pEdit->SetFocus();

	   // Prevent the page from turning
	   return -1;
   }

	// Get the parent window
   CWizard* pWiz = (CWizard*) GetParent();
   ASSERT_VALID(pWiz);

   // Update the wizard data
   pWiz->m_rgi.sServerName		= sServer;
   pWiz->m_rgi.sDatabaseName	= sDatabase;
   pWiz->m_rgi.sReportPath		= sReportPath;
      
   // set wizard buttons
   pWiz->SetWizardButtons(PSWIZB_FINISH | PSWIZB_BACK);

   // Call the inherited method
	return CPropertyPage::OnWizardNext();
}

CPageTwo::~CPageTwo()
{
}


