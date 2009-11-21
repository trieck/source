// SettingsSheet.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "SettingsSheet.h"


// SettingsSheet

IMPLEMENT_DYNAMIC(SettingsSheet, CPropertySheet)

SettingsSheet::SettingsSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
		:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pColorsPage = NULL;
}

SettingsSheet::SettingsSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
		:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

SettingsSheet::~SettingsSheet()
{
	delete m_pOptionsPage;
	delete m_pColorsPage;
}

BEGIN_MESSAGE_MAP(SettingsSheet, CPropertySheet)
END_MESSAGE_MAP()


// SettingsSheet message handlers

void SettingsSheet::BuildPropPageArray()
{
	m_pOptionsPage = new OptionsPage;
	m_pOptionsPage->Construct(IDD_OPTIONS_PAGE);
	AddPage(m_pOptionsPage);

	m_pColorsPage = new CColorsPage;
	m_pColorsPage->Construct(IDD_COLORS_PAGE);
	AddPage(m_pColorsPage);

	CPropertySheet::BuildPropPageArray();
}
