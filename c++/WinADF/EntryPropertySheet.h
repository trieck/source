#pragma once

#include "entry.h"

// EntryPropertySheet

class EntryPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(EntryPropertySheet)

public:
	EntryPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	EntryPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~EntryPropertySheet();

	void SetEntry(Entry *pEntry);
	Entry *GetEntry() const;
protected:
	DECLARE_MESSAGE_MAP()
protected:
	CPropertyPage **m_pPages;
	uint32_t m_nPages;
	Entry *m_pEntry;

	virtual void BuildPropPageArray();
};

inline Entry *EntryPropertySheet::GetEntry() const {
	return m_pEntry;
}
