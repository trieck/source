// SettingsSheet.cpp : implementation file
//

#include "stdafx.h"
#include "torrentexplorer.h"
#include "SettingsSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingsSheet

IMPLEMENT_DYNAMIC(SettingsSheet, CPropertySheet)

SettingsSheet::SettingsSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pGeneralPage = NULL;
	m_pColorsPage = NULL;
}

SettingsSheet::SettingsSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pGeneralPage = NULL;
	m_pColorsPage = NULL;
}

SettingsSheet::~SettingsSheet()
{
	delete m_pGeneralPage;
	delete m_pColorsPage;
}

BEGIN_MESSAGE_MAP(SettingsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(SettingsSheet)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingsSheet message handlers

void SettingsSheet::BuildPropPageArray()
{
	m_pGeneralPage = new GeneralPage;
	m_pGeneralPage->Construct(IDD_GENERAL_PAGE);
	AddPage(m_pGeneralPage);

	m_pColorsPage = new ColorsPage;
	m_pColorsPage->Construct(IDD_COLORS_PAGE);
	AddPage(m_pColorsPage);

	CPropertySheet::BuildPropPageArray();
}