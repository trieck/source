// VolPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "VolPropPage.h"
#include "WinADFDoc.h"

// VolPropPage dialog
#define COLOR_BAR RGB(0x40, 0xE0, 0x40)

IMPLEMENT_DYNCREATE(VolPropPage, CPropertyPage)

#ifdef _DEBUG
void VolPropPage::AssertValid() const
{
	CPropertyPage::AssertValid();
}

void VolPropPage::Dump(CDumpContext& dc) const
{
	CPropertyPage::Dump(dc);
}
#endif // _DEBUG


VolPropPage::VolPropPage()
	: CPropertyPage(VolPropPage::IDD)
{

}

VolPropPage::~VolPropPage()
{
}

void VolPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FULL, m_FullProgress);
}


BEGIN_MESSAGE_MAP(VolPropPage, CPropertyPage)
END_MESSAGE_MAP()


// VolPropPage message handlers

BOOL VolPropPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	WinADFDoc *pDoc = (WinADFDoc*)MDIGetActiveDoc();
	ASSERT_VALID(pDoc);
	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(WinADFDoc)));

	Volume *pVol = pDoc->GetVolume();
	GetDlgItem(IDC_VOLNAME)->SetWindowText(pVol->getName().c_str());

	int8_t type = pVol->getType();

	CButton *pButton = (CButton*)GetDlgItem(IDC_FFS);
	pButton->SetCheck(isFFS(type));

	pButton = (CButton*)GetDlgItem(IDC_INTL);
	pButton->SetCheck(isINTL(type));

	pButton = (CButton*)GetDlgItem(IDC_DIRCACHE);
	pButton->SetCheck(isDIRCACHE(type));

	uint32_t totalblocks = (pVol->getLastBlock()+1) - pVol->getFirstBlock();
	uint32_t totalcap = totalblocks * BSIZE;

	CString fmt;
	fmt.Format("%s KB", comma(totalcap / 1024).c_str());
	GetDlgItem(IDC_VOL_TOTAL)->SetWindowText(fmt);

	uint32_t freeblocks = pVol->freeblocks();
	uint32_t freecap = freeblocks * BSIZE;

	fmt.Format("%s KB", comma(freecap / 1024).c_str());
	GetDlgItem(IDC_VOL_FREE)->SetWindowText(fmt);

	uint32_t full =  totalblocks - freeblocks;

	m_FullProgress.SetRange32(0, totalblocks);
	m_FullProgress.SetPos(full);
	m_FullProgress.SendMessage(PBM_SETBARCOLOR, 0, COLOR_BAR);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
