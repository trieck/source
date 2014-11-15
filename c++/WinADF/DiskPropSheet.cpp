// DiskPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "DiskPropSheet.h"
#include "DiskPropPage.h"
#include "VolPropPage.h"

static PageDef pagedefs[] = {
    { RUNTIME_CLASS(DiskPropPage), IDD_DISK_PROPPAGE },
    { RUNTIME_CLASS(VolPropPage), IDD_VOL_PROPPAGE }
};

// DiskPropSheet

IMPLEMENT_DYNAMIC(DiskPropSheet, CPropertySheet)

DiskPropSheet::DiskPropSheet(CWnd* pParentWnd)
    : CPropertySheet(_T("Disk Image Information"), pParentWnd, 0), m_pPages(0), m_nPages(0)
{
}

DiskPropSheet::~DiskPropSheet()
{
    for (uint32_t i = 0; i < m_nPages; i++) {
        CPropertyPage *pPage = m_pPages[i];
        delete pPage;
    }

    if (m_pPages != NULL)
        delete m_pPages;
}

void DiskPropSheet::BuildPropPageArray()
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


BEGIN_MESSAGE_MAP(DiskPropSheet, CPropertySheet)
END_MESSAGE_MAP()


// DiskPropSheet message handlers

BOOL DiskPropSheet::OnInitDialog()
{
    BOOL bResult = CPropertySheet::OnInitDialog();

    GetDlgItem(IDCANCEL)->ModifyStyle(WS_VISIBLE, 0);

    return bResult;
}
