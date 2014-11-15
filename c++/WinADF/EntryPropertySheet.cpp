// EntryPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "EntryPropertySheet.h"
#include "EntryPropertyPage.h"

static PageDef pagedefs[] = {
    { RUNTIME_CLASS(EntryPropertyPage), IDD_ENTRY_PROPPAGE }
};

// EntryPropertySheet

IMPLEMENT_DYNAMIC(EntryPropertySheet, CPropertySheet)

EntryPropertySheet::EntryPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
    : CPropertySheet(nIDCaption, pParentWnd, iSelectPage),
      m_pPages(0), m_nPages(0), m_pEntry(0)
{
}

EntryPropertySheet::EntryPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheet(pszCaption, pParentWnd, iSelectPage),
     m_pPages(0), m_nPages(0), m_pEntry(0)
{

}

EntryPropertySheet::~EntryPropertySheet()
{
    for (uint32_t i = 0; i < m_nPages; i++) {
        CPropertyPage *pPage = m_pPages[i];
        delete pPage;
    }

    if (m_pPages != NULL)
        delete m_pPages;
}


BEGIN_MESSAGE_MAP(EntryPropertySheet, CPropertySheet)
END_MESSAGE_MAP()

void EntryPropertySheet::BuildPropPageArray()
{
    m_nPages = sizeof(pagedefs) / sizeof(PageDef);

    m_pPages = new CPropertyPage*[m_nPages];

    for (uint32_t i = 0; i < m_nPages; i++) {
        m_pPages[i] = (CPropertyPage*)pagedefs[i].Class->CreateObject();
        ASSERT_VALID(m_pPages[i]);
        m_pPages[i]->Construct(pagedefs[i].id, 0);
        AddPage(m_pPages[i]);
    }

    CPropertySheet::BuildPropPageArray();
}

void EntryPropertySheet::SetEntry(Entry *pEntry)
{
    m_pEntry = pEntry;
}
