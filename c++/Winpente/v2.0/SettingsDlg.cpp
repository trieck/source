// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg

IMPLEMENT_DYNAMIC(CSettingsDlg, CPropertySheet)

CSettingsDlg::CSettingsDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	: CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pMiscPage = NULL;
}

CSettingsDlg::CSettingsDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	: CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pMiscPage = NULL;
}

CSettingsDlg::~CSettingsDlg()
{
	if (m_pMiscPage) delete m_pMiscPage;
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CSettingsDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg message handlers

VOID CSettingsDlg::BuildPages()
{
	ASSERT(m_pMiscPage == NULL);

	m_pMiscPage = new CMiscPage;
	ASSERT_VALID(m_pMiscPage);

	m_pMiscPage->Construct(IDD_MISCPAGE, 0);

	// Add the property pages
	AddPage(m_pMiscPage);
}

VOID CSettingsDlg::Init()
{
	BuildPages();
}
