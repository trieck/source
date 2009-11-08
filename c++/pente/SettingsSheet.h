#pragma once

#include "OptionsPage.h"
#include "ColorsPage.h"

// SettingsSheet

class SettingsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(SettingsSheet)

public:
	SettingsSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	SettingsSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~SettingsSheet();

protected:
	virtual void BuildPropPageArray();

	DECLARE_MESSAGE_MAP()
	OptionsPage *m_pOptionsPage;
	CColorsPage *m_pColorsPage;
};


